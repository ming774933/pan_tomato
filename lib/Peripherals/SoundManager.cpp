#include "SoundManager.h"

SoundManager::SoundManager(int pin) {
    _pin = pin;
    _volume = 50; // 預設 50%
}

void SoundManager::begin() {
    ledcSetup(_pwmChannel, 2000, 8); // 8-bit 解析度
    ledcAttachPin(_pin, _pwmChannel);
}

void SoundManager::setVolume(int vol) {
    if(vol < 0) vol = 0;
    if(vol > 100) vol = 100;
    _volume = vol;
}

int SoundManager::getVolume() {
    return _volume;
}

// 支援音量的 Tone 函式
void SoundManager::_tone(int freq, int duration) {
    if (_volume == 0) { delay(duration); return; }

    ledcWriteTone(_pwmChannel, freq);
    
    // 將 0-100 的音量映射到 0-128 (因為方波最大聲是 50% duty cycle = 128)
    int duty = map(_volume, 0, 100, 0, 128); 
    ledcWrite(_pwmChannel, duty); 
    
    delay(duration);
    ledcWrite(_pwmChannel, 0); // 靜音
}

void SoundManager::playButtonTone() {
    _tone(2000, 30);
}

void SoundManager::playFinishTone() {
    _tone(523, 100); delay(50);
    _tone(659, 100); delay(50);
    _tone(784, 100); delay(50);
    _tone(1046, 300);
}

void SoundManager::playBootSound() {
    _tone(740, 60);  delay(40);
    _tone(932, 60);  delay(40);
    _tone(1109, 60); delay(40);
    _tone(1480, 1000);
}