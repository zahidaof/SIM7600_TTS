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

// Create an instance of SIM7600_TTS with the required arguments
SIM7600_TTS tts(MODEM_TX, MODEM_RX, MODEM_PWRKEY, MODEM_UART_BAUD);

void setup() {
  SerialMon.begin(115200);
  delay(10);
  SerialMon.println("Initializing...");

  // Initialize the modem
  tts.begin();

  // Make a test call to verify functionality
  if (tts.makeCall(Number)) {
    SerialMon.println("Call initiated successfully.");
  } else {
    SerialMon.println("Failed to initiate call.");
  }
}

void loop() {
  // Play a TTS message during the call
  tts.playTTSMessage("HI check out my other repos"); // insert your message here

  // Wait indefinitely (or add logic to repeat if needed)
  while (true) {
    delay(1000);
  }
}