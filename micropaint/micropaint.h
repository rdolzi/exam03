#ifndef MICRO_PAINT_H
#define MICRO_PAINT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// r può valere: r / R 
typedef struct s_pixel
{
    char    r;
    int     x_pos;
    int     y_pos;   
    int     width;
    int     height;
    char    backgroud_char;
} t_pixel;

typedef struct s_map
{
    char    **mat;
    int     width;
    int     height;
}   t_map;

// stampa errore
void    open_read_error();
// legge la prima linea e setta width/height/background_char (calloc)
// expected line:
// WIDTH HEIGHT BACKGROUND_CHAR
void    set_map(FILE *fd, t_map *map);
// legge le n-linee e setta l output in mat
// ritorna 0 se non c è linea da leggere, -1 in caso di errore, 1 se lettura è ok
// expected lines:
// r X Y WIDTH HEIGHT CHAR
// R X Y WIDTH HEIGHT CHAR
int     set_pixel(FILE *fd, t_map *map, t_pixel *px);
// stampa la matrice in STDOUT
void    paint(t_map *map);
// free della matrice
void    free_matrix(t_map *map);
#endif


// GOAL:
//     Write a program that will read an "operation file" and print the result in the terminal

// ARGUMENTS:
//     1. Your program must take one argument, it will be the path to the "operation file"
//         A.  If 0 or more than 1 argument is given to your program write "Error: argument" followed by a \n in STDOUT

// OPEN/READ FILE:
//     1. If any problem occurs while you open and/or read the "operation file" write "Error: Operation file corrupted" followed by a \n in STDOUT

// OPERATION FILE :
//     1.  The "operation file" will contains lines with one operation per line
//     2.  The lines must be read in order and therefore operations must be executed in the same order
//     3.  There must be one space between each variable in a line
//     4.  The last line can be with or without a \n
//     5.  If a line is incorrect an error occurs.

// OPERATION FILE RULES:

// 1. WIDTH HEIGHT BACKGROUND_CHAR
//     A.This line is ALWAYS the first line of the file and it defines the zone where to draw.
//     B.Your program should not display anything outside the draw zone.

// - WIDTH: must be a int with 0 < WIDTH <= 300, the horizontal number of characters to use for the draw zone
// - HEIGHT: must be a int with 0 < HEIGHT <= 300, the vertical number of characters to use for the draw zone
// - BACKGROUND_CHAR: any empty space will be filled with BACKGROUND_CHAR

// 2. r X Y WIDTH HEIGHT CHAR
//     A.This operation will draw an EMPTY rectangle (where only the border of the rectangle is drawn)

// - r: the character r
// - X: any float, the horizontal position of the top left corner of the rectangle
// - Y: any float, the vertical position of the top left corner of the rectangle
// - WIDTH: a positive float but not 0, the width of the rectangle (horizontal)
// - HEIGHT: a positive float but not 0, the height of the rectangle (vertical)
// - CHAR: the char use to draw the rectangle

// 3. R X Y WIDTH HEIGHT CHAR
//     A.This operation will draw a FILLED rectangle

// - R: the character R
// - X: any float, the horizontal position of the top left corner of the rectangle
// - Y: any float, the vertical position of the top left corner of the rectangle
// - WIDTH: a positive float but not 0, the width of the rectangle (horizontal)
// - HEIGHT: a positive float but not 0, the height of the rectangle (vertical)
// - CHAR: the char use to draw the rectangle

// MAIN RETURN:
//     1. If an error has occured your program must return 1
//     2. If no error has occured it must return 0

// IMPORTANTE: la mappa viene printata solo dopo che tutte le linee vengono lette