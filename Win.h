#if !defined (WIN_H)
#define WIN_H
//
// Reliable Software (c) 1998
//
#include <windows.h>

class HWnd
{
public:
	HWnd (HWND hwnd) : _hwnd (hwnd) {}
	void Init (HWND hwnd) { _hwnd = hwnd; }
	bool IsEqual (HWND hwnd) const { return _hwnd == hwnd; }
	// Access
	operator HWND () const { return _hwnd; }
	HINSTANCE GetInstance () const
	{ 
		return reinterpret_cast<HINSTANCE> (::GetWindowLongPtr (_hwnd, GWLP_HINSTANCE));
	}
	HWND GetParent () const
	{
		return ::GetParent (_hwnd);
	}
	void SetParent (HWND hwndParent)
	{
		::SetParent (_hwnd, hwndParent);
	}
	// Coordinates
	void ClientToScreen (POINT & pt)
	{
		::ClientToScreen (_hwnd, &pt);
	}
	// Messages
	LRESULT SendMessage (UINT msg, WPARAM wparam = 0, LPARAM lparam = 0) const
	{
		return ::SendMessage (_hwnd, msg, wparam, lparam);
	}
	bool PostMessage (UINT msg, WPARAM wparam = 0, LPARAM lparam = 0) const
	{
		return ::PostMessage (_hwnd, msg, wparam, lparam) != FALSE;
	}
	LRESULT  SendMessageTo (int idChild, UINT msg, WPARAM wparam = 0, LPARAM lparam = 0) const
	{
		return ::SendDlgItemMessage (_hwnd, idChild, msg, wparam, lparam);
	}
	// Focus
  void SetFocus ()
	{ 
		::SetFocus (_hwnd); 
	}
	bool HasFocus () const
	{
		return ::GetFocus () == _hwnd;
	}
	// Mouse capture
	void CaptureMouse ()
	{
		::SetCapture (_hwnd);
	}
	static void ReleaseMouse ()
	{
		::ReleaseCapture ();
	}
	bool HasCapture () const
	{
		return ::GetCapture () == _hwnd;
	}
	// Text/Caption
	void SetText (wchar_t const * text)
	{ 
		::SetWindowText (_hwnd, text); 
	}
	int GetText (wchar_t * buf, int len) const// len includes null
	{ 
		return ::GetWindowText (_hwnd, buf, len); 
	}
	// Font
	void SetFont (HFONT hFont)
	{
		BOOL fRedraw = TRUE;
		SendMessage (WM_SETFONT, (WPARAM)hFont, MAKELPARAM(fRedraw, 0));
	}
	// Visibility
	void Show (int cmdShow = SW_SHOW) 
	{ 
		::ShowWindow (_hwnd, cmdShow); 
	}
	void Hide () 
	{ 
		::ShowWindow (_hwnd, SW_HIDE); 
	}
	void Update () 
	{ 
		::UpdateWindow (_hwnd); 
	}
	// Moving
    void Move (int x, int y, int width, int height)
	{
		::MoveWindow (_hwnd, x, y, width, height, TRUE);
	}
    void MoveDelayPaint (int x, int y, int width, int height)
	{
		::MoveWindow (_hwnd, x, y, width, height, FALSE);
	}
	// Repainting
	void Invalidate ()
	{
		::InvalidateRect (_hwnd, 0, TRUE);
	}
	void Invalidate (RECT const & rect)
	{
		::InvalidateRect (_hwnd, &rect, TRUE);
	}
	void ForceRepaint ()
	{
		Invalidate ();
		Update ();
	}
	// Scrolling
	void Scroll (int xAmount, int yAmount)
	{
		::ScrollWindow (_hwnd, xAmount, yAmount, 0, 0);
	}
	void Scroll (RECT & rect, int xAmount, int yAmount)
	{
		::ScrollWindow (_hwnd, xAmount, yAmount, &rect, 0);
	}
	// Rectangles
	void GetClientRect (RECT & rect)
	{
		::GetClientRect (_hwnd, &rect);
	}
	void GetWindowRect (RECT & rect)
	{
		::GetWindowRect (_hwnd, &rect);
	}
	// Menu
	void AttachMenu (HMENU hMenu)
	{
        if (!::SetMenu (_hwnd, hMenu))
            throw "Internal error: Cannot attach menu.";
	}
private:
	HWND	_hwnd;
};

#endif
