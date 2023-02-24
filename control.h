#if !defined CONTROL_H
#define CONTROL_H
//------------------------------------
//  control.h
//  (c) Reliable Software, 1996
//------------------------------------

#include "Win.h"

class Controller
{

public:
    Controller (HWND hwnd, CREATESTRUCT * pCreat);
    ~Controller ();
    void Size (int cx, int cy);
	void MoveSplitter (int x);

private:

	enum { splitWidth = 8 };	// width of splitter

    // User Interface
    HWnd            _hwnd;          //Main controller window
	HWnd			_leftWin;
    HWnd		    _rightWin;
	HWnd			_splitter;
	int				_cx;
	int				_cy;
	int				_splitRatio;	// in per cent
};

#endif
