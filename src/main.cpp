#include <iostream>
#include <windows.h>

#include "main.h"
#include "window/window.h"
// #define DEBUG

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd) {
    #ifdef DEBUG
    setupConsole();
    #endif
    WindowManager window(hInst, nShowCmd);
    if (window.hasError()) return 1;

    window.mainloop();

    return 0;
}

void setupConsole() {
    AllocConsole();
    freopen("conin$", "r", stdin);
    freopen("conout$", "w", stdout);
    freopen("conout$", "w", stderr);
    std::cout.sync_with_stdio();
}
