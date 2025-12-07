/* Unified Graphics Type Abstraction
 * 
 * This header provides a unified interface for both Allegro and STB backends.
 * It allows HAMOOPI.cpp to work with either backend through compile-time selection.
 */

#ifndef HAMOOPI_UNIFIED_TYPES_H
#define HAMOOPI_UNIFIED_TYPES_H

#ifdef USE_STB_BACKEND
    /* STB Backend - Use abstract types */
    #include "hamoopi_image.h"
    #include "hamoopi_font.h"
    
    /* Define BITMAP as an alias for HamoopiImage */
    typedef struct HamoopiImage BITMAP;
    typedef struct HamoopiFont FONT;
    
    /* Define SAMPLE and MIDI as opaque types for now */
    typedef struct HamoopiSample SAMPLE;
    typedef struct HamoopiMidi MIDI;
    
    /* Bitmap field accessors as macros */
    #define BITMAP_W(bmp) hamoopi_image_width((HamoopiImage*)(bmp))
    #define BITMAP_H(bmp) hamoopi_image_height((HamoopiImage*)(bmp))
    
    /* Helper functions to get width/height */
    static inline int hamoopi_bitmap_width(BITMAP* bmp) {
        extern ImageBackend* get_stb_image_backend(void);
        return get_stb_image_backend()->image_width((HamoopiImage*)bmp);
    }
    
    static inline int hamoopi_bitmap_height(BITMAP* bmp) {
        extern ImageBackend* get_stb_image_backend(void);
        return get_stb_image_backend()->image_height((HamoopiImage*)bmp);
    }
    
#else
    /* Allegro Backend - Use Allegro types directly */
    #include <allegro.h>
    
    /* For Allegro, just use the struct fields directly */
    #define BITMAP_W(bmp) ((bmp)->w)
    #define BITMAP_H(bmp) ((bmp)->h)
    
    static inline int hamoopi_bitmap_width(BITMAP* bmp) {
        return bmp ? bmp->w : 0;
    }
    
    static inline int hamoopi_bitmap_height(BITMAP* bmp) {
        return bmp ? bmp->h : 0;
    }
#endif

#endif /* HAMOOPI_UNIFIED_TYPES_H */
