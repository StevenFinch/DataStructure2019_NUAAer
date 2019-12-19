#include "01_process.h"
using namespace std;

Process::Process(DWORD processID)
{
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;//����struct���ڴ洢���̵��ڴ�ͳ����Ϣ

	PID = processID;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);//�򿪾��
	if (NULL == hProcess)
		return;

	if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))//��ȡ�ڴ�ͳ����Ϣ���洢��pmc��
	{
		GetModuleFileNameEx(hProcess, NULL, PNAME, sizeof(PNAME) / sizeof(TCHAR));
		PagefileUsage = pmc.PagefileUsage / 1024;
	}
	CloseHandle(hProcess);//�رվ��
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
