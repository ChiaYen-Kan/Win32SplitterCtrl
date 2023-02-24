//------------------------------------
//  control.cpp
//  (c) Reliable Software, 1996, 97
//------------------------------------

#include "control.h"
#include "resource.h"
#include "message.h"
#include "WinMaker.h"
#include "splitter.h"

LRESULT CALLBACK WndProcPane (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Do-nothing window procedure
    return ::DefWindowProc (hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProcMain (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Controller * pCtrl = GetWindowLongPtr<Controller *> (hwnd);

    switch (message)
    {
    case WM_CREATE:
        try
        {
            pCtrl = new Controller (hwnd, reinterpret_cast<CREATESTRUCT *>(lParam));
            SetWinLongPtr<Controller *> (hwnd, pCtrl);
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
	case MSG_MOVESPLITTER:
		pCtrl->MoveSplitter (wParam);
		return 0;
    case WM_DESTROY:
		SetWinLongPtr<Controller *> (hwnd, 0);
		delete pCtrl;
		return 0;
    }

    return ::DefWindowProc (hwnd, message, wParam, lParam);
}

Controller::Controller (HWND hwnd, CREATESTRUCT * pCreat)
   :
    _hwnd (hwnd),
	_leftWin (0),
	_rightWin (0),
	_splitter (0),
	_splitRatio (50)
{
    // Create child windows
	{
		ChildWinMaker     leftWinMaker (IDC_PANE, _hwnd, ID_LEFT_WINDOW);
		leftWinMaker.Create ();
		_leftWin.Init (leftWinMaker);

		leftWinMaker.Show ();
	}

	{
		ChildWinMaker  rightWinMaker (IDC_PANE, _hwnd, ID_RIGHT_WINDOW);
		rightWinMaker.Create ();
		_rightWin.Init (rightWinMaker);

		rightWinMaker.Show ();
	}

	Splitter::MakeWindow (_splitter, _hwnd, ID_SPLITTER);
}

Controller::~Controller ()
{
    ::PostQuitMessage (0);
}

void Controller::Size (int cx, int cy) 
{
	_cx = cx;
	_cy = cy;
	int xSplit = (_cx * _splitRatio) / 100;
	if (xSplit < 0)
		xSplit = 0;
	_splitter.MoveDelayPaint (xSplit, 0, splitWidth, cy);
	_leftWin.Move (0, 0, xSplit, cy);
    _rightWin.Move (xSplit + splitWidth, 0, cx - xSplit - splitWidth, cy);

	_splitter.ForceRepaint ();
}


void Controller::MoveSplitter (int x)
{
	_splitRatio = x * 100 / _cx;
	if (_splitRatio < 0)
		_splitRatio = 0;
	else if (_splitRatio > 100)
		_splitRatio = 100;
	Size (_cx, _cy);
}


