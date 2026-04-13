#include <iostream>
#include <windows.h>

#include "window.h"

#define GET_X_POS (int)(short)LOWORD
#define GET_Y_POS (int)(short)HIWORD

LRESULT WindowManager::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            displayTextCenter(88, 10, "Sidebar", hdc, "Segoe UI", 24, FW_BOLD);

            HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
            RECT windowRect;
            GetClientRect(hwnd, &windowRect);

            RECT lineRect = {175, 0, 177, windowRect.bottom - windowRect.top};
            FillRect(hdc, &lineRect, brush);
            DeleteObject(brush);

            for (ButtonId btn : buttons) {
                displayButton(btn, hdc);
            }

            EndPaint(hwnd, &ps);
            return 0;
        } break;

        case WM_CREATE: {
            sidebar = new Sidebar();
            sidebar->createSidebarButtons(this);
            setSidebarBtn(1);
            return 0;
        } break;

        case WM_MOUSEMOVE: {
            POINT pt = { GET_X_POS(lParam), GET_Y_POS(lParam) };

            for (ButtonId &btn : buttons) {
                bool inside = PtInRect(&btn.rect, pt);

                if (inside) {
                    if (btn.status != 1) {
                        if (btn.status != 2 && btn.hoverChange) {
                            btn.status = 2;
                            updateButton(hwnd, btn);
                        }
                    }
                } else {
                    if (btn.status == 2) {
                        btn.status = 0;
                        updateButton(hwnd, btn);
                    }
                }
            }
            return 0;

        } break;

        case WM_LBUTTONDOWN: {
            POINT pt = { GET_X_POS(lParam), GET_Y_POS(lParam) };

            for (ButtonId &btn : buttons) {
                if (PtInRect(&btn.rect, pt)) {
                    btn.status = 1;
                    activeBtnId = btn.id;

                    updateButton(hwnd, btn);
                }
            }
            return 0;
        } break;

        case WM_LBUTTONUP: {
            POINT pt = { GET_X_POS(lParam), GET_Y_POS(lParam) };

            for (ButtonId &btn : buttons) {
                if (btn.id == activeBtnId) {
                    if (PtInRect(&btn.rect, pt)) {
                        btn.status = 2;

                        setSidebarBtn(btn.id);
                    } else {
                        btn.status = 0;
                    }

                    updateButton(hwnd, btn);
                    break;
                }
            }

            activeBtnId = -1;
            return 0;
        } break;

        case WM_GETMINMAXINFO: {
            MINMAXINFO* mmi = (MINMAXINFO*)lParam;
            mmi->ptMinTrackSize.x = 400;
            mmi->ptMinTrackSize.y = 300;
            return 0;
        } break;

        case WM_DESTROY: {
            delete sidebar;
            PostQuitMessage(0);
            return 0;
        } break;

        case WM_CLOSE: {
            DestroyWindow(hwnd);
            return 0;
        } break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void WindowManager::setSidebarBtn(int id) {
    if (sidebarBtnId == id) {
        getButtonById(id)->status = 0;
        return;
    };
    // int oldActiveId = sidebarBtnId;
    for (ButtonId& btn : buttons) {
        if (btn.id > 5) break;
        if (btn.id == id && btn.fg != WHITE && btn.bg != RGB(70,70,70) && btn.hoverChange) {
            sidebarBtnId = btn.id;
            btn.bg = RGB(70,70,70);
            btn.fg = WHITE;
            btn.status = 0;
            btn.hoverChange = false;
            updateButton(hwnd, btn);
        } else if (btn.fg != BLACK && btn.bg != WHITE && !btn.hoverChange) {
            btn.bg = WHITE;
            btn.fg = BLACK;
            btn.status = 0;
            btn.hoverChange = true;
            updateButton(hwnd, btn);
        }
    }
}

void WindowManager::mainloop() {
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}


