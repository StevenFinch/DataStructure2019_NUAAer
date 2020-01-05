#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

struct date
{
	int year;
	int month;
	int day;
	date(int _year = 0, int _month = 0, int _day = 0)
	{
		year = _year;
		month = _month;
		day = _day;
	}
};

struct member
{
	string name;//姓名
	date birthdate;//出生日期
	bool ismarried;//婚否
	string address;//地址
	bool isliving;//是否健在
	date deathdate;//死亡日期
	int generation;//代
	member* firstchild;//左孩子
	member* nextsibling;//右兄弟
};

typedef member* tn, * Tree;

ostream& operator<<(ostream& out, const date& d)
{
	out << d.year << "/" << d.month << "/" << d.day;
	return out;
}

ostream& operator<<(ostream& out, const member& m)
{

	out << left;
	out << setw(10) << "a.姓名：" << m.name << endl;
	out << setw(10) << "b.出生日期：" << m.birthdate << endl;
	out << setw(10) << "c.住址：" << m.address << endl;

	out << setw(10) << "d.婚否：";
	if (m.ismarried)
		cout << "已婚";
	else
		cout << "未婚";
	out << endl;

	out << setw(10) << "e.健在：";
	if (m.isliving)
		cout << "健在";
	else
		cout << "已逝";
	out << endl;

	if (!m.isliving)
		out << "去世日期：" << m.deathdate << endl;

	return out;
}

//输出家谱成员信息
void OutputFamily(Tree T)
{
	if (T)
	{
		cout << *T;
		cout << "**************************" << endl;
		OutputFamily(T->firstchild);
		OutputFamily(T->nextsibling);
	}
}

//先序序列创建CSTree
void CreateTree(Tree& T, istream& fin, int generation)
{
	if (fin.eof())
	{
		T = NULL;
		return;
	}
	T = new member;

	fin >> T->name;
	fin >> T->birthdate.year >> T->birthdate.month >> T->birthdate.day;
	fin >> T->ismarried;//bool
	fin >> T->address;
	fin >> T->isliving;//bool
	fin >> T->deathdate.year >> T->deathdate.month >> T->deathdate.day;

	T->generation = generation;

	generation++;
	CreateTree(T->firstchild, fin, generation);

	generation--;
	CreateTree(T->nextsibling, fin, generation);

	generation--;
	return;
}

//销毁该树
void DestroyTree(Tree& T)
{
	if (!T)
		return;
	DestroyTree(T->firstchild);
	T->firstchild = NULL;
	free(T);
	T = NULL;
}

//通过姓名查找成员信息
bool SearchByName(Tree T, string name, tn& m)
{
	static bool flag = false;
	if (T)
	{
		if (T->name == name)
		{
			flag = true;
			cout << *T;
			cout << "**************************" << endl;
		}
		SearchByName(T->firstchild, name, m);
		SearchByName(T->nextsibling, name, m);
	}
	return flag;
}

bool Search_FaS(Tree T, string name)
{
	Tree p;
	if (T)
	{
		if (T->name == name)
		{
			if (T->firstchild)
			{
				cout << "孩子为：" << endl;
				cout << *T->firstchild;
				p = T->firstchild;
				while (p->nextsibling)
				{
					cout << *p->nextsibling;

					if (p->nextsibling->nextsibling != NULL)
						p = p->nextsibling;
					else
						break;
				}
			}


		}
		else
		{
			if (T->firstchild)
			{
				if (T->firstchild->name == name)
				{
					cout << "父亲为：" << endl;
					cout << *T;
				}
				else
				{
					p = T->firstchild;

					while (p->nextsibling)
					{
						if (p->nextsibling->name == name)
						{
							cout << "父亲为：" << endl;
							cout << *T;
						}
						if (p->nextsibling->nextsibling)
							p = p->nextsibling;
						else
							break;
					}
				}
			}
		}
	}
	if (T->firstchild)
		Search_FaS(T->firstchild, name);
	if (T->nextsibling)
		Search_FaS(T->nextsibling, name);

	return true;
}

