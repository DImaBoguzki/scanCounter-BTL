#ifndef _TOOLS_H
#define _TOOLS_H
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include "mexcel.h"
#include <ListView.h>
#include <StringDate.h>

void getPrevDay(SYSTEMTIME *st);
void getNextDay(SYSTEMTIME *nd);
int cmmCount(std::string cmm, std::string type, int shift, const SYSTEMTIME *tm);
void WatchDirectory(std::string lpDir);
void copyDate(SYSTEMTIME *n, SYSTEMTIME *c);
void getCmmResult(const SYSTEMTIME &tm, miniexcel::CMiniExcel &excel, ListView *_list);


#endif // _TOOLS_H
