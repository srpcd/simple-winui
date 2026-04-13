#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <iostream>
#include <windows.h>
#include "..\ui\sidebar.h"

#define BLACK RGB(0, 0, 0)
#define WHITE RGB(255, 255, 255)

struct ButtonId {
    int id;
    RECT rect;
    const char* text;
    const char* fontName;
    int size;
    int weight;
    char status;
    COLORREF bg;
    COLORREF fg;

    COLORREF hoverbg = RGB(220,220,220);
    COLORREF pressbg = RGB(110,110,110);
    COLORREF hoverfg = RGB(0,0,0);
    COLORREF pressfg = RGB(255,255,255);
    bool hoverChange = true;
};

class WindowManager {
    public:
        Sidebar* sidebar = nullptr;

        WindowManager(HINSTANCE, int);
        void mainloop();
        bool hasError();

        void createButton(int, int, int, int, int, const char*, const char*, int, int, COLORREF, COLORREF);
        void displayText(int, int, const char*, HDC&, const char*, int, int);
        void displayTextCenter(int, int, const char*, HDC&, const char*, int, int);
        void deleteFont(HDC&, HFONT);
        HFONT setFont(HDC&, const char*, int, int);
        LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);
        ButtonId* getButtonById(int id);

    private:
        std::vector<ButtonId> buttons;
        int sidebarBtnId;
        int activeBtnId;
        HFONT oldFont;
        HWND hwnd;
        MSG msg;
        bool err;

        void displayButton(ButtonId, HDC&);
        void updateButton(HWND, ButtonId&);
        void setSidebarBtn(int);
        static LRESULT CALLBACK _WndProc(HWND, UINT, WPARAM, LPARAM);
};

#endif
