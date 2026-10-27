#pragma once

// LCDWiki/Hosyond ES3C28P - 2.8" 240x320 portrait IPS TFT, ILI9341V over
// plain 4-wire SPI, FT6336G capacitive touch. ESP32-S3R8: 16 MB flash + 8 MB
// octal PSRAM. The panel has no brightness command, so backlight is LEDC PWM.

#define BOARD_NAME           "LCDWiki ES3C28P"

// ---- Display geometry (portrait) ----
#define LCD_WIDTH            240
#define LCD_HEIGHT           320

// ---- SPI display pins (ILI9341) ----
#define TFT_CS               10
#define TFT_MOSI             11
#define TFT_SCLK             12
#define TFT_MISO             13
#define TFT_BL               45    // backlight, LEDC PWM
#define TFT_DC               46
#define TFT_RST              -1    // no reset line; software reset

// ---- I2C touch (FT6336G) ----
#define IIC_SDA              16
#define IIC_SCL              15
#define TP_INT               17
#define TP_RST               18
#define TOUCH_ADDR           0x38

// ---- Buttons ----
#define BTN_PWR_GPIO         0     // BOOT - PWR role: brightness, hold-to-pair

// ---- Capability flags ----
#define BOARD_HAS_SECONDARY_BUTTON 0
#define BOARD_HAS_ROTATION         0
#define BOARD_HAS_IMU              0
#define BOARD_HAS_BATTERY          0
#define BOARD_HAS_IO_EXPANDER      0
