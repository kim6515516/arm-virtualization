/*!
 * \file    Visualisation.h
 * \brief   PV Model GUI Visualisation interface
 * \date    Copyright 2007-2008 ARM Limited. All rights reserved.
 *
 * Abstract interface to the host visualisation implementation.
 * A visualisation instance represents a window which the client
 * can divide into regions, which can be used to display push buttons
 * or client-rendered bitmaps.
 */

#ifndef VISUALISATION_H
#define VISUALISATION_H

#include "sg/SGstdint.h"

// Forward declarations
class Visualisation;
class VisRegion;
class VisPushButtonRegion;
class VisRenderRegion;

/*! An opaque encapsulation of a loaded bitmap. */
class VisBitmap;


/*! Information required to convert pixel data to the target format. */
struct VisPixelFormat
{
    uint32_t rbits, gbits, bbits; //! number of bits per colour channel.
    uint32_t roff, goff, boff;    //! offset within a pixel of colour channel.
    uint32_t pbytes;              //! number of bytes in a pixel.
};

/*! Information required to rasterise pixels into a VisRenderRegion. */
struct VisRasterLayout {
    uint8_t * buffer;      //! start of buffer data.
    uint32_t pitch;       //! BYTE count from one line to the next.
    
    uint32_t width;       //! width of the buffer in pixels.
    uint32_t height;      //! heigh of the buffer in pixels.
    
    VisPixelFormat format; //! pixel format of buffer data.
    
    bool     changed;      //! true if the layout has changed since last lock.
};

/*! Base class for objects that can be displayed in a region of the visualisation display. */
class VisRegion {
    void *id;

 public:
    /*! Clients can simply delete regions when they no longer need them. */
    virtual ~VisRegion() { };

    /*! Give the object a user-defined id. */
    void setId(void *id);

    /*! Retrieve the user-defined id for the object. */
    void *getId();

    /*! Control whether the object is currently visible. */
    virtual void setVisible(bool vis) = 0;

    /*! Change the location and size of the region on the visualisation display. */
    virtual void setLocation(int x, int y,
                             unsigned int width, unsigned int height) = 0;
};

/*! A PushButton represents a three-state (up/rollover/down) bitmap;
 *  when it is pushed/released, it will emit cause the visualisation to emit
 *  KEYDOWN/KEYUP events using the given keycode.
 */
class VisPushButtonRegion : public VisRegion {
 public:
    virtual void setButtonUpImage(VisBitmap *bmpUp) = 0;
    virtual void setButtonDownImage(VisBitmap *bmpDown) = 0;
    virtual void setButtonRollOverImage(VisBitmap *bmpRoll) = 0;
    virtual void setKeyCode(int code) = 0;
};

/*! A RenderRegion represents a region of the display that can be used
 *  to render rasterised pixel data - eg. an LCD display, dynamically
 *  rendered buttons, counters, etc.
 *
 *  To draw graphics, the client should call lock(), which returns
 *  a VisRasterLayout structure, describing the memory location and
 *  pixel layout of the raster buffer.
 *
 *  Once drawing is complete, the client must call unlock(), then
 *  update(), to make the changes visible.
 */
class VisRenderRegion : public VisRegion {
 public:
    /*! Lock the raster buffer, ready for client-side rendering.
     *  This returns a structure that defines the memory-layout of the 
     *  framebuffer.
     *  The client should write new data into the frame buffer, then
     *  call unlock() and update().
     */
    virtual VisRasterLayout const *lock() = 0;

    /*! Unlock the raster buffer; the client must call this after before the
     *  changes can be made visible.
     */
    virtual void unlock() = 0;

    /*! Ensure that any client-drawn changes in the given region get copied to the
     *  screen on (or before) the next call to Visualisation::poll().  This
     *  must be called after calling unlock(), in order to make any changes to
     *  the framebuffer visible.
     */
    virtual void update(int left, int top, unsigned int width, unsigned int height) = 0;

    /*! Draw a line of text onto an unlocked render region.
     *  \return the x co-ordinate at the end of the line of text.
     */
    virtual int writeText(uint32_t fg_colour, uint32_t bg_colour,
                          const char *text,
                          int x, int y) = 0;

