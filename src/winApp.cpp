#include "winApp.h"
#include "resource.h"

winApp::winApp(HINSTANCE hInst, LPCTSTR ClsName,
	WNDPROC WndPrc, LPCTSTR MenuName)
{
	_WndClsEx.cbSize = sizeof(WNDCLASSEX);
	_WndClsEx.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	_WndClsEx.lpfnWndProc = WndPrc;
	_WndClsEx.cbClsExtra = 0;
	_WndClsEx.cbWndExtra = 0;
	_WndClsEx.hInstance = hInst;
	_WndClsEx.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON32));
	_WndClsEx.hCursor = LoadIcon(hInst, IDC_ARROW);
	_WndClsEx.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));
	_WndClsEx.lpszMenuName = MenuName;
	_WndClsEx.lpszClassName = ClsName;
	_WndClsEx.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON64));
}
void winApp::registerClass()
{
	RegisterClassEx(&_WndClsEx);
}
void winApp::setBackground(int r,int g,int b)
{
    _WndClsEx.hbrBackground = static_cast<HBRUSH>(CreateSolidBrush(RGB(r, g, b)));
}
