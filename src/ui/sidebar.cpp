#include "sidebar.h"
#include "..\window\window.h"

Sidebar::Sidebar() {}

void Sidebar::createSidebarButtons(WindowManager* wm_obj) {
    wm_obj->createButton(1, 0, 45, 175, 40, "Button 1", "Segoe UI", 22, FW_NORMAL, WHITE, BLACK);
    wm_obj->createButton(2, 0, 85, 175, 40, "Button 2", "Segoe UI", 22, FW_NORMAL, WHITE, BLACK);
    wm_obj->createButton(3, 0, 125, 175, 40, "Button 3", "Segoe UI", 22, FW_NORMAL, WHITE, BLACK);
    wm_obj->createButton(4, 0, 165, 175, 40, "Button 4", "Segoe UI", 22, FW_NORMAL, WHITE, BLACK);
    wm_obj->createButton(5, 0, 205, 175, 40, "Button 5", "Segoe UI", 22, FW_NORMAL, WHITE, BLACK);
}


