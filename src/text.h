#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Dichiarazioni di funzioni

char *read_ascii_art_from_file(const char *filename);
char** split_string(const char* str, int* num_lines);

#endif // TEXT_H_INCLUDED
