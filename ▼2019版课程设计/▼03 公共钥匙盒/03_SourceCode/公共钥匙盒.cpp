/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/10
**	ID: 161840225   */
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

struct key
{//钥匙盒
	int num;
	int status;
};
struct node
{//事件
	int num;//取还钥匙编号
	int time;//取还发生时间
	int flag;//取还是还
};
struct Queue
{//模拟队列
	struct node* qns;
	int front;
	int rear;
	int length;
	void Enqueue(struct node n)
	{
		qns[rear++] = n;
		length++;
	}
	struct node Dequeue()
	{
		length--;
		return qns[front++];
	}
};
void PrintStatus(struct Queue& q, struct key* ks, int n)
{
	int j;
	cout << "                                                            ▲"<<endl;
	cout << "                                                   ——————————" << endl;
	cout << "                                                   |";
	for (j = 1; j < n + 1; j++)
	{
		cout << ' ' << ks[j].num << " |";
	}
	cout << endl << "                                                   ——————————" << endl;
	cout << "" << endl;
	for (j = q.front; j < q.rear; j++)
	{
		cout << "                                                    将于" << setfill('0') << setw(2) << q.qns[j].time << "时刻";
		if (q.qns[j].flag == 0)
			cout << "取" << q.qns[j].num << "号钥匙";
		else
			cout << "还" << q.qns[j].num << "号钥匙";
		cout << endl <<endl;
	}
}
int main()
{
	int n, k;//教室数量，借还事件数量
	int w, s, c;//钥匙编号，借的时间，上课时长
	int i, j;
	node temp;
	ifstream fin("key.txt");
	fin >> n >> k;
	struct key* ks = (key*)malloc((n + 1) * sizeof(key));//所有挂钩
	struct node* ns = (node*)malloc((2 * k + 1) * sizeof(node));//所有事件
	struct Queue q = { (node*)malloc((2 * k + 1) * sizeof(node)), 1, 1, 0 };
	for (i = 1; i < n + 1; i++)
	{//初始化所有钥匙
		ks[i].num = i;
		ks[i].status = 1;//所有挂钩都有钥匙
	}
	for (i = 1; i < 2 * k + 1; i += 2)
	{//统计所有事件
		fin >> w >> s >> c;
		ns[i].num = w;
		ns[i].time = s;//取的时间
		ns[i].flag = 0;//0代表取
		ns[i + 1].num = w;
		ns[i + 1].time = s + c;//还的时间
		ns[i + 1].flag = 1;//1代表还
	}
	//对所有事件按时间进行排序
	for (i = 2 * k; i >= 1; i--)
	{
		for (j = 2; j <= i; j++)
		{
			if (ns[j - 1].time > ns[j].time)
			{
				temp = ns[j - 1];
				ns[j - 1] = ns[j];
				ns[j] = temp;
			}
			else if (ns[j - 1].time == ns[j].time)
			{
				if (ns[j - 1].flag == 1 && ns[j].flag == 1)
				{
					if (ns[j - 1].num > ns[j].num)
					{
						temp = ns[j - 1];
						ns[j - 1] = ns[j];
						ns[j] = temp;
					}
				}
				if (ns[j - 1].flag == 0 && ns[j].flag == 1)
				{
					temp = ns[j - 1];
					ns[j - 1] = ns[j];
					ns[j] = temp;
				}
			}
		}
	}
	//所有事件进入队列
	for (i = 1; i < 2 * k + 1; i++)
	{
		q.Enqueue(ns[i]);
	}
	//模拟事件发生
	while (q.length)
	{
		PrintStatus(q, ks, n);
		temp = q.Dequeue();
		if (temp.flag == 0)
		{
			for (j = 1; j < n + 1; j++)
			{
				if (ks[j].num == temp.num)
				{
					ks[j].num = 0;
					ks[j].status = 0;
				}
			}
		}
		else
		{
			for (j = 1; j < n + 1; j++)
			{
				if (ks[j].status == 0)
				{
					ks[j].num = temp.num;
					ks[j].status = 1;
					break;
				}
			}
		}

	}
	PrintStatus(q, ks, n);
	fin.close();
	return 0;
}