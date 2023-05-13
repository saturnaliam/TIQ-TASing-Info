// update commands

#include <Windows.h>
#include <TlHelp32.h>

void getWindowCoordinates(const HWND &windowHandle, RECT &rect) {
    GetWindowRect(windowHandle, &rect);
}

void getRelativePosition(const HWND &windowHandle, POINT &p) {
    GetCursorPos(&p);
    ScreenToClient(windowHandle, &p);
}