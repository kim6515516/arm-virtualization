/*
 * 
 *
 * This is an automatically generated file. Do not edit.
 *
 * Copyright 2006 ARM Limited.
 * Copyright 2011 ARM LImited.
 *
 * All rights reserved.
 */

/** \file
 * Class definition for Component PL11x_CLCD.
 */

#ifndef Component_Component__PL11x_CLCD_ClassDef_h_
#define Component_Component__PL11x_CLCD_ClassDef_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <limits.h>
#include <map>
#include <fstream>
#include "SystemGenComponent.h"
#include "CADIBase.h"
#include "ComponentRegister.h"
#include "ResourceAccessFuncTypes.h"
#include "CADIParameterProxy.h"
#include "ParameterFilter.h"
#include "sg/SGTargetInfo.h"
#include "FVP_VE_Cortex_A15x1_DSO.h"

using namespace std;

#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PL11x_CLCD.lisa"

    
        #include "pv/PVBusMaster.h"
        #include "components/Visualisation.h"

        #define PL11x_TRACE if(!0) ; else printf

        // create a mask of with bits s (MSB) to e (LSB) inclusive set
        #define pl11x_mask(s, e) (0xffffffff>>(31-(s)) & (0xffffffff << (e)))
        #define pl11x_bit(b) (1<<(b))

         // timing0
         enum {
            LCD_HBP_MASK  = pl11x_mask(31, 24),
            LCD_HBP_SHIFT = 24,
            LCD_HFP_MASK  = pl11x_mask(23, 16),
            LCD_HFP_SHIFT = 16,
            LCD_HSW_MASK  = pl11x_mask(15,8),
            LCD_HSW_SHIFT = 8,
            LCD_PPL_MASK  = pl11x_mask(7,2),
            LCD_PPL_SHIFT = 2,
            LCD_TIMING0_MASK = (LCD_HBP_MASK|LCD_HFP_MASK|LCD_HSW_MASK|LCD_PPL_MASK)
         };
        // timing1
        enum {
            LCD_VBP_MASK  = pl11x_mask(31,24),
            LCD_VBP_SHIFT = 24,
            LCD_VFP_MASK  = pl11x_mask(23,16),
            LCD_VFP_SHIFT = 16,
            LCD_VSW_MASK  = pl11x_mask(15,10),
            LCD_VSW_SHIFT = 10,
            LCD_LPP_MASK  = pl11x_mask(9,0),
            LCD_LPP_SHIFT = 0,
            LCD_TIMING1_MASK = (LCD_VBP_MASK|LCD_VFP_MASK|LCD_VSW_MASK|LCD_LPP_MASK)
        };
        // timing2
        enum {
            LCD_PCD_HI_MASK = pl11x_mask(31,27),
            LCD_PCD_HI_SHIFT = 27,
            LCD_BCD_MASK  = pl11x_bit(26),
            LCD_BCD_SHIFT = 26,
            LCD_CPL_MASK  = pl11x_mask(25,16),
            LCD_CPL_SHIFT = 16,
            LCD_IEO_MASK  = pl11x_bit(14),
            LCD_IEO_SHIFT = 14,
            LCD_IPC_MASK  = pl11x_bit(13),
            LCD_IPC_SHIFT = 13,
            LCD_IHS_MASK  = pl11x_bit(12),
            LCD_IHS_SHIFT = 12,
            LCD_IVS_MASK  = pl11x_bit(11),
            LCD_IVS_SHIFT = 11,
            LCD_ACB_MASK  = pl11x_mask(10,6),
            LCD_ACB_SHIFT_6,
            LCD_CLKSEL_MASK = pl11x_bit(5),
            LCD_CLKSEL_SHIFT = 5,
            LCD_PCD_LO_MASK = pl11x_mask(4,0),
            LCD_PCD_LO_SHIFT = 0,
            LCD_TIMING2_MASK = (LCD_PCD_HI_MASK|LCD_BCD_MASK|LCD_CPL_MASK|LCD_IEO_MASK| \
                LCD_IPC_MASK|LCD_IHS_MASK|LCD_IVS_MASK|LCD_ACB_MASK| \
                LCD_CLKSEL_MASK|LCD_PCD_LO_MASK)
        };
        // timing3
        enum {
            LCD_LEE_MASK = pl11x_bit(16),
            LCD_LEE_SHIFT  = 16,
            LCD_LED_MASK   = pl11x_mask(6,0),
            LCD_LED_SHIFT  = 0,
            LCD_TIMING3_MASK  = (LCD_LEE_MASK|LCD_LED_MASK)
        };
        // control
        enum {
             LCD_WATERMARK = pl11x_bit(16),
             LCD_VCOMP_MASK = pl11x_mask(13,12),
             LCD_VCOMP_SHIFT = 12,
             LCD_POWER = pl11x_bit(11),
             LCD_BEPO  = pl11x_bit(10),
             LCD_BEBO  = pl11x_bit(9),
             LCD_BGR   = pl11x_bit(8),
             LCD_DUAL  = pl11x_bit(7),
             LCD_MONO8 = pl11x_bit(6),
             LCD_TFT   = pl11x_bit(5),
             LCD_BW    = pl11x_bit(4),
             LCD_BPP_MASK = pl11x_mask(3,1),
             LCD_BPP_SHIFT = 1,
             LCD_ENABLE = pl11x_bit(0)
        };
        // CM_CTRL bits (shifted down)
        enum {
             LCD_CM_N24BIT  = pl11x_bit(11),
             LCD_CM_UDFLIP  = pl11x_bit(9),
             LCD_CM_LRFLIP  = pl11x_bit(8),
             LCD_CM_EN1     = pl11x_bit(7),
             LCD_CM_EN0     = pl11x_bit(6),
             LCD_CM_MUX_MASK = pl11x_mask(5,3),
             LCD_CM_MUX_SHIFT = 3,
             LCD_CM_DIMMER   = pl11x_bit(2),
             LCD_CM_BRIGHTER = pl11x_bit(1),
             LCD_CM_LIGHT    = pl11x_bit(0)
        };
        // Interrupt bits
        enum {
             INT_MBERROR = pl11x_bit(4),
             INT_Vcomp   = pl11x_bit(3),
             INT_LNBU    = pl11x_bit(2),
             INT_FUF     = pl11x_bit(1),
             LCD_INT_MASK = (INT_MBERROR|INT_Vcomp|INT_LNBU|INT_FUF)
        };
        // palette layout - r and b may be swapped by BGR
        enum {
             PAL_RBITS  =  5,
             PAL_ROFF   =  0,
             PAL_GBITS  =  5,
             PAL_GOFF   =  5,
             PAL_BBITS  =  5,
             PAL_BOFF   = 10
        };

        enum {
            CLCDCLK = 1536000
        };

        // ********************
        // CONFIG_PL111 - Start
        // ********************
        // Cursor Control
        enum {
            CRSR_NUM_MASK = pl11x_mask(5,4),
            CRSR_NUM_SHIFT = 4,
            CRSR_ON = pl11x_bit(0)
        };
        // Cursor Configuration
        enum {
            CRSR_FRAME_SYNC = pl11x_bit(1),
            CRSR_SIZE = pl11x_bit(0)
        };
        // Cursor Palette0/1
        enum {
            CRSR_PAL_BLUE_MASK = pl11x_mask(23,16),
            CRSR_PAL_BLUE_SHIFT = 16,
            CRSR_PAL_GREEN_MASK = pl11x_mask(15,8),
            CRSR_PAL_GREEN_SHIFT = 8,
            CRSR_PAL_RED_MASK = pl11x_mask(7,0),
            CRSR_PAL_RED_SHIFT = 0
        };
        // Cursor XY Position
        enum {
            CRSR_Y_EXPAN_MASK = pl11x_mask(27,26),
            CRSR_Y_EXPAN_SHIFT = 26,
            CRSR_Y_MASK = pl11x_mask(25,16),
            CRSR_Y_SHIFT = 16,
            CRSR_X_EXPAN_MASK = pl11x_mask(11,10),
            CRSR_X_EXPAN_SHIFT = 10,
            CRSR_X_MASK = pl11x_mask(9,0),
            CRSR_X_SHIFT = 0
        };
        // Cursor Clip Position
        enum {
            CRSR_CLIPY_MASK = pl11x_mask(13,8),
            CRSR_CLIPY_SHIFT = 8,
            CRSR_CLIPX_MASK = pl11x_mask(5,0),
            CRSR_CLIPX_SHIFT = 0
        };
        // Cursor Interrupt Mask Set/Clear
        enum {
            CRSR_IM = pl11x_bit(0)
        };
        // Cursor Interrupt Clear
        enum {
            CRSR_IC = pl11x_bit(0)
        };
        // Cursor Raw Interrupt Status
        enum {
            CRSR_RIS = pl11x_bit(0)
        };
        // Cursor Masked Interrupt Status
        enum {
            CRSR_MIS = pl11x_bit(0)
        };
        // ******************
        // CONFIG_PL111 - End
        // ******************

        // control register change bits
        enum LCDRegisters
        {
            eLCDTiming0=0,
            eLCDTiming1=1,
            eLCDTiming2=2,
            eLCDTiming3=3,
            eLCDUpbase=4,
            eLCDLpbase=5,
            eLCDControl=7,
            eLCDPalette=8
        };

        // ********************
        // CONFIG_PL111 - Start
        // ********************
        enum  CursorRegisters
        {
            CrsrCtrl=9,
            CrsrConfig=10,
            CrsrPalette0=11,
            CrsrPalette1=12,
            CrsrXY=13,
            CrsrClip=14,
            CrsrIMSC=15,
            CrsrICR=16,
            CrsrRIS=17,
            CrsrMIS=18,
            CrsrIMG=19
        };
        // ******************
        // CONFIG_PL111 - End
        // ******************
        // Gross pixel format. Other differences are handled in the palette
        enum PL11X_PixelFormat
        {
            LB8, BB8, RGB16, BGR16, RGB24, BGR24
        };

        // serializer format (fifo bits -> channels)
        enum PL11X_ChannelFormat
        {
            CF_INDEX, CF_1555, CF_565, CF_444, CF_888
        };

        // Used for producing pixel doubling variants of templated fns
        enum Size
        {
            Single = 1, Double = 2
        };

        class PL11X_Blit_Line {
            public:
            PL11X_Blit_Line()
            {
                crsrWidth = 0;
                crsrHeight = 0;
            }


            // Lookup tables for CLCD 1-16 bit data -> host framebuffer pixel format conversion
            union {
                // Map 1-8 bits of paletized source pixel data onto a number of pixels in a
                // destination format. A 1/2/4/8 bpp source gives 8/4/2/1 pixels output respectively.
                //
                // Structuring it as a array-of-unions means each palette entry takes up exactly 32
                // bytes no matter which dst format we use. This means if we need to fall back to
                // blitting with memcpy we don't need to know the dst format to calculate the address
                // of a run of pixels
                union {
                    uint8_t  dst8[8];
                    uint16_t dst16[8];
                    uint32_t dst32[8];
                } clut_src8[256];

                // Each of the RGB channels of a 16 bit source pixel is gamma converted by passing it
                // through a lookup table. For now, precalculate the table for all 16 bits, and look
                // up destination pixels in that, but might be more efficient (memory locality) to
                // extract the channels and look them up.
                union {
                    uint8_t  dst8;
                    uint16_t dst16;
                    uint32_t dst32;
                } clut_src16[65536];
            };

            uint8_t crsrImageEncoding[32*32*4]; // At 32*32 pixel cursor with at most 32bpp.

            uint8_t crsrMergeLine[32+8];

            // colour components for destination surface channels. Assumes max 32bpp destination format
            uint32_t rcomp[256];
            uint32_t gcomp[256];
            uint32_t bcomp[256];

            uint32_t crsrx;
            uint32_t crsry;
            uint32_t clipx;
            uint32_t clipy;
            uint32_t crsrWidth;
            uint32_t crsrHeight;
            uint32_t crsrnum;

            uint32_t palette0;
            uint32_t palette1;

            uint32_t cx, cy, cw, ch;

            PL11X_PixelFormat *pl11x_pixel_format;
            PL11X_ChannelFormat *pl11x_channel_format;
            VisPixelFormat const *f;
            uint32_t *pixels_per_line;
            uint32_t *pl11x_bpp; // Bits per pixel of the current framebuffer mode
            bool bgr;           // swap b+r channels

            void decodeCursorImage(uint32_t *crsrram)
            {
                // Merge cursor pixels with the pixels from frame
                uint32_t paletteEncoding[4];
                uint32_t m=0;
                for (int i=0; i<256; i++){
                    switch(crsrWidth)
                    {
                    case 32:
                        paletteEncoding[0] = *crsrram++; i++;
                        paletteEncoding[1] = *crsrram++;
                        break;
                    case 64:
                        paletteEncoding[0] = *crsrram++; i++;
                        paletteEncoding[1] = *crsrram++; i++;
                        paletteEncoding[2] = *crsrram++; i++;
                        paletteEncoding[3] = *crsrram++;
                        break;
                    }

                    uint32_t palette = 0;
                    int index = 7;

                    for (int j=0; j<4 && palette<crsrWidth/16; j++)
                    {
                        crsrImageEncoding[m++] = (paletteEncoding[palette] & pl11x_mask(index-j*2, index-j*2-1)) >> (index-j*2-1);

                        if (index == 31 && j == 3) // one palette has 32 bits
                        {
                            index = -1;
                            palette++;
                        }
                        if(j == 3) // using LBBP hence the decoding sequency is bit 7-0, 15-8, 23-16, 31-24
                        {
                            j = -1;
                            index += 8;
                        }
                    }
                }
            }

            // merge the cursor pixel with the src pixel
            // and send the merged pixel to the destination
            // instead of the original src pixel.
            // color   ANDmask  XORmask  Display
            // color0     0      color0    color0
            // color1     0      color1    color1
            //  frame     1        0        Frame
            //  frame     1        1        invert frame
            template<class T> T mergePixel(T srcPixel, uint8_t encoding)
            {
                // using andmask and xormask
                T t = (T)0x0;

                switch(encoding)
                {
                case 0: // Color0
                    t = (T)palette0;
                    break;
                case 1: // Color1
                    t = (T)palette1;
                    break;
                case 2: //Transparent
                    t = srcPixel;
                    break;
                case 3: // Inverted
                    t = srcPixel ^ (T)0xFFFFFFFF;
                    break;
                }

                return t;
            }

            template<Size S, class T, class U> int updatePointers(T** dst, const U** src, uint32_t len,
                uint32_t offset, uint32_t line)
            {
                int crsr_pos = 0;

                // Calculate what's the start merging point and the merging length.
                if (offset == 0 && crsrx<len)
                    crsr_pos = crsrx;
                else if (offset == 0 && crsrx>=len)
                    return 0;
                else if (offset > 0 && crsrx>=offset)
                    crsr_pos = crsrx;
                else if (offset > 0 && crsrx<offset && (crsrx+cw)>=offset)
                    crsr_pos = offset;
                else if (offset > 0 && (crsrx+cw)<offset)
                    return 0;
                else if (offset > 0 && crsrx>=(len+offset))
                    return 0;

                (*dst) += (crsr_pos - offset) * S;

                if (*pl11x_bpp==24)
                    (*src) += (crsr_pos-offset)*4;
                else
                    (*src) += crsr_pos-offset;

                uint32_t merge_len;

                if((crsrx+cw)<(len+offset))
                    merge_len = crsrx+cw-crsr_pos;
                else
                    merge_len = len+offset-crsr_pos;
                // Ensure word alignment
                uint8_t start_offset = crsr_pos%4;
                uint8_t end_offset = (crsr_pos+merge_len)%4;
                end_offset = (end_offset==0)?0:(4-end_offset);

                if (*pl11x_bpp==24)
                    (*src) -= start_offset *4;
                else
                    (*src) -= start_offset;

                (*dst) -= start_offset * S;

                if (crsrWidth == 32)
                {
                    switch(crsrnum)
                    {
                    case 1: crsr_pos += 0x400; break;
                    case 2: crsr_pos += 0x800; break;
                    case 3: crsr_pos += 0xC00; break;
                    }
                }

                crsr_pos += (line-crsry+clipy)*crsrWidth-crsrx+clipx;

                // Prepare cursor merge line
                uint32_t i=0;
                for(;i<start_offset; i++)
                    crsrMergeLine[i] = 2; // Transparent
                for(; i<merge_len+start_offset; i++)
                    crsrMergeLine[i] = crsrImageEncoding[crsr_pos++];
                for(; i<merge_len+start_offset+end_offset; i++)
                    crsrMergeLine[i] = 2; // Transparent;
                merge_len += start_offset + end_offset;

                return merge_len;
            }


            template<Size S, class T, class U> void mergeCursor( T* dst, const U* src,
                uint32_t len)
                {
                for (uint32_t i=0; i<len; i++)
                {
                    switch(*pl11x_pixel_format)
                    {
                    case LB8:
                        *dst++ = mergePixel(*getCLUT8Pixels<T*>(*src++), crsrMergeLine[i]);
                        if (S == Double) { *dst = *(dst-1); dst++; }
                        break;
                    case BB8:
                        {
                            T pixeldata0 = *getCLUT8Pixels<T*>(*src++);
                            T pixeldata1 = *getCLUT8Pixels<T*>(*src++);
                            T pixeldata2 = *getCLUT8Pixels<T*>(*src++);
                            T pixeldata3 = *getCLUT8Pixels<T*>(*src++);

                            *dst++ = mergePixel(pixeldata3, crsrMergeLine[i++]); if (S == Double) { *dst = *(dst-1); dst++; }
                            *dst++ = mergePixel(pixeldata2, crsrMergeLine[i++]); if (S == Double) { *dst = *(dst-1); dst++; }
                            *dst++ = mergePixel(pixeldata1, crsrMergeLine[i++]); if (S == Double) { *dst = *(dst-1); dst++; }
                            *dst++ = mergePixel(pixeldata0, crsrMergeLine[i]);   if (S == Double) { *dst = *(dst-1); dst++; }
                            // TODO: should this final i have a ++?
                        }
                        break;
                    case RGB16:
                    case BGR16:
                        *dst++ = mergePixel( getCLUT16Pixel<T>(*src++), crsrMergeLine[i]);
                        if (S == Double) { *dst = *(dst-1); dst++; }
                        break;
                    case RGB24:
                        {
                            uint32_t bmask = bcomp[*src++];
                            uint32_t gmask = gcomp[*src++];
                            uint32_t rmask = rcomp[*src++];
                            src++; // Skip 4th byte lane
                            T pixeldata = rmask|gmask|bmask;
                            *dst++ = mergePixel(pixeldata, crsrMergeLine[i]);
                            if (S == Double) { *dst = *(dst-1); dst++; }
                        }
                        break;
                    case BGR24:
                        {
                            uint32_t rmask = bcomp[*src++];
                            uint32_t gmask = gcomp[*src++];
                            uint32_t bmask = rcomp[*src++];
                            src++; // Skip 4th byte lane
                            T pixeldata = rmask|gmask|bmask;
                            *dst++ = mergePixel(pixeldata, crsrMergeLine[i]);
                            if (S == Double) { *dst = *(dst-1); dst++; }
                        }
                        break;
                    }
                }
            }

            // templated fast version for known sizes
            template<Size S, class T> T* blit_line_lb8(T* dst, const uint8_t* src, uint32_t src_bytes)
            {
                while (src_bytes > 0)
                {
                    for (int i=0; i<4; ++i)
                    {
                        T pixeldata = *getCLUT8Pixels<T*>(*src++);
                        *dst++ = pixeldata; if (S == Double) { *dst++ = pixeldata; }
                    }
                    src_bytes -= 4;
                }
                return dst;
            }

            template<Size S, class T>  T* blit_line_bb8(T* dst, const uint8_t* src, uint32_t src_bytes)
            {
                while (src_bytes > 0)
                {
                    T pixeldata0 = *getCLUT8Pixels<T*>(*src++);
                    T pixeldata1 = *getCLUT8Pixels<T*>(*src++);
                    T pixeldata2 = *getCLUT8Pixels<T*>(*src++);
                    T pixeldata3 = *getCLUT8Pixels<T*>(*src++);

                    *dst++ = pixeldata3; if (S == Double) { *dst++ = pixeldata3; }
                    *dst++ = pixeldata2; if (S == Double) { *dst++ = pixeldata2; }
                    *dst++ = pixeldata1; if (S == Double) { *dst++ = pixeldata1; }
                    *dst++ = pixeldata0; if (S == Double) { *dst++ = pixeldata0; }
                    src_bytes -= 4;
                }
                return dst;
            }

            template<Size S, class T>  T* blit_line_rgb16(T* dst, const uint16_t* src16, uint32_t src_bytes)
            {
                while (src_bytes > 0)
                {
                    T pixeldata0 = getCLUT16Pixel<T>(*src16++);
                    T pixeldata1 = getCLUT16Pixel<T>(*src16++);
                    *dst++ = pixeldata0; if (S == Double) { *dst++ = pixeldata0; }
                    *dst++ = pixeldata1; if (S == Double) { *dst++ = pixeldata1; }
                    src_bytes -= 4;
                }
                return dst;
            }

            template<Size S, class T>  T* blit_line_rgb24(T* dst, const uint8_t* src, uint32_t src_bytes)
            {
                while (src_bytes > 0)
                {
                    uint32_t rmask = rcomp[*src++];
                    uint32_t gmask = gcomp[*src++];
                    uint32_t bmask = bcomp[*src++];
                    src++; // Skip 4th byte lane
                    T pixeldata = rmask|gmask|bmask;
                    *dst++ = pixeldata; if (S == Double) { *dst++ = pixeldata; }
                    src_bytes -= 4;
                }
                return dst;
            }

            template<Size S, class T>  T* blit_line_bgr24(T* dst, const uint8_t* src, uint32_t src_bytes)
            {
                while (src_bytes > 0)
                {
                    uint32_t rmask = bcomp[*src++];
                    uint32_t gmask = gcomp[*src++];
                    uint32_t bmask = rcomp[*src++];
                    src++; // Skip 4th byte lane
                    T pixeldata = rmask|gmask|bmask;
                    *dst++ = pixeldata; if (S == Double) { *dst++ = pixeldata; }
                    src_bytes -= 4;
                }
                return dst;
            }

            // In 1/2/4 bpp mode, 1 byte of PL11x data  maps onto >1 destination pixel.
            // If pbytes * pixels_per_byte > 4, we need to copy these using memcpy.
            template<Size S> uint8_t*  blit_line_lb8(uint8_t* dst, const uint8_t* src, uint32_t src_bytes, uint32_t dst_bytes)
            {
                while (src_bytes > 0)
                {
                    for (int i=0; i<4; ++i)
                    {
                        uint8_t *pixeldata = getCLUT8Pixels<uint8_t*>(*src++);
                        memcpy(dst, pixeldata, dst_bytes); dst += dst_bytes; if (S == Double) { memcpy(dst, pixeldata, dst_bytes); dst += dst_bytes; }
                    }
                    src_bytes -= 4;
                }
                return dst;
            }

            // In 1/2/4 bpp mode, 1 byte of PL11x data  maps onto >1 destination pixel.
            // If pbytes * pixels_per_byte > 4, we need to copy these using memcpy.
            template<Size S> uint8_t*  blit_line_bb8(uint8_t* dst, const uint8_t* src, uint32_t src_bytes, uint32_t dst_bytes)
            {
                while (src_bytes > 0)
                {
                    uint8_t* pixeldata0 = getCLUT8Pixels<uint8_t*>(*src++);
                    uint8_t* pixeldata1 = getCLUT8Pixels<uint8_t*>(*src++);
                    uint8_t* pixeldata2 = getCLUT8Pixels<uint8_t*>(*src++);
                    uint8_t* pixeldata3 = getCLUT8Pixels<uint8_t*>(*src++);

                    memcpy(dst, pixeldata3, dst_bytes); dst += dst_bytes; if (S == Double) { memcpy(dst, pixeldata3, dst_bytes); dst += dst_bytes; }
                    memcpy(dst, pixeldata2, dst_bytes); dst += dst_bytes; if (S == Double) { memcpy(dst, pixeldata2, dst_bytes); dst += dst_bytes; }
                    memcpy(dst, pixeldata1, dst_bytes); dst += dst_bytes; if (S == Double) { memcpy(dst, pixeldata1, dst_bytes); dst += dst_bytes; }
                    memcpy(dst, pixeldata0, dst_bytes); dst += dst_bytes; if (S == Double) { memcpy(dst, pixeldata0, dst_bytes); dst += dst_bytes; }

                    src_bytes -= 4;
                }
                return dst;
            }

            template <Size S> uint32_t crsrUpdatePointers(uint8_t** dst, const uint8_t** src, uint32_t render_len, uint32_t offset, uint32_t line,
                uint32_t dst_bytes)
            {
                switch(*pl11x_pixel_format)
                {
                case LB8:
                case BB8:
                    switch(dst_bytes)
                    {
                        case 1: return updatePointers<S>(            dst, src, render_len, offset, line); break;
                        case 2: return updatePointers<S>((uint16_t**)dst, src, render_len, offset, line); break;
                        case 4: return updatePointers<S>((uint32_t**)dst, src, render_len, offset, line); break;
                    }
                    break;
                case RGB16:
                case BGR16:
                    switch(dst_bytes)
                    {
                        case 1: return updatePointers<S>(            dst, (const uint16_t**)src, render_len, offset, line); break;
                        case 2: return updatePointers<S>((uint16_t**)dst, (const uint16_t**)src, render_len, offset, line); break;
                        case 4: return updatePointers<S>((uint32_t**)dst, (const uint16_t**)src, render_len, offset, line); break;
                    }
                    break;
                case RGB24:
                case BGR24:
                    switch(dst_bytes)
                    {
                        case 1: return updatePointers<S>(            dst, src, render_len, offset, line); break;
                        case 2: return updatePointers<S>((uint16_t**)dst, src, render_len, offset, line); break;
                        case 4: return updatePointers<S>((uint32_t**)dst, src, render_len, offset, line); break;
                    }
                    break;
                }
                return 0;
            }

            template<Size S> void blit_cursor_line(uint8_t* dst, const uint8_t* src, uint32_t src_bytes, uint32_t dst_bytes)
            {
                switch(*pl11x_pixel_format)
                {
                case LB8:
                case BB8:
                    switch(dst_bytes)
                    {
                        case 1: mergeCursor<S>((uint8_t*) dst, src, src_bytes); break;
                        case 2: mergeCursor<S>((uint16_t*)dst, src, src_bytes); break;
                        case 4: mergeCursor<S>((uint32_t*)dst, src, src_bytes); break;
                    }
                    break;
                case RGB16:
                case BGR16:
                    switch(dst_bytes)
                    {
                        case 1: mergeCursor<S>((uint8_t*) dst, (uint16_t*)src, src_bytes); break;
                        case 2: mergeCursor<S>((uint16_t*)dst, (uint16_t*)src, src_bytes); break;
                        case 4: mergeCursor<S>((uint32_t*)dst, (uint16_t*)src, src_bytes); break;
                    }
                    break;
                case RGB24:
                case BGR24:
                    switch(dst_bytes)
                    {
                        case 1: mergeCursor<S>((uint8_t*) dst, src, src_bytes); break;
                        case 2: mergeCursor<S>((uint16_t*)dst, src, src_bytes); break;
                        case 4: mergeCursor<S>((uint32_t*)dst, src, src_bytes); break;
                    }
                    break;
                }
            }

            // returns the new dst ptr
            template<Size S> uint8_t* blit_line(uint8_t* dst, const uint8_t* src, uint32_t src_bytes, uint32_t dst_bytes)
            {
                switch (*pl11x_pixel_format)
                {
                case LB8:
                    if (src)
                    {
                        switch (dst_bytes)
                        {
                        case 1:  dst = (uint8_t*)blit_line_lb8<S>((uint8_t*) dst, src, src_bytes); break;
                        case 2:  dst = (uint8_t*)blit_line_lb8<S>((uint16_t*)dst, src, src_bytes); break;
                        case 4:  dst = (uint8_t*)blit_line_lb8<S>((uint32_t*)dst, src, src_bytes); break;
                        default: dst =           blit_line_lb8<S>(           dst, src, src_bytes, dst_bytes); break;
                        }
                    } else {
                        dst += dst_bytes * src_bytes;
                    }
                    break;
                case BB8:
                    if (src)
                    {
                        switch (dst_bytes)
                        {
                        case 1:  dst = (uint8_t*)blit_line_bb8<S>((uint8_t*) dst, src, src_bytes); break;
                        case 2:  dst = (uint8_t*)blit_line_bb8<S>((uint16_t*)dst, src, src_bytes); break;
                        case 4:  dst = (uint8_t*)blit_line_bb8<S>((uint32_t*)dst, src, src_bytes); break;
                        default: dst =           blit_line_bb8<S>(           dst, src, src_bytes, dst_bytes); break;
                        }
                    } else {
                        dst += dst_bytes * src_bytes;
                    }
                    break;
                case RGB16:
                case BGR16:
                    if (src)
                    {
                        switch (dst_bytes)
                        {
                        case 1:  dst = (uint8_t*)blit_line_rgb16<S>( (uint8_t*)dst, (uint16_t*)src, src_bytes); break;
                        case 2:  dst = (uint8_t*)blit_line_rgb16<S>((uint16_t*)dst, (uint16_t*)src, src_bytes); break;
                        case 4:  dst = (uint8_t*)blit_line_rgb16<S>((uint32_t*)dst, (uint16_t*)src, src_bytes); break;
                        default: assert(!"Unsupported output format");
                        }
                    } else {
                        dst += dst_bytes * src_bytes/2;
                    }
                    break;
                case RGB24:
                    if (src)
                    {
                        switch (dst_bytes)
                        {
                        case 1:  dst = (uint8_t*)blit_line_rgb24<S>((uint8_t*) dst, src, src_bytes); break;
                        case 2:  dst = (uint8_t*)blit_line_rgb24<S>((uint16_t*)dst, src, src_bytes); break;
                        case 4:  dst = (uint8_t*)blit_line_rgb24<S>((uint32_t*)dst, src, src_bytes); break;
                        default: assert(!"Unsupported output format");
                        }
                    } else {
                        dst += dst_bytes * src_bytes/4;
                    }
                    break;
                case BGR24:
                    if (src)
                    {
                        switch (dst_bytes)
                        {
                        case 1:  dst = (uint8_t*)blit_line_bgr24<S>((uint8_t*) dst, src, src_bytes); break;
                        case 2:  dst = (uint8_t*)blit_line_bgr24<S>((uint16_t*)dst, src, src_bytes); break;
                        case 4:  dst = (uint8_t*)blit_line_bgr24<S>((uint32_t*)dst, src, src_bytes); break;
                        default: assert(!"Unsupported output format");
                        }
                    } else {
                        dst += dst_bytes * src_bytes/4;
                    }
                    break;
                }
                return dst;
            }

            template<typename T> T getCLUT8Pixels(const int i);
            template<typename T> T getCLUT16Pixel(const int i);
        };

        // Specialised accessors to let us access the right destination pixel types in templated fns.

        template<> inline uint8_t*  PL11X_Blit_Line::getCLUT8Pixels<uint8_t*>(const int i)  { return clut_src8[i].dst8; }
        template<> inline uint16_t* PL11X_Blit_Line::getCLUT8Pixels<uint16_t*>(const int i) { return clut_src8[i].dst16; }
        template<> inline uint32_t* PL11X_Blit_Line::getCLUT8Pixels<uint32_t*>(const int i) { return clut_src8[i].dst32; }

        template<> inline uint8_t  PL11X_Blit_Line::getCLUT16Pixel<uint8_t>(const int i)  { return clut_src16[i].dst8; }
        template<> inline uint16_t PL11X_Blit_Line::getCLUT16Pixel<uint16_t>(const int i) { return clut_src16[i].dst16; }
        template<> inline uint32_t PL11X_Blit_Line::getCLUT16Pixel<uint32_t>(const int i) { return clut_src16[i].dst32; }