    int writeText(uint32_t fg_colour,
                  const char *text,
                  int x, int y) { return writeText(fg_colour, 0x000000, text, x, y); }

    int writeText(const char *text,
                  int x, int y) { return writeText(0xc0c0c0, text, x, y); }

    /*! Get the width of a string of text. */
    virtual int textWidth(const char *text) = 0;

    /*! Render a bitmap onto an unlocked render region. */
    virtual void renderBitmap(VisBitmap *bitmap,
                              int x, int y) = 0;

    /*! Get a pixel value for a 24-bit RGB value. */
    virtual uint32_t mapRGB(unsigned int r,
                            unsigned int g,
                            unsigned int b) = 0;

    /*! Fill a rectangle with a single pixel. */
    virtual void fillRect(uint32_t pixel,
                          int x, int y,
                          unsigned int w, unsigned int h) = 0;
};

/*! The event structure returned by Visualisation::poll(). */
struct VisEvent {
    enum VisEventType
    { 
        None, 
        KEYDOWN, 
        KEYUP, 
        MOUSEBUTTONDOWN, 
        MOUSEBUTTONUP, 
        MOUSEMOTION, 
        QUIT
    };
    
    VisEventType type;// Type of this event
    int keysym;       // Keycode for keydown/up events.
    int rel_x, rel_y; // Mouse motion since last update.
    int abs_x, abs_y; // Absolute location (with respect to render region).
    int button;       // Mouse button for up/down event.
    VisRegion *region;// Region responsible for event.
};

/*! A Visualisation object, encapsulating a display window with a
 *  background bitmap and a number of VisRegions.
 */
class Visualisation {
 public:
    virtual ~Visualisation() {}

    /*! Configure the size and depth of the visualisation window. */
    virtual void configureWindow(unsigned int width, unsigned int height,
                                 unsigned int bit_depth) = 0;

    /*! Create a bitmap image from raw data.  */
    virtual VisBitmap * createImage(unsigned width, unsigned height, uint32_t* raw_rgb) = 0;

    /*! Load a bitmap image from a file.  */
    virtual VisBitmap * loadImage(char const *filename) = 0;

    /*! Load a bitmap image from a file, and specify the RGB value of a color key
     *  that represents transparent pixels in the bitmap.
     */
    virtual VisBitmap * loadImageWithAlphaKey(char const *filename,
                                              unsigned int r, unsigned int g, unsigned int b) = 0;

    /*! Create a new bitmap by cropping an existing one. */
    virtual VisBitmap * cropImage(VisBitmap * in,
                                  int x, int y,
                                  unsigned int width, unsigned int height) = 0;

    /*! Release a client's reference to an image, allowing the memory to 
     *  be released when it is no longer used.  
     *
     *  It is safe for a client to release an image even if the image is
     *  still in use on a button or as the background.
     */
    virtual void releaseImage(VisBitmap *) = 0;

    /*! Set the background for the visualisation window. */
    virtual void setBackground(VisBitmap *background,
                               int x, int y) = 0;

    /*! Create a new VisRenderRegion associated with this window. */
    virtual VisRenderRegion * createRenderRegion() = 0;

    /*! Create a new VisPushButtonRegion associated with this window. */
    virtual VisPushButtonRegion * createPushButtonRegion() = 0;

    /*! Poll the event queue for mouse/key activity; this also
     *  flushes any outstanding display updates. */
    virtual bool poll(VisEvent *event) = 0;

    /*! Lock the mouse into a given region. */
    virtual void lockMouse(VisRegion *region) = 0;

    /*! Unlock the mouse. */
    virtual void unlockMouse() = 0;

    /*! Return true if the user has closed the window. */
    virtual bool hasQuit() = 0;
};

/*! Create a new instance of a visualisation window.
 *  This is currently implemented using SDL, which only allows
 *  one window to be created.
 *
 *  The window may not be displayed until poll() is called.
 */
Visualisation *createVisualisation(char const *cpu = "", char const *title = "CLCD %cpu%");

#endif
