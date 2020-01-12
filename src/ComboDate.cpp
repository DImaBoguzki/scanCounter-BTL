#include "ComboDate.h"

ComboDate::ComboDate()
{
    _day=NULL;
    _month=NULL;
    _year=NULL;
}

ComboDate::~ComboDate()
{
    //dtor
}
bool ComboDate::create(HWND hwnd, int x,int y)
{
    SYSTEMTIME tm;
    char buff[5];
    GetLocalTime(&tm);
    _year=CreateWindowEx(WS_EX_CLIENTEDGE,"ComboBox","year",CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_VISIBLE | WS_CHILD,x,y,80,100,
                        hwnd,NULL,(HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),NULL);
    _month=CreateWindowEx(WS_EX_CLIENTEDGE,"ComboBox","month",CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_VISIBLE | WS_CHILD,x+100,y,50,250,
                        hwnd,NULL,(HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),NULL);
    _day=CreateWindowEx(WS_EX_CLIENTEDGE,"ComboBox","month",CBS_DROPDOWNLIST | CBS_DROPDOWN | CBS_HASSTRINGS | WS_VISIBLE | WS_CHILD | WS_VSCROLL,x+170,y,50,200,
                        hwnd,NULL,(HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),NULL);
    if(_year!=NULL && _month!=NULL)
    {
        for(int i=0;i<2;i++)
        {
            memset(buff,0,5);
            sprintf(buff,"%d",tm.wYear);
            if(SendMessage(_year,CB_ADDSTRING,0,(LPARAM)buff)==CB_ERR)
            {
                std::cout<<"error add string \" "<<buff<<" to combo box"<<std::endl;
                return false;
            }
            tm.wYear--;
        }
        for(int i=1;i<=12;i++)
        {
            memset(buff,0,5);
            sprintf(buff,"%d",i);
            if(SendMessage(_month,CB_ADDSTRING,0,(LPARAM)buff)==CB_ERR)
            {
                std::cout<<"error add string \" "<<buff<<" to combo box"<<std::endl;
                return false;
            }
        }
    }
    else
    {
        std::cout<<"error with create combo box!\n";
        return false;
    }
    return true;
}

int ComboDate::getEndMonth(int month,int year)
{
    if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
        return 31;
    else if(month==4 || month==6 || month==9 || month==11)
        return 30;
    else if(month==2)
    {
        if(year%4==0 && year%100!=0)
            return 29;
        else
            return 28;
    }
    else
        return -1; // ERROR
}

int ComboDate::getYear()
{
    int index;
    char buff[5];
    memset(buff,0,5);
    index=SendMessage(_year,CB_GETCURSEL,0,0);
    SendMessage(_year,CB_GETLBTEXT,index,(LPARAM)buff);
    return atoi(buff);
}
int ComboDate::getMonth()
{
    int index;
    char buff[3];
    memset(buff,0,3);
    index=SendMessage(_month,CB_GETCURSEL,0,0);
    SendMessage(_month,CB_GETLBTEXT,index,(LPARAM)buff);
    return atoi(buff);
}

int ComboDate::getDay()
{
    int index;
    char buff[3];
    memset(buff,0,3);
    index=SendMessage(_day,CB_GETCURSEL,0,0);
    SendMessage(_day,CB_GETLBTEXT,index,(LPARAM)buff);
    return atoi(buff);
}

bool ComboDate::setDayCombo(int year,int month)
{
    char buff[3];
    if(month==-1 || year==-1)
        return false;
    for(int i=1;i<=getEndMonth(month,year);i++)
    {
        memset(buff,0,3);
        sprintf(buff,"%d",i);
        if(SendMessage(_day,CB_ADDSTRING,i-1,(LPARAM)buff)==CB_ERR)
        {
            std::cout<<"error add string \" "<<buff<<" to combo box"<<std::endl;
            return false;
        }
    }
    return true;
}
void ComboDate::clearDayCombo(int endMonth)
{
    for(int i=0;i<endMonth;i++)
        SendMessage(_day,CB_DELETESTRING,0,0);
}