#line 811 "./Linux-Release-GCC-4.1/gen/Component__PL11x_CLCD_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockSignal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__LCD_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVDevice_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Signal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__TimerCallback_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__TimerControl_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Value_ClassDef.h"



class SimulationEngine;
class ObjectLoader;

using namespace sg::accessfunc;

namespace eslapi
{
    class CADI;
}

namespace FVP_VE_Cortex_A15x1_NMS {

class ParameterFilter_busslave_of_PVBusSlave_to_PL11x_CLCD : public ParameterFilter
{
public:
	ParameterFilter_busslave_of_PVBusSlave_to_PL11x_CLCD()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Addressable range of device (0 means 2^64)",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "0" );
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__PL11x_CLCD: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *busslave;
	sg::ComponentBase *busmaster;
	sg::ComponentBase *timer;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_busslave__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_busmaster__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_timer__;


    // abstract ports
	FVP_VE_Cortex_A15x1__PVDevice device;
	FVP_VE_Cortex_A15x1__PVBus pvbus;
	FVP_VE_Cortex_A15x1__ClockSignal clk_in;
	FVP_VE_Cortex_A15x1__Signal intr;
	FVP_VE_Cortex_A15x1__LCD display;
	FVP_VE_Cortex_A15x1__Value control;
	FVP_VE_Cortex_A15x1__TimerCallback timer_callback_handler;
	FVP_VE_Cortex_A15x1__PVBus pvbus_m;
	FVP_VE_Cortex_A15x1__TimerControl __PL11x_CLCD_internal_1;


