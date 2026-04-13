#include "window.h"

WindowManager::WindowManager(HINSTANCE hInstance, int nCmdShow) {
    this->err = 0;
    this->activeBtnId = -1;

    const char CLASS_NAME[] = "SampleUIClass";

    WNDCLASSA wc = {};
    wc.lpfnWndProc = _WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

    if (!RegisterClassA(&wc)) {
        this->err = 1;
        return;
    }

    hwnd = CreateWindowExA(
        0, CLASS_NAME, "Sample UI by srpcd", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, hInstance, this);

    if (!hwnd) {
        this->err = 2;
        return;
    }

    ShowWindow(hwnd, nCmdShow);
}

bool WindowManager::hasError() {
    return (err > 0);
}

ButtonId* WindowManager::getButtonById(int id) {
    for (ButtonId &btn : buttons) {
        if (btn.id == id) {
            return &btn;
        }
    }
    return nullptr;
}

LRESULT CALLBACK WindowManager::_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    WindowManager* window;
    if (msg == WM_NCCREATE) {
        CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
        window = (WindowManager*)cs->lpCreateParams;

        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
        window->hwnd = hwnd;
    }
    else {
        window = (WindowManager*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if (window) {
        return window->WndProc(hwnd, msg, wParam, lParam);
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

