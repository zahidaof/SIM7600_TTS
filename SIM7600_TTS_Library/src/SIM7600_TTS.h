/*
=================================================================
 Author: Zahid Alfahmi, Jeddah, Saudi Arabia
 Date: April 25, 2025
=================================================================
*/
#ifndef SIM7600_TTS_H
#define SIM7600_TTS_H

#include <Arduino.h>

class SIM7600_TTS {
public:
    SIM7600_TTS(int txPin, int rxPin, int powerKeyPin, long baudRate);
    void begin();
    bool makeCall(const char* number);
    void playTTSMessage(const char* message);
    void setTTSPlayPath(int mode); // Add this if needed
    void setTTSParameters(int volume, int sysVolume, int digitMode, int pitch, int speed);
    
private:
    int _txPin;
    int _rxPin;
    int _powerKeyPin;
    long _baudRate;
    bool waitForResponse(unsigned long timeout);
};

#endif // SIM7600_TTS_H

