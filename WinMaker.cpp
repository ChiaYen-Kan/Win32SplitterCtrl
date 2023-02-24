//
// (c) Reliable Software, 1997
//
#include "WinMaker.h"

WinMaker::WinMaker (int idClassName, HINSTANCE hInst)
  : _hwnd (0),
    _classString (hInst, idClassName),
    _exStyle (0),       // extended window style
    _className (_classString), // pointer to registered class name
    _windowName (0),    // pointer to window name
    _style (WS_OVERLAPPED), // window style
    _x (CW_USEDEFAULT), // horizontal position of window
    _y (0),             // vertical position of window
    _width (CW_USEDEFAULT), // window width  
    _height (0),        // window height
    _hWndParent (0),    // handle to parent or owner window
    _hMenu (0),         // handle to menu, or child-window identifier
    _hInstance (hInst), // handle to application instance
    _data (0)           // pointer to window-creation data
{
}

WinMaker::WinMaker (wchar_t const * className, HINSTANCE hInst)
  : _hwnd (0),
    _exStyle (0),       // extended window style
    _className (className), // pointer to registered class name
    _windowName (0),    // pointer to window name
    _style (WS_OVERLAPPED), // window style
    _x (CW_USEDEFAULT), // horizontal position of window
    _y (0),             // vertical position of window
    _width (CW_USEDEFAULT), // window width  
    _height (0),        // window height
    _hWndParent (0),    // handle to parent or owner window
    _hMenu (0),         // handle to menu, or child-window identifier
    _hInstance (hInst), // handle to application instance
    _data (0)           // pointer to window-creation data
{
}

void WinMaker::SetPosition (int x, int y, int width, int height)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
}

void WinMaker::Create ()
{
    _hwnd = ::CreateWindowEx (
        _exStyle,
        _className,
        _windowName,
        _style,
        _x,
        _y,
        _width,
        _height,
        _hWndParent,
        _hMenu,
        _hInstance,
        _data);

    if (_hwnd == 0)
        throw "Internal error: Window Creation Failed.";
}

void WinMaker::Show (int nCmdShow)
{
    _hwnd.Show (nCmdShow);
    _hwnd.Update ();
}

TopWinMaker::TopWinMaker (wchar_t const * caption, int idClassName, HINSTANCE hInst)
    : WinMaker (idClassName, hInst)
{
    _style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
    _windowName = caption;
}

ChildWinMaker::ChildWinMaker (int idClassName, HWnd hwndParent, int childId)
    : WinMaker (idClassName, hwndParent.GetInstance ())
{
    _style = WS_CHILD;
    _hWndParent = hwndParent;
    _hMenu = (HMENU) childId;
}

ChildWinMaker::ChildWinMaker (wchar_t const * className, HWnd hwndParent, int childId)
    : WinMaker (className, hwndParent.GetInstance ())
{
    _style = WS_CHILD;
    _hWndParent = hwndParent;
    _hMenu = (HMENU) childId;
}

PopupWinMaker::PopupWinMaker (int idClassName, HINSTANCE hInst)
    : WinMaker (idClassName, hInst)
{
    _style = WS_POPUP | WS_VISIBLE;
}

