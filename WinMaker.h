#if !defined (WINMAKER_H)
#define WINMAKER_H
//
// (c) Reliable Software, 1997
//

#include "Win.h"
#include "WinString.h"
#include <winuser.h>

class WinMaker
{
public:
    WinMaker (int idClassName, HINSTANCE hInstance);
    WinMaker (wchar_t const * className, HINSTANCE hInstance);
    operator HWND () { return _hwnd; }
    void SetPosition (int x, int y, int width, int height);
	void AddCaption (wchar_t const * caption)
	{
		_windowName = caption;
	}
	void AddSysMenu () { _style |= WS_SYSMENU; }
    void AddVScrollBar () { _style |= WS_VSCROLL; }
    void AddHScrollBar () { _style |= WS_HSCROLL; }
	void AddDlgBorder () { _style |= WS_DLGFRAME; }
	void AddBorder () { _style |= WS_BORDER; }
	void AddTitleBar () { _style |= WS_CAPTION; }
    void Create ();
    void Show (int nCmdShow = SW_SHOWNORMAL);
protected:

    ResString   _classString;
    HWnd        _hwnd;

    DWORD       _exStyle;       // extended window style
    wchar_t const *_className;     // pointer to registered class name
    wchar_t const *_windowName;    // pointer to window name
    DWORD       _style;         // window style
    int         _x;             // horizontal position of window
    int         _y;             // vertical position of window
    int         _width;         // window width  
    int         _height;        // window height
    HWnd        _hWndParent;    // handle to parent or owner window
    HMENU       _hMenu;         // handle to menu, or child-window identifier
    HINSTANCE   _hInstance;     // handle to application instance
    void *      _data;          // pointer to window-creation data
};

class TopWinMaker: public WinMaker
{
public:
    TopWinMaker (wchar_t const * caption, int idClassName, HINSTANCE hInst);
};

class ChildWinMaker: public WinMaker
{
public:
    ChildWinMaker (int idClassName, HWnd hwndParent, int childId);
    ChildWinMaker (wchar_t const * className, HWnd hwndParent, int childId);
};

class PopupWinMaker: public WinMaker
{
public:
    PopupWinMaker (int idClassName, HINSTANCE hInst);
};

// Getting and Setting WindowLong: default is GWL_USERDATA

template <class T>
inline T GetWindowLongPtr(HWND hwnd, int which = GWLP_USERDATA)
{
    return reinterpret_cast<T> (::GetWindowLongPtr (hwnd, which));
}

template <class T>
inline void SetWinLongPtr (HWND hwnd, T value, int which = GWLP_USERDATA)
{
    ::SetWindowLongPtr (hwnd, which, reinterpret_cast<LONG_PTR>(value));
}

#endif
