#include "ui.h"

// Funzione per inizializzare la modalità ncurses
void init_ncurses() {
    initscr();              // Inizializza lo schermo
    start_color();          // Abilita il supporto ai colori
    cbreak();               // Abilita l'input di linea
    noecho();               // Non mostrare i caratteri inseriti
    keypad(stdscr, TRUE);   // Abilita il tasto F1, F2, ecc.
    curs_set(0);            // Nasconde il cursore
}

// Funzione per pulire lo schermo e terminare ncurses
void cleanup_ncurses() {
    endwin();   // Termina ncurses
}

// Funzione per ottenere l'handle della finestra
HWND get_window_handle() {
    return GetConsoleWindow();
}

// Funzione per evitare che la finestra venga ridimensionata
void prevent_window_resize(HWND window) {
    SetWindowLong(window, GWL_STYLE, GetWindowLong(window, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

// Funzione per impostare (limitare a "buffer") le dimensioni
void set_size(int width, int height) {
    resize_term(height, width);
}

// Funzione per impostare un titolo alla console
void set_title(const char *title) {
    SetConsoleTitle(TEXT(title));
}

// Funzioner per impostare dimensione e titolo della finestra in una volta
void set_window(int width, int height, const char* title) {
    set_size(width, height);
    set_title(title);
}

// Funzione per proporre un menu con opzioni
void choice_menu(Point print_xy, MenuItem items[], int item_count, int exit_with_escape, int demanding_refresh_menu) {
    void refresh_menu() {
        int i;
        for (i = 0; i < item_count; i++) {
            mvprintw(print_xy.y + i, print_xy.x, "  << %s >>", items[i].label);
        }

        refresh();
    }

    // Visualizza il menu a schermo
    refresh_menu();

    int index = 0;
    while(1) {
        // Controlla la precedente selezione (retroazione)
        int previous_index = index;

        // Seleziona il nuovo elemento
        mvprintw(print_xy.y + index, print_xy.x, "*");

        // Ottieni l'input dell'utente
        char key = getch();

        // Aggiorna l'indice in base al tasto premuto
        switch (key) {
            case ARROW_UP:
                index = (index - 1 + item_count) % item_count;
                break;
            case ARROW_DOWN:
                index = (index + 1) % item_count;
                break;
            case ENTER:
                // Esegui l'azione in base all'index corrente
                items[index].action();
                // Aggiorna il menu, se richiesto
                if (demanding_refresh_menu) refresh_menu();
                break;
            case ESC:
                // Esci solo se è stato abilitato
                if (exit_with_escape) return;
            default:
                break;
        }

        // Rimuovi la selezione dall'elemento precedentemente selezionato
        if (previous_index != index) mvprintw(print_xy.y + previous_index, print_xy.x, " ");
    }
}

// Funzione per stampare un testo su una sola riga
void print_single_line_text(Point print_xy, const char *text, ...) {
    va_list args;
    va_start(args, text);
    move(print_xy.y, print_xy.x); // Muovi il cursore alla posizione specificata
    vw_printw(stdscr, text, args); // Utilizza vw_printw per stampare utilizzando gli argomenti variabili
    va_end(args);
    refresh();
}

// Funzione per stampare un testo su più righe a schermo, partendo da coordinate arbitrarie
void print_multi_line_text(Point print_xy, char *lines[], int item_count) {
    int i;
    for (i = 0; i < item_count; i++) {
        mvprintw(print_xy.y + i, print_xy.x, "%s", lines[i]);
    }

    refresh();
}

// Funzione per ripulire un'area rettangolare
void clear_rect_area(Point start, Point end) {
    int i;
    char space_row[end.x - start.x + 1]; // Stringa di spazi della lunghezza dell'area

    // Riempie la stringa di spazi
    for (i = 0; i < (end.x - start.x + 1); i++) {
        space_row[i] = ' ';
    }
    space_row[i] = '\0'; // Aggiungi il terminatore di stringa

    // Stampa la stringa di spazi per ogni riga dell'area specificata
    for (i = start.y; i <= end.y; i++) {
        mvprintw(i, start.x, "%s", space_row);
    }

    refresh(); // Aggiorna lo schermo
}

// Funzione per ripulire un area di testo
void clear_text_area(Point start, char *text[], int item_count) {
    int x, y;

    for (y = 0; y < item_count; y++) {
        for (x = 0; x < strlen(text[y]); x++) {
            mvprintw(start.y + y, start.x + x, " ");
        }
    }

    refresh(); // Aggiorna lo schermo
}

// Funzione per ripulire una singola riga
void clear_row(int y) {
    mvprintw(y, 0, "\n");
    refresh(); // Aggiorna lo schermo
}

// Funzione per pulire un range di righe
void clear_row_range(int start_y, int end_y) {
    int y;

    for (y = start_y; y <= end_y; y++) {
        mvprintw(y, 0, "\n");
    }

    refresh(); // Aggiorna lo schermo
}

// Funzione per evidenziare un'area rettangolare
void highlight_rect_area(Point start, Point end, int highlight) {
    int x, y;

    // Se highlight è true, attiva l'attributo di inversione dei colori, altrimenti disattiva
    int attr = highlight ? A_REVERSE : A_NORMAL;

    // Cambia l'attributo dell'area specificata
    for (y = start.y; y <= end.y; y++) {
        for (x = start.x; x <= end.x; x++) {
            mvchgat(y, x, 1, attr, 0, NULL);
        }
    }

    refresh(); // Aggiorna lo schermo
}

// Funzione per evidenziare un'area di testo
void highlight_text_area(Point start, char *text[], int item_count, int highlight) {
    int x, y;

    // Se highlight è true, attiva l'attributo di inversione dei colori, altrimenti disattiva
    int attr = highlight ? A_REVERSE : A_NORMAL;

    // Cambia l'attributo dell'area di testo specificata
    for (y = 0; y < item_count; y++) {
        for (x = 0; x < strlen(text[y]); x++) {
            mvchgat(start.y + y, start.x + x, 1, attr, 0, NULL);
        }
    }

    refresh(); // Aggiorna lo schermo
}

// Funzione per evidenziare un determinato punto
void highlight_point(Point point, int highlight) {
    // Se highlight è true, attiva l'attributo di inversione dei colori, altrimenti disattiva
    int attr = highlight ? A_REVERSE : A_NORMAL;

    // Cambia l'attributo del punto specificato
    mvchgat(point.y, point.x, 1, attr, 0, NULL);
    refresh(); // Aggiorna lo schermo
}

// Funzione per una scelta multipla in linea
int choice_in_line(Point print_xy, const char *prompt, const char *choices[], int num_choices) {
    int choice = 0;
    int i;
    char *format;
    while (1) {
        // Formatta il testo
        mvprintw(print_xy.y, print_xy.x, "%s ", prompt);
        for (i = 0; i < num_choices; i++) {
            if (i == choice) {
                format = "[*]%s ";
            } else {
                format = "[ ]%s ";
            }
            printw(format, choices[i]);
        }
        refresh();

        // Ottieni l'input dell'utente
        char key = getch();

        // Aggiorna l'indice in base al tasto premuto
        switch (key) {
            case ARROW_RIGHT:
                choice = (choice + 1) % num_choices;
                break;
            case ARROW_LEFT:
                choice = (choice - 1 + num_choices) % num_choices;
                break;
            case ENTER:
                mvprintw(print_xy.y, print_xy.x, "\n");
                return choice;
            case ESC:
                mvprintw(print_xy.y, print_xy.x, "\n");
                return -1;
            default:
                break;
        }
    }
}

// Funzione "Premi qualsiasi tasto per continuare"
void any_key_to_continue(Point print_xy, const char *prompt) {
    print_single_line_text(print_xy, prompt);
    getch();
}

// Funzione "Sei sicuro? S/N" per chiedere conferma all'utente
int are_you_sure(Point print_xy, const char *prompt, const char *confirm, const char *cancel) {
    char *choices[] = {confirm, cancel};
    return !choice_in_line(print_xy, prompt, choices, 2);
}

// Funzione di "info" per rendere consapevole l'utente
void info(Point print_xy, const char *prompt, const char *awared) {
    char *choices[] = {awared};
    choice_in_line(print_xy, prompt, choices, 1);
}

// Funzione per stampare un prompt in un punto specifico
void print_prompt(Point print_xy, const char* prompt) {
    mvprintw(print_xy.y, print_xy.x, "%s: ", prompt);
    refresh();
}

// Funzione per chiedere all'utente di inserire un intero
int ask_int(Point print_xy, const char* prompt, int* err) {
    int value;
    print_prompt(print_xy, prompt);
    int res = scanw("%d", &value);
    if (err != NULL) *err = res;
    mvprintw(print_xy.y, print_xy.x, "\n");
    return value;
}

// Funzione per chiedere all'utente di inserire una stringa
char* ask_string(Point print_xy, const char* prompt, int buffer_size) {
    char* buffer = malloc(buffer_size); // Inizializza il puntatore e alloca memoria al buffer

    // Stampa il prompt
    print_prompt(print_xy, prompt);

    // Utilizza snprintf per creare la stringa di formato dinamicamente
    char format[20];
    snprintf(format, sizeof(format), "%%%ds", buffer_size);

    // Utilizza la stringa di formato con scanw per acquisire la stringa
    scanw(format, buffer);

    // Pulisci l'input rimanente nel buffer di input
    //flushinp();

    mvprintw(print_xy.y, print_xy.x, "\n");
    return buffer;
}
