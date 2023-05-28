/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micropaint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:21:09 by rdolzi            #+#    #+#             */
/*   Updated: 2023/05/28 14:53:22 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// stampa errore
// void    open_read_error();

// legge la prima linea e setta width/height/background_char (malloc)
// void    set_mat(FILE *fd);

// legge le n-linee e setta l output in mat
// ritorna 0 se non c è linea da leggere, -1 in caso di errore, 1 se lettura è ok
// int set_pixel(FILE *fd, char **mat, t_pixel *pixel);

// stampa la matrice in STDOUT
// void    paint(char **mat);

// free della matrice
// void free_matrix(char **mat);


#include "micropaint.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//TO TEST
void    paint(t_map *map)
{
    int i;
    int j;

    i = -1;
    while (++i < map->height)
    {
        j = -1;
        while (++j < map->width)
        {
            write(1, &map->mat[i][j], 1);
            write(1, &" ", 1);
        }
        write(1, &"\n", 1);
    }
}

void open_read_error()
{
    write(1, &"Error: Operation file corrupted\n", 32);
    exit(1);
}

// legge la prima linea e setta width/height/background_char (calloc)
void    set_map(FILE *fd, t_map *map)
{
    int i;
    int j;
    int res;
    char background_char;

    res = fscanf(fd, "%d %d %c", &map->width, &map->height, &background_char);
    if (res == -1 || (map->width <= 0 || map->width > 300) 
    || (map->height <= 0 || map->height > 300))
        open_read_error();
    map->mat = malloc(map->height * sizeof(char *));
    i = -1;
    while (++i < map->height)
        map->mat[i] = calloc(map->width + 1, 1);
    i = -1;
    while (++i < map->height)
    {
        j = -1;
        while (++j < map->width)
            map->mat[i][j] = background_char;
    }
}

// flag values:
//      > 0 se non ce nuova linea
//      > -1 se nuova linea contiene errori
//      > 1 se nuova linea è valida
int main(int argc, char **argv)
{
    FILE *fd;
    t_pixel *pixel;
    t_map   map;
    int flag;

    if (argc != 2)
    {
        write(1, &"Error: argument\n", 16);
        return (1);
    }
    if ((fd = fopen(argv[1], "r")) == NULL)
        open_read_error();
    set_map(fd, &map);
    paint(&map);
    // while (1)
    // {
    //     flag = set_pixel(fd, mat, pixel);
    //     if (flag == 0)
    //         break;
    //     if (flag == -1)
    //         open_read_error();
    //     free(pixel);
    // }
    // paint(mat);
    // free_matrix(mat);
    // fclose(fd);
    return (0);
}