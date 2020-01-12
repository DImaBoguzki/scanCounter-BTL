#include "StringDate.h"

StringDate::StringDate()
{
    _dateAndTime = NULL;
    _date=NULL;
    _day = NULL;
    _month = NULL;
    _year = NULL;
    _hour = NULL;
    _minute = NULL;
}

StringDate::~StringDate()
{
    if(_dateAndTime!=NULL)
        delete[] _dateAndTime;
    if(_date!=NULL)
        delete [] _date;
    if(_day!=NULL)
        delete[] _day;
    if(_month!=NULL)
        delete[] _month;
    if(_year!=NULL)
        delete[] _year;
    if(_hour!=NULL)
        delete[] _hour;
    if(_minute!=NULL)
        delete[] _minute;
}

char* StringDate::getDateAndTime()
{
    int pos=0;
    GetLocalTime(&_st);
    if(_dateAndTime!=NULL)
        delete [] _dateAndTime;
    _dateAndTime = new char[26];
    //DATE
    if(_st.wDay<10)
        pos=snprintf(_dateAndTime, 90,"0%d\\", _st.wDay);
    else
        pos=snprintf(_dateAndTime, 90,"%d\\", _st.wDay);
    if(_st.wMonth<10)
        pos+=snprintf(_dateAndTime+pos,90-pos,  "0%d\\", _st.wMonth);
    else
        pos+=snprintf(_dateAndTime+pos,90-pos,  "%d\\", _st.wMonth);
    pos+=snprintf(_dateAndTime+pos,90-pos,  "%d ", _st.wYear);
    //TIME
    if(_st.wHour<10)
        pos+=snprintf(_dateAndTime+pos,90-pos,"0%d:", _st.wHour);
    else
        pos+=snprintf(_dateAndTime+pos,90-pos,"%d:", _st.wHour);
    if(_st.wMinute<10)
        pos+=snprintf(_dateAndTime+pos,90-pos,"0%d:", _st.wMinute);
    else
        pos+=snprintf(_dateAndTime+pos,90-pos,"%d:", _st.wMinute);
    if(_st.wSecond<10)
        pos+=snprintf(_dateAndTime+pos,90-pos,"0%d", _st.wSecond);
    else
        pos+=snprintf(_dateAndTime+pos,90-pos,"%d", _st.wSecond);
    return _dateAndTime;
}

char* StringDate::getDate()
{
    int pos=0;
    GetLocalTime(&_st);
    if(_date!=NULL)
        delete [] _date;
    _date = new char[26];
    //DATE
    if(_st.wDay<10)
        pos=snprintf(_date, 90,"0%d\\", _st.wDay);
    else
        pos=snprintf(_date, 90,"%d\\", _st.wDay);
    if(_st.wMonth<10)
        pos+=snprintf(_date+pos,90-pos,  "0%d\\", _st.wMonth);
    else
        pos+=snprintf(_date+pos,90-pos,  "%d\\", _st.wMonth);
    pos+=snprintf(_date+pos,90-pos,  "%d ", _st.wYear);
    return _date;
}
char* StringDate::getDateDot(SYSTEMTIME *_st)
{
    int pos=0;
    if(_date!=NULL)
        delete [] _date;
    _date = new char[26];
    //DATE
    if(_st->wDay<10)
        pos=snprintf(_date, 90,"0%d.", _st->wDay);
    else
        pos=snprintf(_date, 90,"%d.", _st->wDay);
    if(_st->wMonth<10)
        pos+=snprintf(_date+pos,90-pos,  "0%d.", _st->wMonth);
    else
        pos+=snprintf(_date+pos,90-pos,  "%d.", _st->wMonth);
    pos+=snprintf(_date+pos,90-pos,  "%d ", _st->wYear);
    return _date;
}
char* StringDate::getDate(const SYSTEMTIME *st)
{
    int pos=0;
    if(_date!=NULL)
        delete [] _date;
    _date = new char[26];
    //DATE
    pos=snprintf(_date, 90,"%d\\", st->wDay);
    pos+=snprintf(_date+pos,90-pos,  "%d\\", st->wMonth);
    pos+=snprintf(_date+pos,90-pos,  "%d ", st->wYear);
    return _date;
}

char* StringDate::getDay()
{
    GetLocalTime(&_st);
    if(_day!=NULL)
        delete [] _day;
    _day = new char[3];
    if(_st.wDay<10)
        sprintf(_day,"0%d", _st.wDay);
    else
        sprintf(_day,"%d", _st.wDay);
    return _day;
}

char* StringDate::getMonth()
{
    GetLocalTime(&_st);
    if(_month!=NULL)
        delete [] _month;
    char *_month = new char[3];
    if(_st.wDay<10)
        sprintf(_month,"0%d", _st.wMonth);
    else
        sprintf(_month,"%d", _st.wMonth);
    return _month;
}

char* StringDate::getYear()
{
    GetLocalTime(&_st);
    if(_year!=NULL)
        delete [] _year;
    char *_year = new char[5];
    sprintf(_year,"%d", _st.wYear);
    return _year;
}

char* StringDate::getHour()
{
    GetLocalTime(&_st);
    if(_hour!=NULL)
        delete [] _hour;
    char *_hour = new char[3];
    if(_st.wDay<10)
        sprintf(_hour,"0%d", _st.wHour);
    else
        sprintf(_hour,"%d", _st.wHour);
    return _hour;
}

char* StringDate::getMinute()
{
    GetLocalTime(&_st);
    char *_minute = new char[3];
    if(_st.wDay<10)
        sprintf(_minute,"0%d", _st.wMinute);
    else
        sprintf(_minute,"%d", _st.wMinute);
    return _minute;
}
