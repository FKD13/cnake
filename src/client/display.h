#ifndef CNAKE_DISPLAY_H
#define CNAKE_DISPLAY_H

#include <caca.h>

struct display {
    caca_display_t *display;
    caca_canvas_t *canvas;
};

typedef struct display display_t;

int init_display(display_t *dp);
void free_display(display_t *dp);

#endif //CNAKE_DISPLAY_H
