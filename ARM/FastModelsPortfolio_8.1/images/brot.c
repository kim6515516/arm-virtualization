/* Copyright (c) ARM Ltd 2005-2013 All Rights Reserved.
 *
 * Very simple fixed-point Mandelbrot renderer.
 * Runs on Emulation Baseboard platforms and
 * Versatile Express platforms.
 */

/*! Fixed point arithmetic shift. */
#define SHIFT 13

/*! Fixed point co-ord shift. */
#define COORD_SHIFT 20

/*! VGA screen size (pixels) */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480


char *buff;


//! Configure PL111 CLCD
void init_pl111( unsigned int  clcd_base,
                 int           width,
                 int           height,
                 unsigned int  frame_base )
{
    volatile unsigned int*  clcd  = (volatile unsigned int*) clcd_base;

        // PL111 register offsets (32-bit words)
    const int PL111_TIM0 = (0x00/4);
    const int PL111_TIM1 = (0x04/4);
    const int PL111_TIM2 = (0x08/4);
    const int PL111_TIM3 = (0x0C/4);
    const int PL111_UBAS = (0x10/4);
    const int PL111_LBAS = (0x14/4);
    const int PL111_CNTL = (0x18/4);
    const int PL111_IENB = (0x1C/4);


         // Timing number for an 8.4" LCD screen for use on a VGA screen
    unsigned int TIM0_VAL = ( (((width/16)-1)<<2) | (63<<8) | (31<<16) | (63<<8) );
    unsigned int TIM1_VAL = ( (height - 1) | (24<<10) | (11<<16) | (9<<24) );
    unsigned int TIM2_VAL = ( (0x7<<11) | ((width - 1)<<16) | (1<<26) );


       // Statically allocate memory for screen buffer
    buff = (char*) frame_base;


         // Program the CLCD controller registers and start the CLCD
    clcd[ PL111_TIM0 ] = TIM0_VAL;
    clcd[ PL111_TIM1 ] = TIM1_VAL;
    clcd[ PL111_TIM2 ] = TIM2_VAL;
    clcd[ PL111_TIM3 ] = 0; 
    clcd[ PL111_UBAS ] = frame_base;
    clcd[ PL111_LBAS ] = 0;
    clcd[ PL111_IENB ] = 0;
    
         // Set the control register: 16BPP, Power OFF
    clcd[ PL111_CNTL ] = (1<<0) | (4<<1) | (1<<5);

         // Power ON
    clcd[ PL111_CNTL ] |= (1<<11);
}


//! Detect and configure LCD for EB platform
int init_lcd_eb(int width, int height)
{
        // EB Memory map
    const unsigned int EB_SYS_BASE   = 0x10000000;
    const unsigned int EB_CLCD_BASE  = 0x10020000;
    const unsigned int EB_FRAME_BASE = 0x00100000;

        // EB System Register 32-bit word offsets
    const int EB_SYS_OSC4    = (0x1C/4);
    const int EB_SYS_LOCK    = (0x20/4);
    const int EB_SYS_EB_CLCD = (0x50/4);

    volatile unsigned int* eb_sysreg = (unsigned int *)EB_SYS_BASE;

    if (eb_sysreg[0] != 0x01400400)
        return  0;

      // We're an EB
    eb_sysreg[EB_SYS_EB_CLCD] = 1;                   //  Mode is 5-5-5 mux
    eb_sysreg[EB_SYS_LOCK] = 0x0000A05F;        
    eb_sysreg[EB_SYS_OSC4] = 0x2C77;                 // Set CLCDCLK to 5.4MHz 
    eb_sysreg[EB_SYS_LOCK] = 0x0;

    init_pl111(EB_CLCD_BASE, width, height, EB_FRAME_BASE);

    return 1;
}


