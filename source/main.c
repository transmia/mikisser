#include <lcd.h>
#include <clock.h>

static bool running = true;
static bool shift = false;
static bool alpha = false;

int mikisser_main(void) {
    clock_init(CLOCK_MAX_HZ);
    lcd_init();
    lcd_set_enabled(true);
    lcd_clear();
    lcd_set_contrast(200);

    display_set_symbol(DISP_SYM_SHIFT, true);
    display_set_symbol(DISP_SYM_ALPHA, true);

    while (clock_wait()) {
        lcd_set_pixel(50, 50, true);
        lcd_refresh();
    }
    
    lcd_shutdown();
    clock_shutdown();

    return 0;
}