/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/10
**	ID: 161840225   */
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

struct key
{//Կ�׺�
	int num;
	int status;
};
struct node
{//�¼�
	int num;//ȡ��Կ�ױ��
	int time;//ȡ������ʱ��
	int flag;//ȡ���ǻ�
};
struct Queue
{//ģ�����
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
	cout << "                                                            ��"<<endl;
	cout << "                                                   ��������������������" << endl;
	cout << "                                                   |";
	for (j = 1; j < n + 1; j++)
	{
		cout << ' ' << ks[j].num << " |";
	}
	cout << endl << "                                                   ��������������������" << endl;
	cout << "" << endl;
	for (j = q.front; j < q.rear; j++)
	{
		cout << "                                                    ����" << setfill('0') << setw(2) << q.qns[j].time << "ʱ��";
		if (q.qns[j].flag == 0)
			cout << "ȡ" << q.qns[j].num << "��Կ��";
		else
			cout << "��" << q.qns[j].num << "��Կ��";
		cout << endl <<endl;
	}
}
int main()
{
	int n, k;//�����������軹�¼�����
	int w, s, c;//Կ�ױ�ţ����ʱ�䣬�Ͽ�ʱ��
	int i, j;
	node temp;
	ifstream fin("key.txt");
	fin >> n >> k;
	struct key* ks = (key*)malloc((n + 1) * sizeof(key));//���йҹ�
	struct node* ns = (node*)malloc((2 * k + 1) * sizeof(node));//�����¼�
	struct Queue q = { (node*)malloc((2 * k + 1) * sizeof(node)), 1, 1, 0 };
	for (i = 1; i < n + 1; i++)
	{//��ʼ������Կ��
		ks[i].num = i;
		ks[i].status = 1;//���йҹ�����Կ��
	}
	for (i = 1; i < 2 * k + 1; i += 2)
	{//ͳ�������¼�
		fin >> w >> s >> c;
		ns[i].num = w;
		ns[i].time = s;//ȡ��ʱ��
		ns[i].flag = 0;//0����ȡ
		ns[i + 1].num = w;
		ns[i + 1].time = s + c;//����ʱ��
		ns[i + 1].flag = 1;//1����
	}
	//�������¼���ʱ���������
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
	//�����¼��������
	for (i = 1; i < 2 * k + 1; i++)
	{
		q.Enqueue(ns[i]);
	}
	//ģ���¼�����
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