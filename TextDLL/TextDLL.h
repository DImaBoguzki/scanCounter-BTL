#ifndef __TEXTDLL_H__
#define __TEXTDLL_H__

#include <windows.h>

#ifdef BUILD_DLL
    #define DLL_EXPORT  __declspec(dllexport)
#else
    #define DLL_EXPORT  __declspec(dllimport)
#endif


struct DLL_EXPORT FontInfo
{
    int     nHeight;
    int     nWidth;
    int     nEscapement;
    int     nOrientation;
    int     fnWeight;
    DWORD   fdwItalic;
    DWORD   fdwUnderline;
    DWORD   fdwStrikeOut;
    DWORD   fdwCharSet;
    DWORD   fdwOutputPrecision;
    DWORD   fdwClipPrecision;
    DWORD   fdwQuality;
    DWORD   fdwPitchAndFamily;
    LPCTSTR lpszFac;
};

class DLL_EXPORT Paint
{
public:
    operator HDC () { return _hdc; }
    void ReasetFontInfo();
    void Text(int x, int y, char const * buf, int cBuf);
    void setBackGround(int bk);
    void setColor(BYTE red,BYTE green,BYTE blue);
    void sizeText(int size);
    void italic();
    void underline();
    void setEdge(int x, int y, int w, int h);
    ~Paint()
    {
        ::DeleteObject(_font);
    }
protected:

    Paint(HDC hdc);
    FontInfo _fontInfo;
    HFONT _font;
    RECT _recto;
    HDC  _hdc;
};

class DLL_EXPORT PaintText : public Paint
{
public:
    PaintText (HWND hwnd);
    ~PaintText ()
    {
        ::EndPaint(_hwnd, &_paint);
    }

protected:

    PAINTSTRUCT _paint;
    HWND        _hwnd;
};

#endif // __TEXTDLL_H__
