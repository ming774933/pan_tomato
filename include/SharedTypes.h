#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

enum SystemState {
    STATE_BOOT,
    STATE_MENU,
    
    // 番茄鐘模式
    STATE_TOMATO_SET,
    STATE_TOMATO_RUN,
    STATE_TOMATO_PAUSE,
    STATE_CONFIRM_EXIT,
    
    // 休息模式
    STATE_BREAK_SET,
    STATE_BREAK_RUN,
    
    // 其他功能
    STATE_FEED_DOG,
    STATE_WEATHER,
    STATE_STATS,
    
    // 週統計功能
    STATE_WEEKLY_MENU,
    STATE_WEEKLY_DETAIL,
    
    // 設定選單
    STATE_SETTING_MENU,
    STATE_SET_BRIGHTNESS,
    STATE_SET_VOLUME,
    
    // [修正] 確保這裡上方有逗號，並且新增以下刪除狀態
    STATE_DELETE_MENU,       
    STATE_DELETE_WEEK_SELECT 
};

#endif