    // resources
    std::string application_pathname;


#line 792 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PL11x_CLCD.lisa"

        const uint32_t   pixel_double_limit     ;
        const uint32_t  pl11x_behavior    ;


        pv::StreamingTransactionGenerator* dma;  // memory accessor (dma)

        bool fbuffer_changed;   // true if any changes were detected in the fbuffer
        bool force_redraw;      // force redraw even if source data hasn't changed

        // Packed control registers as written by the programmer
        uint32_t timing0, timing1, timing2, timing3;
        uint32_t upbase, lpbase;
        uint32_t r_control;
        uint32_t palette[128]; // messy representation, decode when it changes
        uint32_t irq_raw;
        uint32_t irq_mask;

        uint32_t reg_changed;  // which of the above registers changed


        // expanded, safe control registers - stable during a frame
        // there are lots more registers but we don't use them all yet

        uint32_t pixels_per_line;
        uint32_t lines_per_panel;
        uint32_t bytes_per_line;

        uint32_t panel_clock_divisor;
        bool   bypass_pcd;
        uint32_t clocks_per_line;

        uint32_t up_base; // upper panel base
        uint32_t lp_base; // lower panel base

        uint32_t vcomp;    // when to generate an interrupt (ignored)

        // pixel colour layout

        bool be_pixel_order;// little/big endian pixel order
        bool be_byte_order; // little/big endian byte order (<16bpp only)
        bool bgr;           // swap b+r channels

        bool lcddual;       // dual panel stn style panel (ignored)
        bool lcdmono8;      // monochrome stn/lcd panel (ignored)
        bool lcdtft;        // colour tft panel (ignored)
        bool lcdbw;         // greyscale panel (ignored)

        uint32_t pl11x_bpp; // bpp code (0-7)

        bool enabled;       // critical - determines if the event runs or not

        uint32_t cm_control;  // core module control bits (>>8)
        uint32_t mux;         // pixel multiplexer control (for pl110 only)

        uint32_t lcd_event;    // timer event for handling video dma+interrupts
        int32_t  event_period; // variable period between lcd events, depends on timing

        uint32_t dst_bytes;    // In the current PL11x colour format, how many bytes of
                               // destination pixels does a single CLUT entry hold?
                               // In 8/16/24 bpp, each CLUT entry will hold 1 destination pixel.
                               // In 4/2/1 bpp, each CLUT entry will hold 2/4/8 destination pixels

        const VisRasterLayout * fdata;  // frame buffer data when locked

        bool pixel_double;               // draw each source pixel as 2x2 dest pixels

        PL11X_PixelFormat    pl11x_pixel_format;   // 8/16/24 bpp + channel order
        PL11X_ChannelFormat  pl11x_channel_format; // bits per channel + offset

