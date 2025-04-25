/*
=================================================================
 Author: Zahid Alfahmi, Jeddah, Saudi Arabia
 Date: April 25, 2025
=================================================================
*/
#include "SIM7600_TTS.h"

SIM7600_TTS::SIM7600_TTS(int txPin, int rxPin, int powerKeyPin, long baudRate, Stream& debugSerial)
  : _txPin(txPin), _rxPin(rxPin), _powerKeyPin(powerKeyPin), _baudRate(baudRate), _debugSerial(&debugSerial) {
}

void SIM7600_TTS::begin() {
  pinMode(_powerKeyPin, OUTPUT);
  digitalWrite(_powerKeyPin, LOW);
  delay(1000);
  digitalWrite(_powerKeyPin, HIGH);
  delay(5000);
  
  Serial1.begin(_baudRate, SERIAL_8N1, _rxPin, _txPin);
  delay(3000);

  _debugSerial->println("Setting fixed baud rate...");
  Serial1.println("AT+IPR=115200");
  if (waitForResponse(5000)) {
    _debugSerial->println("Baud rate set successfully.");
  } else {
    _debugSerial->println("Failed to set baud rate.");
  }

  _debugSerial->println("Testing modem communication...");
  Serial1.println("AT");
  if (waitForResponse(5000)) {
    _debugSerial->println("Modem communication successful.");
  } else {
    _debugSerial->println("Failed to communicate with modem.");
  }

  _debugSerial->println("Getting modem information...");
  Serial1.println("ATI");
  if (waitForResponse(5000)) {
    _debugSerial->println("Modem information retrieved successfully.");
  } else {
    _debugSerial->println("Failed to retrieve modem information.");
  }
}

bool SIM7600_TTS::makeCall(const char* number) {
  _debugSerial->println("Dialing number: " + String(number));
  Serial1.print("ATD");
  Serial1.print(number);
  Serial1.println(";");
  if (waitForResponse(10000)) {
    _debugSerial->println("Call initiated successfully.");
    return true;
  } else {
    _debugSerial->println("Failed to initiate call.");
    return false;
  }
}

void SIM7600_TTS::playTTSMessage(const char* message) {
  _debugSerial->println("Playing TTS message: " + String(message));
  Serial1.print("AT+CTTS=2,\"");
  Serial1.print(message);
  Serial1.println("\"");
  if (waitForResponse(10000)) {
    _debugSerial->println("TTS message played successfully.");
  } else {
    _debugSerial->println("Failed to play TTS message.");
  }
}

bool SIM7600_TTS::waitForResponse(unsigned long timeout) {
  unsigned long start = millis();
  while (millis() - start < timeout) {
    if (Serial1.available()) {
      String response = Serial1.readString();
      _debugSerial->println("Modem Response: " + response);  // Print the modem's response
      if (response.indexOf("OK") != -1 || response.indexOf("+CTTS: 0") != -1) {
        return true;
      }
    }
  }
  _debugSerial->println("No valid response received within timeout.");
  return false;
}

void SIM7600_TTS::setTTSParameters(int volume, int sysVolume, int digitMode, int pitch, int speed) {
  _debugSerial->println("Setting TTS parameters...");
  Serial1.print("AT+CTTSPARAM=");
  Serial1.print(volume);
  Serial1.print(",");
  Serial1.print(sysVolume);
  Serial1.print(",");
  Serial1.print(digitMode);
  Serial1.print(",");
  Serial1.print(pitch);
  Serial1.print(",");
  Serial1.println(speed);

  if (waitForResponse(5000)) {
    _debugSerial->println("TTS parameters set successfully.");
  } else {
    _debugSerial->println("Failed to set TTS parameters.");
  }
}

void SIM7600_TTS::setTTSPlayPath(int mode) {
  _debugSerial->println("Setting TTS play path...");
  Serial1.print("AT+CDTAM=");
  Serial1.println(mode);

  if (waitForResponse(5000)) {
    _debugSerial->println("TTS play path set successfully.");
  } else {
    _debugSerial->println("Failed to set TTS play path.");
  }
}