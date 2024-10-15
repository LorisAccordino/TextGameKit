#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <ncurses.h>
#include "windows.h"


// Definizioni varie

#define _WIN32_WINNT 0x0500

#define ARROW_UP 3
#define ARROW_DOWN 2
#define ARROW_LEFT 4
#define ARROW_RIGHT 5

#define ENTER '\n'
#define ESC 27


// Definizioni di macro di utilità

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#undef ARRAYSIZE


// Definizioni di strutture

typedef struct {
    int x;
    int y;
} Point;


// Dichiarazioni di funzioni

void init_random();
int generate_random(int min, int max);
void reset_int_vector(int vector[], int value, int size);
void reset_int_array(int *array[], int value, int rows, int cols);
void reset_char_vector(char vector[], int value, int size);
void reset_char_array(char *array[], int value, int rows, int cols);
char* point_to_string();
Point string_to_point(char* format);

#endif // COMMON_H_INCLUDED
