#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <libnet.h>

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

// Returns a timestamp in microseconds
uint64_t GetTimeStamp() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * (uint64_t) 1000000 + tv.tv_usec;
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

void draw_border(WINDOW* win){
  int maxY, maxX;
  getmaxyx(win,maxY,maxX);
  attron(COLOR_PAIR(3));
  for(uint i = 0; i < maxX; i++){
    mvprintw(0, i, "@");
    mvprintw(maxY-1, i, "@");
  }
  for(uint i = 0; i < maxY; i++){
    mvprintw(i, 0, "@");
    mvprintw(i, maxX-1, "@");
  }
}

void draw(WINDOW* win, Snake *snake, Coord *apple) {
    clear();
    draw_border(win);
    /* select snake color */
    attron(COLOR_PAIR(1));
    unsigned int i;
    for (i=0;i<snake->body_size;i++) {
        Coord *c = snake->body[i];
        mvprintw(c->y,c->x,"@");
    }
    /* select apple color */
    attron(COLOR_PAIR(2));
    mvprintw(apple->y,apple->x, "@");
    refresh();
}

void add_coord(Coord *coord, Coord *direction) {
    coord->x += direction->x;
    coord->y += direction->y;
}

Coord* rand_coord(WINDOW* win){
    int maxY, maxX;
    getmaxyx(win,maxY,maxX);
    Coord* random_coord = malloc(sizeof(Coord));
    random_coord->x = (rand() % (maxX-2)) + 1;
    random_coord->y = (rand() % (maxY-2)) + 1;
    return random_coord;
}

/* TODO: check realloc succeeded */
void move_snake(WINDOW* win, Snake *snake, Coord *apple, Coord *direction) {
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

    if (current->x == apple->x && current->y == apple->y) {
        // Spawn new apple
        free(apple);
        apple = rand_coord(win);
    } else {
        // You did grow you noob. Resize back
        snake->body[snake->body_size-1] = NULL;
        snake->body_size--;
    }
}


int main() {
    WINDOW* win;
    /*  Initialize ncurses  */
    if ( (win = initscr()) == NULL ) {
      fprintf(stderr, "Error initialising ncurses.\n");
      exit(EXIT_FAILURE);
    }
    start_color();
    noecho();
    /* disable cursor */
    curs_set(0);
    /* turn off delay on getch */
    nodelay(stdscr, TRUE);
    /* colors */
    /* snake color */
    init_pair(1, COLOR_RED, COLOR_RED);
    /* apple color */
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    /* border color */
    init_pair(3, COLOR_BLUE, COLOR_BLUE);
    /* set random seed */
    srand(42);
    /* main loop */
    uint64_t last = GetTimeStamp();

    Snake snake;
    init_snake(&snake);
    Coord* apple = rand_coord(win);
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
        uint64_t newLast = GetTimeStamp();
        if ( newLast - last >= 100000) {
            last = newLast;
            move_snake(win, &snake, apple, &direction);
            draw(win, &snake, apple);
        }
    };

    /* close the ncurses screen */
    endwin();
    return 0;
}
