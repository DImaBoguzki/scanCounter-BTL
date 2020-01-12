#include "tools.h"

void getPrevDay(SYSTEMTIME *st)
{
    if(st->wDay==1)
    {
        if(st->wMonth==11 || st->wMonth==9 || st->wMonth==8 || st->wMonth==6 || st->wMonth==4 || st->wMonth==2)
        {
            st->wDay==31;
            st->wMonth--;
        }
        else if(st->wMonth==12 || st->wMonth==10 || st->wMonth==7 || st->wMonth==5)
        {
            st->wDay=30;
            st->wMonth--;
        }
        else if(st->wMonth==3)
        {
            st->wMonth--;
            if(st->wYear%4==0 && st->wYear%100!=0)
                st->wDay==29;
            else
                st->wDay=28;
        }
        else if(st->wMonth==1)
        {
            st->wDay=31;
            st->wMonth=12;
            st->wYear--;
        }
    }
    else
        st->wDay--;
}
void getNextDay(SYSTEMTIME *nd)
{
    if(nd->wDay==31)
    {
        nd->wDay=1;
        if(nd->wMonth!=12)
        {
            nd->wMonth=1;
            nd->wYear++;
        }
        else
            nd->wMonth++;
    }
    else if(nd->wDay==30)
    {
        if(nd->wMonth==4 || nd->wMonth==6 || nd->wMonth==9 || nd->wMonth==11)
        {
            nd->wMonth++;
            nd->wDay=1;
        }
        else
            nd->wDay++;
    }
    else if(nd->wDay==29)
    {
        if(nd->wMonth==2)
        {
            nd->wMonth++;
            nd->wDay=1;
        }
        else
            nd->wDay++;
    }
    else if(nd->wDay==28)
    {
        if(nd->wMonth==2)
        {
            if(nd->wYear%4!=0)
            {
                nd->wMonth=1;
                nd->wDay=1;
            }
            else
                nd->wDay++;
        }
        else
            nd->wDay++;
    }
    else
        nd->wDay++;
}
void copyDate(SYSTEMTIME *n, SYSTEMTIME *c)
{
    c->wDay=n->wDay;
    c->wMonth=n->wMonth;
    c->wYear=n->wYear;
}
int cmmCount(std::string cmm, std::string type, int shift, const SYSTEMTIME *tm)
{
    std::string searchPath="\\\\btl-store2\\CMMDATA\\"+type+"\\GOODFILES\\"+cmm+"\\*.*";
    std::cout<<searchPath<<std::endl;
    int res=0;
    SYSTEMTIME fst;
    SYSTEMTIME nextDay;
    FILETIME ft;
    WIN32_FIND_DATA data;
    nextDay.wDay=tm->wDay;
    nextDay.wMonth=tm->wMonth;
    nextDay.wYear=tm->wYear;
    getNextDay(&nextDay);
    HANDLE h = FindFirstFile(searchPath.c_str(),&data);
    if(h==INVALID_HANDLE_VALUE)
    {
        std::cout << "Error: No such Root folder "<<std::endl;
        return -1;
    }
    do
    {
        FileTimeToLocalFileTime(&data.ftLastWriteTime,&ft);
        FileTimeToSystemTime(&ft,&fst);
        if(shift==1)
        {
            if(fst.wYear==tm->wYear)
            {
                if(fst.wMonth==tm->wMonth)
                {
                    if(fst.wDay==tm->wDay)
                    {
                        if(fst.wHour>=7 && fst.wHour<19)
                            res++;
                    }
                }
            }
        }
        else if(shift==2)
        {
            if(fst.wYear==tm->wYear)
            {
                if(fst.wMonth==tm->wMonth)
                {
                    if(fst.wDay==tm->wDay)
                    {
                        if(fst.wHour>=19 && fst.wHour<=23)
                            res++;
                    }
                    if(fst.wDay==nextDay.wDay)
                    {
                        if(fst.wHour>=0 && fst.wHour<7)
                            res++;
                    }
                }
            }
        }
    } while(FindNextFile(h,&data));
    FindClose(h);
    return res;
}


void WatchDirectory(std::string lpDir)
{
    DWORD dwWaitStatus;
    HANDLE dwChangeHandles;

    dwChangeHandles = FindFirstChangeNotification(
        lpDir.c_str(),                         // directory to watch
        FALSE,                         // do not watch subtree
        FILE_NOTIFY_CHANGE_FILE_NAME); // watch file name changes

    if (dwChangeHandles == INVALID_HANDLE_VALUE)
    {
        printf("\n ERROR: FindFirstChangeNotification function failed.\n");
        ExitProcess(GetLastError());
    }

    if (dwChangeHandles == NULL)
    {
        printf("\n ERROR: Unexpected NULL from FindFirstChangeNotification.\n");
        ExitProcess(GetLastError());
    }

    while (TRUE)
    {
    // Wait for notification.

        printf("\nWaiting for notification...\n");

        dwWaitStatus = WaitForSingleObject(dwChangeHandles, INFINITE);

        switch (dwWaitStatus)
        {
            case WAIT_OBJECT_0:
                std::cout<<"new file!"<<std::endl;
                if ( FindNextChangeNotification(dwChangeHandles) == FALSE )
                {
                    printf("\n ERROR: FindNextChangeNotification function failed.\n");
                    ExitProcess(GetLastError());
                }
                break;
            case WAIT_TIMEOUT:
                printf("\nNo changes in the timeout period.\n");
                break;

            default:
                printf("\n ERROR: Unhandled dwWaitStatus.\n");
                ExitProcess(GetLastError());
                break;
      }
   }
}

