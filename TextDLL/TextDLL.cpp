#include "TextDLL.h"

Paint::Paint(HDC hdc): _hdc (hdc)
{
    ReasetFontInfo();
    _font=::CreateFont(_fontInfo.nHeight, _fontInfo.nWidth, _fontInfo.nEscapement, _fontInfo.nOrientation,
            _fontInfo.fnWeight, _fontInfo.fdwItalic, _fontInfo.fdwUnderline, _fontInfo.fdwStrikeOut,
                _fontInfo.fdwCharSet, _fontInfo.fdwOutputPrecision,_fontInfo.fdwClipPrecision ,
                 _fontInfo.fdwQuality,_fontInfo.fdwPitchAndFamily, _fontInfo.lpszFac);
    SelectObject(_hdc,_font);
}
PaintText::PaintText(HWND hwnd): Paint (::BeginPaint (hwnd, &_paint)),_hwnd (hwnd)
{}
void Paint::ReasetFontInfo()
{
    _fontInfo.nHeight=18;
    _fontInfo.nWidth=9;
    _fontInfo.nEscapement=0;
    _fontInfo.nOrientation=0;
    _fontInfo.fnWeight=FW_NORMAL;
    _fontInfo.fdwItalic=FALSE;
    _fontInfo.fdwUnderline=FALSE;
    _fontInfo.fdwStrikeOut=FALSE;
    _fontInfo.fdwCharSet=ANSI_CHARSET;
    _fontInfo.fdwOutputPrecision=OUT_DEFAULT_PRECIS;
    _fontInfo.fdwClipPrecision=CLIP_DEFAULT_PRECIS;
    _fontInfo.fdwQuality=DEFAULT_QUALITY;
    _fontInfo.fdwPitchAndFamily=DEFAULT_PITCH | FF_ROMAN;
    _fontInfo.lpszFac=NULL;
}
void Paint::Text(int x, int y, char const * buf, int cBuf)
{
    ::TextOut ( _hdc, x, y, buf, cBuf );
}
void Paint::setBackGround(int bk)
{
    ::SetBkMode(_hdc, bk);
}
void Paint::setColor(BYTE red,BYTE green,BYTE blue)
{
    ::SetTextColor(_hdc,RGB(red,green,blue));
}
void Paint::sizeText(int size)
{
    _fontInfo.nHeight=size;
    _fontInfo.nWidth=size/2;
    _font=::CreateFont(_fontInfo.nHeight, _fontInfo.nWidth, _fontInfo.nEscapement, _fontInfo.nOrientation,
            _fontInfo.fnWeight, _fontInfo.fdwItalic, _fontInfo.fdwUnderline, _fontInfo.fdwStrikeOut,
                _fontInfo.fdwCharSet, _fontInfo.fdwOutputPrecision,_fontInfo.fdwClipPrecision ,
                 _fontInfo.fdwQuality,_fontInfo.fdwPitchAndFamily, _fontInfo.lpszFac);
    SelectObject(_hdc,_font);
}
void Paint::italic()
{
    if(_fontInfo.fdwItalic)
        _fontInfo.fdwItalic=FALSE;
    else
        _fontInfo.fdwItalic=TRUE;
    _font=::CreateFont(_fontInfo.nHeight, _fontInfo.nWidth, _fontInfo.nEscapement, _fontInfo.nOrientation,
            _fontInfo.fnWeight, _fontInfo.fdwItalic, _fontInfo.fdwUnderline, _fontInfo.fdwStrikeOut,
                _fontInfo.fdwCharSet, _fontInfo.fdwOutputPrecision,_fontInfo.fdwClipPrecision ,
                 _fontInfo.fdwQuality,_fontInfo.fdwPitchAndFamily, _fontInfo.lpszFac);
    SelectObject(_hdc,_font);
}
void Paint::underline()
{
    if(_fontInfo.fdwUnderline)
        _fontInfo.fdwUnderline=FALSE;
    else
        _fontInfo.fdwUnderline=TRUE;
    _font=::CreateFont(_fontInfo.nHeight, _fontInfo.nWidth, _fontInfo.nEscapement, _fontInfo.nOrientation,
            _fontInfo.fnWeight, _fontInfo.fdwItalic, _fontInfo.fdwUnderline, _fontInfo.fdwStrikeOut,
                _fontInfo.fdwCharSet, _fontInfo.fdwOutputPrecision,_fontInfo.fdwClipPrecision ,
                 _fontInfo.fdwQuality,_fontInfo.fdwPitchAndFamily, _fontInfo.lpszFac);
    SelectObject(_hdc,_font);
}
void Paint::setEdge(int x, int y, int w, int h)
{
    _recto = {x, y, w, h};
    ::DrawEdge(_hdc, &_recto, BDR_SUNKENOUTER | BDR_SUNKENINNER, BF_RECT);
}
