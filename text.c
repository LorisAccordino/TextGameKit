#include "text.h"

// Funzione per leggere una ASCII art da un file di testo
char* read_ascii_art_from_file(const char *filename) {
    // Apri il file in modalità di lettura
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL; //Impossibile aprire il file
    }

    // Calcola la dimensione del file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Alloca memoria per la stringa ASCII art
    char *ascii_art = (char *)malloc((file_size + 1) * sizeof(char));
    if (ascii_art == NULL) {
        fclose(file);
        return NULL; // Errore nell'allocazione di memoria
    }

    // Leggi il contenuto del file nella stringa ASCII art
    size_t result = fread(ascii_art, sizeof(char), file_size, file);

    // Aggiungi il terminatore di stringa
    ascii_art[file_size] = '\0';

    // Chiudi il file e restituisci la stringa ASCII art
    fclose(file);
    return ascii_art;
}

// Funzione per separare una stringa "multi riga" in un array di tante stringhe quante le righe
char** split_string(const char* str, int* num_lines) {
    // Conta il numero di righe
    int count = 1;  // Partiamo da 1 perché ci sarà sempre almeno una riga
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == '\n') {
            count++;
        }
    }

    // Alloca memoria per l'array di stringhe
    char** lines = (char**)malloc(count * sizeof(char*));
    if (lines == NULL) {
        *num_lines = 0;
        return NULL;  // Errore di allocazione della memoria
    }

    // Copia le righe nella memoria allocata
    int line_index = 0;
    const char* start = str;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == '\n') {
            // Calcola la lunghezza della riga
            int length = &str[i] - start;
            // Alloca memoria per la riga
            lines[line_index] = (char*)malloc((length + 1) * sizeof(char));
            if (lines[line_index] == NULL) {
                // Errore di allocazione della memoria, dealloca le righe già allocate
                for (int j = 0; j < line_index; ++j) {
                    free(lines[j]);
                }
                free(lines);
                *num_lines = 0;
                return NULL;
            }
            // Copia la riga nella memoria allocata
            strncpy(lines[line_index], start, length);
            lines[line_index][length] = '\0';  // Aggiunge il terminatore di stringa
            // Aggiorna l'indice di partenza per la prossima riga
            start = &str[i + 1];
            line_index++;
        }
    }

    // Gestisci l'ultima riga
    int length = &str[strlen(str)] - start;
    lines[line_index] = (char*)malloc((length + 1) * sizeof(char));
    if (lines[line_index] == NULL) {
        // Errore di allocazione della memoria, dealloca le righe già allocate
        for (int j = 0; j <= line_index; ++j) {
            free(lines[j]);
        }
        free(lines);
        *num_lines = 0;
        return NULL;
    }
    strncpy(lines[line_index], start, length);
    lines[line_index][length] = '\0';

    *num_lines = count;
    return lines;
}
