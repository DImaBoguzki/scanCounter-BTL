#ifndef LISTVIEW_H
#define LISTVIEW_H

#define _WIN32_IE 0x300

#include <windows.h>
#include <CommCtrl.h>



#ifdef BUILD_DLL
    #define DLL_EXPORT  __declspec(dllexport)
#else
    #define DLL_EXPORT  __declspec(dllimport)
#endif

class DLL_EXPORT ListView
{
    public:
        ListView(int x, int y, int width, int heigth);
        bool show(const HWND &hwnd);
        void addColumns(int x, char* str);
        void addRow(int col, int row, char *str);
        void registerColumens();
        void registerRows();
        void setStyle();
        bool setTextColor(COLORREF clrText);
        bool deleteAllItem();
        bool deleteColumn(int col);
        bool deleteItem(int item);
        virtual ~ListView();
    protected:
        HWND        _hwList;
        LVCOLUMN    _lc;
        LVITEM      _itc;
        int         _row, _col;
        int         _posX, _posY, _width, _heigth;
};

#endif // LISTVIEW_H
