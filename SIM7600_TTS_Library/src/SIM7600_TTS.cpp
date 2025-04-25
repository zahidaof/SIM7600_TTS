/*
=================================================================
 Author: Zahid Alfahmi, Jeddah, Saudi Arabia
 Date: April 25, 2025
=================================================================
*/
#include "SIM7600_TTS.h"

SIM7600_TTS::SIM7600_TTS(HardwareSerial& serial, int powerKeyPin) 
  : SerialAT(serial), MODEM_PWRKEY(powerKeyPin) {
}

void SIM7600_TTS::begin() {
  pinMode(MODEM_PWRKEY, OUTPUT);
  digitalWrite(MODEM_PWRKEY, LOW);
  delay(1000);
  digitalWrite(MODEM_PWRKEY, HIGH);
  delay(5000);
  
  SerialAT.begin(MODEM_UART_BAUD, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);
  
  SerialAT.println("AT");
  waitForResponse(5000);
}

bool SIM7600_TTS::makeCall(const char* number) {
  SerialAT.print("ATD");
  SerialAT.print(number);
  SerialAT.println(";");
  return waitForResponse(10000);
}

void SIM7600_TTS::setTTSPlayPath(int mode) {
  SerialAT.print("AT+CDTAM=");
  SerialAT.println(mode);
  waitForResponse(5000);
}

void SIM7600_TTS::playTTSMessage(const char* message) {
  SerialAT.print("AT+CTTS=2,\"");
  SerialAT.print(message);
  SerialAT.println("\"");
  waitForResponse(10000);
}

bool SIM7600_TTS::waitForResponse(unsigned long timeout) {
  unsigned long start = millis();
  while (millis() - start < timeout) {
    if (SerialAT.available()) {
      String response = SerialAT.readString();
      if (response.indexOf("OK") != -1 || response.indexOf("+CTTS: 0") != -1) {
        return true;
      }
    }
  }
  return false;
}