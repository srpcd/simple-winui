#include <iostream>
#include <windows.h>

#include "window.h"

void WindowManager::displayText(int x, int y, const char* text, HDC &hdc, const char* fontName, int size, int weight) {
    HFONT font = setFont(hdc, fontName, size, weight);

    TextOutA(hdc, x, y, text, strlen(text));
    deleteFont(hdc, font);
}

void WindowManager::displayTextCenter(int x, int y, const char* text, HDC &hdc, const char* fontName, int size, int weight) {
    HFONT font = setFont(hdc, fontName, size, weight);

    SIZE textSize;
    GetTextExtentPoint32A(hdc, text, strlen(text), &textSize);
    x -= textSize.cx / 2;

    TextOutA(hdc, x, y, text, strlen(text));
    deleteFont(hdc, font);
}

void WindowManager::updateButton(HWND hwnd, ButtonId& btn) {
    HDC hdc = GetDC(hwnd);
    displayButton(btn, hdc);
    ReleaseDC(hwnd, hdc);
}

void WindowManager::displayButton(ButtonId id, HDC &hdc) {
    HBRUSH brush = CreateSolidBrush(id.status == 1 ? id.pressbg : (id.status == 2 ? id.hoverbg : id.bg));
    FillRect(hdc, &id.rect, brush);
    DeleteObject(brush);

    HFONT font = setFont(hdc, id.fontName, id.size, id.weight);

    int bkMode = SetBkMode(hdc, TRANSPARENT);
    COLORREF bkColor = SetTextColor(hdc, id.status == 1 ? id.pressfg : (id.status == 2 ? id.hoverfg : id.fg));

    DrawTextA(hdc, id.text, -1, &id.rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    SetBkMode(hdc, bkMode);
    SetTextColor(hdc, bkColor);
    deleteFont(hdc, font);
}

HFONT WindowManager::setFont(HDC &hdc, const char* fontName, int size, int weight) {
    HFONT hFont = CreateFontA(
        size, 0, 0, 0, weight, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, fontName
    );
    oldFont = (HFONT)SelectObject(hdc, hFont);
    return hFont;
}

void WindowManager::deleteFont(HDC &hdc, HFONT hFont) {
    SelectObject(hdc, oldFont);
    DeleteObject(hFont);
}

void WindowManager::createButton(int id, int x, int y, int width, int height, const char* text, const char* fontName, int size, int weight,
                                 COLORREF bg, COLORREF fg) {
    buttons.push_back({id, {x, y, x+width, y+height}, text, fontName, size, weight, 0, bg, fg});
}
