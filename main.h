#if !defined MAIN_H
#define MAIN_H

#include <windows.h>

LRESULT CALLBACK WndProcMain
   (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProcPane
   (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif