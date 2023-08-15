#include "block.h"
#include <curses.h>


void init_block()
{
    
    mvaddch(0,70,'#');
    refresh();
}