/*
=================================================================
 Author: Zahid Alfahmi, Jeddah, Saudi Arabia
 Date: April 25, 2025
=================================================================
*/
//this example is for sim7600 module only!!!
// This code demonstrates how to make a TTS (Text-to-Speech) call using the SIM7600 GSM module.
//using the AT commands to dial a number and play a TTS message over the call.



// Serial interfaces
#define SerialMon Serial
#define SerialAT Serial1

// GSM Modem configuration
// replace with your modem's serial pins
// Note: The RX and TX pins are swapped in the Serial1 configuration important

// in my case Modem TX → ESP32 GPIO 16 (RX)
//            Modem RX → ESP32 GPIO 17 (TX)
#define MODEM_TX 16     
#define MODEM_RX 17
#define MODEM_PWRKEY 5
#define MODEM_UART_BAUD 115200

// Emergency contact number
const char* Number = "";// insert your number here

void setup() {
  // Initialize serial monitors
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
  SerialAT.begin(MODEM_UART_BAUD, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);

  // Send basic AT command to check communication
  SerialAT.println("AT");
  if (waitForResponse(5000)) {
    SerialMon.println("Modem initialized successfully.");
  } else {
    SerialMon.println("Failed to communicate with modem. Check connections.");
    while (true);
  }

  // Display modem information
  SerialAT.println("ATI");
  waitForResponse(5000);
}

void loop() {
  // Make a TTS call
  makeTTSCall();

  // Wait indefinitely (or add logic to repeat if needed)
  while (true) {
    delay(1000);
  }
}

void makeTTSCall() {
  SerialMon.println("Making emergency call...");

  // Dial the number
  SerialAT.print("ATD");
  SerialAT.print(Number);
  SerialAT.println(";");
  if (waitForResponse(10000)) {  // Wait for call initiation
    SerialMon.println("Call initiated. Waiting for connection...");
    delay(5000);  // Wait for the call to connect

    // Set TTS play path to remote (over the call)
    SerialAT.println("AT+CDTAM=1");
    /* AT+CDTAM=<mode>
    <mode> Set TTS play path, local or remote. Default value is 0. 
    0 – Local path
    1 – Remote path
    */
    if (waitForResponse(5000)) {
      SerialMon.println("TTS play path set to remote.");
    } else {
      SerialMon.println("Failed to set TTS play path.");
    }

    // Play TTS message
    playTTSMessage("HI check out my other repos");// insert your message here

    
  } else {
    SerialMon.println("Failed to initiate the call.");
  }
}

void playTTSMessage(const char* message) {
  SerialMon.println("Playing TTS message: " + String(message));

  // Set TTS parameters (optional, adjust as needed)
  SerialAT.println("AT+CTTSPARAM=2,3,0,1,1");  // Example: max volume, normal tone, normal speed
    /* AT+CTTSPARAM=<volume>[,<sysvolume>[,<digitmode>[,<pitch>[,<speed>]]]
    <volume>,<sysvolume>,<digitmode>,<pitch>,<speed>
    Defined Values
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

  if (waitForResponse(5000)) {
    SerialMon.println("TTS parameters set successfully.");
  } else {
    SerialMon.println("Failed to set TTS parameters.");
  }

  // Play the TTS message
  SerialAT.print("AT+CTTS=2,\"");
  /*AT+CTTS=<mode>[,<text>]
  <mode> Stop or play TTS. 
  0 – Stop TTS
  1 – <text> is in UCS2 coding format, Start to synth and play
  2 –<text> is in ASCII coding format for English,Chinese text isinGBKcoding format. Start to synth and play
  3 – <text> is in ASCII coding format for English,Chinese text isinGBKcoding format. Start to synth and play, and save pcmdata as wavfile. 
  4 – <text> is in UCSII coding format . Start to synth and play, andsavepcm data as wav file.
  */
  SerialAT.print(message);// this will go with the above AT command dont remove it 
  SerialAT.println("\"");  // Mode 2: ASCII text
  if (waitForResponse(10000)) {
    SerialMon.println("TTS message played successfully.");
  } else {
    SerialMon.println("Failed to play TTS message.");
  }
}

bool waitForResponse(unsigned long timeout) {
  unsigned long start = millis();
  while (millis() - start < timeout) {
    if (SerialAT.available()) {
      String response = SerialAT.readString();
      SerialMon.println("Modem Response: " + response);
      if (response.indexOf("OK") != -1 || response.indexOf("+CTTS: 0") != -1) {
        return true;
      }
    }
  }
  return false;
}