#include <stdio.h>
#include "../thirdparty/raylib.h"

#include "clock.c"
#include "lcd.c"

extern int mikisser_main(void);

int main(int argc, char** argv) {
    InitWindow(LCD_WIDTH*PIXEL_SCALE + DRAW_X_OFFSET, LCD_HEIGHT*PIXEL_SCALE + DRAW_Y_OFFSET, "Raylib Window");
    
    mikisser_main();

    CloseWindow();
    return 0;
}