//! Detect and configure LCD for VE platforms
int init_lcd_ve(int           width,
                int           height,
                unsigned int  dvi_mux,
                unsigned int  ve_sysreg_base,
                unsigned int  ve_clcd_base,
                unsigned int  ve_frame_base )
{
        // VE System Register 32-bit word offsets
    const int VE_SYS_ID       = (0x00/4);
    const int VE_SYS_CFG_DATA = (0xA0/4);
    const int VE_SYS_CFG_CTRL = (0xA4/4);
    const int VE_SYS_ID_HBI = 0x225;

    volatile unsigned int*  ve_sysreg = (volatile unsigned int*) ve_sysreg_base;

    if (((ve_sysreg[VE_SYS_ID] >> 16) & 0xFFF) != VE_SYS_ID_HBI)
        return  0;

         // We're a Versatile Express

         // Set CLCD clock
         //   SYS_CFG_DATA sets oscillator rate value as 5.4MHz
         //   SYS_CFG_CTRL( start=1 | write=1 | function=1 | site=0 | position=0 | device=1 )
    ve_sysreg[ VE_SYS_CFG_DATA ] = 5400000;
    ve_sysreg[ VE_SYS_CFG_CTRL ] = 0x80000000 | (1<<30) | (1<<20) | (0<<16) | (0<<12) | (1<<0);


         // Set DVI mux for correct MMB
         //   SYS_CFG_CTRL( start=1 | write=1 | function=7 | site=0 | position=0 | device=0 )
    ve_sysreg[ VE_SYS_CFG_DATA ] = dvi_mux;
    ve_sysreg[ VE_SYS_CFG_CTRL ] = 0x80000000 | (1<<30) | (7<<20) | (0<<16) | (0<<12) | (0<<0);


    init_pl111(ve_clcd_base, width, height, ve_frame_base);

    return 1;
}


//! Detect and configure LCD for VE-A platform
int init_lcd_ve_a(int width, int height)
{
        // VE-A Memory map
    const unsigned int VE_A_SYSREG_BASE = 0x1C010000;  // CS3 + 0x010000
    const unsigned int VE_A_CLCD_BASE   = 0x1C1F0000;  // CS3 + 0x1F0000
    const unsigned int VE_A_FRAME_BASE  = 0x80100000;  // DMC + 0x100000
    const unsigned int VE_DVI_MUX       = 0;

    return init_lcd_ve(width, height, VE_DVI_MUX,
                       VE_A_SYSREG_BASE, VE_A_CLCD_BASE, VE_A_FRAME_BASE);
}


//! Detect and configure LCD for VE-R platform
int init_lcd_ve_r(int width, int height)
{
        // VE-R Memory map
    const unsigned int VE_R_SYSREG_BASE = 0xB0000000;  // CS7
#if defined( DB_CLCD )
          // Use daughter-board CLCD
    const unsigned int VE_R_CLCD_BASE   = 0xA0000000; 
    const unsigned int VE_R_FRAME_BASE  = 0x00100000;  // DMC + 0x100000
    const unsigned int VE_DVI_MUX       = 1;
#else
          // Use mother-board CLCD
    const unsigned int VE_R_CLCD_BASE   = 0xB01F0000;  // CS7 + 0x1F0000
    const unsigned int VE_R_FRAME_BASE  = 0x48000000;  // CS2 (PSRAM)
    const unsigned int VE_DVI_MUX       = 0;
#endif

    return init_lcd_ve(width, height, VE_DVI_MUX,
                       VE_R_SYSREG_BASE, VE_R_CLCD_BASE, VE_R_FRAME_BASE);
}


//! Detect platform and configure LCD
int init_lcd(int width, int height)
{
        // Figure out if we're an EB, VE-A, VE-R

    if ( init_lcd_eb(width, height) )
        return 1;

    if ( init_lcd_ve_a(width, height) )
        return 1;

    if ( init_lcd_ve_r(width, height) )
        return 1;

    return 0;
}


