# ElechouseVR3_ESP32

![Unofficial ESP32 Port](https://img.shields.io/badge/status-unofficial%20ESP32%20port-orange)

> ⚠️ **Unofficial Port**  
> This project is an **unofficial adaptation** of the [Elechouse VoiceRecognitionV3 Arduino library](https://github.com/elechouse/VoiceRecognitionV3/tree/master), made to support the **ESP32** platform.  
> It is **not affiliated with or endorsed by Elechouse**.

---

## 🧰 Installation

1. Create a folder named `VoiceRecognitionV3_ESP32` inside your [Arduino libraries folder](https://docs.arduino.cc/retired/hacking/software/Libraries/).
2. Download the following files from this repository:
   - `VoiceRecognitionV3_ESP32.h`
   - `VoiceRecognitionV3_ESP32.cpp`
3. Copy both files into the newly created folder.

---

## 🚀 Getting Started

You can either:

- Use the **original examples** from the [official Elechouse repo](https://github.com/elechouse/VoiceRecognitionV3/tree/master), or  
- Use the **modified examples** provided here.

### ✅ If you use the official examples:

1. Replace the `#include` directive:

   ```cpp
   #include "VoiceRecognitionV3.h"
   // becomes:
   #include "VoiceRecognitionV3_ESP32.h"
   ```

2. Update the RX and TX pins to match your ESP32 setup:

   ```cpp
   VR myVR(2, 3);  // RX = GPIO 2, TX = GPIO 3 (example)
   // VR3 RXD ===>  TX (GPIO 2)
   // VR3 TXD ===> RX (GPIO 3)
   ```

---

## ⚠️ Logic Level Warning

The **Voice Recognition Module V3** uses **5V logic**, while the **ESP32** uses **3.3V** logic.

To protect your ESP32, you **must** add a **voltage divider** to the module’s **TX pin** to reduce the 5V signal down to 3.3V.

### Example Wiring:

![Voltage Divider Diagram](https://github.com/user-attachments/assets/d5c38b18-878f-4ed2-9c76-72eaabfe5552)

---

## 📄 License

This is an **unofficial** project. The original library is © Elechouse.  
This port is provided under the same license as the original unless stated otherwise.
