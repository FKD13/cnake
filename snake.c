#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct {
  unsigned int x;
  unsigned int y;
} Coord;

typedef struct {
  Coord **body;
  unsigned int body_size;
  unsigned int full_body_size;
  bool alive;
} Snake;

char key_hit(const char key) {
  int chr = getch();
  return (chr != ERR ) && ((char) chr) == key;
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
  //refresh();
  //sleep(5);
  clear();
  unsigned int i;
  for (i=0;i<snake->body_size;i++) {
    Coord *c = snake->body[i];
    //printw("\n%d %d,", c->x, c->y); 
    mvprintw(c->y,c->x,"O");
  }
  //printw("%d", snake->body_size);
  refresh();
}

void add_coord(Coord *coord, Coord *direction) {
  coord->x += direction->x;
  coord->y += direction->y;
}

/* TODO: check realloc succeeded */
void move_snake(Snake *snake, Coord *direction) {
  //printw("%d %d,", direction->x, direction->y); 
  if (snake->full_body_size < snake->body_size + 1) {
    snake->body = realloc(snake->body, snake->full_body_size*2*sizeof(Coord));
    snake->full_body_size *= 2;
  }
  
  snake->body_size += 1;
  unsigned int i;
  for (i=snake->body_size-1;i>0;i--) {
    snake->body[i] = snake->body[i-1];
  }
  //for (i=1;i<=snake->body_size;i++) {
  //  tmp = snake->body[i];
  //  snake->body[i] = next;
  //  next = tmp;
  //}
  //snake->body[i] = next;
  
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
  noecho();
  /* disable cursor */
  curs_set(0);
  /* turn off delay on getch */
  nodelay(stdscr, TRUE);
  /* main loop */
  Snake snake;
  init_snake(&snake);

  while(!key_hit('\n')) {
    Coord direction = (Coord) {1, 0};
    move_snake(&snake, &direction);
    //printw("%d", snake.body_size);
    draw(&snake);
    sleep(1);
  };
  
  /* close the ncurses screen */
  endwin();
  return 0;
}
