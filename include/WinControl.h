#pragma once
#include <Windows.h>
#include "ListView.h"
#include "resource.h"
#include <StringDate.h>
#include <ComboDate.h>
#include <TextDLL.h>


LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
class WinControl
{
	public:
	    WinControl();
		WinControl(HWND hwnd);
		//Create Window
		HWND createWin(HINSTANCE hinst,
			LPCTSTR clsname,
			HWND parent = NULL,
			DWORD dStyle = WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			DWORD dXStyle = 0L,
			int x = 50,
			int y = 50,
			int width = 920,
			int height = 600);

		BOOL showWin(int dCmdShow = SW_SHOWNORMAL);
		static BOOL CALLBACK DlgProc(HWND hwDialog, UINT Message, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

        void SetWindowTitle(LPCTSTR lpszTitle)
        {
            ZeroMemory(szWindowTitle, sizeof(char)*256);
            strcpy(szWindowTitle, lpszTitle);
        };
		operator HWND();
	protected:
		HWND _hwnd;
		char szWindowTitle[256];
};