void getCmmResult(const SYSTEMTIME &tm, miniexcel::CMiniExcel &miniexcel, ListView *_list)
{
    int res=0;
    int resAFX=0;
    char buffer[10];
    StringDate *date;
    date=new StringDate();
    //first shift
    _list->addRow(0,0, date->getDate(&tm));
    miniexcel(1,0)=date->getDate(&tm);
    _list->addRow(1,0, "בוקר");
    miniexcel(1,1)="Morning";
    res=cmmCount("IB-354","ROOT",1,&tm);
    memset(buffer,0,sizeof(buffer));
    sprintf(buffer,"%d",res);
    miniexcel(1,2)=res;
    _list->addRow(2,0, buffer);
    res=cmmCount("SGA-1592","ROOT",1,&tm);
    resAFX=cmmCount("SGA-1592","AFX",1,&tm);
    memset(buffer,0,sizeof(buffer));
    if(resAFX!=-1)
    {
        sprintf(buffer,"%d",res+resAFX);
        miniexcel(1,3)=res+resAFX;
    }
    else
    {
        sprintf(buffer,"%d",res);
        miniexcel(1,3)=res;
    }
    _list->addRow(3,0, buffer);
    res=cmmCount("SGA-2301","ROOT",1,&tm);
    resAFX=cmmCount("SGA-2301","AFX",1,&tm);
    memset(buffer,0,sizeof(buffer));
    if(resAFX!=-1)
    {
        sprintf(buffer,"%d",res+resAFX);
        miniexcel(1,4)=res+resAFX;
    }
    else
    {
        sprintf(buffer,"%d",res);
        miniexcel(1,4)=res;
    }
    _list->addRow(4,0, buffer);
    res=cmmCount("SGA-2049","ROOT",1,&tm);
    resAFX=cmmCount("SGA-2049","AFX",1,&tm);
    memset(buffer,0,sizeof(buffer));
    if(resAFX!=-1)
    {
        sprintf(buffer,"%d",res+resAFX);
        miniexcel(1,5)=res+resAFX;
    }
    else
    {
        sprintf(buffer,"%d",res);
        miniexcel(1,5)=res;
    }
    _list->addRow(5,0, buffer);
    res=cmmCount("NTXPBLAZER-008","Blazer",1,&tm);
    memset(buffer,0,sizeof(buffer));
    sprintf(buffer,"%d",res);
    miniexcel(1,6)=res;
    _list->addRow(6,0, buffer);


    //second shift
    _list->addRow(0,1, date->getDate(&tm));
    miniexcel(2,0)=date->getDate(&tm);
    _list->addRow(1,1, "לילה");
    miniexcel(2,1)="Night";
    res=cmmCount("IB-354","ROOT",2,&tm);
    memset(buffer,0,sizeof(buffer));
    sprintf(buffer,"%d",res);
    miniexcel(2,2)=res;
    _list->addRow(2,1, buffer);
    res=cmmCount("SGA-1592","ROOT",2,&tm);
    resAFX=cmmCount("SGA-1592","AFX",2,&tm);
    memset(buffer,0,sizeof(buffer));
    if(resAFX!=-1)
    {
        sprintf(buffer,"%d",res+resAFX);
        miniexcel(2,3)=res+resAFX;
    }
    else
    {
        sprintf(buffer,"%d",res);
        miniexcel(2,3)=res;
    }
    _list->addRow(3,1, buffer);
    res=cmmCount("SGA-2301","ROOT",2,&tm);
    resAFX=cmmCount("SGA-2301","AFX",2,&tm);
    memset(buffer,0,sizeof(buffer));
    if(resAFX!=-1)
    {
        sprintf(buffer,"%d",res+resAFX);
        miniexcel(2,4)=res+resAFX;
    }
    else
    {
        sprintf(buffer,"%d",res);
        miniexcel(2,4)=res;
    }
    _list->addRow(4,1, buffer);
    res=cmmCount("SGA-2049","ROOT",2,&tm);
    resAFX=cmmCount("SGA-2049","AFX",2,&tm);
    memset(buffer,0,sizeof(buffer));
    if(resAFX!=-1)
    {
        sprintf(buffer,"%d",res+resAFX);
        miniexcel(2,5)=res+resAFX;
    }
    else
    {
        sprintf(buffer,"%d",res);
        miniexcel(2,5)=res;
    }
    _list->addRow(5,1, buffer);
    res=cmmCount("NTXPBLAZER-008","Blazer",2,&tm);
    memset(buffer,0,sizeof(buffer));
    sprintf(buffer,"%d",res);
    miniexcel(2,6)=res;
    _list->addRow(6,1, buffer);
    miniexcel(3,7)="Sum";
    miniexcel(3,6)=miniexcel(1,6) + miniexcel(2,6);
    miniexcel(3,5)=miniexcel(1,5) + miniexcel(2,5);
    miniexcel(3,4)=miniexcel(1,4) + miniexcel(2,4);
    miniexcel(3,3)=miniexcel(1,3) + miniexcel(2,3);
    miniexcel(3,2)=miniexcel(1,2) + miniexcel(2,2);
    miniexcel(7,4)="cmm";
    miniexcel(7,3)=miniexcel(3,5)+miniexcel(3,4)+miniexcel(3,3)+miniexcel(3,2);
    miniexcel(8,4)="cmm+blazer";
    miniexcel(8,3)=miniexcel(3,6)+miniexcel(7,3);
    delete date;
}
