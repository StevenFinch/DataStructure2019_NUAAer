#include"HuffmanCoding.h"
using namespace std;

void HuffmanCoding::Coding()
{
	this->WriteCodeTxt();
	this->WriteSourceCodeTxt();
	int left = this->WriteSourceCodeDat();
	this->DecodeTargetCodeTxt(left);
	this->DecodeTargetTxt();
}

HuffmanCoding::HuffmanCoding(string sourcefile)
{
	n = 0;
	hufcode_ = (HufCode*)malloc((128 + 1) * sizeof(HufCode));
	sourcefile_ = sourcefile;
	ReadSource();
	CreateHufTree();
	Encoding();
}

void Select(HufNode*& huftree_, int m, int& s1, int& s2)
{
	int i, j;
	int* a = (int*)malloc((m + 1) * sizeof(int));

	for (i = 1, j = 1; i < m + 1; i++)
	{//把parent为0的结点复制到a[]中
		if (huftree_[i].parent == 0)
		{
			a[j++] = huftree_[i].fre;
		}
	}
	for (i = 1; i < j - 1; i++)
	{//对a[]冒泡排序
		for (int k = i + 1; k < j; k++)
		{
			if (a[i] > a[k])
				swap(a[i], a[k]);
		}
	}
	//找出s1, s2
	for (i = 1; i <= m; i++)
	{
		if (huftree_[i].fre == a[1] && huftree_[i].parent == 0)
		{
			s1 = i;
			break;
		}
	}
	for (i = 1; i <= m; i++)
	{
		if (huftree_[i].fre == a[2] && huftree_[i].parent == 0 && i != s1)
		{
			s2 = i;
			break;
		}
	}
	free(a);
}

//统计
void HuffmanCoding::ReadSource()
{
	ifstream fin(sourcefile_);
	unsigned char now;//当前字符
	while (fin)
	{
		now = fin.get();
		int i;
		//已经出现过
		for (i = 1; i < n + 1; i++)
		{
			if (hufcode_[i].val == now)
			{
				hufcode_[i].fre++;
				break;
			}
		}
		//新字符
		if (i == n + 1)
		{
			hufcode_[i].val = now;
			hufcode_[i].fre = 1;
			n++;
		}
	}
	fin.close();
}

//建树
void HuffmanCoding::CreateHufTree()
{
	huftree_ = (HufNode*)malloc((2 * n) * sizeof(HufNode));//一共有2n-1个结点，其中0号位置闲置
	if (NULL == huftree_)
		exit(OVERFLOW);
	int i;
	//初始化叶节点
	for (i = 1; i < n + 1; i++)
	{
		huftree_[i].val = hufcode_[i].val;
		huftree_[i].fre = hufcode_[i].fre;
		huftree_[i].parent = 0;
		huftree_[i].lchild = 0;
		huftree_[i].rchild = 0;
	}
	//建树
	for (i; i < 2 * n; i++)
	{
		int s1, s2;
		Select(huftree_, i - 1, s1, s2);
		huftree_[s1].parent = huftree_[s2].parent = i;
		huftree_[i].val = '\0';
		huftree_[i].fre = huftree_[s1].fre + huftree_[s2].fre;
		huftree_[i].parent = 0;
		huftree_[i].lchild = s1;
		huftree_[i].rchild = s2;
	}
}

//字符编码
void HuffmanCoding::Encoding()
{
	int i;
	for (i = 1; i < n + 1; i++)
	{//字符编码
		int t = 0;
		for (int c = i, p = huftree_[i].parent; p != 0; c = p, p = huftree_[p].parent)
		{
			if (huftree_[p].lchild == c)
				hufcode_[i].code[t++] = '0';
			else
				hufcode_[i].code[t++] = '1';
		}
		reverse(hufcode_[i].code, hufcode_[i].code + t);
		hufcode_[i].code[t++] = '\0';
	}
}

//字符编码文本
void HuffmanCoding::WriteCodeTxt()
{
	ofstream fout("code.txt");
	int i;
	for (i = 1; i < n + 1; i++)
	{
		fout << left;
		fout << setw(5) << hufcode_[i].val << setw(20) << hufcode_[i].code << endl;
	}
	fout.close();
}

//文档编码文本
void HuffmanCoding::WriteSourceCodeTxt()
{
	ifstream fin("Source.txt");
	ofstream fout("SourceCode.txt");
	unsigned char t;
	while (fin)
	{
		t = fin.get();
		for (int i = 1; i < n + 1; i++)
		{
			if (hufcode_[i].val == t)
			{
				fout << hufcode_[i].code;
			}
		}
	}
	fout.close();
	fin.close();
}

//文档编码二进制文本
int HuffmanCoding::WriteSourceCodeDat()
{
	ifstream fin("SourceCode.txt");
	ofstream fout("SourceCode.dat", ios::binary);
	unsigned char c = '\0';
	unsigned char now;
	int m = 0;
	int left = 0;
	fin >> now;
	while (fin)
	{
		for (int i = 1; i < 9; i++)
		{	
			if (now == '1')
				c = (c << 1) | 0x01;
			else
				c = (c << 1);
			fin >> now;
			if (fin.eof())
			{
				left = 8 - i;
				for (int j = 1; j < left + 1; j++)
				{
					c = (c << 1);
				}
				break;
			}
		}//end for
		fout.write((char*)&c, sizeof(c));
	}//end while
	fout.close();
	fin.close();
	return left;
}

//解码后编码文本
void HuffmanCoding::DecodeTargetCodeTxt(int left)
{
	ifstream fin("SourceCode.dat", ios::binary);
	ofstream fout("TargetCode.txt");
	unsigned char c;
	fin.read((char*)&c, sizeof(c));
	while (fin)
	{
		for (int i = 1; i < 9; i++)
		{
			if ((c & 0x80) == 0x80)
				fout << 1;
			else
				fout << 0;
			c <<= 1;
		}
		fin.read((char*)&c, sizeof(c));
	}
	fout.seekp(-left * (int)sizeof(char), fout.end);
	fout << "########";
	fout.close();
	fin.close();
}

//解码后文本
void HuffmanCoding::DecodeTargetTxt()
{
	ifstream fin("TargetCode.txt");
	ofstream fout("Target.txt");
	unsigned char t = '\0';
	//从根节点走到叶节点然后输出当前字符
	while (fin)
	{
		int i = 2 * n - 1;
		while (0 != huftree_[i].lchild && 0 != huftree_[i].rchild)
		{
			fin >> t;
			if ('0' == t)
				i = huftree_[i].lchild;
			else if ('1' == t)
				i = huftree_[i].rchild;
			else//'#'
				break;
		}
		if ('#' == t)
			break;
		fout << huftree_[i].val;
	}
	fout.close();
	fin.close();
}

HuffmanCoding::~HuffmanCoding()
{
	free(huftree_);
	free(hufcode_);
}