//通过年份查找成员信息
bool SearchByYear(Tree T, int year)
{
	static bool flag = false;
	if (T)
	{
		if (T->birthdate.year == year)
		{
			flag = true;
			cout << *T;
			cout << "**************************" << endl;
		}
		SearchByYear(T->firstchild, year);
		SearchByYear(T->nextsibling, year);
	}
	return flag;
}

//打印某代人全部成员信息
bool PrintGenMember(Tree T, int i)
{
	static bool flag = false;
	if (T)
	{
		if (T->generation == i)
		{
			flag = true;
			cout << *T;
			cout << "**************************" << endl;
		}
		PrintGenMember(T->firstchild, i);
		PrintGenMember(T->nextsibling, i);
	}
	return flag;
}

//添加孩子
bool AddChild(Tree& T, string name)
{
	if (T)
	{
		if (T->name == name)
		{
			//建一个结点
			Tree p = new member;

			cout << "请输入姓名" << endl;
			cin >> p->name;

			cout << "请输入生日" << endl;
			cin >> p->birthdate.year >> p->birthdate.month >> p->birthdate.day;

			cout << "请输入婚姻状况" << endl;
			cin >> p->ismarried;

			cout << "请输入地址" << endl;
			cin >> p->address;

			cout << "请输入存活情况" << endl;
			cin >> p->isliving;

			if (p->isliving == 0)
			{
				cout << "请输入死亡日期" << endl;
				cin >> p->deathdate.year >> p->deathdate.month >> p->deathdate.day;
			}
			else
			{
				p->deathdate.year = 0;
				p->deathdate.month = 0;
				p->deathdate.day = 0;
			}

			p->generation = T->generation + 1;
			p->nextsibling = NULL;
			p->firstchild = NULL;

			cout << *p;

			//当前节点没有孩子
			if (!T->firstchild)
			{
				T->firstchild = p;
				cout << *T;
				cout << *T->firstchild;
			}

			//当前节点有孩子
			else
			{
				Tree q = T->firstchild;
				while (q->nextsibling)
					q = q->nextsibling;
				q->nextsibling = p;
				cout << "添加完成" << endl;
				return true;
			}
		}
		else
		{
			AddChild(T->firstchild, name);
			AddChild(T->nextsibling, name);
		}
	}
	return true;
}

//删除某成员及其后代
bool DeleteMember(Tree& T, string name)
{
	Tree p;
	if (T)
	{
		p = T;
		if (p->nextsibling)
			p = p->nextsibling;

		//祖先为删除节点
		if (T->name == name)
		{
			DestroyTree(T);
			T = p;
			return true;
		}
		else//寻找name成员
		{
			if (T->firstchild)//左孩子是删除节点
			{
				if (T->firstchild->name == name)
				{
					p = T->firstchild;

					//有右兄弟则保留
					if (p->nextsibling)
					{
						p = p->nextsibling;
						DestroyTree(T->firstchild);
						T->firstchild = p;
					}
					//没有右兄弟则全部删掉
					else
					{
						T->firstchild = NULL;
						DestroyTree(p);
					}
				}
				else//按照右兄弟遍历森林的某一层
				{
					p = T->firstchild;
					while (p->nextsibling)
					{
						if (p->nextsibling->name == name)
						{
							DestroyTree(p->nextsibling);
							p->nextsibling = NULL;
							break;
						}
						if (p->nextsibling->nextsibling)
							p = p->nextsibling;
						else
							break;
					}
				}
			}
		}
	}
	if (T->firstchild)
		DeleteMember(T->firstchild, name);
	if (T->nextsibling)
		DeleteMember(T->nextsibling, name);

	return true;
}

