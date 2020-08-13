#include "display.h"

int init_display(display_t *dp) {
    dp->display = caca_create_display(NULL);
    if (!dp->display) { return -1; }
    dp->canvas = caca_get_canvas(dp->display);
    return 0;
}

void free_display(display_t *dp) {
    caca_free_display(dp->display);
    dp->display = NULL;
    dp->canvas = NULL;
}