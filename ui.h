#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include <stdarg.h>
#include "common.h"

// Definizioni di strutture

typedef struct {
    char *label;
    void (*action)();
} MenuItem;


// Dichiarazioni di funzioni

void init_ncurses();
void cleanup_ncurses();
HWND get_window_handle();
void prevent_window_resize(HWND window);
void set_size(int width, int height);
void set_title(const char *title);
void set_window(int width, int height, const char* title);

void choice_menu(Point print_xy, MenuItem items[], int item_count, int exit_with_escape, int demanding_refresh_menu);
void print_single_line_text(Point print_xy, const char *text, ...);
void print_multi_line_text(Point print_xy, char *lines[], int item_count);
void clear_rect_area(Point start, Point end);
void clear_text_area(Point start, char *text[], int item_count);
void clear_row(int y);
void clear_row_range(int start_y, int end_y);
void highlight_rect_area(Point start, Point end, int highlight);
void highlight_text_area(Point start, char *text[], int item_count, int highlight);
void highlight_point(Point point, int highlight);
int choice_in_line(Point print_xy, const char *prompt, const char *choices[], int num_choices);
void any_key_to_continue(Point print_xy, const char *prompt);
int are_you_sure(Point print_xy, const char *prompt, const char *confirm, const char *cancel);
void info(Point print_xy, const char *prompt, const char *awared);
void print_prompt(Point print_xy, const char* prompt);
int ask_int(Point print_xy, const char* prompt, int* err);
char* ask_string(Point print_xy, const char* prompt, int buffer_size);

#endif // UI_H_INCLUDED
