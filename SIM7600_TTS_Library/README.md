# SIM7600 TTS Library

## Overview
The SIM7600 TTS Library, created by **Zahid Alfahmi**, provides an easy-to-use interface for making Text-to-Speech (TTS) calls using the SIM7600 GSM module. This library allows you to initialize the modem, make calls, set TTS parameters, and play TTS messages.

## Features
- Initialize the SIM7600 modem
- Make TTS calls to specified numbers
- Set TTS parameters such as volume, pitch, and speed
- Play TTS messages during calls

## Installation
1. Download the SIM7600 TTS Library from the repository.
2. Copy the `SIM7600_TTS_Library` folder into your Arduino libraries directory (usually located in `Documents/Arduino/libraries`).
3. Restart the Arduino IDE to recognize the new library.

## Usage
To use the SIM7600 TTS Library, include the header file in your Arduino sketch:

```cpp
#include <SIM7600_TTS.h>
```

### Example
Refer to the example sketch located in the `examples/SIM7600_call_tts_example` directory. This sketch demonstrates how to initialize the modem, make a TTS call, and play a message.

## API Reference
### SIM7600_TTS Class
- `void begin()`: Initializes the modem.
- `void makeTTSCall(const char* number)`: Initiates a TTS call to the specified number.
- `void playTTSMessage(const char* message)`: Plays the specified TTS message during the call.

## Author
This library was developed by **Zahid Alfahmi**.

## Contributing
Contributions are welcome! Please submit a pull request or open an issue for any enhancements or bug fixes.

## License
This library is released under the MIT License. See the LICENSE file for more details.