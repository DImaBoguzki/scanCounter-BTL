#ifndef COMBODATE_H
#define COMBODATE_H
#include <windows.h>
#include <iostream>
#include <stdio.h>

class ComboDate
{
    public:
        ComboDate();
        virtual ~ComboDate();

        bool create(HWND hwnd,int x,int y);
        HWND getHWyear(){return _year;}
        HWND getHWmonth(){return _month;}
        HWND getHWday(){return _day;}
        int getEndMonth(int month,int year);
        int getYear();
        int getMonth();
        int getDay();
        bool setDayCombo(int year,int month);
        void clearDayCombo(int endMonth);
    protected:
        HWND _year;
        HWND _month;
        HWND _day;
};

#endif // COMBODATE_H
