/***************************************
 **   Filename： 顺序表选择排序.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/
#include <iostream>
#include <fstream>

using namespace std;

const int LIST_INIT_SIZE = 256;	
typedef struct
{
	int* pElem;
	int length;
	int size;
}SeqList;

bool InitList(SeqList* List)
{
	List->pElem = NULL;	//分配内存之前必须将指针设置为NULL，否则为野指针，后续无法判断内存是否分配成功。
	List->pElem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	//检验分配内存是否成功
	if (NULL == List->pElem)
		exit(OVERFLOW);
	for (int i = 0; i < LIST_INIT_SIZE; i++)	//分配内存成功，顺序表内容初始化
	{
		List->pElem[i] = -1;
	}
	List->length = 0;
	List->size = LIST_INIT_SIZE;

	//读取数据
	ifstream inFile("SeqquenceList.txt");
	if (!inFile)
	{
		return false;
	}
	int i = 0;
	while (!inFile.eof())
	{
		inFile >> List->pElem[i++];
		List->length++;
	}
	inFile.close();
	return true;
}
bool SelectSortList(SeqList* List)	//核心代码
{
	int small;
	int temp;
	for (int i = 0; i < List->length - 1; i++)
	{
		small = i;
		for (int j = i + 1; j < List->length; j++)
		{
			if (List->pElem[j] < List->pElem[small])
			{
				small = j;
			}
		}
		if (small != i)
		{
			temp = List->pElem[small];
			List->pElem[small] = List->pElem[i];
			List->pElem[i] = temp;
		}
	}
	return true;
}
bool TraverseList(SeqList* List)
{
	for (int i = 0; i < List->length; i++)
	{
		cout << List->pElem[i] << ' ';
	}
	cout << endl;
	return true;
}
//主函数（测试函数）
int main()
{
	SeqList List;
	InitList(&List);
	TraverseList(&List);
	SelectSortList(&List);
	TraverseList(&List);
	system("pause");
	return 0;
}