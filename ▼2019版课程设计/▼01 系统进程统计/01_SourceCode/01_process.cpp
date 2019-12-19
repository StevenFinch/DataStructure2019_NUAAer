#include "01_process.h"
using namespace std;

Process::Process(DWORD processID)
{
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;//创建struct用于存储进程的内存统计信息

	PID = processID;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);//打开句柄
	if (NULL == hProcess)
		return;

	if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))//获取内存统计信息并存储在pmc中
	{
		GetModuleFileNameEx(hProcess, NULL, PNAME, sizeof(PNAME) / sizeof(TCHAR));
		PagefileUsage = pmc.PagefileUsage / 1024;
	}
	CloseHandle(hProcess);//关闭句柄
}

DWORD Process::getPID()
{
	return PID;
}

TCHAR* Process::getPNAME()
{
	return PNAME;
}

SIZE_T Process::getPagefileUsage()
{
	return PagefileUsage;
}
