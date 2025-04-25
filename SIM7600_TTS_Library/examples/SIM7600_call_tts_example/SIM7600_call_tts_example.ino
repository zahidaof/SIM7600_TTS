/*
=================================================================
 Author: Zahid Alfahmi, Jeddah, Saudi Arabia
 Date: April 25, 2025
=================================================================
*/
// This example is for SIM7600 module only!!!
// This code demonstrates how to make a TTS (Text-to-Speech) call using the SIM7600 GSM module.
// Using the AT commands to dial a number and play a TTS message over the call.

// Serial interfaces
#include <SIM7600_TTS.h>

#define SerialMon Serial
#define SerialAT Serial1

// GSM Modem configuration
#define MODEM_TX 16     
#define MODEM_RX 17
#define MODEM_PWRKEY 5
#define MODEM_UART_BAUD 115200

// Emergency contact number
const char* Number = ""; // insert your number here

SIM7600_TTS tts;

void setup() {
  SerialMon.begin(115200);
  delay(10);
  SerialMon.println("Initializing...");

  // Power on the modem
  pinMode(MODEM_PWRKEY, OUTPUT);
  digitalWrite(MODEM_PWRKEY, LOW);
  delay(1000);
  digitalWrite(MODEM_PWRKEY, HIGH);
  delay(5000);

  // Initialize the modem
  tts.begin(MODEM_UART_BAUD, MODEM_RX, MODEM_TX);
  
  // Check communication
  if (tts.checkCommunication()) {
    SerialMon.println("Modem initialized successfully.");
  } else {
    SerialMon.println("Failed to communicate with modem. Check connections.");
    while (true);
  }

  // Display modem information
  tts.displayModemInfo();
}

void loop() {
  // Make a TTS call
  tts.makeTTSCall(Number, "HI check out my other repos"); // insert your message here

  // Wait indefinitely (or add logic to repeat if needed)
  while (true) {
    delay(1000);
  }
}