/*
=================================================================
 Author: Zahid Alfahmi, Jeddah, Saudi Arabia
 Date: April 25, 2025
=================================================================
*/
#include "SIM7600_TTS.h"

SIM7600_TTS::SIM7600_TTS(int txPin, int rxPin, int powerKeyPin, long baudRate)
  : _txPin(txPin), _rxPin(rxPin), _powerKeyPin(powerKeyPin), _baudRate(baudRate) {
}

void SIM7600_TTS::begin() {
  pinMode(_powerKeyPin, OUTPUT);
  digitalWrite(_powerKeyPin, LOW);
  delay(1000);
  digitalWrite(_powerKeyPin, HIGH);
  delay(5000);
  
  Serial1.begin(_baudRate, SERIAL_8N1, _rxPin, _txPin);
  delay(3000);
  
  Serial1.println("AT");
  waitForResponse(5000);
}

bool SIM7600_TTS::makeCall(const char* number) {
  Serial1.print("ATD");
  Serial1.print(number);
  Serial1.println(";");
  return waitForResponse(10000);
}

void SIM7600_TTS::playTTSMessage(const char* message) {
  Serial1.print("AT+CTTS=2,\"");
  Serial1.print(message);
  Serial1.println("\"");
  waitForResponse(10000);
}

bool SIM7600_TTS::waitForResponse(unsigned long timeout) {
  unsigned long start = millis();
  while (millis() - start < timeout) {
    if (Serial1.available()) {
      String response = Serial1.readString();
      if (response.indexOf("OK") != -1 || response.indexOf("+CTTS: 0") != -1) {
        return true;
      }
    }
  }
  return false;
}