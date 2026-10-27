#include "board.h"
#include <Wire.h>
#include <esp32-hal-rgb-led.h>

extern "C" void board_init(void) {
    // The WS2812-style status LED retains its last latched colour across an
    // ESP reset. Explicitly clear it so it does not glow behind the display.
    rgbLedWrite(RGB_LED_GPIO, 0, 0, 0);
    Wire.begin(IIC_SDA, IIC_SCL);
}
