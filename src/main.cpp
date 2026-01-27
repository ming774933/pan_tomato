#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include <RTClib.h>
#include <WiFi.h>
#include <Preferences.h>

#include "ui/ui.h"

// --- 使用者設定 ---
const char* ssid     = "TP-LINK_E1C0";
const char* password = "88888888";

// --- 硬體腳位設定 ---
#define TFT_BLK     27
#define BUZZER_PIN  25
#define BTN_PREV    13
#define BTN_NEXT    12
#define BTN_ENTER   14

// --- PWM 設定 ---
#define PWM_CH_BLK      0
#define PWM_CH_BUZZ     1
#define PWM_FREQ        5000
#define PWM_RES         8

// --- 物件宣告 ---
TFT_eSPI tft = TFT_eSPI();
RTC_DS3231 rtc;
Preferences prefs;

// --- LVGL 緩衝區 ---
static const uint16_t screenWidth  = 160;
static const uint16_t screenHeight = 128;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 40 ];
lv_group_t * g_btn_group;

// --- 變數宣告 ---
lv_obj_t * current_focused_panel = NULL;

bool isTimerRunning = false;
bool isTimerPaused = false;
long totalSeconds = 300;
long remainingSeconds = 300;
unsigned long lastTimerTick = 0;
long initialTotalSeconds = 0;

bool isStopwatchRunning = false;
long stopwatchSeconds = 0;
unsigned long lastStopwatchTick = 0;

int screenBrightness = 200;
int systemVolume = 150;
unsigned long lastClockUpdate = 0;

unsigned long buzzerStartTime = 0;
bool isBuzzerActive = false;
int buzzerDuration = 0;

// WiFi 管理變數
bool wifiSyncAttempted = false;
unsigned long wifiStartTime = 0;

// --- 函式宣告 ---
void my_keypad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data);
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void update_clock();
void update_timer_ui();
void update_stopwatch_ui();
void trigger_buzzer(int durationMs);
long parse_dropdown_time(const char* str);

void check_and_update_focus();
void apply_group_focus(lv_obj_t * panel);
void ui_event_auto_next(lv_event_t * e);

void confirm_settings_logic(lv_event_t * e);
void confirm_time_set_logic(lv_event_t * e);
void stop_timer_logic(lv_event_t * e);
void reset_and_run_logic(lv_event_t * e);
void exit_timer_logic(lv_event_t * e);
void rest_timer_logic(lv_event_t * e);

void toggle_stopwatch_logic(lv_event_t * e);
void reset_stopwatch_logic(lv_event_t * e);
void exit_stopwatch_logic(lv_event_t * e);

void slider_brightness_event(lv_event_t * e);
void slider_volume_event(lv_event_t * e);
void run_splash_bar_animation();
void play_button_sound();

// 歷史紀錄相關
void save_daily_data(int focusAddSec, int restAddSec);
void load_history_to_ui(int year, int month, int day);
void load_history_from_dropdown(lv_event_t * e);
void handle_wifi_sync_in_loop();

