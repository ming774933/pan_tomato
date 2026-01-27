#include "HardwareMonitor.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 28800; 
const int   daylightOffset_sec = 0;

HardwareMonitor::HardwareMonitor() {
    _lastTick = 0;
    _lastWeatherUpdate = 0;
    _currentTemp = 0;
    _currentHum = 0;
    _weatherMain = "--";
    _currentBat = 100;
}

void HardwareMonitor::begin(const char* ssid, const char* password, const char* apiKey) {
    _ssid = ssid;
    _password = password;
    _apiKey = apiKey;
    WiFi.begin(_ssid, _password);
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

bool HardwareMonitor::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void HardwareMonitor::update() {
    unsigned long currentMillis = millis();
    
    // [使用區域變數防止衝突]
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)) {
        // 尚未同步
    } 

    if (isConnected() && (currentMillis - _lastWeatherUpdate >= 600000 || _lastWeatherUpdate == 0)) {
        _fetchWeather();
        _lastWeatherUpdate = currentMillis;
    }

    if (currentMillis - _lastTick >= 5000) {
        _lastTick = currentMillis;
        _currentBat--; 
        if(_currentBat < 0) _currentBat = 100;
    }
}

void HardwareMonitor::_fetchWeather() {
    if(WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = "http://api.openweathermap.org/data/2.5/weather?q=" + _city + "&appid=" + String(_apiKey) + "&units=metric";
        http.begin(url);
        int httpCode = http.GET();

        if (httpCode > 0) {
            String payload = http.getString();
            DynamicJsonDocument doc(1024);
            DeserializationError error = deserializeJson(doc, payload);

            if (!error) {
                _currentTemp = (int)doc["main"]["temp"];
                _currentHum = (int)doc["main"]["humidity"];
                const char* w = doc["weather"][0]["main"];
                _weatherMain = String(w);
            }
        }
        http.end();
    }
}

String HardwareMonitor::getTimeString() {
    struct tm timeinfo; 
    // [修改] 若無法取得時間，回傳 No find
    if(!getLocalTime(&timeinfo)) return "No find";
    
    char buffer[8];
    sprintf(buffer, "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
    return String(buffer);
}

int HardwareMonitor::getDayOfYear() {
    struct tm timeinfo; 
    if(!getLocalTime(&timeinfo)) return -1; 
    return timeinfo.tm_yday; 
}

int HardwareMonitor::getISODayOfWeek() {
    struct tm timeinfo; 
    if(!getLocalTime(&timeinfo)) return -1;
    if(timeinfo.tm_wday == 0) return 7; 
    return timeinfo.tm_wday;
}

int HardwareMonitor::getWeekOfYear() {
    struct tm timeinfo; 
    if(!getLocalTime(&timeinfo)) return -1;
    char buf[4];
    strftime(buf, sizeof(buf), "%W", &timeinfo);
    return atoi(buf);
}

int HardwareMonitor::getTemperature() { return _currentTemp; }
int HardwareMonitor::getHumidity() { return _currentHum; }
String HardwareMonitor::getWeatherMain() { return _weatherMain; }
int HardwareMonitor::getBatteryLevel() { return _currentBat; }