/*
 * UI classes used by Visualization component
 *
 * Copyright 2009 ARM Limited. All rights reserved.
 */


#include "components/Visualisation.h"
#include "string.h"


// Constants
enum {
    VIS_FONT_WIDTH = 6,
    VIS_FONT_HEIGHT = 15,
    VIS_LINE_SPACE = 1 ,
    VIS_RED = 0,
    VIS_YELLOW = 1,
    VIS_ORANGE = 2,
    VIS_GREEN = 3,
};


class UIColour {
public:
    uint8_t red, grn, blu;
    UIColour(uint8_t red_=0x00, uint8_t grn_=0x00, uint8_t blu_=0x00) : red(red_), grn(grn_), blu(blu_) {}
};


class UIPos
{
public:
    int x, y;
    UIPos(int x_=0, int y_=0) : x(x_),y(y_) {}
};


class Cui {
public:
    Cui(VisRenderRegion *render_reg, int x, int y, int width, int height) 
        : pos(x, y), size(width, height), rr(render_reg), is_drawn(false)
    {
        setFgColour(0xff, 0xff, 0xff, false); // Default foreground colour is white
        setBgColour(0x00, 0x00, 0x00, false); // Default background colour is black
    }
    
    virtual ~Cui() {}

    inline int getX() const          { return pos.x;  }
    inline int getY() const          { return pos.y;  }
    inline int getWidth(void) const  { return size.x; }
    inline int getHeight(void) const { return size.y; }
    inline int getMaxX() const       { return pos.x + size.x; }
    inline int getMaxY() const       { return pos.y + size.y; }

    inline bool isHit(int x, int y) const
    {
       return (x >= pos.x) && (y >= pos.y) && (x <= getMaxX()) && (y <= getMaxY());
    }

    inline void setWidth(int width)   { size.x = width; }
    inline void setHeight(int height) { size.y = height; }

    inline void setFgColour(uint8_t red, uint8_t grn, uint8_t blu, bool do_redraw=true)
    {
        fg_colour = rr->mapRGB(red, grn, blu);
        if (do_redraw) redraw();
    }

    inline void setBgColour(uint8_t red, uint8_t grn, uint8_t blu, bool do_redraw=true)
    {
        bg_colour = rr->mapRGB(red, grn, blu);
        if (do_redraw) redraw();
    }

    inline void setColours(const UIColour& fg_colour, const UIColour& bg_colour, bool do_redraw=true)
    {
       setFgColour(fg_colour.red, fg_colour.grn, fg_colour.blu, false);
       setBgColour(bg_colour.red, bg_colour.grn, bg_colour.blu, do_redraw);
    }

    virtual void redraw() {}

protected:
    UIPos    pos;         // Absolute position
    UIPos    size;        // Size
    uint32_t fg_colour;   // Foreground colour value
    uint32_t bg_colour;   // Background colour value
    VisRenderRegion* rr;
    bool     is_drawn;

    inline void clear(uint32_t colour)
    {
       rr->fillRect(colour, pos.x, pos.y, size.x, size.y);
    }
    
    inline void update()
    {
       rr->update(pos.x, pos.y, size.x, size.y);
       is_drawn = true;
    }
};

class Clabel : public Cui {
public:
    
    // Initialize with a constant string
    Clabel(VisRenderRegion *render_reg, const char *label, int x, int y);
    // Initialize with a blank string
    Clabel(VisRenderRegion *render_reg, int length, int x, int y);

    ~Clabel() {delete [] str;}
    
    unsigned getLength() const { return length; }

    void setRightJustify(void) { rj = true; }
    void setLeftJustify(void)  { rj = false; }
    void setLabel(const char *label);
    void redraw(void);

protected:
    bool  rj;
    char  *str;
    unsigned length;
    
    void init(const char*);
};


class Cicount : public Clabel{
public:
    Cicount(VisRenderRegion *render_reg, int x, int y, int num_digits_=15);
    
    bool setCount(uint64_t n);

private:
    uint64_t count;
    unsigned num_digits;
};


class Cbutton : public Cui {
public:
    Cbutton(VisRenderRegion *render_reg, int x, int y, int width, 
            int height, bool on_, uint32_t colour_index);
    ~Cbutton(){}
   
    bool setState(bool on_);
    void redraw(void);

private:
    bool  on;
};


class Cled : public Cui {
public:
    Cled(VisRenderRegion *render_reg, int x, int y, unsigned led_num_, uint32_t led_stat_, unsigned led_size_=6);
    
    ~Cled() {}

    bool setState(uint32_t led_stat_);
    void redraw(void);

private:
    unsigned led_num;  // Number of LEDs
    uint32_t led_stat; // LED status
    unsigned led_size; // Width and height of LED (pixels)
    
    void     draw_led(int& offset, bool led_on, uint8_t red, uint8_t grn, uint8_t blu);
};


class Cdipswitch : public Cui {
public:
    Cdipswitch(VisRenderRegion *render_reg, int x, int y, unsigned dip_num_, uint32_t dip_stat_, unsigned dip_size_=4);

    ~Cdipswitch() {};

    bool setState(uint32_t dip_stat_);
    uint32_t getState();
    void redraw(void);
    bool isHit(int x, int y);
    
private:
    unsigned dip_num;  // Number of DIPs
    uint32_t dip_stat; // dipswitch status
    int      dip_size; // Width and height of a single DIP (pixels)
};

class Cseparateline : public Cui {
public:
    Cseparateline(VisRenderRegion *render_reg, int x, int y, int width, int height);

    ~Cseparateline() {};

    void redraw(void);
};