// ----------------------------------------------------------------
// Setup
// ----------------------------------------------------------------
void setup() {
    Serial.begin(115200);

    pinMode(BTN_PREV, INPUT_PULLUP);
    pinMode(BTN_NEXT, INPUT_PULLUP);
    pinMode(BTN_ENTER, INPUT_PULLUP);

    ledcSetup(PWM_CH_BLK, PWM_FREQ, PWM_RES);
    ledcAttachPin(TFT_BLK, PWM_CH_BLK);
    ledcWrite(PWM_CH_BLK, screenBrightness);

    ledcSetup(PWM_CH_BUZZ, 2000, PWM_RES);
    ledcAttachPin(BUZZER_PIN, PWM_CH_BUZZ);
    ledcWrite(PWM_CH_BUZZ, 0);

    if (!rtc.begin()) { Serial.println("Couldn't find RTC"); }
    
    // 確保有初始時間 (若 RTC 掉電)
    if (rtc.lostPower()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 40);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = my_keypad_read;
    lv_indev_t * my_indev = lv_indev_drv_register(&indev_drv);

    g_btn_group = lv_group_create();
    lv_group_set_default(g_btn_group);
    lv_indev_set_group(my_indev, g_btn_group);
    lv_group_set_wrap(g_btn_group, true);

    ui_init();

    // 解決開機顯示問題
    if(ui_time_set_Panel) lv_obj_add_flag(ui_time_set_Panel, LV_OBJ_FLAG_HIDDEN);
    if(ui_Main_Panel) lv_obj_clear_flag(ui_Main_Panel, LV_OBJ_FLAG_HIDDEN);

    if(ui_SplashScreen) {
        lv_obj_set_style_radius(ui_SplashScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui_SplashScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_SplashScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_SplashScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    run_splash_bar_animation();

    // 先啟動 WiFi 連線，但不等待
    WiFi.begin(ssid, password);
    wifiStartTime = millis();
    wifiSyncAttempted = false;

    // 初始化 Arc2
    if(ui_Arc2) {
        lv_arc_set_range(ui_Arc2, 0, 100);
    }
    
    // 載入今天數據
    DateTime now = rtc.now();
    load_history_to_ui(now.year(), now.month(), now.day());

    // ------------------------------------------------------------
    // 事件綁定
    // ------------------------------------------------------------
    if(ui_hour_Dropdown) lv_obj_add_event_cb(ui_hour_Dropdown, ui_event_auto_next, LV_EVENT_VALUE_CHANGED, NULL);
    if(ui_min_Dropdown)  lv_obj_add_event_cb(ui_min_Dropdown, ui_event_auto_next, LV_EVENT_VALUE_CHANGED, NULL);
    if(ui_Button6) lv_obj_add_event_cb(ui_Button6, confirm_time_set_logic, LV_EVENT_CLICKED, NULL);

    // History Panel 綁定
    if(ui_Dropdown_year) lv_obj_add_event_cb(ui_Dropdown_year, ui_event_auto_next, LV_EVENT_VALUE_CHANGED, NULL);
    if(ui_Dropdown_moth) lv_obj_add_event_cb(ui_Dropdown_moth, ui_event_auto_next, LV_EVENT_VALUE_CHANGED, NULL);
    if(ui_Dropdown_day)  lv_obj_add_event_cb(ui_Dropdown_day, ui_event_auto_next, LV_EVENT_VALUE_CHANGED, NULL);
    
    // 綁定查詢按鈕
    if(ui_Button13) lv_obj_add_event_cb(ui_Button13, load_history_from_dropdown, LV_EVENT_CLICKED, NULL);

    if(ui_Dropdown3) lv_obj_add_event_cb(ui_Dropdown3, ui_event_auto_next, LV_EVENT_VALUE_CHANGED, NULL);
    if(ui_Button19) lv_obj_add_event_cb(ui_Button19, confirm_settings_logic, LV_EVENT_CLICKED, NULL);

    if(ui_stop_buttom) lv_obj_add_event_cb(ui_stop_buttom, stop_timer_logic, LV_EVENT_CLICKED, NULL);
    if(ui_back_Button) lv_obj_add_event_cb(ui_back_Button, reset_and_run_logic, LV_EVENT_CLICKED, NULL);
    if(ui_out_Button)  lv_obj_add_event_cb(ui_out_Button, exit_timer_logic, LV_EVENT_CLICKED, NULL);

    if(ui_stop_buttom1) lv_obj_add_event_cb(ui_stop_buttom1, stop_timer_logic, LV_EVENT_CLICKED, NULL);
    if(ui_back_Button1) lv_obj_add_event_cb(ui_back_Button1, reset_and_run_logic, LV_EVENT_CLICKED, NULL);
    if(ui_out_Button1)  lv_obj_add_event_cb(ui_out_Button1, exit_timer_logic, LV_EVENT_CLICKED, NULL);

    if(ui_Button16) lv_obj_add_event_cb(ui_Button16, rest_timer_logic, LV_EVENT_CLICKED, NULL); 
    if(ui_Button17) lv_obj_add_event_cb(ui_Button17, exit_timer_logic, LV_EVENT_CLICKED, NULL);

    if(ui_stop_buttom2) lv_obj_add_event_cb(ui_stop_buttom2, toggle_stopwatch_logic, LV_EVENT_CLICKED, NULL); 
    if(ui_back_Button2) lv_obj_add_event_cb(ui_back_Button2, reset_stopwatch_logic, LV_EVENT_CLICKED, NULL);  
    if(ui_out_Button2)  lv_obj_add_event_cb(ui_out_Button2, exit_stopwatch_logic, LV_EVENT_CLICKED, NULL);    

    if(ui_Slider1) {
        lv_obj_add_event_cb(ui_Slider1, slider_brightness_event, LV_EVENT_VALUE_CHANGED, NULL);
        lv_slider_set_range(ui_Slider1, 0, 10); 
        int initVal = map(screenBrightness, 10, 255, 0, 10); 
        lv_slider_set_value(ui_Slider1, initVal, LV_ANIM_OFF);
        if(ui_Label14) lv_label_set_text_fmt(ui_Label14, "%d", initVal);
    }
    if(ui_Slider2) {
        lv_obj_add_event_cb(ui_Slider2, slider_volume_event, LV_EVENT_VALUE_CHANGED, NULL);
        lv_slider_set_range(ui_Slider2, 0, 10);
        int initVal = map(systemVolume, 0, 255, 0, 10); 
        lv_slider_set_value(ui_Slider2, initVal, LV_ANIM_OFF);
        if(ui_Label16) lv_label_set_text_fmt(ui_Label16, "%d", initVal);
    }
    
    update_clock();
}

// ----------------------------------------------------------------
// Loop
// ----------------------------------------------------------------
void handle_wifi_sync_in_loop() {
    if (wifiSyncAttempted) return;

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi Connected! Syncing NTP...");
        configTime(28800, 0, "pool.ntp.org", "time.nist.gov"); // UTC+8
        
        struct tm timeinfo;
        if (getLocalTime(&timeinfo, 100)) { 
            rtc.adjust(DateTime(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, 
                                timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec));
            Serial.println("RTC Updated via WiFi");
            
            wifiSyncAttempted = true;
            WiFi.disconnect(true);
            WiFi.mode(WIFI_OFF);
        }
    }
    
    if (millis() - wifiStartTime > 15000) {
        Serial.println("WiFi Timeout. Using DS3231.");
        wifiSyncAttempted = true;
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
    }
}

void save_daily_data(int focusAddSec, int restAddSec) {
    DateTime now = rtc.now();
    char dateKey[12];
    sprintf(dateKey, "%04d%02d%02d", now.year(), now.month(), now.day());
    
    String keyFocus = String("F_") + String(dateKey);
    String keyRest = String("R_") + String(dateKey);

    prefs.begin("history", false);
    
    int currentFocusMin = prefs.getInt(keyFocus.c_str(), 0);
    int currentRestMin = prefs.getInt(keyRest.c_str(), 0);

    // 累積邏輯
    int addFocusMin = focusAddSec / 60; 
    if (focusAddSec > 0 && addFocusMin == 0) addFocusMin = 1; 
    
    int addRestMin = restAddSec / 60;
    if (restAddSec > 0 && addRestMin == 0) addRestMin = 1;

    if (focusAddSec > 0) prefs.putInt(keyFocus.c_str(), currentFocusMin + addFocusMin);
    if (restAddSec > 0) prefs.putInt(keyRest.c_str(), currentRestMin + addRestMin);
    
    prefs.end();

    // 儲存後立即更新介面
    load_history_to_ui(now.year(), now.month(), now.day());
}

void load_history_to_ui(int year, int month, int day) {
    char dateKey[12];
    sprintf(dateKey, "%04d%02d%02d", year, month, day);
    
    String keyFocus = String("F_") + String(dateKey);
    String keyRest = String("R_") + String(dateKey);

    prefs.begin("history", true); 
    int focusMin = prefs.getInt(keyFocus.c_str(), 0);
    int restMin = prefs.getInt(keyRest.c_str(), 0);
    prefs.end();

    float focusHour = focusMin / 60.0;
    float restHour = restMin / 60.0;

    int fh_int = (int)focusHour;
    int fh_dec = (int)((focusHour - fh_int) * 10);
    
    int rh_int = (int)restHour;
    int rh_dec = (int)((restHour - rh_int) * 10);

    if(ui_Label35) lv_label_set_text_fmt(ui_Label35, "%d.%d", fh_int, fh_dec);
    if(ui_Label36) lv_label_set_text_fmt(ui_Label36, "%d.%d", rh_int, rh_dec);

    if(ui_Arc2) {
        int percent = (int)((focusHour / 24.0) * 100);
        if (focusHour > 0 && percent == 0) percent = 1; 
        if (percent > 100) percent = 100;
        lv_arc_set_value(ui_Arc2, percent);
    }
}

void load_history_from_dropdown(lv_event_t * e) {
    if (ui_Dropdown_year && ui_Dropdown_moth && ui_Dropdown_day) {
        int yIdx = lv_dropdown_get_selected(ui_Dropdown_year); 
        int mIdx = lv_dropdown_get_selected(ui_Dropdown_moth); 
        int dIdx = lv_dropdown_get_selected(ui_Dropdown_day);  

        int year = 2026 + yIdx; 
        int month = mIdx + 1;
        int day = dIdx + 1;

        load_history_to_ui(year, month, day);
    }
}

void ui_event_auto_next(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if (code == LV_EVENT_VALUE_CHANGED && lv_obj_check_type(obj, &lv_dropdown_class)) {
        lv_group_focus_next(g_btn_group);
    }
}

void run_splash_bar_animation() {
    if(ui_Bar2) {
        lv_bar_set_value(ui_Bar2, 0, LV_ANIM_OFF);
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, ui_Bar2);
        lv_anim_set_values(&a, 0, 100);
        lv_anim_set_time(&a, 4000); 
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_bar_set_value);
        lv_anim_start(&a);
    }
}

