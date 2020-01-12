#pragma once
#include <Windows.h>
#include "WinControl.h"
class winApp
{
	public:
		winApp(HINSTANCE hInst, LPCTSTR ClasName,
			WNDPROC WndPrc, LPCTSTR MenuName);

		void registerClass();
		void setBackground(int r,int g,int b);

	protected:
		WNDCLASSEX _WndClsEx;
};

