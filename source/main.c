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

    int i = 0;

    while (clock_wait()) {
        lcd_set_pixel(50, 50, true);
        display_clear_symbols();
        display_set_symbol(1 << i, true);
        i++; if (i >= 20) i = 0;
        lcd_refresh();
        clock_sleep_us(100000);
    }
    
    lcd_shutdown();
    clock_shutdown();

    return 0;
}