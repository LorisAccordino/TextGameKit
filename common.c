#include "common.h"

// Funzione per inizializzare il seed del generatore di numeri casuali
void init_random() {
    srand(time(NULL) * getpid()); // Migliora la casualità, moltiplicando il timestamp attuale con il PID
}

// Funzione per generare un numero casuale tra min e max (inclusi)
int generate_random(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Funzione per resettare un vettore di interi
void reset_int_vector(int vector[], int value, int size) {
    memset(vector, value, sizeof(vector[0]) * size);
}

// Funzione per resettare una matrice di interi
void reset_int_array(int *array[], int value, int rows, int cols) {
    memset(array, value, sizeof(array[0][0]) * rows * cols);
}

// Funzione per resettare un vettore di char
void reset_char_vector(char vector[], int value, int size) {
    memset(vector, value, sizeof(vector[0]) * size);
}

// Funzione per resettare una matrice di char
void reset_char_array(char *array[], int value, int rows, int cols) {
    memset(array, value, sizeof(array[0][0]) * rows * cols);
}

// Formatta un punto in una stringa che lo descrive
char* point_to_string(Point to_format) {
    char* format;
    int res = asprintf(&format, "{%d,%d}", to_format.x, to_format.y);
    return res >= 0 ? format : NULL;
}

// Ottiene un punto dalla stringa formattata che lo descrive
Point string_to_point(char* format) {
    Point p;
    if (sscanf(format, "{%d,%d}", &p.x, &p.y) != 2) {
        // Se sscanf non riesce a leggere i valori correttamente, imposta valori di default
        p.x = 0;
        p.y = 0;
    }
    return p;
}
