#include "WinControl.h"
#include "tools.h"
#include "mexcel.h"
WinControl::WinControl()
{
	_hwnd = NULL;
}
WinControl::WinControl(HWND hwnd) : _hwnd(hwnd){}

WinControl::operator HWND()
{
	return _hwnd;
}
HWND WinControl::createWin(HINSTANCE hinst, LPCTSTR clsname, HWND parent, DWORD dStyle, DWORD dXStyle,
	int x, int y, int width, int height)
{
	_hwnd = CreateWindowEx(dXStyle, clsname, this->szWindowTitle, dStyle, x, y, width,
		height, parent, NULL, hinst, NULL);

	if (_hwnd != NULL)
		return _hwnd;
	return NULL;
}

BOOL WinControl::showWin(int dCmdShow)
{
	if (ShowWindow(_hwnd, dCmdShow) && UpdateWindow(_hwnd))
		return TRUE;
	return FALSE;

}
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hwButtonToday,hwButtonGET,hwButtonTest;
    static ListView *_list;
    static ListView *_listAverage;
    static FILE *f;
    static miniexcel::CMiniExcel miniexcel;
    static bool buttonToday = false;
    static ComboDate comboDate;
    static int year=-1;
    static int month=-1;
    static int day=-1;
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
	switch (Msg)
	{
    case WM_CREATE:
    {
        hwButtonToday=CreateWindowEx(0,"BUTTON","אתמול",WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                700,50,195,60,hWnd,NULL,(HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),NULL);
        hwButtonGET=CreateWindowEx(0,"BUTTON","משוך",WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                300,520,60,27,hWnd,NULL,(HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),NULL);
        hwButtonTest=CreateWindowEx(0,"BUTTON","test",WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                700,200,195,60,hWnd,NULL,(HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),NULL);
        comboDate.create(hWnd,60,520);
        EnableWindow(comboDate.getHWday(),false);
        _list = new ListView(60,50,615,420);
        _list->show(hWnd);
        _list->registerColumens();

        _list->setStyle();
        _list->addColumns(80,"תאריך");
        miniexcel(0,0)=TEXT("Date");
        _list->addColumns(80,"משמרת");
        miniexcel(0,1)="Shift";
        _list->addColumns(90,"IB-354");
        miniexcel(0,2)="IB-354";
        _list->addColumns(90,"SGA-1592");
        miniexcel(0,3)="SGA-1592";
        _list->addColumns(90,"SGA-2301");
        miniexcel(0,4)="SGA-2301";
        _list->addColumns(90,"SGA-2049");
        miniexcel(0,5)="SGA-2049";
        _list->addColumns(90,"BLAZER 008");
        miniexcel(0,6)="BLAZER 008";
        _list->registerRows();
        break;
    }
    case WM_COMMAND:
    {
        if(HIWORD(wParam) == CBN_SELCHANGE && comboDate.getHWday() != (HWND)lParam)
        {
            if(month!=-1 && year!=-1)
                comboDate.clearDayCombo(comboDate.getEndMonth(month,year));
            if(comboDate.getHWyear() == (HWND)lParam)
                year=comboDate.getYear();
            if(comboDate.getHWmonth() == (HWND)lParam)
                month=comboDate.getMonth();
            if(month==-1 || month==-1)
            {
                EnableWindow(comboDate.getHWday(),false);
            }
            else
            {
                EnableWindow(comboDate.getHWday(),true);
                SetFocus(comboDate.getHWday());
            }
            break;
        }
        else if(HIWORD(wParam) == CBN_SELCHANGE && comboDate.getHWday() == (HWND)lParam)
            day=comboDate.getDay();
        if(HIWORD(wParam) == CBN_SETFOCUS)
        {
            if(comboDate.getHWday() == (HWND)lParam)
            {
                comboDate.setDayCombo(year,month);
            }
            break;
        }
        switch(LOWORD(wParam))
        {
            case BN_CLICKED:
            {
                //########   TEST   ######
                if(hwButtonTest == (HWND)lParam)
                {

                    break;
                }
                if(hwButtonGET == (HWND)lParam)
                {
                    if(year==-1 || month==-1 || day==-1)
                    {
                        MessageBox(hWnd,"Please Choice Date!","Error",MB_ICONERROR);
                        break;
                    }
                    //################## SEARCH BY DATE ########################
                    SYSTEMTIME yst;
                    StringDate ys;
                    int res=0;
                    int resAFX=0;
                    char buffer[10];

                    yst.wDay=day;
                    yst.wMonth=month;
                    yst.wYear=year;

                    std::string strdate=ys.getDateDot(&yst);
                    std::string path="\\\\btlstore\\cmmti$\\avi\\כמות סריקות\\"+strdate+".xls";
                    std::string debug ="C:\\Users\\cmmti\\Desktop\\"+strdate+".xls";
                    f=fopen (path.c_str(), "wb");
                    if(f==NULL)
                        std::cout<<"fail file!"<<std::endl;
                    getCmmResult(yst, miniexcel, _list);
                    miniexcel.Write(f);
                    fclose(f);
                    break;
                }
                if(hwButtonToday == (HWND)lParam && buttonToday==false)
                {
                    //################## YESTRDAY BY DATE ########################
                    SYSTEMTIME yst;
                    StringDate ys;
                    GetLocalTime(&yst);
                    getPrevDay(&yst);
                    int res=0;
                    int resAFX=0;
                    char buffer[10];

                    std::string strdate=ys.getDateDot(&yst);
                    std::string path="\\\\btlstore\\cmmti$\\avi\\כמות סריקות\\"+strdate+".xls";
                    std::string debug ="C:\\Users\\cmmti\\Desktop\\"+strdate+".xls";
                    f=fopen (path.c_str(), "wb");
                    if(f==NULL)
                        std::cout<<"fail file!"<<std::endl;
                    buttonToday=true;
                    getCmmResult(yst, miniexcel, _list);
                    miniexcel.Write(f);
                    fclose(f);
                    break;
                }
            }

        }
        break;
    }
    case WM_PAINT:
    {
        PaintText paint(hWnd);
        paint.setEdge(600,520,900,565);
        paint.setEdge(50,490,450,560);
        paint.setBackGround(0);
        paint.setColor(250,250,250);
        paint.Text(60,495,"Search by date",15);
        paint.sizeText(20);
        paint.italic();
        paint.Text(607,533,"Developed by Dima Boguzki",25);
        break;
    }

	case WM_DESTROY:
	    delete _list;
	    delete _listAverage;
		PostQuitMessage(WM_QUIT);
		return 0;

	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);

}

BOOL CALLBACK WinControl::DlgProc(HWND hwDialog, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG:
            return FALSE;
        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwDialog, IDOK);
                    return FALSE;
            }
            return FALSE;
        }
        default:
            return FALSE;
    }
    return TRUE;
}
