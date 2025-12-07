#ifndef HAMOOPI_TYPES_COMPAT_H
#define HAMOOPI_TYPES_COMPAT_H

/* 
 * Type Compatibility Layer
 * 
 * This header provides compatibility between Allegro types and abstract types.
 * It allows HAMOOPI.c to continue using BITMAP/FONT while the backend can
 * be implemented with either Allegro or STB.
 */

/* Backend selection */
#ifdef USE_STB_BACKEND
    /* STB backend - use abstract types */
    #include "hamoopi_image.h"
    #include "hamoopi_font.h"
    
    /* Map old types to new types */
    typedef HamoopiImage BITMAP;
    typedef HamoopiFont FONT;
    
#else
    /* Allegro backend - use Allegro types directly */
    #include <allegro.h>
    /* BITMAP and FONT come from allegro.h */
#endif

#endif /* HAMOOPI_TYPES_COMPAT_H */
