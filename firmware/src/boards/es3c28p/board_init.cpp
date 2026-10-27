#include "board.h"
#include <Wire.h>

extern "C" void board_init(void) {
    Wire.begin(IIC_SDA, IIC_SCL);
}
