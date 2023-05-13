#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif  

#include <iostream>
#include <Windows.h>
#include <string>
#include "include/ce.h"
#include "include/gmb.h"
#include "include/uc.h"

const int COORD_OFFSET_X = 8;
const int COORD_OFFSET_Y = 31;

const DWORD FL32SA_OFFSET[8] = { 0xC95B64, 0x24, 0xA8C, 0x4, 0x2C, 0x50, 0x264, 0x4C };

void onExit() {
    printf("%s", TM_CL);
    showConsoleCursor(true);
    system("cls");
}

void initialize() {
    atexit(onExit);
    system("cls");
    showConsoleCursor(false);
    printf(R"(,--------.,--. ,-----.       ,--------. ,---.   ,---.  ,--.                   ,--.         ,---.        
'--.  .--'|  |'  .-.  '      '--.  .--'/  O  \ '   .-' `--',--,--,  ,---.     |  |,--,--, /  .-' ,---.  
   |  |   |  ||  | |  |         |  |  |  .-.  |`.  `-. ,--.|      \| .-. |    |  ||      \|  `-,| .-. | 
   |  |   |  |'  '-'  '-.       |  |  |  | |  |.-'    ||  ||  ||  |' '-' '    |  ||  ||  ||  .-'' '-' ' 
   `--'   `--' `-----'--'       `--'  `--' `--'`-----' `--'`--''--'.`-  /     `--'`--''--'`--'   `---'  
                                                                   `---'                                  )");
    printf("%s\nUse D to exit.\n\n", TM_PO);
}

int main() {
    int scene;

    // Initialization stuff. duh
    initialize();

    // Obtains all necessary information to hook into the program.
    DWORD PID;
    HWND windowHandle = FindWindow(nullptr, L"Adobe Flash Player 32");

    GetWindowThreadProcessId(windowHandle, &PID);
    HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, PID);

    if (processHandle == NULL) {
        returnToLine(2);
        printf("%sProcess not found. Press D to exit.", TM_BR);

        while (processHandle == NULL) {
            if (GetKeyState('D') & 0x8000) break;
        }

        system("exit");
    }

    // Obtains the base address then follows pointer path to obtain the final value.
    DWORD address = getModuleBase(L"flashplayer_32_sa.exe", PID);
    SIZE_T bytesRead;

    printf("%sMemory%s\n", TM_PB, TM_CL);
    printf("Base Address: %s%#x%s\n", TM_LG, address, TM_CL);

    int arrayLength = sizeof(FL32SA_OFFSET)/sizeof(FL32SA_OFFSET[0]);
    for (int i = 0; i < arrayLength; i++) {
        address += FL32SA_OFFSET[i];

        // this code is jank asf
        if (i + 1 == arrayLength) {
            ReadProcessMemory(processHandle, (LPVOID)address, &scene, sizeof(scene), &bytesRead);
        } else {
            ReadProcessMemory(processHandle, (LPVOID)address, &address, sizeof(address), &bytesRead);
        }
        
        printf("Pointer %#d: %s%#x%s [%s%#x%s]\n", i + 1, TM_LG, address, TM_CL, TM_LB, FL32SA_OFFSET[i], TM_CL);
    }

    // Loop that prints
    printf("\n%sGame Data%s\n", TM_PI, TM_CL);

    POINT p;
    RECT rect = {0};
    while (true) {
        // updates the scene variable
        ReadProcessMemory(processHandle, (LPVOID)address, &scene, sizeof(scene), &bytesRead);
        printf("Current Scene: %s%d%s                                         \r\n", TM_PO, scene, TM_CL);

        // finds the current coordinates of the window
        getWindowCoordinates(windowHandle, rect);
        printf("Window Coordinates: %s%d%s, %s%d%s                  \r\n", TM_PO, rect.right, TM_CL, TM_PO, rect.bottom, TM_CL);

        // the position of the cursor relative to the process
        getRelativePosition(windowHandle, p);
        printf("Relative Cursor Position: %s%d%s, %s%d%s                                                              \r\n", TM_PO, p.x, TM_CL, TM_PO, p.y, TM_CL);

        returnToLine(3);

        // breaks when the break key is pressed
        if (GetKeyState('D') & 0x8000) break;
    }           

    CloseHandle(processHandle);
}