/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/10/30
**	ID: 161840225   */
#include<iostream>
#include<fstream>
#include<iomanip>
#include<algorithm>

using namespace std;
const int MAXSIZE = 256;
typedef struct
{
	int i;//行号
	int j;//列号
	int e;//数�?
}triple;//矩阵中的每一个元�?
typedef struct
{
	triple data[MAXSIZE + 1];//存储的非零元数据,data[0]弃用
	int row_num;//矩阵行数
	int col_num;//矩阵列数
	int total_num;//矩阵非零元个�?
}SMatrix_;
void CreateSMatrix(SMatrix_& SMatrix)
{
	//打开文件
	ifstream fin("SMatrix.txt");
	if (!fin)
	{
		cout << "文件读取失败";
		system("pause");
		exit(1);
	}//文件成功打开

	//读取矩阵元素
	char ch = fin.peek();
	if (EOF == ch)
	{//矩阵为空
		cout << "矩阵为空" << endl;
		system("pause");
		exit(1);
	}
	else
	{//矩阵非空
		SMatrix.row_num = 1;
		SMatrix.col_num = 0;
		SMatrix.total_num = 0;
	}

	int p = 1;//遍历稀疏矩阵中每一个元�?
	int temp;//临时存储元素

	while (!fin.eof())
	{
		if ('\n' == ch)//行尾
		{
			SMatrix.row_num++;
			SMatrix.col_num = 0;
		}

		fin >> temp;//读取每个元素
		SMatrix.col_num++;
		if (temp != 0)//判断是否非零
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
	SMatrix_ SMr;
	SMr.row_num = SMatrix.col_num;
	SMr.col_num = SMatrix.row_num;
	SMr.total_num = SMatrix.total_num;

	//在原三元组顺序表中按列数递增挑出矩阵元素存入转置后矩阵的三元组顺序表�?
	int p = 1;//计数�?
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