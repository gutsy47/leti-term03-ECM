#include <dos.h>
#include <stdio.h>
#include <conio.h>

char phrase[100];
int index = 0;

int strlen(char* str) {
    int l = 0;
    while (str[l] != '\0') l++;
    return l;
}

void interrupt (*oldInt09h) (...);

void interrupt newInt09h (...) {
unsigned char keyState = inp(0x60);
if ((keyState & 128) == 0) {
// Ignore key release
putch(phrase[index]);
index = (index + 1) % strlen(phrase);
}
(*oldInt09h)();
}

int main() {
    clrscr();

    // Get string
    printf("Enter a phrase: ");
    gets(phrase);
    if (strlen(phrase) == 0) return -1;

    // Set new interrupt
    oldInt09h = _dos_getvect(0x09);
    _dos_setvect(0x09, newInt09h);

    // Main loop
    printf("Press <ESC> to exit...\n");
    while (1) {
        if (kbhit() && getch() == 27) {
            // Restore old interrupt and exit
            _dos_setvect(0x09, oldInt09h);
            return 0;
        }
    }
}