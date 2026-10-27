# LCDWiki ES3C28P — `es3c28p`

Hardware notes for this board. Shared firmware rules are in `firmware/CLAUDE.md`.

LCDWiki/Hosyond **ES3C28P** (2.8" ILI9341V 240×320 portrait over plain
4-wire SPI, ESP32-S3R8: 16 MB flash + 8 MB octal PSRAM). Build env:
`es3c28p`.

- ILI9341 with inversion on (`ips = true`); the ST7789 init leaves this panel dark with a lit backlight. No reset line (software reset). The panel has no brightness command: the backlight is LEDC PWM on GPIO 45.
- FT6336G capacitive touch is at address 0x38 on SDA 16 / SCL 15, with
  INT 17 and RST 18. Coordinates are native portrait orientation.
- **No PMU, IMU or implemented audio.** `minimal_ui = true`: meters and a
  still corner Clawd only (slow SPI TFT).
- **BOOT (GPIO 0) is the only button**, so it takes the PWR role
  (`power.cpp`): short press → brightness, hold ~1.5 s and release → pair.
  `button_count = 0` (no primary/secondary: no push to talk).
