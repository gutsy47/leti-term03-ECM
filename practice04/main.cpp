#include <iostream.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <bios.h>


#define LEFT  19200
#define RIGHT 19712
#define UP    18432
#define DOWN  20480
#define ESC   283


void printWindow(int x1, int y1, int x2, int y2) {
    // Border window
    clrscr();
    window(x1 - 1, y1 - 1, x2 + 1, y2 + 2);
    textbackground(BLACK);
    textcolor(WHITE);

    // Upper horizontal line
    cprintf("+");
    for (int i = 0; i < x2 - x1 + 1; ++i)
        cprintf("-");
    cprintf("+");

    // Vertical lines
    for (i = 0; i < y2 - y1 + 1; ++i) {
        cprintf("|");
        for (int j = 0; j < x2 - x1 + 1; ++j)
            cprintf(" ");
        cprintf("|");
    }

    // Lower horizontal line
    cprintf("+");
    for (i = 0; i < x2 - x1 + 1; ++i)
        cprintf("-");
    cprintf("+");

    // Active window
    window(x1, y1, x2, y2);
}


int getMode() {
    int ch;
    if (bioskey(1)) {
        ch = bioskey(0);
        if (ch == DOWN)  return 1;
        if (ch == UP)    return 2;
        if (ch == LEFT)  return 3;
        if (ch == RIGHT) return 4;
        if (ch == ESC)   return -1;
    }

    return 0;
}


int main() {
    int x1 = 10, y1 = 15, x2 = 70, y2 = 20;
    int x = (x2 - x1) / 2, y = (y2 - y1) / 2;

    printWindow(x1, y1, x2, y2);
    _setcursortype(_NOCURSOR);

    gotoxy(x, y);
    cprintf("x");

    while (1) {
        int response = getMode();

        while (!bioskey(1)) {
            switch (response) {
                case -1: // Escape
                    return 0;
                case 1: // Down
                    y++;
                    if (y == y2 - y1 + 2) y = 1;
                    break;
                case 2: // Up
                    y--;
                    if (y == 0) y = y2 - y1 + 1;
                    break;
                case 3: // Left
                    x--;
                    if (x == 0) x = x2 - x1 + 1;
                    break;
                case 4: // Right
                    x++;
                    if (x == x2 - x1 + 2) x = 1;
                    break;
                default: // Unknown command
                    continue;
            }

            clrscr();
            gotoxy(x, y);
            cprintf("x");
            delay(100);
        }
    }
}