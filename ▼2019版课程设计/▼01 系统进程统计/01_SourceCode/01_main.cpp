/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/17
**	ID: 161840225   */

/*  Reference:  https://blog.csdn.net/byxdaz/article/details/82494325   */
#include "01_process.h"
using namespace std;

int main()
{
	// Get the list of process identifiers.

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return 1;
	}

	// Calculate how many process identifiers were returned.

	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the memory usage for each process

	for (i = 0; i < cProcesses; i++)
	{
		setlocale(LC_ALL, "chs");
		Process p(aProcesses[i]);
		cout << p.getPID() <<endl;
		_tprintf(TEXT("%s\n"), p.getPNAME());
		cout << p.getPagefileUsage() << endl;
	}

	return 0;
}