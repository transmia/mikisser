#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    KEY_MOD_NONE   = 0,
    KEY_MOD_SHIFT  = 0x10000000,
    KEY_MOD_ALPHA  = 0x20000000
} KeyModifier;
 
/* Base Physical Key Enum */
typedef enum {
    KEY_BASE_NONE       = 0x00,
    KEY_BASE_ON         = 0x01,
    KEY_BASE_MENU       = 0x02,  /* MENU key */
    KEY_BASE_UP         = 0x03,
    KEY_BASE_DOWN       = 0x04,
    KEY_BASE_LEFT       = 0x05,
    KEY_BASE_RIGHT      = 0x06,
    KEY_BASE_OPTN       = 0x07,
    KEY_BASE_CUBE       = 0x08,  /* x^3 */
    KEY_BASE_FRAC       = 0x09,  /* a/b */
    KEY_BASE_SQRT       = 0x0A,  /* sqrt */
    KEY_BASE_SQUARE     = 0x0B,  /* x^2 */
    KEY_BASE_POWER      = 0x0C,  /* x^n */
    KEY_BASE_ABS        = 0x0D,  /* Abs */
    KEY_BASE_LOGBASE    = 0x0E,  /* log_ab */
    KEY_BASE_LOG        = 0x0F,  /* log */
    KEY_BASE_LN         = 0x10,  /* ln */
    KEY_BASE_SIN        = 0x11,  /* sin */
    KEY_BASE_COS        = 0x12,  /* cos */
    KEY_BASE_TG         = 0x13,  /* tg */
    KEY_BASE_NEG        = 0x14,  /* (-) */
    KEY_BASE_DEG        = 0x15,  /* ° ' " */
    KEY_BASE_INV        = 0x16,  /* x^-1 */
    KEY_BASE_ENG        = 0x17,  /* ENG */
    KEY_BASE_LPAREN     = 0x18,  /* ( */
    KEY_BASE_RPAREN     = 0x19,  /* ) */
    KEY_BASE_SD         = 0x1A,  /* S<=>D */
    KEY_BASE_M_PLUS     = 0x1B,  /* M+ */
    KEY_BASE_STO        = 0x1C,  /* STO */
    KEY_BASE_DEL        = 0x20,  /* DEL */
    KEY_BASE_AC         = 0x21,  /* AC */
    KEY_BASE_7          = 0x22,
    KEY_BASE_8          = 0x23,
    KEY_BASE_9          = 0x24,
    KEY_BASE_MUL        = 0x25,  /* * */
    KEY_BASE_DIV        = 0x26,  /* / */
    KEY_BASE_4          = 0x27,
    KEY_BASE_5          = 0x28,
    KEY_BASE_6          = 0x29,
    KEY_BASE_ADD        = 0x2A,  /* + */
    KEY_BASE_SUB        = 0x2B,  /* - */
    KEY_BASE_1          = 0x2C,
    KEY_BASE_2          = 0x2D,
    KEY_BASE_3          = 0x2E,
    KEY_BASE_EXP        = 0x2F,  /* *10^x */
    KEY_BASE_ANS        = 0x30,  /* Ans */
    KEY_BASE_0          = 0x31,
    KEY_BASE_COMMA      = 0x32,  /* , */
    KEY_BASE_EQUALS     = 0x33   /* = */
} BaseKey;
 
