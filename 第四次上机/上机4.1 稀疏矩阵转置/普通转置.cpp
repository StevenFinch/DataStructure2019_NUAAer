/***************************************
 **   Filename： 普通转置.cpp
 **
 **   Compiler:  Visual Studio 2019
 **
 **   StudentID: 1618*****
 **
 **   Name:      Steven
 **
 ***************************************/
#include<iostream>
#include<fstream>
#include<iomanip>
#include<algorithm>

using namespace std;
const int MAXSIZE = 256;
typedef struct
{
	int i;//�к�
	int j;//�к�
	int e;//��ֵ
}triple;//�����е�ÿһ��Ԫ��
typedef struct
{
	triple data[MAXSIZE + 1];//�洢�ķ���Ԫ����,data[0]����
	int row_num;//��������
	int col_num;//��������
	int total_num;//�������Ԫ����
}SMatrix_;
void CreateSMatrix(SMatrix_& SMatrix)
{
	//���ļ�
	ifstream fin("SMatrix.txt");
	if (!fin)
	{
		cout << "�ļ���ȡʧ��";
		system("pause");
		exit(1);
	}//�ļ��ɹ���

	//��ȡ����Ԫ��
	char ch = fin.peek();
	if (EOF == ch)
	{//����Ϊ��
		cout << "����Ϊ��" << endl;
		system("pause");
		exit(1);
	}
	else
	{//����ǿ�
		SMatrix.row_num = 1;
		SMatrix.col_num = 0;
		SMatrix.total_num = 0;
	}

	int p = 1;//����ϡ�������ÿһ��Ԫ��
	int temp;//��ʱ�洢Ԫ��

	while (!fin.eof())
	{
		if ('\n' == ch)//��β
		{
			SMatrix.row_num++;
			SMatrix.col_num = 0;
		}

		fin >> temp;//��ȡÿ��Ԫ��
		SMatrix.col_num++;
		if (temp != 0)//�ж��Ƿ����
		{
			SMatrix.data[p].i = SMatrix.row_num;
			SMatrix.data[p].j = SMatrix.col_num;
			SMatrix.data[p].e = temp;
			SMatrix.total_num++;
			p++;
		}
		ch = fin.peek();
	}
}
void OutputSMatrixInfo(SMatrix_& SMatrix)
{
	cout << "Sparse Matrix Info: " << endl;
	cout << "1.Row   Number: " << SMatrix.row_num << endl;
	cout << "2.Col   Number: " << SMatrix.col_num << endl;
	cout << "3.Total Number: " << SMatrix.total_num << endl;
	cout << "4.SMatrix Data: " << endl;
	for (int i = 1; i < SMatrix.total_num + 1; i++)
		cout << setw(16) << '(' << SMatrix.data[i].i << ' ' << SMatrix.data[i].j << ' ' << SMatrix.data[i].e << ')' << endl;
}
SMatrix_ NormalTransposeSMatrix(SMatrix_& SMatrix)
{
	//��ʼ��ת�ú����˳���
	SMatrix_ SMr;
	SMr.row_num = SMatrix.col_num;
	SMr.col_num = SMatrix.row_num;
	SMr.total_num = SMatrix.total_num;

	//����һ��ԭ���󣬰�������������ת�ú���������������ת�þ���˳�����
	int p = 1;//������
	for (int colCount = 1; colCount < SMatrix.col_num + 1; colCount++)
	{
		for (int i = 1; i < SMatrix.total_num + 1; i++)
		{
			if (SMatrix.data[i].j == colCount)
			{
				SMr.data[p] = SMatrix.data[i];
				swap(SMr.data[p].i, SMr.data[p].j);
				p++;
			}
		}
	}
	return SMr;
}
int main()
{
	SMatrix_ SMatrix;
	CreateSMatrix(SMatrix);
	OutputSMatrixInfo(SMatrix);
	SMatrix_ SMr = NormalTransposeSMatrix(SMatrix);
	OutputSMatrixInfo(SMr);
	return 0;
}