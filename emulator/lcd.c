#include "include/lcd.h"
#include "top_symbols.h"
#include "../thirdparty/raylib.h"
#include <string.h>

static bool framebuffer[LCD_WIDTH * LCD_HEIGHT];
static uint8_t contrast = 0;
static bool dirty = false;
static bool initialized = false;
static bool enabled = false;

static SymbolFlags symbol_flags;

#define PIXEL_SCALE 2
#define DRAW_X_OFFSET 0
#define DRAW_Y_OFFSET 19
#define SYMBOL_SCALE 0.571f

bool lcd_init(void) {
    if (initialized) return false;
    initialized = true;
    return true;
}

void lcd_shutdown(void) {
    initialized = false;
    return;
}

bool lcd_set_pixel(uint16_t x, uint16_t y, bool enabled) {
    if (!initialized) return false;
    if (x >= LCD_WIDTH || y >= LCD_HEIGHT) return false;
    framebuffer[y * LCD_WIDTH + x] = enabled;
    dirty = true;
    return true;
}

bool lcd_get_pixel(uint16_t x, uint16_t y, bool* enabled) {
    if (!initialized) return false;
    if (x >= LCD_WIDTH || y >= LCD_HEIGHT) return false;
    *enabled = framebuffer[y * LCD_WIDTH + x];
    return true;
}

void lcd_clear(void) {
    if (!initialized) return;
    memset(framebuffer, 0, sizeof(framebuffer));
    dirty = true;
}

static float get_bit(const uint8_t* bitmap, int width, int height, int r, int c) {
    if (r < 0 || r >= height || c < 0 || c >= width) return 0.0f;
    int byte_idx = r * ((width + 7) / 8) + c / 8;
    int bit_idx = 7 - (c % 8);
    return ((bitmap[byte_idx] >> bit_idx) & 1) ? 1.0f : 0.0f;
}

static void draw_symbol(const uint8_t* bitmap, int width, int height, int x, int y, uint8_t opacity, float scale) {
    int scaled_width = (int)(width * scale);
    int scaled_height = (int)(height * scale);
    
    for (int row = 0; row < scaled_height; row++) {
        for (int col = 0; col < scaled_width; col++) {
            float orig_row_f = row / scale;
            float orig_col_f = col / scale;
            
            int row0 = (int)orig_row_f;
            int col0 = (int)orig_col_f;
            int row1 = row0 + 1;
            int col1 = col0 + 1;
            
            float row_frac = orig_row_f - row0;
            float col_frac = orig_col_f - col0;
            
            float v00 = get_bit(bitmap, width, height, row0, col0);
            float v10 = get_bit(bitmap, width, height, row1, col0);
            float v01 = get_bit(bitmap, width, height, row0, col1);
            float v11 = get_bit(bitmap, width, height, row1, col1);
            
            float v0 = v00 * (1 - col_frac) + v01 * col_frac;
            float v1 = v10 * (1 - col_frac) + v11 * col_frac;
            float value = v0 * (1 - row_frac) + v1 * row_frac;
            
            if (value > 0.5f) {
                Color c = {0x00, 0x00, 0x00, opacity};
                DrawPixel(x + col, y + row, c);
            }
        }
    }
}

static void draw_all_symbols(void) {
    int x_pos = DRAW_X_OFFSET;
    int y_pos = 0;
    
    for (int i = 0; i < (int)(sizeof(symbols) / sizeof(symbols[0])); i++) {
        bool is_enabled = display_get_symbol(symbols[i].symbol);
        uint8_t opacity;
        if (is_enabled) {
            opacity = contrast;
        } else {
            opacity = 20;
        }
        
        int scaled_width = (int)(symbols[i].width * SYMBOL_SCALE);
        draw_symbol(symbols[i].bitmap, symbols[i].width, symbols[i].height, x_pos, y_pos, opacity, SYMBOL_SCALE);
        x_pos += scaled_width;
    }
}

void lcd_refresh(void) {
    if (!initialized) return;
    if (!dirty) return;

    BeginDrawing();

    /* took colors from https://www.reddit.com/r/calculators/comments/1rbv86x/casio_classwiz_graph_light/ image */
    Color bgbgc = {0x83, 0x8F, 0x7B, 0xFF};
    Color bgc = {0x3F, 0x45, 0x3B, contrast};
    Color fgc = {0x00, 0x00, 0x00, contrast};

    ClearBackground(bgbgc);
    
    DrawRectangle(DRAW_X_OFFSET, 0, LCD_WIDTH * PIXEL_SCALE, DRAW_Y_OFFSET, bgbgc);
    draw_all_symbols();
    
    DrawRectangle(DRAW_X_OFFSET, DRAW_Y_OFFSET, LCD_WIDTH * PIXEL_SCALE, LCD_HEIGHT * PIXEL_SCALE, bgc);

    for (uint16_t y = 0; y < LCD_HEIGHT; y++) {
        for (uint16_t x = 0; x < LCD_WIDTH; x++) {
            if (framebuffer[y * LCD_WIDTH + x]) {
                DrawRectangle(x * PIXEL_SCALE + DRAW_X_OFFSET, y * PIXEL_SCALE + DRAW_Y_OFFSET, PIXEL_SCALE, PIXEL_SCALE, fgc);
            }
        }
    }

    EndDrawing();

    dirty = false;
}

bool lcd_set_contrast(uint8_t c) {
    if (!initialized) return false;
    contrast = c;
    return true;
}

uint8_t lcd_get_contrast(void) {
    if (!initialized) return 0;
    return contrast;
}

bool lcd_set_enabled(bool enable) {
    if (!initialized) return false;
    enabled = enable;
    return true;
}

bool lcd_is_enabled(void) {
    if (!initialized) return false;
    return enabled;
}

void display_clear_symbols(void) {
    symbol_flags = 0;
    dirty = true;
}

void display_set_symbol(TopSymbol symbol, bool enabled) {
    if (enabled) {
        symbol_flags |= (1 << symbol);
    } else {
        symbol_flags &= ~(1 << symbol);
    }
    dirty = true;
}

bool display_get_symbol(TopSymbol symbol) {
    return (symbol_flags & (1 << symbol)) != 0;
}

SymbolFlags display_get_symbols(void) {
    return symbol_flags;
}

void display_set_symbols(SymbolFlags symbols) {
    symbol_flags = symbols;
    dirty = true;
}
