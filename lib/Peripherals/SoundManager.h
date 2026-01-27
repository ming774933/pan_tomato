#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <Arduino.h>

class SoundManager {
private:
    int _pin;
    int _volume; // 0-100
    int _pwmChannel = 0;

public:
    SoundManager(int pin);
    void begin();
    
    void setVolume(int vol); // [新增]
    int getVolume();

    void playButtonTone();
    void playFinishTone();
    void playBootSound();
    
    void _tone(int freq, int duration);
};

#endif