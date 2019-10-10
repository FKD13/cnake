#include <ncurses.h>

typedef struct {
  unsigned int x;
  unsigned int y;
} Coord;

char key_hit(const char *key) {
  int chr = getch();
  return (chr != ERR ) && ((char) chr) == *key;
}

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