/*! Fill the screen with black. */
void clear_screen(int width, int height)
{
    int x, y;
    for (y=0; y<height; ++y) {
        for (x=0; x<width; x++) {
            int offset = (y*width+x)*2;
            buff[offset] = 0;
            buff[offset+1] = 0;
        }
    }
}


/*! Let p, s represent (px + i.py), (sx + i.sy)
 *  Initially:
 *    p = s         =>  (px, py) = (sx, sy)
 *
 *  Iterate calculation:
 *    p' = p^2 + s  =>  (px', py') = (px*px - py*py + sx, 2*px*py + sy)
 *
 *  All performed using fixed-point arithmetic with precision 'SHIFT'.
 */
int brot(long sx, long sy)
{
    int count;
    long px = sx, py = sy;

    for (count = 0; count < 256; count++) {
        long px2, py2;
        px2 = (px*px) >> SHIFT;
        py2 = (py*py) >> SHIFT;

        // Terminate when (px^2 + py^2) > 2^2.
        if (px2 + py2 > (4<<SHIFT)) {
            return count;
        }

        py = ((px*py) >> (SHIFT-1)) + sy;
        px = px2 - py2 + sx;
    }
    return -1;
}



/*! Render a view of the Mandelbrot, centred on (cx, cy)
 *  with each pixel covering an area of (dx x dy); all values
 *  in COORD_SHIFT fixed-point units.  Pixels are doubled up
 *  horizontally, so the view covers an area of (256*dx, 512*dy).
 */
void render(int cx, int cy, int dx, int dy)
{
    int sx = cx - dx * 128;
    int sy = 0 * dy;
    int py = sy;
    int x, y;
    
    for (y = ( SCREEN_HEIGHT / 2 ) - 1; y >= 0; y--) {
        int px = sx;
        for (x = 0; x < SCREEN_WIDTH; x+=2) {
            int offset = (y*SCREEN_WIDTH+x)*2;
            int col;
            unsigned short pixel;

            // Get iteration count.
            col = brot(px >> (COORD_SHIFT - SHIFT),
                       py >> (COORD_SHIFT - SHIFT));

            // Random colour mapping:
            pixel = ((col/16)<<10) | (((col*9)/16)<<5) | (((col*7)/16)<<0);

            // Plot first pair of pixels.
            buff[offset]     = buff[offset + 2] = (pixel & 0xff);
            buff[offset + 1] = buff[offset + 3] = (pixel >> 8);

            // Plot mirror image pixels:
            offset = ((SCREEN_HEIGHT - 1 - y) * SCREEN_WIDTH + x) * 2;
            buff[offset]     = buff[offset + 2] = (pixel & 0xff);
            buff[offset + 1] = buff[offset + 3] = (pixel >> 8);
            px += dx;
        }
        py -= dy;
    }
}


/*! Zoom in on the mandelbrot image for several frames. */
void zoom_loop(void)
{
    long cx, cy, dx, dy;
    int count;

    // Centre the view on (-1, 0)
    cx = (-1) << COORD_SHIFT;
    cy = (0)  << COORD_SHIFT;
    
    // Calculate dx/dy values for initial view 4 units wide and high,
    // given that screen is 256 dx units across and 512 dy units high
    dx = 4 << (COORD_SHIFT - 8);  //  = (4/256) * pow(2,COORD_SHIFT)
    dy = 4 << (COORD_SHIFT - 9);  //  = (4/512) * pow(2,COORD_SHIFT)
    
    for (count = 0; count < 13; count++)
    {
        render(cx, cy, dx, dy);
        
        // Zoom in and recentre slightly.
        cx -= 2 * dx;
        dx = dx * 16 / 17;
        dy = dy * 16 / 17;
    }
}


int main(void)
{
    if ( init_lcd(SCREEN_WIDTH, SCREEN_HEIGHT) )
    {
        clear_screen(SCREEN_WIDTH, SCREEN_HEIGHT);

        do
        {
           zoom_loop();

        } while(1);
    }

    return( 0 );
}
