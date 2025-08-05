/**
 ******************************************************************************
 * @file      VoiceRecognitionV3_ESP32.h
 * @author    Elechouse Team (original)
 * @editor    Unofficial ESP32 Port by @Muehli-Industries
 * @version   V1.0.0
 * @date      2025-08-05
 * @brief     ESP32-compatible version of the Elechouse Voice Recognition V3 library.
 *
 ******************************************************************************
 * NOTE:
 * -----
 * This is an UNOFFICIAL adaptation of the Elechouse VoiceRecognitionV3 library
 * to work with the ESP32 using HardwareSerial instead of SoftwareSerial.
 *
 * Repository:
 *   https://github.com/Muehli-Industries/ElechouseVR3_ESP32
 *
 * Original library:
 *   https://github.com/elechouse/VoiceRecognitionV3
 *
 * IMPORTANT:
 * The Voice Recognition Module V3 uses 5V logic.
 * Always use a voltage divider on the module’s TX pin when connecting to an ESP32.
 *
 ******************************************************************************
 * @section  LICENSE
 *
 * This project is provided "as-is" without any warranty.
 * The original source code is © 2013 Elechouse and licensed accordingly.
 * This ESP32 port is an unofficial modification.
 *
 ******************************************************************************
 */

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif


#include "HardwareSerial.h"
#define VR_SERIAL_TYPE HardwareSerial

#define DEBUG
#ifdef DEBUG
#define DBGSTR(message)     Serial.print(message)
#define DBGBUF(buf, len)    Serial.write(buf, len)
#define DBGLN(message)      Serial.println(message)
#define DBGFMT(msg, fmt)    Serial.print(msg, fmt)
#define DBGCHAR(c)          Serial.write(c)
#else
#define DBGSTR(message)
#define DBGBUF(buf, len)
#define DBGLN(message)
#define DBGFMT(msg, fmt)
#define DBGCHAR(c)
#endif

#define VR_DEFAULT_TIMEOUT  (1000)

#define FRAME_HEAD          (0xAA)
#define FRAME_END           (0x0A)

#define FRAME_CMD_CHECK_SYSTEM    (0x00)
#define FRAME_CMD_CHECK_BSR       (0x01)
#define FRAME_CMD_CHECK_TRAIN     (0x02)
#define FRAME_CMD_CHECK_SIG       (0x03)
#define FRAME_CMD_RESET_DEFAULT   (0x10)
#define FRAME_CMD_SET_BR          (0x11)
#define FRAME_CMD_SET_IOM         (0x12)
#define FRAME_CMD_SET_PW          (0x13)
#define FRAME_CMD_RESET_IO        (0x14)
#define FRAME_CMD_SET_AL          (0x15)
#define FRAME_CMD_TRAIN           (0x20)
#define FRAME_CMD_SIG_TRAIN       (0x21)
#define FRAME_CMD_SET_SIG         (0x22)
#define FRAME_CMD_LOAD            (0x30)
#define FRAME_CMD_CLEAR           (0x31)
#define FRAME_CMD_GROUP           (0x32)
 #define FRAME_CMD_GROUP_SET      (0x00)
 #define FRAME_CMD_GROUP_SUGRP    (0x01)
 #define FRAME_CMD_GROUP_LSGRP    (0x02)
 #define FRAME_CMD_GROUP_LUGRP    (0x03)
 #define FRAME_CMD_GROUP_CUGRP    (0x04)
#define FRAME_CMD_TEST            (0xEE)
 #define FRAME_CMD_TEST_READ      (0x01)
 #define FRAME_CMD_TEST_WRITE     (0x00)
#define FRAME_CMD_VR              (0x0D)
#define FRAME_CMD_PROMPT          (0x0A)
#define FRAME_CMD_ERROR           (0xFF)

class VR  {
public:
    VR(uint8_t receivePin, uint8_t transmitPin);
    static HardwareSerial* serial;

    static VR* getInstance() {
        return instance;
    }

    typedef enum {
        PULSE = 0,
        TOGGLE = 1,
        SET = 2,
        CLEAR = 3
    } io_mode_t;

    typedef enum {
        LEVEL0 = 0, LEVEL1, LEVEL2, LEVEL3, LEVEL4, LEVEL5, LEVEL6, LEVEL7,
        LEVEL8, LEVEL9, LEVEL10, LEVEL11, LEVEL12, LEVEL13, LEVEL14, LEVEL15
    } pulse_width_level_t;

    typedef enum {
        GROUP0 = 0, GROUP1, GROUP2, GROUP3, GROUP4, GROUP5, GROUP6, GROUP7, GROUP_ALL = 0xFF
    } group_t;
    void begin(unsigned long baud);
    int setBaudRate(unsigned long br);
    int setIOMode(io_mode_t mode);
    int resetIO(uint8_t *ios = 0, uint8_t len = 1);
    int setPulseWidth(uint8_t level);
    int setAutoLoad(uint8_t *records = 0, uint8_t len = 0);
    int disableAutoLoad();
    int restoreSystemSettings();
    int checkSystemSettings(uint8_t* buf);
    int recognize(uint8_t *buf, int timeout = VR_DEFAULT_TIMEOUT);
    int train(uint8_t *records, uint8_t len = 1, uint8_t *buf = 0);
    int train(uint8_t record, uint8_t *buf = 0);
    int trainWithSignature(uint8_t record, const void *buf, uint8_t len = 0, uint8_t *retbuf = 0);
    int load(uint8_t *records, uint8_t len = 1, uint8_t *buf = 0);
    int load(uint8_t record, uint8_t *buf = 0);
    int clear();
    int setSignature(uint8_t record, const void *buf = 0, uint8_t len = 0);
    int deleteSignature(uint8_t record);
    int checkSignature(uint8_t record, uint8_t *buf);
    int checkRecognizer(uint8_t *buf);
    int checkRecord(uint8_t *buf, uint8_t *records = 0, uint8_t len = 0);

    int setGroupControl(uint8_t ctrl);
    int checkGroupControl();
    int setUserGroup(uint8_t grp, uint8_t *records, uint8_t len);
    int checkUserGroup(uint8_t grp, uint8_t *buf);
    int loadSystemGroup(uint8_t grp, uint8_t *buf = 0);
    int loadUserGroup(uint8_t grp, uint8_t *buf = 0);
    int test(uint8_t cmd, uint8_t *bsr);
    int writehex(uint8_t *buf, uint8_t len);

    int len(uint8_t *buf);
    int cmp(uint8_t *buf, uint8_t *bufcmp, int len);
    void cpy(char *buf, char *pbuf);
    void sort(uint8_t *buf, int len);
    int cleanDup(uint8_t *des, uint8_t *buf, int len);

    void send_pkt(uint8_t *buf, uint8_t len);
    void send_pkt(uint8_t cmd, uint8_t *buf, uint8_t len);
    void send_pkt(uint8_t cmd, uint8_t subcmd, uint8_t *buf, uint8_t len);
    int receive(uint8_t *buf, int len, uint16_t timeout = VR_DEFAULT_TIMEOUT);
    int receive_pkt(uint8_t *buf, uint16_t timeout = VR_DEFAULT_TIMEOUT);

private:
    static VR* instance;
    uint8_t rxPin;
    uint8_t txPin;
};