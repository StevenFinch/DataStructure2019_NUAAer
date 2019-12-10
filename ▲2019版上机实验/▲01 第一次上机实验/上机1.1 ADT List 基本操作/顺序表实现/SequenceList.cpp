/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/09/19
**	ID: 161840225   */
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int LIST_INIT_SIZE = 256;	//顺序表初始容量
const int LIST_INCREMENT = 256;	//顺序表增加容量
const int OK = 1;
const int ERROR = 0;
const int YES = 1;
const int NO = 0;

typedef int ElemType;
typedef int Status;
typedef struct
{
	ElemType* pElem;
	int length;
	int size;
}SeqList;

//初始化、销毁、清空操作
Status InitList(SeqList* List)
{
	List->pElem = NULL;	//分配内存之前必须将指针设置为NULL，否则为野指针，后续无法判断内存是否分配成功。
	List->pElem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
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
		return ERROR;
	}
	int i = 0;
	while (!inFile.eof())
	{
		inFile >> List->pElem[i++];
		List->length++;
	}
	inFile.close();
	return OK;
}

Status DestoryList(SeqList* List)
{
	if (NULL == List->pElem)
	{
		free(List->pElem);
		List->pElem = NULL;	//释放内存之后必须将指针设置为NULL，否则成为野指针。
	}
	List->size = 0;
	List->length = 0;
	return OK;
}

Status ClearList(SeqList* List)
{
	for (int i = 0; i < List->length; i++)
	{
		List->pElem[i] = 0;
	}
	List->length = 0;
	return OK;
}

//访问型操作
Status ListEmpty(SeqList* List)
{
	return 0 == List->length ? YES : NO;
}

int ListLength(SeqList* List)
{
	return List->length;
}

Status GetElem(SeqList* List, int logicalPos, ElemType* targetElem)
{
	if (logicalPos < 1 || logicalPos > List->length)
	{
		return ERROR;
	}
	else
	{
		*targetElem = List->pElem[logicalPos - 1];	//targetElem=...无效！
		return OK;
	}
}

int LocateElem(SeqList* List, ElemType elem)
{
	for (int i = 0; i < List->length; i++)
	{
		if (elem == List->pElem[i])
			return i + 1;	//返回值为logicalPos，而非phycalPos
	}
	return 0;	//返回值可以为零，因为返回值为logicalPos，逻辑0代表元素不存在
}

Status PriorElem(SeqList* List, ElemType curElem, ElemType* priorElem)
{
	int posCurElem = LocateElem(List, curElem);	//logicalPos of curElem
	if (posCurElem > 1 && posCurElem < List->length + 1)	//curElem非头元素
	{
		*priorElem = List->pElem[posCurElem - 2];	//targetElem=...无效！
		return OK;
	}
	return ERROR;
}

Status NextElem(SeqList* List, ElemType curElem, ElemType* nextElem)
{
	int posCurElem = LocateElem(List, curElem);	//logicalPos of curElem
	if (posCurElem > 0 && posCurElem < List->length)	//curElem非尾元素
	{
		*nextElem = List->pElem[posCurElem];	//targetElem=...无效！
		return OK;
	}
	return ERROR;
}

Status ListTraverse(SeqList* List)
{
	if (!ListEmpty(List))
	{
		for (int i = 0; i < List->length; i++)
		{
			cout << setw(4) << List->pElem[i];
		}
		cout << endl;
		return OK;
	}
	return ERROR;
}

//加工型操作
Status SetElem(SeqList* List, int logicalPos, ElemType* elem)
{
	if (logicalPos > 0 && logicalPos < List->length + 1)
	{
		ElemType temp = List->pElem[logicalPos - 1];
		List->pElem[logicalPos - 1] = *elem;
		*elem = temp;
		return OK;
	}
	return ERROR;
}

Status InsertElem(SeqList* List, int logicalPos, ElemType elem)
{
	//合法性检验
	if (logicalPos > 0 && logicalPos < List->length + 1)
	{
		//存储空间大小检验
		if (List->length >= List->size)
		{
			List->pElem = (ElemType*)realloc(List->pElem, (List->size + LIST_INCREMENT) * sizeof(ElemType));
			if (NULL == List->pElem)	//检查内存分配是否成功
			{
				cout << "Reallocating failed";
				exit(OVERFLOW);
			}
			List->size = List->size + LIST_INCREMENT;
		}
		ElemType* q = &List->pElem[logicalPos - 1];	//q为插入位置
		for (ElemType* p = &List->pElem[List->length - 1]; p >= q; p--)	//p为移动指针
		{
			*(p + 1) = *p;
		}
		*q = elem;
		List->length++;
		return OK;
	}
	return ERROR;
}

Status DeleteElem(SeqList* List, int logicalPos, ElemType* elem)
{
	if (logicalPos > 0 && logicalPos < List->length + 1)
	{
		ElemType* q = &List->pElem[logicalPos - 1];	//q为删除位置
		*elem = *q;
		for (ElemType* p = q; p <= &List->pElem[List->length - 2]; p++)	//p为移动指针
		{
			*p = *(p + 1);
		}
		List->length--;
		return OK;
	}
	return ERROR;
}

//主函数（测试函数）
int main()
{
	//在栈区分配内存，但结构体内部变量未初始化
	SeqList List;

	//初始化顺序表：
	InitList(&List);

	ElemType targetElem;	//创建实体变量，在函数中通过传地址进而改变变量值。

	if (!ListEmpty(&List))
	{
		cout << left;

		//遍历顺序表：
		cout << setw(50) << "1.List Elements: ";
		ListTraverse(&List);

		//打印顺序表长度：
		cout << setw(50) << "2.List Length: " << ListLength(&List) << endl;

		//打印第三个元素：
		if (GetElem(&List, 3, &targetElem))
			cout << setw(50) << "3.The third one: " << targetElem << endl;

		//打印元素11的位置:
		cout << setw(50) << "4.Position of the 11th one: " << LocateElem(&List, 11) << endl;

		//打印位于9前面的元素：
		if (PriorElem(&List, 9, &targetElem))
			cout << setw(50) << "5.Prior Element 9: " << targetElem << endl;

		//打印位于18后面的元素：
		if (NextElem(&List, 18, &targetElem))
			cout << setw(50) << "6.Next Element 18: " << targetElem << endl;

		//打印第三个元素并重置为targetElem：
		if (SetElem(&List, 3, &targetElem))
			cout << setw(50) << "7.The 3th one before reseting: " << targetElem << endl;

		//插入targetElem到第三位上，并打印新的顺序表：
		if (InsertElem(&List, 3, targetElem))
		{
			cout << setw(50) << "8.List Elements after inserting: ";
			ListTraverse(&List);
		}

		//删除第三个元素后打印顺序表：
		if (DeleteElem(&List, 3, &targetElem))
		{
			cout << setw(50) << "9.List Elements after deleting the 3th one: ";
			ListTraverse(&List);
		}

	}
	system("pause");
	return 0;
}
