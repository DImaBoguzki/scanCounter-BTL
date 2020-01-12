#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <StringDate.h>
#include <winApp.h>
#include <WinControl.h>


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR ipCmdLine, int nCmdShow)
{
	MSG messge;
	LPCTSTR className = TEXT("BasicAPP");

	winApp winAplications(hInstance, className, WndProcedure,NULL);
	winAplications.setBackground(120,20,160);
	winAplications.registerClass();

	WinControl Wnd;
	Wnd.SetWindowTitle("Scan Counter");
	Wnd.createWin(hInstance, className);
	Wnd.showWin();

	while (GetMessage(&messge, NULL, 0, 0))
	{
		TranslateMessage(&messge);
		DispatchMessage(&messge);
	}
	return messge.wParam;
}