/* Unified Key Code Enum (supporting bitwise combination) */
typedef enum {
    /* Modifiers */
    KEY_SHIFT           = KEY_MOD_SHIFT,
    KEY_ALPHA           = KEY_MOD_ALPHA,
 
    /* Base Physical Keys */
    KEY_ON              = KEY_BASE_ON,
    KEY_MENU            = KEY_BASE_MENU,
    KEY_UP              = KEY_BASE_UP,
    KEY_DOWN            = KEY_BASE_DOWN,
    KEY_LEFT            = KEY_BASE_LEFT,
    KEY_RIGHT           = KEY_BASE_RIGHT,
    KEY_OPTN            = KEY_BASE_OPTN,
    KEY_CUBE            = KEY_BASE_CUBE,
    KEY_FRAC            = KEY_BASE_FRAC,
    KEY_SQRT            = KEY_BASE_SQRT,
    KEY_SQUARE          = KEY_BASE_SQUARE,
    KEY_POWER           = KEY_BASE_POWER,
    KEY_ABS             = KEY_BASE_ABS,
    KEY_LOGBASE         = KEY_BASE_LOGBASE,
    KEY_LOG             = KEY_BASE_LOG,
    KEY_LN              = KEY_BASE_LN,
    KEY_SIN             = KEY_BASE_SIN,
    KEY_COS             = KEY_BASE_COS,
    KEY_TG              = KEY_BASE_TG,
    KEY_NEG             = KEY_BASE_NEG,
    KEY_DEG             = KEY_BASE_DEG,
    KEY_INV             = KEY_BASE_INV,
    KEY_ENG             = KEY_BASE_ENG,
    KEY_LPAREN          = KEY_BASE_LPAREN,
    KEY_RPAREN          = KEY_BASE_RPAREN,
    KEY_SD              = KEY_BASE_SD,
    KEY_M_PLUS          = KEY_BASE_M_PLUS,
    KEY_STO             = KEY_BASE_STO,
    KEY_DEL             = KEY_BASE_DEL,
    KEY_AC              = KEY_BASE_AC,
    KEY_7               = KEY_BASE_7,
    KEY_8               = KEY_BASE_8,
    KEY_9               = KEY_BASE_9,
    KEY_MUL             = KEY_BASE_MUL,
    KEY_DIV             = KEY_BASE_DIV,
    KEY_4               = KEY_BASE_4,
    KEY_5               = KEY_BASE_5,
    KEY_6               = KEY_BASE_6,
    KEY_ADD             = KEY_BASE_ADD,
    KEY_SUB             = KEY_BASE_SUB,
    KEY_1               = KEY_BASE_1,
    KEY_2               = KEY_BASE_2,
    KEY_3               = KEY_BASE_3,
    KEY_EXP             = KEY_BASE_EXP,
    KEY_ANS             = KEY_BASE_ANS,
    KEY_0               = KEY_BASE_0,
    KEY_COMMA           = KEY_BASE_COMMA,
    KEY_EQUALS          = KEY_BASE_EQUALS,
 
    /* ---------------------------------------------------------------- *
     * Shift Modified Keys (Yellow)                                     *
     * ---------------------------------------------------------------- */
    KEY_SETUP           = KEY_SHIFT | KEY_BASE_MENU,       /* SETUP      - yellow above MENU      */
    KEY_QR              = KEY_SHIFT | KEY_BASE_OPTN,       /* QR         - yellow above OPTN      */
    KEY_CBRT            = KEY_SHIFT | KEY_BASE_CUBE,       /* third root - yellow above sqrt      */
    KEY_MIXED_FRAC      = KEY_SHIFT | KEY_BASE_FRAC,       /* a b/c mix  - yellow above a b/c     */
    KEY_ROOT_X          = KEY_SHIFT | KEY_BASE_POWER,      /* x-th root  - yellow above x^n       */
    KEY_TEN_POWER       = KEY_SHIFT | KEY_BASE_LOG,        /* 10^x       - yellow above log       */
    KEY_EXP_E           = KEY_SHIFT | KEY_BASE_LN,         /* e^x        - yellow above ln        */
    KEY_ASIN            = KEY_SHIFT | KEY_BASE_SIN,        /* sin^-1     - yellow above sin       */
    KEY_ACOS            = KEY_SHIFT | KEY_BASE_COS,        /* cos^-1     - yellow above cos       */
    KEY_ATG             = KEY_SHIFT | KEY_BASE_TG,         /* tg^-1      - yellow above tg        */
    KEY_RECALL          = KEY_SHIFT | KEY_BASE_NEG,        /* RECALL     - yellow above (-)       */
    KEY_FACT            = KEY_SHIFT | KEY_BASE_DEG,        /* FACT       - yellow above °'"       */
    KEY_FACTORIAL       = KEY_SHIFT | KEY_BASE_INV,        /* x!         - yellow above x^-1      */
    KEY_ENG_LEFT        = KEY_SHIFT | KEY_BASE_ENG,        /* <--        - yellow above ENG       */
    KEY_M_MINUS         = KEY_SHIFT | KEY_BASE_M_PLUS,     /* M−         - yellow above M+        */
    KEY_RCL             = KEY_SHIFT | KEY_BASE_STO,        /* RCL        - yellow above STO       */
    KEY_INS             = KEY_SHIFT | KEY_BASE_DEL,        /* INS        - yellow above DEL       */
    KEY_OFF             = KEY_SHIFT | KEY_BASE_AC,         /* OFF        - yellow above AC        */
    KEY_CONST           = KEY_SHIFT | KEY_BASE_7,          /* CONST      - yellow above 7         */
    KEY_CONV            = KEY_SHIFT | KEY_BASE_8,          /* CONV       - yellow above 8         */
    KEY_RESET           = KEY_SHIFT | KEY_BASE_9,          /* RESET      - yellow above 9         */
    KEY_NPR             = KEY_SHIFT | KEY_BASE_MUL,        /* nPr        - yellow above *         */
    KEY_NCR             = KEY_SHIFT | KEY_BASE_DIV,        /* nCr        - yellow above /         */
    KEY_POL             = KEY_SHIFT | KEY_BASE_ADD,        /* Pol        - yellow above +         */
    KEY_REC             = KEY_SHIFT | KEY_BASE_SUB,        /* Rec        - yellow above −         */
    KEY_RND             = KEY_SHIFT | KEY_BASE_1,          /* Rnd        - yellow above 1         */
    KEY_RAN_NUM         = KEY_SHIFT | KEY_BASE_2,          /* Ran#       - yellow above 2         */
    KEY_PI              = KEY_SHIFT | KEY_BASE_3,          /* pi         - yellow above 3         */
    KEY_PERCENT         = KEY_SHIFT | KEY_BASE_EXP,        /* %          - yellow above *10^x     */
    KEY_APPROX          = KEY_SHIFT | KEY_BASE_EQUALS,     /* ~=         - yellow above =         */
 
    /* ---------------------------------------------------------------- *
     * Alpha Modified Keys (Magenta)                                    *
     * ---------------------------------------------------------------- */
    KEY_A               = KEY_ALPHA | KEY_BASE_NEG,        /* A          - magenta above (-)         */
    KEY_B               = KEY_ALPHA | KEY_BASE_DEG,        /* B          - magenta above °'"         */
    KEY_C               = KEY_ALPHA | KEY_BASE_INV,        /* C          - magenta above x^-1        */
    KEY_D               = KEY_ALPHA | KEY_BASE_SIN,        /* D          - magenta above sin         */
    KEY_E               = KEY_ALPHA | KEY_BASE_COS,        /* E          - magenta above cos         */
    KEY_F               = KEY_ALPHA | KEY_BASE_TG,         /* F          - magenta above tg          */
    KEY_X               = KEY_ALPHA | KEY_BASE_RPAREN,     /* x (var)    - magenta above )           */
    KEY_M               = KEY_ALPHA | KEY_BASE_M_PLUS,     /* M          - magenta above M+          */
    KEY_COLON           = KEY_ALPHA | KEY_BASE_CUBE,       /* :          - magenta above x^3         */
    KEY_SEMICOLON       = KEY_ALPHA | KEY_BASE_LPAREN,     /* ;          - magenta above (           */
    KEY_UNDO            = KEY_ALPHA | KEY_BASE_DEL,        /* UNDO       - magenta above DEL         */
    KEY_RAN_INT         = KEY_ALPHA | KEY_BASE_1,          /* RanInt     - magenta above 1           */
    KEY_EULER           = KEY_ALPHA | KEY_BASE_3           /* e          - magenta above 3           */
} KeyMap;

typedef enum {
    KEY_EVENT_DOWN,
    KEY_EVENT_UP,
    KEY_EVENT_REPEAT
} KeyEventType;

typedef struct {
    BaseKey key;
    KeyEventType type;
} KeyEvent;

bool keypad_init(void);
void keypad_shutdown(void);
bool keypad_poll_event(KeyEvent* event);
bool keypad_is_pressed(BaseKey key);

#endif
