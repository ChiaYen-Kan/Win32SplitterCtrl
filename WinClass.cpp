//
// (c) Reliable Software, 1997
//
#include "WinClass.h"

WinClassMaker::WinClassMaker (WNDPROC wndProc, int idClassName, HINSTANCE hInst)
: _classString (hInst, idClassName)
{
    lpszClassName = _classString;
	SetDefaults (wndProc, hInst);
}

WinClassMaker::WinClassMaker (WNDPROC wndProc, wchar_t const * className, HINSTANCE hInst)
{
    lpszClassName = className;
	SetDefaults (wndProc, hInst);
}

void WinClassMaker::SetDefaults (WNDPROC wndProc, HINSTANCE hInst)
{
    // Provide reasonable default values
    cbSize = sizeof (WNDCLASSEX);
    style = 0;
    lpfnWndProc = wndProc;
    hInstance = hInst;
    hIcon = 0;
    hIconSm = 0;
    lpszMenuName = 0;
    cbClsExtra = 0;
    cbWndExtra = 0;
    hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    hCursor = ::LoadCursor (0, IDC_ARROW);
}

void WinClassMaker::SetResIcons (int resId)
{
    hIcon = ::LoadIcon (hInstance, MAKEINTRESOURCE (resId));
    hIconSm = (HICON)::LoadImage (
        hInstance, 
        MAKEINTRESOURCE (resId), 
        IMAGE_ICON, 
        ::GetSystemMetrics (SM_CXSMICON),
        ::GetSystemMetrics (SM_CYSMICON),
        LR_SHARED);
}

HWND WinClassMaker::GetRunningWindow ()
{
    HWND hwnd = ::FindWindow (lpszClassName, 0);
    if (::IsWindow (hwnd))
    {
        HWND hwndPopup = ::GetLastActivePopup (hwnd);
        if (::IsWindow (hwndPopup))
            hwnd = hwndPopup;
    }
    else 
        hwnd = 0;

    return hwnd;
}

void WinClassMaker::Register ()
{
    if (::RegisterClassEx (this) == 0)
        throw "Internal error: RegisterClassEx failed.";
}

TopWinClassMaker::TopWinClassMaker (WNDPROC wndProc, int idClassName, HINSTANCE hInst, int resId)
: WinClassMaker (wndProc, idClassName, hInst)
{
    style = 0;
	SetResIcons (resId);
    lpszMenuName = MAKEINTRESOURCE (resId);
}