        bool palette_changed;        // true if the palette changed
        bool crsr_palette_changed;   // true if the cursor palette changed
        bool colour_format_changed;  // true if any of the colour related registers changed


        PL11X_Blit_Line blit;
        // ********************
        // CONFIG_PL111 - Start
        // ********************
        // Registers
        uint32_t crsr_ram[256];     // CursorImage RAM size 256 x 32 bits
        uint32_t crsr_ctrl;         // ClcdCrsrCtrl
        uint32_t crsr_config;       // ClcdCrsrConfig;
        uint32_t crsr_palette0;     // ClcdCrsrPalette0
        uint32_t crsr_palette1;     // ClcdCrsrPalette1
        uint32_t crsr_xy;           // ClcdCrsrXY
        uint32_t crsr_clip;         // ClcdCrsrClip
        uint32_t crsr_imsc;         // ClcdCrsrIMSC
        uint32_t crsr_icr;          // ClcdCrsrICR
        uint32_t crsr_ris;          // ClcdCrsrRIS
        uint32_t crsr_mis;          // ClcdCrsrMIS

        uint32_t old_crsrx;
        uint32_t old_crsry;
        uint32_t old_clipx;
        uint32_t old_clipy;
        uint32_t old_ch;
        // ******************
        // CONFIG_PL111 - End
        // ******************
    
#line 984 "./Linux-Release-GCC-4.1/gen/Component__PL11x_CLCD_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__PL11x_CLCD(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__PL11x_CLCD();

