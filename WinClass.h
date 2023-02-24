#if !defined (WINCLASS_H)
#define WINCLASS_H
//
// (c) Reliable Software, 1997
//

#include "WinString.h"
#include <windows.h>

class WinClassMaker: public WNDCLASSEX
{
public:
    WinClassMaker (WNDPROC WndProc, int idClassName, HINSTANCE hInst);
    WinClassMaker (WNDPROC WndProc, wchar_t const * className, HINSTANCE hInst);
    void SetBgSysColor (int sysColor)
    {
        hbrBackground = (HBRUSH) (sysColor + 1);
    }

	void SetBgBrush (HBRUSH hbr)
	{
		hbrBackground = hbr;
	}

    HWND GetRunningWindow ();

    void SetSysCursor (wchar_t const * id)
    { 
        hCursor = ::LoadCursor (0, id); 
    }
    void SetResCursor (int id) 
    { 
        HCURSOR hCur = ::LoadCursor (hInstance, MAKEINTRESOURCE (id));
        hCursor = hCur; 
    }
	void SetResIcons (int resId);
    void SetDblClicks ()
    {
        style |= CS_DBLCLKS;
    }
    void SetSizeRedraw ()
    {
        // Redraw the whole window every time size changes
        style |= (CS_HREDRAW | CS_VREDRAW);
    }
    void AddExtraLong () { cbWndExtra += 4; }
    void Register ();
private:
	void SetDefaults (WNDPROC wndProc, HINSTANCE hInst);

    ResString	_classString;
};

class TopWinClassMaker: public WinClassMaker
{
public:
    TopWinClassMaker (WNDPROC WndProc, int idClassName, HINSTANCE hInst, int resId);
};

#endif
