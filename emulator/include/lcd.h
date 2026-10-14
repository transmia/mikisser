#ifndef LCD_H
#define LCD_H

#include <stdbool.h>
#include <stdint.h>

#define LCD_WIDTH 192
#define LCD_HEIGHT 63

bool lcd_init(void);
void lcd_shutdown(void);

bool lcd_set_pixel(uint16_t x, uint16_t y, bool enabled);
bool lcd_get_pixel(uint16_t x, uint16_t y, bool* enabled);
void lcd_clear(void);
void lcd_refresh(void);

bool lcd_set_contrast(uint8_t contrast);
uint8_t lcd_get_contrast(void);
bool lcd_set_enabled(bool enabled);
bool lcd_is_enabled(void);

typedef enum {
    DISP_SYM_NONE       = 0x00000000,
    DISP_SYM_SHIFT      = (1ULL << 0),  /* "S"   - Shift active                        */
    DISP_SYM_ALPHA      = (1ULL << 1),  /* "A"   - Alpha active                        */
    DISP_SYM_M          = (1ULL << 2),  /* "M"   - Memory stored                       */
    DISP_SYM_STO        = (1ULL << 3),  /* "STO" - Store mode                          */
    DISP_SYM_BOX_WRITE  = (1ULL << 4),  /* box   - Box write mode                      */
    DISP_SYM_DEG        = (1ULL << 5),  /* "D"   - Degree angle unit                   */
    DISP_SYM_RAD        = (1ULL << 6),  /* "R"   - Radian angle unit                   */
    DISP_SYM_GRAD       = (1ULL << 7),  /* "G"   - Gradian angle unit                  */
    DISP_SYM_FIX        = (1ULL << 8),  /* "FIX" - Fixed decimal places format         */
    DISP_SYM_SCI        = (1ULL << 9),  /* "SCI" - Scientific notation format          */
    DISP_SYM_ERROR      = (1ULL << 10),  /* "E"   - Error indicator                     */
    DISP_SYM_IMAGINARY  = (1ULL << 11), /* "i"   - Complex / imaginary number mode     */
    DISP_SYM_ANGLE      = (1ULL << 12), /* angle - Polar coordinates                   */
    DISP_SYM_SCROLL_DN  = (1ULL << 13), /* down  - Menu/options continue downwards     */
    DISP_SYM_ARROW_LT   = (1ULL << 14), /* left  - Left arrow pressed indicator        */
    DISP_SYM_ARROW_DN   = (1ULL << 15), /* down  - Down arrow pressed indicator        */
    DISP_SYM_ARROW_UP   = (1ULL << 16), /* up    - Up arrow pressed indicator          */
    DISP_SYM_ARROW_RT   = (1ULL << 17), /* right - Right arrow pressed indicator       */
    DISP_SYM_PAUSE      = (1ULL << 18), /* pause - Pause symbol                        */
    DISP_SYM_SOLAR      = (1ULL << 19)  /* sun   - Solar panel / power indicator       */
} TopSymbol;

typedef uint64_t SymbolFlags;

void display_clear_symbols(void);
void display_set_symbol(TopSymbol symbol, bool enabled);
bool display_get_symbol(TopSymbol symbol);
SymbolFlags display_get_symbols(void);
void display_set_symbols(SymbolFlags symbols);

#endif
