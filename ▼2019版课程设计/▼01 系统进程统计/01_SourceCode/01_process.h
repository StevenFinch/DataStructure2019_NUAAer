#pragma once
#include <windows.h>
#include <iostream>
#include <psapi.h>
#include <tchar.h>

class Process
{
private:
	DWORD PID;
	TCHAR PNAME[MAX_PATH];
	SIZE_T PagefileUsage;
public:
	Process(DWORD processID);
	DWORD getPID();
	TCHAR* getPNAME();
	SIZE_T getPagefileUsage();
	//~Process();
};