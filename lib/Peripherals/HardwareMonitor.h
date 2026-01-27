#ifndef HARDWARE_MONITOR_H
#define HARDWARE_MONITOR_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "time.h"

class HardwareMonitor {
public:
    HardwareMonitor();
    void begin(const char* ssid, const char* password, const char* apiKey);
    void update();
    
    String getTimeString();
    int getTemperature();
    int getHumidity();
    String getWeatherMain();
    int getBatteryLevel();
    bool isConnected();
    
    int getDayOfYear();
    int getISODayOfWeek();
    int getWeekOfYear();

private:
    const char* _ssid;
    const char* _password;
    const char* _apiKey;
    String _city = "Taichung"; 
    
    unsigned long _lastTick;
    unsigned long _lastWeatherUpdate;
    
    // [已刪除] struct tm timeinfo; 以避免 Race Condition

    int _currentTemp;
    int _currentHum;
    String _weatherMain;
    int _currentBat;
    
    void _fetchWeather();
};

#endif