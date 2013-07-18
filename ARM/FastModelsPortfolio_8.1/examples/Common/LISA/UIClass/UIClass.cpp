/*
 * UI classes used by Visualization component
 *
 * Copyright 2009 ARM Limited. All rights reserved.
 */

#include "UIClass.h"

// Translate visualisation colour indexes to RGB values
static void colour_index_to_rgb(unsigned colour_index, uint8_t& red, uint8_t& grn, uint8_t& blu)
{
    switch(colour_index)
    {
    case VIS_RED:    red = 0xff; grn = 0x00; blu = 0x00; break;
    case VIS_YELLOW: red = 0xff; grn = 0xff; blu = 0x00; break;
    case VIS_ORANGE: red = 0xff; grn = 0x80; blu = 0x40; break;
    case VIS_GREEN:  red = 0x00; grn = 0xff; blu = 0x00; break;
    default:         red = 0xff; grn = 0xff; blu = 0xff; break; // White
    }
}


/****************
 * Class Cicount
 ***************/

Cicount::Cicount(VisRenderRegion *render_reg, int x, int y, int num_digits_)
        : Clabel(render_reg,
                 num_digits_+((num_digits_-1)/3), x, y ),   // Add space for commas
                 count(0), num_digits(num_digits_) {}
    
bool Cicount::setCount(uint64_t count_)
{
    if (is_drawn && (count_ == count)) return false;
    count = count_;

    char buffer[30];
    int  buff_size=0;

    uint64_t value = count;

    for(unsigned place=0; place < num_digits; place++)
    {
        int digit = (int)(value % 10);

        buffer[buff_size++] = '0' + digit;

        value /= 10;
        if (value == 0) break;

        if ((place % 3) == 2) buffer[buff_size++] = ',';
    }

    // Reverse copy into rendered string
    for(int i=0; i<buff_size; i++)
    {
       str[i] = buffer[buff_size-i-1];
    }
    str[buff_size] = '\0';
 
    redraw();
    return true;
}

/**** Class Cicount END *****/

/***************
 * Class Clabel
 ***************/

    // Initialize with a constant string
Clabel::Clabel(VisRenderRegion *render_reg, const char *label, int x, int y)  
    : Cui(render_reg, x, y, 0, VIS_FONT_HEIGHT-1), rj(false), str(0)
{
    length = unsigned(strlen(label));
    init(label);
}
    
   // Initialize with a string length
Clabel::Clabel(VisRenderRegion *render_reg, int length_, int x, int y)  
    : Cui(render_reg, x, y, 0, VIS_FONT_HEIGHT-1), rj(false), str(0)
{
    length = length_;
    init("");
}

void Clabel::init(const char* label)
{
    if (str)
        delete [] str;
    str = new char[length+1];

    str[length]='\0';

    setWidth(length * VIS_FONT_WIDTH);
    setFgColour(0xc0, 0xc0, 0xc0, false);
    setLabel(label);
}
    
void Clabel::setLabel(const char *label)
{
    strncpy(str, label, length);
    redraw();
}

void Clabel::redraw(void)
{
    int x = rj ? (getMaxX() - unsigned(strlen(str))*VIS_FONT_WIDTH)
               : pos.x;

    clear(bg_colour);
    rr->writeText(fg_colour, bg_colour, str, x, pos.y);
    update();
}


/*** Class Clabel END ***/

/*************
 * Class Cbutton
 *************/

Cbutton::Cbutton(VisRenderRegion *render_reg, int x, int y, int width, 
                 int height, bool on_, uint32_t colour_index)
    : Cui(render_reg, x, y, width, height), on(on_)
{
    uint8_t red, grn,blu;

    colour_index_to_rgb(colour_index, red, grn, blu);

    setFgColour(red, grn, blu, false);
    setBgColour(red/4, grn/4, blu/4, false);
}

bool Cbutton::setState(bool on_)
{
    if (is_drawn && (on == on_)) return false;

    on=on_;
    redraw();
    return true;
}

void Cbutton::redraw(void)
{
    clear(on ? fg_colour : bg_colour);
    update();
}

/*** Class Cbutton END ***/

/*************
 * Class Cled
 *************/

Cled::Cled(VisRenderRegion *render_reg, int x, int y,
           unsigned led_num_, uint32_t led_stat_, unsigned led_size_)
    : Cui(render_reg, x, y, led_num_*(led_size_+1)+1, led_size_*2),
      led_num(led_num_), led_stat(led_stat_), led_size(led_size_)
{}
    
bool Cled::setState(uint32_t led_stat_)
{
    if (is_drawn && (led_stat_ == led_stat))  return false;
    led_stat = led_stat_;
    redraw();
    return true;
}

void Cled::redraw(void)
{
    clear(bg_colour);
    
    int offset = 0;

    for(unsigned i=0; i<led_num; i++)
    {
        bool    led_on = (led_stat & (1 << i)) != 0;
        uint8_t red, grn, blu;

        colour_index_to_rgb(i & 0x3, red, grn, blu);
        draw_led(offset, led_on, red, grn, blu);
    }

    update();
}

void Cled::draw_led(int& offset, bool led_on, uint8_t red, uint8_t grn, uint8_t blu)
{
    uint32_t colour = led_on ? rr->mapRGB(red, grn, blu) : rr->mapRGB(red/4, grn/4, blu/4);

    rr->fillRect(colour, pos.x + offset, pos.y, led_size, led_size);

    offset += led_size + 1;
}

/*** Class Cled END ***/

/*******************
 * Class Cdipswitch
 *******************/

Cdipswitch::Cdipswitch(VisRenderRegion *render_reg, int x, int y,
                       unsigned dip_num_, uint32_t dip_stat_, unsigned dip_size_)
    : Cui(render_reg, x, y, dip_num_*(dip_size_+1)+1, dip_size_*2),
      dip_num(dip_num_), dip_stat(dip_stat_), dip_size(dip_size_)
{
    setFgColour(200, 200, 200); // Default colour to nearly white
}

bool Cdipswitch::setState(uint32_t dip_stat_)
{
    if (is_drawn && (dip_stat_ == dip_stat))  return false;
    dip_stat = dip_stat_;
    redraw();
    return true;
}

uint32_t Cdipswitch::getState() { return dip_stat; }

void Cdipswitch::redraw(void)
{
    clear(bg_colour);
    
    UIPos dip;

    dip.x = pos.x;

    for (uint32_t i=0; i<dip_num; i++)
    {
        bool dip_on = ((dip_stat & (1 << i)) != 0 );
        dip.y  = dip_on ? pos.y : pos.y + dip_size;
        rr->fillRect(fg_colour, dip.x, dip.y, dip_size, dip_size);
        dip.x += dip_size + 1;
    }
    
    update();
}

bool Cdipswitch::isHit(int x, int y)
{
    if (Cui::isHit(x, y))
    {
        unsigned index = (x - pos.x) / (dip_size + 1);
        uint32_t mask  = 1 << index;
        bool     set   = (y - pos.y) < dip_size;

        if (set)
            setState(dip_stat | mask);
        else
            setState(dip_stat & ~mask);

        return true;
    }

    return false;
}


/*** Class Cdipswitch END ***/

/**********************
 * Class Cseparateline
 **********************/

Cseparateline::Cseparateline(VisRenderRegion *render_reg, int x, int y, int width, int height)
    : Cui(render_reg, x, y, width, height) {}
    
void Cseparateline::redraw(void)
{
    clear(fg_colour);
    update();
}
/*** Class Cseparateline END ***/
