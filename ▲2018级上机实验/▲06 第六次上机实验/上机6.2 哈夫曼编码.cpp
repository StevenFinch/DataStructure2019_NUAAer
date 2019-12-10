/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/11/14
**	ID: 161840225   */
#include<iostream>
#include<algorithm>

using namespace std;

typedef struct
{
	unsigned weight;
	unsigned parent, lchild, rchild;
}HTNode, * HufTree;

typedef char** HufCode;

void Select_two_small(HufTree& HT, int n, int& s1, int& s2)
{
	int i, j;
	int* a = (int*)malloc((n + 1) * sizeof(int));
	if (NULL == a)
		exit(OVERFLOW);

	for (i = 1, j = 1; i < n + 1; i++)
	{//把parent为0的结点复制到a[]中
		if (HT[i].parent == 0)
			a[j++] = HT[i].weight;
	}
	for (i = 1; i < j - 1; i++)
	{//Bubblesort to a[]
		for (int k = i + 1; k < j; k++)
			if (a[i] > a[k])
				swap(a[i], a[k]);
	}
	//找出s1, s2
	for (i = 1; i <= n; i++)
	{
		if (HT[i].weight == a[1] && HT[i].parent == 0)
		{
			s1 = i;
			break;
		}
	}
	for (i = 1; i <= n; i++)
	{
		if (HT[i].weight == a[2] && HT[i].parent == 0 && i != s1)
		{
			s2 = i;
			break;
		}
	}
	free(a);
}
void HuffmanCoding(HufTree& HT, HufCode& HC, int* weight, int n)
{
	if (n <= 1)
		return;
	int tn = 2 * n - 1;//结点总数
	int i;
	int s1, s2;//找两个权值最小且无父亲的叶子节点
	HT = (HufTree)malloc((tn + 1) * sizeof(HTNode));//节点总数加一，0号位置闲置
	if (NULL == HT)
		exit(OVERFLOW);

	for (i = 1; i < n + 1; i++)
	{//叶子节点初始化
		HT[i].weight = weight[i];
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (i; i < tn + 1; i++)
	{//建树
		Select_two_small(HT, i - 1, s1, s2);
		HT[s1].parent = HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
		HT[i].parent = 0;
	}
	HC = (HufCode)malloc((n + 1) * sizeof(char*));
	if (NULL == HC)
		exit(OVERFLOW);

	char* code = (char*)malloc(n * sizeof(char));//n个叶节点编码长度最长为n-1，最后一位存放'\0'
	if (NULL == code)
		exit(OVERFLOW);

	for (i = 1; i < n + 1; i++)
	{//遍历所有叶节点
		int t = 0;
		for (int child = i, parent = HT[i].parent; parent != 0; child = parent, parent = HT[parent].parent)
		{//对每个叶节点编码（从当前叶节点按照到根节点路径返回）
			if (HT[parent].lchild == child)
				code[t++] = '0';//左分支为0
			else
				code[t++] = '1';//右分支为1
		}
		reverse(code, code + t);
		code[t++] = '\0';
		HC[i] = (char*)malloc(t * sizeof(char));
		if (NULL == HC[i])
			exit(OVERFLOW);
		strcpy_s(HC[i], strlen(code) + 1, code);//将临时空间编码copy到HC表中
	}
	free(code);
}
int main()
{
	HufTree HT;
	HufCode HC;
	int n;
	int i;

	cout << "Number of Node: " << endl;
	cin >> n;
	int* weight = (int*)malloc((n + 1) * sizeof(int));
	if (NULL == weight)
		return -1;

	cout << "Weight of Node: " << endl;
	for (i = 1; i < n + 1; i++)
	{
		cin >> weight[i];
	}
	HuffmanCoding(HT, HC, weight, n);

	cout << "HuffmanTree: " << endl;
	for (i = 1; i < 2 * n; i++)
	{
		cout << i << ": " << HT[i].weight << " " << HT[i].parent << " " << HT[i].lchild << " " << HT[i].rchild << endl;
	}

	cout << "HuffmanCode: " << endl;
	for (i = 1; i <= n; i++)
	{
		cout << HT[i].weight << ": " << HC[i] << endl;
	}
	free(weight);
	free(HT);
	return 0;
}

