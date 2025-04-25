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
        SIM7600_TTS(int txPin, int rxPin, int powerKeyPin, long baudRate, Stream& debugSerial);
        void begin();
        bool makeCall(const char* number);
        void playTTSMessage(const char* message);
        void setTTSParameters(int volume, int sysVolume, int digitMode, int pitch, int speed);
        void setTTSPlayPath(int mode);
        bool waitForResponse(unsigned long timeout);
    
    private:
        int _txPin, _rxPin, _powerKeyPin;
        long _baudRate;
        Stream* _debugSerial;  
    };

#endif // SIM7600_TTS_H

