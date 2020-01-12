#ifndef STRINGDATE_H
#define STRINGDATE_H
#include <windows.h>
#include <stdio.h>

class StringDate
{
    public:
        StringDate();
        virtual ~StringDate();

        char* getDateAndTime();
        char* getDateDot(SYSTEMTIME *st);
        char* getDate();
        char* getDate(const SYSTEMTIME *st);
        char* getDay();
        char* getMonth();
        char* getYear();
        char* getHour();
        char* getMinute();
    private:
        SYSTEMTIME _st;
        char *_dateAndTime;
        char *_date;
        char *_day;
        char *_month;
        char *_year;
        char *_hour;
        char *_minute;
};

#endif // STRINGDATE_H
