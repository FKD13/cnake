#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

typedef struct {
    int x;
    int y;
} Coord;

typedef struct {
    Coord **body;
    unsigned int body_size;
    unsigned int full_body_size;
    bool alive;
} Snake;

char key_hit(const char key) {
    int chr = getch();
    return chr != ERR && ((char) chr) == key;
}

/* TODO: check if malloc creation has succeeded */
void init_snake(Snake *snake) {
    snake->body = (Coord **) malloc(20*sizeof(Coord *));
    snake->body[0] = malloc(sizeof(Coord));
    snake->body[0]->x = 3;
    snake->body[0]->y = 3;
    snake->body_size = 1;
    snake->full_body_size = 20;
    snake->alive = TRUE;
}

void draw(Snake *snake) {
    clear();
    /* select snake color */
    attron(COLOR_PAIR(1));
    unsigned int i;
    for (i=0;i<snake->body_size;i++) {
        Coord *c = snake->body[i];
        mvprintw(c->y,c->x,"@");
    }
    refresh();
}

void add_coord(Coord *coord, Coord *direction) {
    coord->x += direction->x;
    coord->y += direction->y;
}

/* TODO: check realloc succeeded */
void move_snake(Snake *snake, Coord *direction) {
    if (snake->full_body_size < snake->body_size + 1) {
        snake->body = realloc(snake->body, snake->full_body_size*2*sizeof(Coord));
        snake->full_body_size *= 2;
    }

    snake->body_size += 1;
    unsigned int i;
    for (i=snake->body_size-1;i>0;i--) {
        snake->body[i] = snake->body[i-1];
    }

    Coord *next = snake->body[0];
    Coord *current = malloc(sizeof(Coord));
    current->x = next->x;
    current->y = next->y;
    add_coord(current, direction);
    snake->body[0] = current;
}

int main() {
    /* init the ncurses screen */
    initscr();
    start_color();
    noecho();
    /* disable cursor */
    curs_set(0);
    /* turn off delay on getch */
    nodelay(stdscr, TRUE);
    /* colors */
    /* snake color */
    init_pair(1, COLOR_RED, COLOR_RED);
    /* main loop */
    time_t last;
    last = time(0);

    Snake snake;
    init_snake(&snake);
    Coord direction = (Coord) {1, 0};

    bool running = TRUE;
    while(running) {
        /* handle input */
        int chr = getch();
        if (chr != ERR) {
            char key = (char) chr;
            if (key == 'a') {
                direction = (Coord) {-1, 0};
            } else if (key == 'z') {
                direction = (Coord) {0, -1};
            } else if (key == 'd') {
                direction = (Coord) {1, 0};
            } else if (key == 's') {
                direction = (Coord) {0, 1};
            } else if (key == '\n') {
                running = FALSE;
            }
        }
        /* step when every second */
        if ( difftime(time(0), last) >= 1) {
            last = time(0);
            move_snake(&snake, &direction);
            draw(&snake);
        }
    };

    /* close the ncurses screen */
    endwin();
    return 0;
}