void loop() {
    lv_timer_handler(); 
    
    handle_wifi_sync_in_loop();

    if (isBuzzerActive) {
        if (millis() - buzzerStartTime >= buzzerDuration) {
            ledcWrite(PWM_CH_BUZZ, 0); 
            isBuzzerActive = false;
        }
    }

    static unsigned long lastFocusCheck = 0;
    if (millis() - lastFocusCheck > 100) {
        lastFocusCheck = millis();
        check_and_update_focus();
    }

    if (millis() - lastClockUpdate > 1000) {
        lastClockUpdate = millis();
        update_clock();
    }

    if (isTimerRunning && !isTimerPaused) {
        if (millis() - lastTimerTick >= 1000) {
            lastTimerTick = millis();
            if (remainingSeconds > 0) {
                remainingSeconds--;
                update_timer_ui();
            } else {
                isTimerRunning = false;
                remainingSeconds = 0;
                update_timer_ui(); 
                
                if (!lv_obj_has_flag(ui_timer_Panel, LV_OBJ_FLAG_HIDDEN)) {
                    save_daily_data(initialTotalSeconds, 0);
                }
                else if (!lv_obj_has_flag(ui_timer_Panel1, LV_OBJ_FLAG_HIDDEN)) {
                    save_daily_data(0, initialTotalSeconds);
                }

                if(ui_time_stop_Panel) {
                    lv_obj_clear_flag(ui_time_stop_Panel, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_move_foreground(ui_time_stop_Panel);
                    trigger_buzzer(500);
                }
            }
        }
    }

    if (isStopwatchRunning) {
        if (millis() - lastStopwatchTick >= 1000) {
            lastStopwatchTick = millis();
            stopwatchSeconds++;
            update_stopwatch_ui();
        }
    }
}

void trigger_buzzer(int durationMs) {
    if (systemVolume > 0) {
        ledcWrite(PWM_CH_BUZZ, systemVolume);
        buzzerStartTime = millis();
        buzzerDuration = durationMs;
        isBuzzerActive = true;
    }
}

void play_button_sound() {
    trigger_buzzer(50); 
}

// ----------------------------------------------------------------
// 邏輯功能
// ----------------------------------------------------------------

long parse_dropdown_time(const char* str) {
    String s = String(str);
    long seconds = 0;
    int val = s.toInt();
    if (s.indexOf("min") != -1) seconds = val * 60;
    else if (s.indexOf("hour") != -1) seconds = val * 3600;
    if (seconds == 0) seconds = 60; 
    return seconds;
}

void confirm_settings_logic(lv_event_t * e) {
    char buf[32];
    if(ui_Dropdown3) {
        lv_dropdown_get_selected_str(ui_Dropdown3, buf, sizeof(buf));
        long parsed = parse_dropdown_time(buf);
        totalSeconds = (parsed > 0) ? parsed : 60;
        initialTotalSeconds = totalSeconds;
        remainingSeconds = totalSeconds;
        isTimerRunning = true;
        isTimerPaused = false;
        lastTimerTick = millis();
        update_timer_ui();
    }
}

void confirm_time_set_logic(lv_event_t * e) {
    int hourIndex = lv_dropdown_get_selected(ui_hour_Dropdown);
    int minIndex = lv_dropdown_get_selected(ui_min_Dropdown);

    DateTime now = rtc.now();
    rtc.adjust(DateTime(now.year(), now.month(), now.day(), hourIndex, minIndex, 0));
    update_clock();
}

void stop_timer_logic(lv_event_t * e) {
    if (remainingSeconds > 0) {
        isTimerPaused = !isTimerPaused;
    }
}

void reset_and_run_logic(lv_event_t * e) {
    remainingSeconds = totalSeconds; 
    isTimerRunning = true; 
    isTimerPaused = false;
    lastTimerTick = millis(); 
    update_timer_ui();
}

// -----------------------------------------------------
// [重要修改] 提前退出時儲存時間邏輯
// -----------------------------------------------------
void exit_timer_logic(lv_event_t * e) {
    // 檢查是否有正在進行的倒數，且時間有減少
    if (isTimerRunning && initialTotalSeconds > remainingSeconds) {
        long elapsedSeconds = initialTotalSeconds - remainingSeconds;
        
        // 確保時間合理
        if (elapsedSeconds > 0) {
            // 判斷目前是專注頁面還是休息頁面
            if (ui_timer_Panel && !lv_obj_has_flag(ui_timer_Panel, LV_OBJ_FLAG_HIDDEN)) {
                // 專注模式：記錄 Focus 時間
                save_daily_data(elapsedSeconds, 0);
            }
            else if (ui_timer_Panel1 && !lv_obj_has_flag(ui_timer_Panel1, LV_OBJ_FLAG_HIDDEN)) {
                // 休息模式：記錄 Rest 時間
                save_daily_data(0, elapsedSeconds);
            }
        }
    }

    // 重置計時器狀態
    isTimerRunning = false;
    isTimerPaused = false;
    
    // 隱藏相關面板
    if(ui_timer_Panel) lv_obj_add_flag(ui_timer_Panel, LV_OBJ_FLAG_HIDDEN);
    if(ui_timer_Panel1) lv_obj_add_flag(ui_timer_Panel1, LV_OBJ_FLAG_HIDDEN);
    if(ui_count_Panel) lv_obj_add_flag(ui_count_Panel, LV_OBJ_FLAG_HIDDEN);
    if(ui_time_stop_Panel) lv_obj_add_flag(ui_time_stop_Panel, LV_OBJ_FLAG_HIDDEN);
    
    // 顯示主選單
    if(ui_Menu_Panel) lv_obj_clear_flag(ui_Menu_Panel, LV_OBJ_FLAG_HIDDEN);
}

void rest_timer_logic(lv_event_t * e) {
    if(ui_time_stop_Panel) lv_obj_add_flag(ui_time_stop_Panel, LV_OBJ_FLAG_HIDDEN);
    if(ui_timer_Panel) lv_obj_add_flag(ui_timer_Panel, LV_OBJ_FLAG_HIDDEN);
    if(ui_timer_Panel1) lv_obj_clear_flag(ui_timer_Panel1, LV_OBJ_FLAG_HIDDEN);

    totalSeconds = 5 * 60; 
    initialTotalSeconds = totalSeconds;
    remainingSeconds = totalSeconds;
    isTimerRunning = true;
    isTimerPaused = false;
    lastTimerTick = millis();
    update_timer_ui();
}

void update_timer_ui() {
    int m = remainingSeconds / 60;
    int s = remainingSeconds % 60;
    
    if (ui_Label5 && !lv_obj_has_flag(ui_timer_Panel, LV_OBJ_FLAG_HIDDEN)) {
        lv_label_set_text_fmt(ui_Label5, "%02d:%02d", m, s);
        if (ui_Arc1 && totalSeconds > 0) {
             int percent = (remainingSeconds * 100) / totalSeconds;
             lv_arc_set_value(ui_Arc1, percent);
        }
    }
    
    if (ui_Label25 && !lv_obj_has_flag(ui_timer_Panel1, LV_OBJ_FLAG_HIDDEN)) {
        lv_label_set_text_fmt(ui_Label25, "%02d:%02d", m, s);
        if (ui_Arc3 && totalSeconds > 0) {
             int percent = (remainingSeconds * 100) / totalSeconds;
             lv_arc_set_value(ui_Arc3, percent);
        }
    }
}

void toggle_stopwatch_logic(lv_event_t * e) {
    isStopwatchRunning = !isStopwatchRunning;
    if (isStopwatchRunning) lastStopwatchTick = millis();
}

void reset_stopwatch_logic(lv_event_t * e) {
    isStopwatchRunning = false;
    stopwatchSeconds = 0;
    update_stopwatch_ui();
}

void exit_stopwatch_logic(lv_event_t * e) {
    isStopwatchRunning = false;
    if(ui_count_Panel) lv_obj_add_flag(ui_count_Panel, LV_OBJ_FLAG_HIDDEN);
    if(ui_Menu_Panel) lv_obj_clear_flag(ui_Menu_Panel, LV_OBJ_FLAG_HIDDEN);
}

void update_stopwatch_ui() {
    int h = (int)(stopwatchSeconds / 3600);
    int m = (int)((stopwatchSeconds % 3600) / 60);
    int s = (int)(stopwatchSeconds % 60);
    if (ui_Label10) {
        lv_label_set_text_fmt(ui_Label10, "%02d:%02d:%02d", h, m, s);
    }
}

void update_clock() {
    DateTime now = rtc.now();
    if (ui_timeLabel) lv_label_set_text_fmt(ui_timeLabel, "%02d:%02d", now.hour(), now.minute());
    if (ui_date_Label) lv_label_set_text_fmt(ui_date_Label, "%04d/%02d/%02d", now.year(), now.month(), now.day());
}

void slider_brightness_event(lv_event_t * e) {
    lv_obj_t * slider = lv_event_get_target(e);
    int val = (int)lv_slider_get_value(slider); 
    screenBrightness = map(val, 0, 10, 10, 255);
    ledcWrite(PWM_CH_BLK, screenBrightness);
    if(ui_Label14) lv_label_set_text_fmt(ui_Label14, "%d", val);
}

void slider_volume_event(lv_event_t * e) {
    lv_obj_t * slider = lv_event_get_target(e);
    int val = (int)lv_slider_get_value(slider);
    systemVolume = map(val, 0, 10, 0, 255);
    if(ui_Label16) lv_label_set_text_fmt(ui_Label16, "%d", val);
    play_button_sound(); 
}

void my_keypad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data) {
    data->state = LV_INDEV_STATE_RELEASED;
    static bool prev_btn_state = false;
    static bool next_btn_state = false;
    static bool enter_btn_state = false;
    bool current_prev = (digitalRead(BTN_PREV) == LOW);
    bool current_next = (digitalRead(BTN_NEXT) == LOW);
    bool current_enter = (digitalRead(BTN_ENTER) == LOW);

    lv_obj_t* focused = lv_group_get_focused(g_btn_group);
    bool is_editing = lv_group_get_editing(g_btn_group);
    
    bool is_slider = (focused && lv_obj_check_type(focused, &lv_slider_class));
    bool is_dropdown = (focused && lv_obj_check_type(focused, &lv_dropdown_class));

    if (current_enter) {
        data->key = LV_KEY_ENTER; 
        data->state = LV_INDEV_STATE_PRESSED;
        if (!enter_btn_state) play_button_sound(); 
        
        if (!enter_btn_state) { 
             if (is_slider || is_dropdown) {
                 lv_group_set_editing(g_btn_group, !is_editing);
             }
        }
    }
    else if (current_prev) {
        if (is_editing) {
            if(is_dropdown) data->key = LV_KEY_UP;   
            else data->key = LV_KEY_LEFT;            
        }
        else {
            data->key = LV_KEY_PREV;                 
        }
        data->state = LV_INDEV_STATE_PRESSED;
        if (!prev_btn_state) play_button_sound(); 
    }
    else if (current_next) {
        if (is_editing) {
             if(is_dropdown) data->key = LV_KEY_DOWN; 
             else data->key = LV_KEY_RIGHT;           
        } 
        else {
             data->key = LV_KEY_NEXT;                 
        }
        data->state = LV_INDEV_STATE_PRESSED;
        if (!next_btn_state) play_button_sound(); 
    } 
    
    prev_btn_state = current_prev;
    next_btn_state = current_next;
    enter_btn_state = current_enter;
}

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, false);
    tft.endWrite();
    lv_disp_flush_ready(disp);
}

