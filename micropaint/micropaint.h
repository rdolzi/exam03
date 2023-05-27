#ifndef MICRO_PAINT_H
#define MICRO_PAINT_H

// r può valere: r / R 
typedef struct s_pixel
{
    char    r;
    int     x_pos;
    int     y_pos;   
    int     width;
    int     height;
    char    backgroud;
} t_pixel;

#endif