/***************************************
 **   Filename�� SequenceList.cpp
 **                                      
 **   StudentID: 1618*****              
 **                                     
 **   Name:      Steven                 
 **                                     
 ***************************************/
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int LIST_INIT_SIZE = 256;	//˳����ʼ����
const int LIST_INCREMENT = 256;	//˳�����������
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

//��ʼ�������١���ղ���
Status InitList(SeqList* List)
{
	List->pElem = NULL;	//�����ڴ�֮ǰ���뽫ָ������ΪNULL������ΪҰָ�룬�����޷��ж��ڴ��Ƿ����ɹ���
	List->pElem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	//��������ڴ��Ƿ�ɹ�
	if (NULL == List->pElem)
	{
		cout << "Allocating failed";
		exit(OVERFLOW);
	}
	for (int i = 0; i < LIST_INIT_SIZE; i++)	//�����ڴ�ɹ���˳������ݳ�ʼ��
	{
		List->pElem[i] = -1;
	}
	List->length = 0;
	List->size = LIST_INIT_SIZE;

	//��ȡ����
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
		List->pElem = NULL;	//�ͷ��ڴ�֮����뽫ָ������ΪNULL�������ΪҰָ�롣
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

//�����Ͳ���
Status ListEmpty(SeqList* List)
{
	return 0 == List->length ? YES : NO;
}

int ListLength(SeqList* List)
{
	return List->length;
}

Status GetElem(SeqList* List, int logicPos, ElemType* Elem)
{
	if (logicPos < 1 || logicPos > List->length)
	{
		return ERROR;
	}
	else
	{
		*Elem = List->pElem[logicPos - 1];	//Elem=...��Ч��
		return OK;
	}
}

int LocateElem(SeqList* List, ElemType elem)
{
	for (int i = 0; i < List->length; i++)
	{
		if (elem == List->pElem[i])
			return i + 1;	//����ֵΪlogicPos������phycalPos
	}
	return 0;	//����ֵ����Ϊ�㣬��Ϊ����ֵΪlogicPos���߼�0����Ԫ�ز�����
}

Status PriorElem(SeqList* List, ElemType curElem, ElemType* priorElem)
{
	int posCurElem = LocateElem(List, curElem);	//logicPos of curElem
	if (posCurElem > 1 && posCurElem < List->length + 1)	//curElem��ͷԪ��
	{
		*priorElem = List->pElem[posCurElem - 2];	//Elem=...��Ч��
		return OK;
	}
	return ERROR;
}

Status NextElem(SeqList* List, ElemType curElem, ElemType* nextElem)
{
	int posCurElem = LocateElem(List, curElem);	//logicPos of curElem
	if (posCurElem > 0 && posCurElem < List->length)	//curElem��βԪ��
	{
		*nextElem = List->pElem[posCurElem];	//Elem=...��Ч��
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

//�ӹ��Ͳ���
Status SetElem(SeqList* List, int logicPos, ElemType* elem)
{
	if (logicPos > 0 && logicPos < List->length + 1)
	{
		ElemType temp = List->pElem[logicPos - 1];
		List->pElem[logicPos - 1] = *elem;
		*elem = temp;
		return OK;
	}
	return ERROR;
}

Status InsertElem(SeqList* List, int logicPos, ElemType elem)
{
	//�Ϸ��Լ���
	if (logicPos > 0 && logicPos < List->length + 1)
	{
		//�洢�ռ��С����
		if (List->length >= List->size)
		{
			List->pElem = (ElemType*)realloc(List->pElem, (List->size + LIST_INCREMENT) * sizeof(ElemType));
			if (NULL == List->pElem)	//����ڴ�����Ƿ�ɹ�
			{
				cout << "Reallocating failed";
				exit(OVERFLOW);
			}
			List->size = List->size + LIST_INCREMENT;
		}
		ElemType* q = &List->pElem[logicPos - 1];	//qΪ����λ��
		for (ElemType* p = &List->pElem[List->length - 1]; p >= q; p--)	//pΪ�ƶ�ָ��
		{
			*(p + 1) = *p;
		}
		*q = elem;
		List->length++;
		return OK;
	}
	return ERROR;
}

Status DeleteElem(SeqList* List, int logicPos, ElemType* elem)
{
	if (logicPos > 0 && logicPos < List->length + 1)
	{
		ElemType* q = &List->pElem[logicPos - 1];	//qΪɾ��λ��
		*elem = *q;
		for (ElemType* p = q; p <= &List->pElem[List->length - 2]; p++)	//pΪ�ƶ�ָ��
		{
			*p = *(p + 1);
		}
		List->length--;
		return OK;
	}
	return ERROR;
}

//�����������Ժ�����
int main()
{
	//��ջ�������ڴ棬���ṹ���ڲ�����δ��ʼ��
	SeqList List;

	//��ʼ��˳���
	InitList(&List);

	ElemType Elem;	//����ʵ��������ں�����ͨ������ַ�����ı����ֵ��

	if (!ListEmpty(&List))
	{
		cout << left;

		//����˳���
		cout << setw(50) << "1.List Elements: ";
		ListTraverse(&List);

		//��ӡ˳����ȣ�
		cout << setw(50) << "2.List Length: " << ListLength(&List) << endl;

		//��ӡ������Ԫ�أ�
		if (GetElem(&List, 3, &Elem))
			cout << setw(50) << "3.The third one: " << Elem << endl;

		//��ӡԪ��11��λ��:
		cout << setw(50) << "4.Position of the 11th one: " << LocateElem(&List, 11) << endl;

		//��ӡλ��9ǰ���Ԫ�أ�
		if (PriorElem(&List, 9, &Elem))
			cout << setw(50) << "5.Prior Element 9: " << Elem << endl;

		//��ӡλ��18�����Ԫ�أ�
		if (NextElem(&List, 18, &Elem))
			cout << setw(50) << "6.Next Element 18: " << Elem << endl;

		//��ӡ������Ԫ�ز�����ΪElem��
		if (SetElem(&List, 3, &Elem))
			cout << setw(50) << "7.The 3th one before reseting: " << Elem << endl;

		//����Elem������λ�ϣ�����ӡ�µ�˳���
		if (InsertElem(&List, 3, Elem))
		{
			cout << setw(50) << "8.List Elements after inserting: ";
			ListTraverse(&List);
		}

		//ɾ��������Ԫ�غ��ӡ˳���
		if (DeleteElem(&List, 3, &Elem))
		{
			cout << setw(50) << "9.List Elements after deleting the 3th one: ";
			ListTraverse(&List);
		}

	}
	system("pause");
	return 0;
}