void check_and_update_focus() {
    lv_obj_t * target = NULL;

    if (ui_time_stop_Panel && !lv_obj_has_flag(ui_time_stop_Panel, LV_OBJ_FLAG_HIDDEN)) target = ui_time_stop_Panel;
    else if (ui_countdown_set_Panel && !lv_obj_has_flag(ui_countdown_set_Panel, LV_OBJ_FLAG_HIDDEN)) target = ui_countdown_set_Panel;
    else if (ui_timer_Panel && !lv_obj_has_flag(ui_timer_Panel, LV_OBJ_FLAG_HIDDEN)) target = ui_timer_Panel;
    else if (ui_timer_Panel1 && !lv_obj_has_flag(ui_timer_Panel1, LV_OBJ_FLAG_HIDDEN)) target = ui_timer_Panel1;
    else if (ui_count_Panel && !lv_obj_has_flag(ui_count_Panel, LV_OBJ_FLAG_HIDDEN)) target = ui_count_Panel;
    else if (ui_set_time_mode_Panel && !lv_obj_has_flag(ui_set_time_mode_Panel, LV_OBJ_FLAG_HIDDEN)) target = ui_set_time_mode_Panel;
    else if (ui_light_set_Panel && !lv_obj_has_flag(ui_light_set_Panel, LV_OBJ_FLAG_HIDDEN)) target = ui_light_set_Panel;
    else if (ui_sound_set_Panel && !lv_obj_has_flag(ui_sound_set_Panel, LV_OBJ_FLAG_HIDDEN)) target = ui_sound_set_Panel;
    else if (ui_time_set_Panel && !lv_obj_has_flag(ui_time_set_Panel, LV_OBJ_FLAG_HIDDEN)) target = ui_time_set_Panel;
    else if (ui_History_Panel && !lv_obj_has_flag(ui_History_Panel, LV_OBJ_FLAG_HIDDEN)) target = ui_History_Panel;
    else if (ui_system_Panel && !lv_obj_has_flag(ui_system_Panel, LV_OBJ_FLAG_HIDDEN)) target = ui_system_Panel;
    else if (ui_setting_Panel && !lv_obj_has_flag(ui_setting_Panel, LV_OBJ_FLAG_HIDDEN)) target = ui_setting_Panel;
    else if (ui_Menu_Panel && !lv_obj_has_flag(ui_Menu_Panel, LV_OBJ_FLAG_HIDDEN)) target = ui_Menu_Panel;
    else if (ui_Main_Panel && !lv_obj_has_flag(ui_Main_Panel, LV_OBJ_FLAG_HIDDEN)) target = ui_Main_Panel;

    if (target != NULL && target != current_focused_panel) {
        current_focused_panel = target;
        apply_group_focus(target);
    }
}

