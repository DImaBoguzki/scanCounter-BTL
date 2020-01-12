#include "ListView.h"

ListView::ListView(int x, int y, int width, int heigth)
: _posX(x), _posY(y), _width(width), _heigth(heigth)
{
    _hwList=NULL;
}
bool ListView::show(const HWND &hwnd)
{
    _hwList=::CreateWindowEx(WS_EX_CLIENTEDGE,WC_LISTVIEW, NULL, WS_VISIBLE | WS_CHILD | WS_BORDER |
                            LVS_REPORT | LVS_EDITLABELS | LVS_EX_CHECKBOXES, _posX, _posY, _width, _heigth,
                    hwnd,NULL,(HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),NULL);
    if(!_hwList)
        return false;
    return true;
}
ListView::~ListView()
{
    //dtor
}
void ListView::addColumns(int x, char* str)
{
    _lc.pszText=str;
    _lc.cx=x;
    ListView_InsertColumn(_hwList, _col,&_lc);
    this->_col++;
}
void ListView::addRow(int col, int row, char *str)
{
    _itc.iItem    = row;
    _itc.iSubItem = col;
    ListView_InsertItem(_hwList, &_itc);
    ListView_SetItemText(_hwList,row,col,str);
}
bool ListView::setTextColor(COLORREF clrText)
{
    if(ListView_SetTextColor(_hwList,clrText))
        return true;
    else
        return false;
       SendMessage(_hwList,LVM_SETTEXTCOLOR ,0,RGB(100,100,100));
}
void ListView::registerColumens()
{
    memset(&_lc,0,sizeof(LVCOLUMN));
    _lc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH  | LVCF_FMT;
    _lc.fmt  = LVCFMT_CENTER;
    //later more options for style like left ,right,center and more...
}
void ListView::registerRows()
{
    memset(&_itc,0,sizeof(LVITEM));
    _itc.mask      = LVIF_TEXT;
    _itc.state     = 0;
    _itc.stateMask = 0;

    _itc.iItem    = 0;
    _itc.iSubItem = 0;
}
void ListView::setStyle()
{
    ListView_SetExtendedListViewStyle(this->_hwList,
                LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
    //later more style options...
}
bool ListView::deleteAllItem()
{
    if(ListView_DeleteAllItems(_hwList))
        return true;
    else
        return false;
}
bool ListView::deleteColumn(int col)
{
    if(ListView_DeleteColumn(_hwList,col))
        return true;
    else
        return false;
}
bool ListView::deleteItem(int item)
{
    if(ListView_DeleteItem(_hwList,item))
        return true;
    else
        return false;
}
