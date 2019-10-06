/***************************************
 **   Filename�� ˳���ѡ������.cpp
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
	List->pElem = NULL;	//�����ڴ�֮ǰ���뽫ָ������ΪNULL������ΪҰָ�룬�����޷��ж��ڴ��Ƿ����ɹ���
	List->pElem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	//��������ڴ��Ƿ�ɹ�
	if (NULL == List->pElem)
		exit(OVERFLOW);
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
bool SelectSortList(SeqList* List)	//���Ĵ���
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
//�����������Ժ�����
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