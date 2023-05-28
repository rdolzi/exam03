/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micropaint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:21:09 by rdolzi            #+#    #+#             */
/*   Updated: 2023/05/28 17:57:49 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micropaint.h"



void    free_matrix(t_map *map)
{
    int i;

    i = -1;
    while (++i < map->height)
        free(map->mat[i]);
    free(map->mat);
}

// legge le n-linee e setta l output in mat
// ritorna 0 se non c è linea da leggere, -1 in caso di errore, 1 se lettura è ok
// expected lines:
// r X Y WIDTH HEIGHT CHAR
// R X Y WIDTH HEIGHT CHAR
int set_pixel(FILE *fd, t_map *map, t_pixel *px)
{
    int res;
    int h;
    int w;
    int i;
    int j;
    px = malloc(sizeof(t_pixel));
    res = fscanf(fd, "%c %d %d %d %d %c \n", &px->r, &px->x_pos, &px->y_pos, &px->width, &px->height, &px->backgroud_char);
    printf(">res:%d\n",res);
    printf(">r:%c\n", px->r);
    if (px->r == '\0')
        return (0);
    printf(">width:%d | height:%d\n", px->width, px->height);
    if (px->width <= 0 || px->height <= 0)
        return (-1);
    printf("PRE>x_pos:%d | y_pos:%d\n", px->x_pos, px->y_pos);
    w = px->x_pos + px->width + 1;
    h = px->y_pos + px->height + 1;
    if (px->x_pos < 0)
        px->x_pos = 0;
    if (px->y_pos < 0)
        px->y_pos = 0;
    printf("POST>x_pos:%d | y_pos:%d\n", px->x_pos, px->y_pos);
    printf(">w:%d | h:%d\n", w, h);
    i = px->y_pos;
    printf(">map->height:%d | map->width:%d\n", map->height, map->width);
    printf("i:%d | h:%d\n", i, h);
    while ((i < h) && (i < map->height))
    {
        printf("qqqq");
        j = px->x_pos;
        while (j < w && j < map->width)
        {
            printf(">i:%d | j:%d\n", i, j);
            map->mat[i][j] = px->backgroud_char;
            j++;
        }
        i++;
    }
    return (res);
}

void    paint(t_map *map)
{
    int i;
    int j;

    i = -1;
    while (++i < map->height)
    {
        j = -1;
        while (++j < map->width)
            write(1, &map->mat[i][j], 1);
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

    res = fscanf(fd, "%d %d %c \n", &map->width, &map->height, &background_char);
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
    printf(">res:%d\n", res);
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
    while (1)
    {
        flag = set_pixel(fd, &map, pixel);
        printf(">flag:%d\n",flag);
        if (flag == 0)
            break;
        if (flag == -1)
        {
            fclose(fd);
            //free(pixel);
            free_matrix(&map);
            open_read_error();
        }
        //free(pixel);
        paint(&map);
    }
    paint(&map);
    fclose(fd);
    free_matrix(&map);
    return (0);
}