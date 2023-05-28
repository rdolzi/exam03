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

typedef struct s_map
{
    char    **mat;
    int     width;
    int     height;
}   t_map;

#endif