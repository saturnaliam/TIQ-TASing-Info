// console extras

#include <string>
#include <Windows.h>

// Resets console color
char TM_CL[] = "\e[0m";

// Bright red
char TM_BR[] = "\e[91m";

// Pink-ish Orange
char TM_PO[] = "\e[38;5;223m";

// Pastel Blue
char TM_PB[] = "\e[38;5;111m";

// Pink
char TM_PI[] = "\e[38;5;219m";

// Light Green
char TM_LG[] = "\e[38;5;114m";

// Light Blue
char TM_LB[] = "\e[38;5;117m";

// Move cursor up by 1 row
char TM_MU[] = "\e[A";

void showConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
};


/// @param moveUpLines number of lines to move the console cursor up by
void returnToLine(const int &moveUpLines) {
    for (int i = 1; i <= moveUpLines; i++) {
        printf("%s", TM_MU);
    }

    printf("\r");
}