/* Copyright (c) ARM Ltd 2007, All Rights Reserved.
 * Author: Andrew Bolt, andrew.bolt@arm.com
 *
 * Client app for phone skin demo: very simple snake/sketch program
 * using numeric/direction pad.
 */

/*! Render size. */
#define SCREEN_WIDTH 224
#define SCREEN_HEIGHT 300

/*! Scan-line size in pixel words. */
#define SCREEN_PITCH (SCREEN_WIDTH)

typedef unsigned long uint32;

typedef volatile struct KMI {
    uint32 KMI_CR;
    uint32 KMI_STAT;
    uint32 KMI_DATA;
    uint32 KMI_CLKDIV;
    uint32 KMI_IR;
} KMI;

enum KMI_CR_FLAGS {
    KMI_CR_TYPE = (1<<5),
    KMI_CR_RXINTREN = (1<<4),
    KMI_CR_TXINTREN = (1<<3),
    KMI_CR_EN = (1<<2),
    KMI_CR_FKMID = (1<<1),
    KMI_CR_FKMIC = (1<<0)
};

enum KMI_STAT_FLAGS {
    KMI_STAT_TXEMPTY = (1<<6),
    KMI_STAT_TXBUSY = (1<<5),
    KMI_STAT_RXFULL = (1<<4),
    KMI_STAT_RXBUSY = (1<<3),
    KMI_STAT_RXPARITY = (1<<2),
    KMI_STAT_C = (1<<1),
    KMI_STAT_D = (1<<0)
};

volatile KMI *kmi_kbd = (KMI *)0x18000000;

/*! Statically allocate memory for screen buffer. */
unsigned short *buff = (unsigned short *)0x100000;

void put_pixel(int x, int y, unsigned short pixel) {
    if (x >= 0 && y >= 0 && x < SCREEN_WIDTH && y < SCREEN_HEIGHT) {
        buff[y * SCREEN_PITCH + x] = pixel;
    }
}

void fill_rect(int x, int y, int w, int h, unsigned short pixel) {
    int px, py;
    for (py = y; py < y + h; ++py) {
        for (px = x; px < x + w; ++px) {
            put_pixel(px, py, pixel);
        }
    }
}

/*! Fill the screen with black. */
void clear_screen()
{
    fill_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x3000);
    fill_rect(1, 1, SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2, 0x0010);
}

/*! Activate the LCD with a 16-bit display. */
void init_lcd(void)
{
    volatile unsigned int* LCD = (unsigned int*)0xc0000000;
    volatile unsigned int* CM = (unsigned int *)0x10000000;

    // From IntegratorCP manual: setting up VGA display.
    CM[5] = 0xa05f; // Write to CM_LOCK to enable changing the clock rate.
    CM[7] = 0x12c11; // Set AUXCLK (pixel clock) to 25MHz.
    LCD[0] = 0x3f1f3f00 | ((SCREEN_WIDTH / 16 - 1) << 2); // LCD_TIM0 horizontal timing value.
    LCD[1] = 0x080b6000 | ((SCREEN_HEIGHT - 1) << 0); // LCD_TIM1 vertical timing value.
    LCD[2] = 0x067f3800; // LCD_TIM2 other timing values.
    LCD[4] = (unsigned int)buff;
    LCD[7] = 0x1829;     // 16 bits per pixel.
    CM[3] = 0x3e005;     // Output multiplexor to drive VGA interface.
}


void init_kmi(void)
{
    kmi_kbd->KMI_CR = KMI_CR_EN;
}

uint32 kmi_read(void)
{
    if ((kmi_kbd->KMI_STAT) & KMI_STAT_RXFULL) {
        return kmi_kbd->KMI_DATA;
    }
    return 0;
}

#define KEY_PREFIX 224
#define KEY_RELEASE 240

#define KEY_LEFT  107
#define KEY_DOWN  114
#define KEY_RIGHT 116
#define KEY_UP    117
#define KEY_2     30
#define KEY_4     37
#define KEY_6     54
#define KEY_8     62

int main(void)
{
    int delay;
    int x, y;
    int key_pressed = 0;
    int last_key_pressed = 0;
    enum ps2_state { idle, got_prefix, got_release } key_state = idle;
    
    clear_screen();
    init_lcd();
    init_kmi();

    x = 30; y = 30;
    do {
        uint32 key_code;

        fill_rect(x * 3, y * 3, 2, 2, 0xffff);

        last_key_pressed = 0;

        for (delay = 0; delay < 0x80000; ++delay) {
            key_code = kmi_read();

            switch (key_code) {
            case 0: break;
            case KEY_PREFIX: key_state = got_prefix; break;
            case KEY_RELEASE: key_state = got_release; break;
            default:
                if (key_state == got_release) {
                    key_pressed = 0;
                } else {
                    last_key_pressed = key_pressed = key_code;
                }
                key_state = idle;
                break;
            }
        }

        if (last_key_pressed == 0) {
            last_key_pressed = key_pressed;
        }

        fill_rect(x * 3, y * 3, 2, 2, 0x7777);
        switch (last_key_pressed) {
        case KEY_LEFT:  case KEY_4: x -= 1; break;
        case KEY_RIGHT: case KEY_6: x += 1; break;
        case KEY_UP:    case KEY_2: y -= 1; break;
        case KEY_DOWN:  case KEY_8: y += 1; break;
        }

    } while (1);
}
