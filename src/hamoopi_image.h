#ifndef HAMOOPI_IMAGE_H
#define HAMOOPI_IMAGE_H

/* Abstract image type - hides implementation details */
typedef struct HamoopiImage HamoopiImage;

/* Image data structure for internal use */
typedef struct {
    int width;
    int height;
    int channels;  /* 1=grayscale, 3=RGB, 4=RGBA */
    unsigned char* pixels;
} ImageData;

/* Image backend interface */
typedef struct ImageBackend {
    /* Image loading/creation */
    HamoopiImage* (*load_image)(const char* filename);
    HamoopiImage* (*create_image)(int width, int height, int channels);
    void (*destroy_image)(HamoopiImage* image);
    
    /* Image properties */
    int (*image_width)(HamoopiImage* image);
    int (*image_height)(HamoopiImage* image);
    
    /* Image operations */
    void (*blit_image)(HamoopiImage* src, HamoopiImage* dest, 
                       int src_x, int src_y, int dest_x, int dest_y, 
                       int width, int height);
    void (*draw_pixel)(HamoopiImage* image, int x, int y, unsigned int color);
    unsigned int (*get_pixel)(HamoopiImage* image, int x, int y);
    
    /* Drawing primitives */
    void (*draw_rect)(HamoopiImage* image, int x1, int y1, int x2, int y2, unsigned int color);
    void (*fill_rect)(HamoopiImage* image, int x1, int y1, int x2, int y2, unsigned int color);
    void (*draw_line)(HamoopiImage* image, int x1, int y1, int x2, int y2, unsigned int color);
    void (*draw_circle)(HamoopiImage* image, int x, int y, int radius, unsigned int color);
    void (*fill_circle)(HamoopiImage* image, int x, int y, int radius, unsigned int color);
    
    /* Color utilities */
    unsigned int (*make_color)(int r, int g, int b, int a);
    
    /* Image saving */
    int (*save_image)(HamoopiImage* image, const char* filename);
} ImageBackend;

#endif /* HAMOOPI_IMAGE_H */