    // interface functions
    sg::SimulationContext* getSimulationContext() const { return simulationContext__; }

    // control port implementation
    void control_port__configure(const sg::Params& params);
    void control_port__loadApplicationFile(const std::string& filename);
    std::string control_port__getProperty(const std::string& propname);
    std::string control_port__bypass(const std::string&);
    void control_port__run();
    void control_port__stop();
    void control_port__idle();
    void control_port__quit();
    void control_port__getMxDI(std::map<std::string,eslapi::CADI*>*);
    void control_port__setSimulationEngine(SimulationEngine*);
    void control_port__populateCADIMap(std::map< std::string, eslapi::CAInterface* > &, std::string const &);
    void control_port__message(const std::string &msg, sg::message::MessageType msgType);
    std::string control_port__callSimEngine(const std::string&);
    void control_port__reset(int level);
    void control_port__terminate();

    // CADI Port implementations
    eslapi::CADIReturn_t cadiPort__GetParameters(MxU32 startIndex, MxU32 desiredNumOfParams, MxU32 *actualNumOfParams, eslapi::CADIParameterInfo_t *params);
    eslapi::CADIReturn_t cadiPort__GetParameterInfo(const std::string &parameterName, eslapi::CADIParameterInfo_t* param);
    eslapi::CADIReturn_t cadiPort__GetParameterValues (uint32_t parameterCount, uint32_t *actualNumOfParamsRead, eslapi::CADIParameterValue_t *paramValuesOut);
    eslapi::CADIReturn_t cadiPort__SetParameters(uint32_t count, eslapi::CADIParameterValue_t *params, eslapi::CADIFactoryErrorMessage_t *error);
    eslapi::CADIReturn_t cadiPort__GetProperty(const std::string& propertyName, std::string &value);
    void cadiPort__LoadApplicationFile(const std::string& filename);
    void cadiPort__GetApplicationsAndCommandLineParams(std::map<std::string, std::string>&applications2params_);

