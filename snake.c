#include <ncurses.h>

typedef struct {
  unsigned int x;
  unsigned int y;
} coord;

int main() {
  /* init the ncurses screen */
  initscr();
  noecho();
  /* turn off delay on getch */
  nodelay(stdscr, TRUE);
  
  getch();
  /* close the ncurses screen */
  endwin();
  return 0;
}