void apply_group_focus(lv_obj_t * panel) {
    lv_group_remove_all_objs(g_btn_group); 
    lv_group_set_editing(g_btn_group, false); 
    
    if (panel == ui_time_stop_Panel) {
        if(ui_Button16) lv_group_add_obj(g_btn_group, ui_Button16);
        if(ui_Button17) lv_group_add_obj(g_btn_group, ui_Button17);
        if(ui_Button16) lv_group_focus_obj(ui_Button16);
    }
    else if (panel == ui_timer_Panel1) {
        if(ui_stop_buttom1) lv_group_add_obj(g_btn_group, ui_stop_buttom1);
        if(ui_back_Button1) lv_group_add_obj(g_btn_group, ui_back_Button1);
        if(ui_out_Button1) lv_group_add_obj(g_btn_group, ui_out_Button1);
        if(ui_stop_buttom1) lv_group_focus_obj(ui_stop_buttom1);
    }
    else if (panel == ui_timer_Panel) {
        if(ui_stop_buttom) lv_group_add_obj(g_btn_group, ui_stop_buttom);
        if(ui_back_Button) lv_group_add_obj(g_btn_group, ui_back_Button);
        if(ui_out_Button) lv_group_add_obj(g_btn_group, ui_out_Button);
        if(ui_stop_buttom) lv_group_focus_obj(ui_stop_buttom);
    }
    else if (panel == ui_time_set_Panel) {
        if(ui_hour_Dropdown) lv_group_add_obj(g_btn_group, ui_hour_Dropdown);
        if(ui_min_Dropdown)  lv_group_add_obj(g_btn_group, ui_min_Dropdown);
        if(ui_Button6)       lv_group_add_obj(g_btn_group, ui_Button6); 
        if(ui_Button11)      lv_group_add_obj(g_btn_group, ui_Button11); 
        if(ui_hour_Dropdown) lv_group_focus_obj(ui_hour_Dropdown);
    }
    else if (panel == ui_History_Panel) {
        if(ui_Dropdown_year) lv_group_add_obj(g_btn_group, ui_Dropdown_year);
        if(ui_Dropdown_moth) lv_group_add_obj(g_btn_group, ui_Dropdown_moth);
        if(ui_Dropdown_day)  lv_group_add_obj(g_btn_group, ui_Dropdown_day);
        if(ui_Button13)      lv_group_add_obj(g_btn_group, ui_Button13);
        if(ui_Button12)      lv_group_add_obj(g_btn_group, ui_Button12); 
        if(ui_Dropdown_year) lv_group_focus_obj(ui_Dropdown_year);
    }
    else if (panel == ui_system_Panel) {
        if(ui_Button7) lv_group_add_obj(g_btn_group, ui_Button7); 
        if(ui_Button7) lv_group_focus_obj(ui_Button7);
    }
    else if (panel == ui_countdown_set_Panel) {
        if(ui_Dropdown3) lv_group_add_obj(g_btn_group, ui_Dropdown3);
        if(ui_Button19) lv_group_add_obj(g_btn_group, ui_Button19);
        if(ui_Dropdown3) lv_group_focus_obj(ui_Dropdown3);
    }
    else if (panel == ui_set_time_mode_Panel) {
        if(ui_Button8) lv_group_add_obj(g_btn_group, ui_Button8);
        if(ui_Button9) lv_group_add_obj(g_btn_group, ui_Button9);
        if(ui_Button10) lv_group_add_obj(g_btn_group, ui_Button10);
        if(ui_Button8) lv_group_focus_obj(ui_Button8);
    }
    else if (panel == ui_Menu_Panel) {
        if(ui_tomato_Button2) lv_group_add_obj(g_btn_group, ui_tomato_Button2);
        if(ui_setting_Button4) lv_group_add_obj(g_btn_group, ui_setting_Button4);
        if(ui_history_Button3) lv_group_add_obj(g_btn_group, ui_history_Button3);
        if(ui_home_Button1) lv_group_add_obj(g_btn_group, ui_home_Button1);
        if(ui_tomato_Button2) lv_group_focus_obj(ui_tomato_Button2);
    }
    else if (panel == ui_count_Panel) { 
        if(ui_stop_buttom2) lv_group_add_obj(g_btn_group, ui_stop_buttom2);
        if(ui_back_Button2) lv_group_add_obj(g_btn_group, ui_back_Button2);
        if(ui_out_Button2) lv_group_add_obj(g_btn_group, ui_out_Button2);
        if(ui_stop_buttom2) lv_group_focus_obj(ui_stop_buttom2);
    }
    else if (panel == ui_light_set_Panel) {
        if(ui_Slider1) lv_group_add_obj(g_btn_group, ui_Slider1);
        if(ui_Button15) lv_group_add_obj(g_btn_group, ui_Button15);
        if(ui_Slider1) {
            lv_group_focus_obj(ui_Slider1);
        }
    }
    else if (panel == ui_sound_set_Panel) {
        if(ui_Slider2) lv_group_add_obj(g_btn_group, ui_Slider2);
        if(ui_Button14) lv_group_add_obj(g_btn_group, ui_Button14);
        if(ui_Slider2) {
            lv_group_focus_obj(ui_Slider2);
        }
    }
    else if (panel == ui_setting_Panel) {
        if(ui_Button2) lv_group_add_obj(g_btn_group, ui_Button2);
        if(ui_Button3) lv_group_add_obj(g_btn_group, ui_Button3);
        if(ui_Button4) lv_group_add_obj(g_btn_group, ui_Button4);
        if(ui_Button5) lv_group_add_obj(g_btn_group, ui_Button5);
        if(ui_Button1) lv_group_add_obj(g_btn_group, ui_Button1);
        if(ui_Button2) lv_group_focus_obj(ui_Button2);
    }
    else if (panel == ui_Main_Panel) {
        if(ui_InButton) lv_group_add_obj(g_btn_group, ui_InButton);
        if(ui_InButton) lv_group_focus_obj(ui_InButton);
    }
}