//修改成员信息
bool Modify_Info(Tree T, string name)
{
	if (T != NULL)
	{
		if (T->name == name)
		{
			cout << "你要修改什么？" << endl;
			cout << "1.修改姓名\n2.修改生日\n3.修改婚姻状况\n4.修改地址\n5.修改存活情况" << endl;
			int num;
			cin >> num;
			if (num == 1)
			{
				string new_name;
				cin >> new_name;
				T->name = new_name;
			}
			else if (num == 2)
				cin >> T->birthdate.year >> T->birthdate.month >> T->birthdate.day;
			else if (num == 3)
				cin >> T->ismarried;
			else if (num == 4)
			{
				string new_address;
				cin >> new_address;
				T->address = new_address;
			}
			else if (num == 5)
			{
				cin >> T->isliving;
				if (T->isliving == false)			// 如果已经死亡
				{
					cout << "请输入死亡日期" << endl;
					cin >> T->deathdate.year >> T->deathdate.month >> T->deathdate.day;
				}
				else
				{
					T->deathdate.year = 0;
					T->deathdate.month = 0;
					T->deathdate.day = 0;
				}
			}
		}

		else
		{
			Modify_Info(T->firstchild, name);
			Modify_Info(T->nextsibling, name);
		}
	}
	return true;
}


//查询某代所有成员
void Generation(Tree T, string name, int& gen)
{
	if (T != NULL)
	{
		if (T->name == name)
		{
			gen = T->generation;
		}

		else
		{
			Generation(T->firstchild, name, gen);
			Generation(T->nextsibling, name, gen);
		}
	}
}

int main()
{
	Tree T = NULL;
	member* m = new member;

	ifstream fin("family.txt");

	CreateTree(T, fin, 1);

	fin.close();
	int num;
	int year;
	string name;
	string name1, name2;
	int gen1, gen2;
	int generation;
	while (true)
	{
		cout << endl << endl;
		cout << "--------家谱管理系统-----------" << endl << endl;
		cout << "|1.查询某一代所有成员----------" << endl << endl;
		cout << "|2.输入姓名，查询该成员信息----" << endl << endl;
		cout << "|3.显示家谱-------------------" << endl << endl;
		cout << "|4.输入出生日期，查询成员信息-" << endl << endl;
		cout << "|5.输入两个姓名，查询两人关系-" << endl << endl;
		cout << "|6.输入姓名，给他添加孩子-----" << endl << endl;
		cout << "|7.输入姓名，删除该成员-------" << endl << endl;
		cout << "|8.输入姓名，修改该成员信息---" << endl << endl;
		cout << "|9.退出-----------------------" << endl << endl;
		cout << "------------------------------" << endl << endl;
		cout << "请选择你的操作：";
		cin >> num;
		cout << endl << endl;
		if (num == 1)
		{
			cout << "请输入要查询第几代：";

			cin >> generation;
			cout << endl << endl;
			cout << "**************************" << endl;
			if (!PrintGenMember(T, generation))
				cout << "404";
		}
		else if (num == 2)
		{
			cout << "请输入要查询的人的姓名：" << endl;
			cin >> name;
			if (!SearchByName(T, name, m))
				cout << 404;
			Search_FaS(T, name);
		}
		else if (num == 3)
		{
			OutputFamily(T);
		}
		else if (num == 4)
		{
			cout << "请输入年份：" << endl;
			cin >> year;

			if (!SearchByYear(T, year))
				cout << "404";
		}
		else if (num == 5)
		{
			cout << "请输入两个名字，查看其关系：" << endl;
			cin >> name >> name2;
			Generation(T, name, gen1);
			Generation(T, name2, gen2);
			generation = abs(gen1 - gen2);
			switch (generation)
			{
			case 0:cout << "兄弟" << endl; break;
			case 1:cout << "父子" << endl; break;
			case 2:cout << "祖孙" << endl; break;
			default:cout << "三代祖孙以上" << endl;
			}
		}
		else if (num == 6)
		{
			cout << "请输入要为谁添加孩子" << endl;
			cin >> name;
			AddChild(T, name);
		}
		else if (num == 7)
		{
			cout << "请输入要删除的人的姓名" << endl;
			cin >> name;
			DeleteMember(T, name);
		}
		else if (num == 8)
		{
			cout << "请输入要修改信息人的姓名" << endl;
			cin >> name;
			Modify_Info(T, name);
		}
		else if (num == 9)
			break;
		else continue;
	}


	return 0;
}