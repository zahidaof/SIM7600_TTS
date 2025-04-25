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
SIM7600_TTS tts(MODEM_TX, MODEM_RX, MODEM_PWRKEY, MODEM_UART_BAUD, SerialMon);

void setup() {
  SerialMon.begin(115200);
  delay(10);
  SerialMon.println("Initializing...");

  // Initialize the modem
  tts.begin();
  
  
}

void loop() {
  tts.makeCall(Number);
  tts.setTTSPlayPath(1); // Set TTS play path to remote (over the call)
  tts.setTTSParameters(2, 3, 0, 1, 0); // Example: max volume, normal tone, normal speed
  // Play a TTS message during the call
  tts.playTTSMessage("HI check out my other repos"); // insert your message here

  // Wait indefinitely (or add logic to repeat if needed)
  while (true) {
    delay(1000);
  }
}

/*
<volume> TTS Speech Volume, default：2.
    0 – The mix volume
    1 – The normal volume
    2 – The max volume
    <sysvolume> The module system volume, default：3. 
    0 – The mix system volume
    1 – The small system volume
    2 – The normal system volume
    3 – The max system volume
    <digitmode> The digit read mode, default：0
    0 – Auto read digit based on number rule first.
    1 – Auto read digit bases on telegram rule first.
    2 – Read digit based on telegram rule. 
    3 – Read digit based on number rule. 
    <pitch> The voice tone, default：1
    0 – The mix voice tone. 
    1 – The normal voice tone. 
    2 – The max voice tone. 
    <speed> The voice speed, default：1
    0 – The mix speed
    1 – The normal speed
    2 – The max speed*/



     /*=
    <mode> Set TTS play path, local or remote. Default value is 0. 
    0 – Local path
    1 – Remote path
    */