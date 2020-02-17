use ncurses::*;

fn main() {
    initscr();
    printw("Hi");
    refresh();
}
