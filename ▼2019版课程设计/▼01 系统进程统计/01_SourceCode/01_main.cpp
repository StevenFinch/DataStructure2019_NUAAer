/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/17
**	ID: 161840225   */
#include <windows.h>
#include <iostream>
#include <sstream>
#include <map>
#include <psapi.h>
#include <vector>
#include <tlhelp32.h>
#include <iomanip>
#include <ctime>

using namespace std;

// wchar_t to string
void Wchar_tToString(std::string& szDst, wchar_t* wchar)
{
	wchar_t* wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);
	char* psText;
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);
	szDst = psText;
	delete[]psText;
}

struct Process
{
	SIZE_T PagefileUsage;
	DWORD PID;
	string PNAME;
	Process()
	{
		PagefileUsage = 0;
		PID = 0;
		PNAME = "";
	}
	Process(PROCESSENTRY32& pe32)
	{
		Wchar_tToString(PNAME, const_cast<wchar_t*>(pe32.szExeFile));//PNAME
		PID = pe32.th32ProcessID;//ID

		HANDLE hProcess;
		PROCESS_MEMORY_COUNTERS pmc;//创建struct用于存储进程的内存统计信息

		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);//打开句柄

		GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
		PagefileUsage = pmc.PagefileUsage / 1024;//PagefileUsage KB

		CloseHandle(hProcess);
	}
};

typedef struct LNode
{
	Process data;
	struct LNode* prior;
	struct LNode* next;
}LNode;

typedef struct DList
{
	LNode* head;
	LNode* tail;
	LNode* pCurNode;
	int length;
}ListInfo;

ostream& operator<<(ostream& out, Process p)
{
	out << setw(8) << p.PID;
	out << setw(70) << p.PNAME;
	out << setw(8) << p.PagefileUsage << "KB";
	out << endl;
	return out;
}
bool operator<(const Process& p1, const Process& p2)
{
	return p1.PagefileUsage < p2.PagefileUsage;
}
bool operator>(const Process& p1, const Process& p2)
{
	return p1.PagefileUsage > p2.PagefileUsage;
}
void InitList(ListInfo* List)
{
	List->head = new LNode;
	List->head->next = NULL;
	List->head->prior = NULL;

	List->tail = List->head;

	List->pCurNode = List->head;

	List->length = 0;
}
void TraverseList(ListInfo* List)
{
	if (0 == List->length)
		return;
	LNode* p = List->head->next;
	while (p)
	{
		cout << left;
		cout << setw(3) << p->data;
		p = p->next;
	}
	cout << endl;
}
void InsertElemAfterCurNode(ListInfo* List, Process* elem)
{
	LNode* newNode = new LNode;

	newNode->data = *elem;
	newNode->next = List->pCurNode->next;
	newNode->prior = List->pCurNode;

	List->pCurNode->next = newNode;

	if (newNode->next)
		newNode->next->prior = newNode;
	else//如果插入后是尾节点则重置尾指针
		List->tail = newNode;

	List->length++;
}
void SortList(ListInfo* List)
{
	LNode* p;
	LNode* q;
	LNode* s;
	Process temp;
	for (p = List->head->next; p->next != NULL; p = p->next)
	{
		s = p;
		for (q = p->next; q != NULL; q = q->next)
		{
			if (q->data > s->data)
			{
				s = q;
			}
		}
		if (s != p)
		{
			temp = p->data;
			p->data = s->data;
			s->data = temp;
		}
	}
}
int main()
{
	map<string, int> m;
	int flag = 1;
	clock_t begin, stop;
	time_t now_time = time(0);
	ListInfo* DList = new ListInfo;
	InitList(DList);

	begin = clock();

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	while (bMore)
	{
		Process p(pe32);
		m[p.PNAME] = flag;
		InsertElemAfterCurNode(DList, &p);
		bMore = ::Process32Next(hProcessSnap, &pe32);
	}
	int length = DList->length;
	delete DList;

	while (true)
	{
		ListInfo* DList = new ListInfo;

		InitList(DList);
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(pe32);
		HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		
		BOOL bMore = ::Process32First(hProcessSnap, &pe32);
		while (bMore)
		{
			Process p(pe32);
			m[p.PNAME] = -flag;
			InsertElemAfterCurNode(DList, &p);
			bMore = ::Process32Next(hProcessSnap, &pe32);
		}

		SortList(DList);
		cout << "当前进程信息为：" << endl << endl;
		TraverseList(DList);

		cout << "结束进程信息为：" << endl << endl;
		cout << setw(20) << "进程名称" << "   " << "持续时间" << "     " << "结束时间" << endl <<endl;
		for (auto it = m.begin(); it != m.end(); it++)
		{
			if (m[it->first] == flag)
			{
				stop = clock();
				now_time = time(NULL);
				char str[27];
				ctime_s(str, sizeof str, &now_time);
				cout << setw(20) << it->first << "   " << (stop - begin) / CLK_TCK << "s            " << str << endl;
				m[it->first] = -flag;
			}
		}

		for (auto it = m.begin(); it != m.end(); it++)
		{
			m[it->first] == flag;
		}
		flag = -flag;
		delete DList;
		Sleep(2000);
	}
	return 0;
}