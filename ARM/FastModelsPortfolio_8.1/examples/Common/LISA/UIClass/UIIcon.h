/*
 * UIMonoIcon class used by Visualization component
 *
 * Copyright 2012 ARM Limited. All rights reserved.
 */

#ifndef _UI_ICON_H
#define _UI_ICON_H

#include "components/Visualisation.h"

// Base class does not implememt a visible icon
class UIIcon
{
protected:
    Visualisation*  vis;
    VisBitmap*      image;
    unsigned        width, height;

public:
    UIIcon(Visualisation* vis_, unsigned width_, unsigned height_) :
          vis(vis_), image(0), width(width_), height(height_) {}

    ~UIIcon()
    {
        if (image)
        {
           vis->releaseImage(image);
           image = 0;
        }
    }

    unsigned getWidth() const  { return width;  }
    unsigned getHeight() const { return height; }

    void render(VisRenderRegion* rr, unsigned x, unsigned y)
    {
        rr->renderBitmap(image, x, y);
    }
};


// Monochrome icon (actually two colour!) based on ASCII bitmap data
// space char is background anything else is foreground
class UIMonoIcon : public UIIcon
{
public:
    UIMonoIcon(Visualisation* vis,
               unsigned width_,
               unsigned height_,
               uint32_t fg,
               uint32_t bg,
               const char* bitmap[]) :
        UIIcon(vis, width_, height_)
    {
        uint32_t* raw_rgb = new uint32_t[width * height];

        for(unsigned y=0; y < height; y++)
        {
            for(unsigned x=0; x < width; x++)
            {
                raw_rgb[y*width + x] = (bitmap[y][x] == ' ') ? bg : fg;
            }
        }

        image = vis->createImage(width, height, raw_rgb);

        delete[] raw_rgb;
    }
};


#endif
