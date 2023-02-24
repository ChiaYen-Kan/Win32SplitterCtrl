//------------------------------------
// main.cpp
// (c) Reliable Software 1996
//------------------------------------

#include "main.h"
#include "resource.h"
#include "Splitter.h"
#include "WinClass.h"
#include "WinMaker.h"

//#include <new.h>

int NewHandler (size_t size);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine, int nCmdShow)
{
//    _set_new_handler (&NewHandler);

    bool isError = false;
    try
    {
        // Create top window class
        TopWinClassMaker topWinClass (WndProcMain, ID_MAIN, hInstance, ID_MAIN);
        topWinClass.Register ();

        // Create child pane classes
        WinClassMaker paneClass (WndProcPane, IDC_PANE , hInstance);
        paneClass.SetSysCursor (IDC_IBEAM);
        paneClass.SetDblClicks ();
        paneClass.Register ();


		Splitter::RegisterClass (hInstance);

        // Create top window
        ResString caption (hInstance, ID_CAPTION);
        TopWinMaker topWin (caption, ID_MAIN, hInstance);
        topWin.Create ();
        topWin.Show (nCmdShow);
    }
    catch (wchar_t const * msg)
    {
        MessageBox (0, msg, L"Error", MB_ICONEXCLAMATION | MB_OK);
        isError = true;
    }
    catch (...)
    {
        MessageBox (0, L"Internal error: Unknown exception", L"Error", MB_ICONEXCLAMATION | MB_OK);
        isError = true;
    }

    if (isError)
        return 0;

    // The main message loop
    MSG  msg;
    while (::GetMessage (&msg, 0, 0, 0 ))
    {
        ::TranslateMessage (&msg);
        ::DispatchMessage (&msg);
    }

    return msg.wParam;
}            

int NewHandler (size_t size)
{
    throw "Internal error: Out of memory";
    return 0;
}


