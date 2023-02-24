#if !defined (SPLITTER_H)
#define SPLITTER_H
//
// Reliable Software (c) 1998
//

#include "Win.h"
#include "tools.h"

namespace Splitter
{
	void RegisterClass (HINSTANCE hInst);
	void MakeWindow (HWnd & hwndSplitter /* out */, HWnd hwndParent, int childId);
};

class Pens3d
{
public:
	Pens3d ();
	Pen & Hilight () { return _penHilight; }
	Pen & Light () { return _penLight; }
	Pen & Shadow () { return _penShadow; }
	Pen & DkShadow () { return _penDkShadow; }
private:
	Pen		_penHilight;
	Pen		_penLight;
	Pen		_penShadow;
	Pen		_penDkShadow;
};

class SplitController
{
public:
	SplitController (HWND hwnd, CREATESTRUCT * pCreat);

    HWND Hwnd () const { return _hwnd; }
	void Size (int cx, int cy) {
	  _cx = cx;
	  _cy = cy;
	}
	void Paint ();

    void LButtonDown (POINTS pt);
    void LButtonUp (POINTS pt);
    void LButtonDrag (POINTS pt);
	void CaptureChanged ();
private:
	HWnd	_hwnd;
	HWnd	_hwndParent;

	int		_cx;
	int		_cy;

	int		_dragStart;
	int		_dragX;
	Pens3d	_pens;
};

#endif
