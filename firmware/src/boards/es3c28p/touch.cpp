#include "../../hal/touch_hal.h"
#include "board.h"
#include <Arduino.h>
#include <Wire.h>

// Minimal FT6336G reader using the FocalTech register layout. Polling avoids
// relying on the controller's interrupt mode and keeps each read bounded.
static bool touch_init_ok = false;
static bool touch_pressed = false;
static uint16_t touch_x = 0;
static uint16_t touch_y = 0;
static uint32_t last_read_ms = 0;

static void read_touch(void) {
    Wire.beginTransmission(TOUCH_ADDR);
    Wire.write(0x02);
    if (Wire.endTransmission(false) != 0 ||
        Wire.requestFrom(TOUCH_ADDR, (uint8_t)5) != 5) {
        touch_pressed = false;
        return;
    }

    uint8_t fingers = Wire.read() & 0x0f;
    uint8_t xh = Wire.read();
    uint8_t xl = Wire.read();
    uint8_t yh = Wire.read();
    uint8_t yl = Wire.read();
    if (fingers == 0 || fingers > 2) {
        touch_pressed = false;
        return;
    }

    touch_x = ((uint16_t)(xh & 0x0f) << 8) | xl;
    touch_y = ((uint16_t)(yh & 0x0f) << 8) | yl;
    if (touch_x >= LCD_WIDTH || touch_y >= LCD_HEIGHT) {
        touch_pressed = false;
        return;
    }
    touch_pressed = true;
}

void touch_hal_init(void) {
    pinMode(TP_RST, OUTPUT);
    digitalWrite(TP_RST, LOW);
    delay(20);
    digitalWrite(TP_RST, HIGH);
    delay(200);
    pinMode(TP_INT, INPUT_PULLUP);

    Wire.beginTransmission(TOUCH_ADDR);
    Wire.write(0xA5);
    Wire.write(0x00); // active mode
    touch_init_ok = Wire.endTransmission() == 0;
    Serial.println(touch_init_ok ? "FT6336 touch init OK" : "FT6336 touch init failed");
}

void touch_hal_read(uint16_t* x, uint16_t* y, bool* pressed) {
    if (touch_init_ok && millis() - last_read_ms >= 20) {
        last_read_ms = millis();
        read_touch();
    }
    *x = touch_x;
    *y = touch_y;
    *pressed = touch_init_ok && touch_pressed;
}
