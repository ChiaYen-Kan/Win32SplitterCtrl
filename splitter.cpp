//
// Reliable Software (c) 1998
//

#include "splitter.h"
#include "message.h"
#include "Canvas.h"
#include "WinMaker.h"
#include "WinClass.h"

Pens3d::Pens3d ()
:
	_penLight (GetSysColor (COLOR_3DLIGHT)),
	_penHilight (GetSysColor (COLOR_3DHILIGHT)),
	_penShadow (GetSysColor (COLOR_3DSHADOW)),
	_penDkShadow (GetSysColor (COLOR_3DDKSHADOW))
{}

LRESULT CALLBACK WndProcSplitter (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

void Splitter::RegisterClass (HINSTANCE hInst)
{
	WinClassMaker splitterClass (WndProcSplitter, L"RsSplitterClass", hInst);
	splitterClass.SetSysCursor (IDC_SIZEWE);
	splitterClass.SetBgSysColor (COLOR_BTNFACE);
	splitterClass.Register ();
}

void Splitter::MakeWindow (HWnd & hwndSplitter, HWnd hwndParent, int childId)
{
	ChildWinMaker splitterMaker (L"RsSplitterClass", hwndParent, childId);
	splitterMaker.Create ();
	hwndSplitter.Init (splitterMaker);
	splitterMaker.Show ();
}


LRESULT CALLBACK WndProcSplitter (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    SplitController * pCtrl = GetWindowLongPtr<SplitController *> (hwnd);
    switch (message)
    {
    case WM_CREATE:
        try
        {
            pCtrl = new SplitController (hwnd, reinterpret_cast<CREATESTRUCT *>(lParam));
            SetWinLongPtr<SplitController *> (hwnd, pCtrl);
        }
        catch (wchar_t const * msg)
        {
            MessageBox (hwnd, msg, L"Initialization",
                MB_ICONEXCLAMATION | MB_OK);
            return -1;
        }
        catch (...)
        {
            MessageBox (hwnd, L"Unknown Error", L"Initialization",
                MB_ICONEXCLAMATION | MB_OK);
            return -1;
        }
        return 0;
	case WM_SIZE:
		pCtrl->Size (LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_PAINT:
		pCtrl->Paint ();
		return 0;
    case WM_LBUTTONDOWN:
        pCtrl->LButtonDown (MAKEPOINTS (lParam));
        return 0;
    case WM_LBUTTONUP:
        pCtrl->LButtonUp (MAKEPOINTS (lParam));
        return 0;
    case WM_MOUSEMOVE:
        if (wParam & MK_LBUTTON)
            pCtrl->LButtonDrag (MAKEPOINTS (lParam));
        return 0;
	case WM_CAPTURECHANGED:
		pCtrl->CaptureChanged ();
		return 0;
	// Revisit: Abort drag when user presses ESC
    case WM_DESTROY:
        SetWinLongPtr<SplitController *> (hwnd, 0);
        delete pCtrl;
        return 0;
	}
    return DefWindowProc (hwnd, message, wParam, lParam);
}

SplitController::SplitController (HWND hwnd, CREATESTRUCT * pCreat)
    : _hwnd (hwnd), 
	  _hwndParent (pCreat->hwndParent)
{}

void SplitController::Paint ()
{
	PaintCanvas canvas (_hwnd);
	{
		PenHolder pen (canvas, _pens.Light ());
		canvas.Line (0, 0, 0, _cy - 1);
	}
	{
		PenHolder pen (canvas, _pens.Hilight ());
		canvas.Line (1, 0, 1, _cy - 1);
	}
	{
		PenHolder pen (canvas, _pens.Shadow ());
		canvas.Line (_cx - 2, 0, _cx - 2, _cy - 1);
	}
	{
		PenHolder pen (canvas, _pens.DkShadow ());
		canvas.Line (_cx - 1, 0, _cx - 1, _cy - 1);
	}
}

void SplitController::LButtonDown (POINTS pt)
{
    _hwnd.CaptureMouse ();
	// Find x offset of splitter
	// with respect to parent client area
	POINT ptOrg = {0, 0 };
	_hwndParent.ClientToScreen (ptOrg);
	int xParent = ptOrg.x;
	ptOrg.x = 0;
	_hwnd.ClientToScreen (ptOrg);
	int xChild = ptOrg.x;

	_dragStart = xChild - xParent + _cx / 2 - pt.x;

	_dragX = _dragStart + pt.x;

	// Draw a divider using XOR mode
	UpdateCanvas canvas (_hwndParent);
	ModeSetter mode (canvas, R2_NOTXORPEN);
	canvas.Line (_dragX, 0, _dragX, _cy - 1);

}

void SplitController::LButtonDrag (POINTS pt)
{
	// Erase previous divider and draw new one
	UpdateCanvas canvas (_hwndParent);
	ModeSetter mode (canvas, R2_NOTXORPEN);
	canvas.Line (_dragX, 0, _dragX, _cy - 1);
	_dragX = _dragStart + pt.x;
	canvas.Line (_dragX, 0, _dragX, _cy - 1);
}

void SplitController::LButtonUp (POINTS pt)
{
	// Calling ReleaseCapture will send us the WM_CAPTURECHANGED
    _hwnd.ReleaseMouse ();
	_hwndParent.SendMessage (MSG_MOVESPLITTER, _dragStart + pt.x);
}

void SplitController::CaptureChanged ()
{
	// We are losing capture
	// End drag selection -- for whatever reason
	// Erase previous divider
	UpdateCanvas canvas (_hwndParent);
	ModeSetter mode (canvas, R2_NOTXORPEN);
	canvas.Line (_dragX, 0, _dragX, _cy - 1);
}