    // helper functions
    void insertCADIMap__(std::string prefix, std::map< std::string, eslapi::CAInterface*>&componentName2CADI);

    sg::accessfunc::AccessFuncResult parameter_read_func(uint32_t id, int64_t *data);
    sg::accessfunc::AccessFuncResult parameter_read_string_func(uint32_t id, std::string &data);
    sg::accessfunc::AccessFuncResult parameter_write_func(uint32_t id, const int64_t *data);
    sg::accessfunc::AccessFuncResult parameter_write_string_func(uint32_t id, const std::string &data);

    // dummy functions, mostly required by IsimMain (formerly InterpreterMain), will go away soon

    // May be required by TraceGen however that itself is obsolete
    MxU64 getInstructionCount() const { return 0; }
    // May be required by SystemGen however that itself is obsolete
    MxU64 getCycleCount() const { return 0; }

	void init();
	void terminate();
	void reset(int level);
	void update_interrupts();
	void update_registers();
	void update_palette();
	uint32_t updateCrsrPalette(uint32_t palette);
	void update_colour_tables();
	void blit_frame();
	void control_changed();
	uint32_t timer_callback();
	void setCMControl(uint32_t control);
	uint32_t registerRead(uint32_t device_addr);
	void registerWrite(uint32_t device_addr, uint32_t data);
	AccessFuncResult debug_read(uint32_t reg_id, uint64_t* datap, bool side_effects);
	AccessFuncResult debug_write(uint32_t reg_id, const uint64_t* datap, bool side_effects);
	void interconnect();
	void disconnect();
	void update();
	void communicate();
	void traceEndOfCycle();
	void loadApplicationFile(const std::string& filename);
	bool save(MxODataStream& os);
	bool restore(MxIDataStream& is);
	void step();
	pv::Tx_Result abstract_port__device__read(pv::ReadTransaction tx);
	pv::Tx_Result abstract_port__device__write(pv::WriteTransaction tx);
	pv::Tx_Result abstract_port__device__debugRead(pv::ReadTransaction tx);
	pv::Tx_Result abstract_port__device__debugWrite(pv::WriteTransaction tx);
	void abstract_port__control__setValue(uint32_t control);
	uint32_t abstract_port__timer_callback_handler__signal();

    void simHalt();
    void simRun();
    bool simIsRunning();
    void simShutdown();
    void simReset(uint32_t level);


private:
    // methods
    eslapi::CADI* obtainCADI__(const std::string &subcomp, const std::map< std::string, eslapi::CAInterface* > &componentName2CADI) const;
    static bool ForwardParameterValueToSubcomponent(CADIParameterProxy *proxy,
                                                    const char *param_name,
                                                    int64_t intVal,
                                                    const char *strVal);
    uint32_t paramNameToParamAccessFuncID(const std::string &name);

    void reset_resources__();
    void freeCADIResources__();


	ParameterFilter_busslave_of_PVBusSlave_to_PL11x_CLCD parameterFilter_busslave_of_PVBusSlave_to_PL11x_CLCD__;


	CADIParameterProxy *cadiParameterProxy_busslave_of_PVBusSlave_to_PL11x_CLCD__;


    // definition of parameter IDs as constants for use in parameter access functions
	enum
	{
		PARAMETER_ID_pixel_double_limit = 0x1000002B,
		PARAMETER_ID_pl11x_behavior = 0x1000002C,
	};




};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

