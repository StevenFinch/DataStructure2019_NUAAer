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
	string name;//����
	date birthdate;//��������
	bool ismarried;//���
	string address;//��ַ
	bool isliving;//�Ƿ���
	date deathdate;//��������
	int generation;//��
	member* firstchild;//����
	member* nextsibling;//���ֵ�
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
	out << setw(10) << "a.������" << m.name << endl;
	out << setw(10) << "b.�������ڣ�" << m.birthdate << endl;
	out << setw(10) << "c.סַ��" << m.address << endl;

	out << setw(10) << "d.���";
	if (m.ismarried)
		cout << "�ѻ�";
	else
		cout << "δ��";
	out << endl;

	out << setw(10) << "e.���ڣ�";
	if (m.isliving)
		cout << "����";
	else
		cout << "����";
	out << endl;

	if (!m.isliving)
		out << "ȥ�����ڣ�" << m.deathdate << endl;

	return out;
}

//������׳�Ա��Ϣ
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

//�������д���CSTree
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

//���ٸ���
void DestroyTree(Tree& T)
{
	if (!T)
		return;
	DestroyTree(T->firstchild);
	T->firstchild = NULL;
	free(T);
	T = NULL;
}

//ͨ���������ҳ�Ա��Ϣ
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
				cout << "����Ϊ��" << endl;
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
					cout << "����Ϊ��" << endl;
					cout << *T;
				}
				else
				{
					p = T->firstchild;

					while (p->nextsibling)
					{
						if (p->nextsibling->name == name)
						{
							cout << "����Ϊ��" << endl;
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

//ͨ����ݲ��ҳ�Ա��Ϣ
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

//��ӡĳ����ȫ����Ա��Ϣ
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

//��Ӻ���
bool AddChild(Tree& T, string name)
{
	if (T)
	{
		if (T->name == name)
		{
			//��һ�����
			Tree p = new member;

			cout << "����������" << endl;
			cin >> p->name;

			cout << "����������" << endl;
			cin >> p->birthdate.year >> p->birthdate.month >> p->birthdate.day;

			cout << "���������״��" << endl;
			cin >> p->ismarried;

			cout << "�������ַ" << endl;
			cin >> p->address;

			cout << "�����������" << endl;
			cin >> p->isliving;

			if (p->isliving == 0)
			{
				cout << "��������������" << endl;
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

			//��ǰ�ڵ�û�к���
			if (!T->firstchild)
			{
				T->firstchild = p;
				cout << *T;
				cout << *T->firstchild;
			}

			//��ǰ�ڵ��к���
			else
			{
				Tree q = T->firstchild;
				while (q->nextsibling)
					q = q->nextsibling;
				q->nextsibling = p;
				cout << "������" << endl;
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

//ɾ��ĳ��Ա������
bool DeleteMember(Tree& T, string name)
{
	Tree p;
	if (T)
	{
		p = T;
		if (p->nextsibling)
			p = p->nextsibling;

		//����Ϊɾ���ڵ�
		if (T->name == name)
		{
			DestroyTree(T);
			T = p;
			return true;
		}
		else//Ѱ��name��Ա
		{
			if (T->firstchild)//������ɾ���ڵ�
			{
				if (T->firstchild->name == name)
				{
					p = T->firstchild;

					//�����ֵ�����
					if (p->nextsibling)
					{
						p = p->nextsibling;
						DestroyTree(T->firstchild);
						T->firstchild = p;
					}
					//û�����ֵ���ȫ��ɾ��
					else
					{
						T->firstchild = NULL;
						DestroyTree(p);
					}
				}
				else//�������ֵܱ���ɭ�ֵ�ĳһ��
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

//�޸ĳ�Ա��Ϣ
bool Modify_Info(Tree T, string name)
{
	if (T != NULL)
	{
		if (T->name == name)
		{
			cout << "��Ҫ�޸�ʲô��" << endl;
			cout << "1.�޸�����\n2.�޸�����\n3.�޸Ļ���״��\n4.�޸ĵ�ַ\n5.�޸Ĵ�����" << endl;
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
				if (T->isliving == false)			// ����Ѿ�����
				{
					cout << "��������������" << endl;
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


//��ѯĳ�����г�Ա
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
		cout << "--------���׹���ϵͳ-----------" << endl << endl;
		cout << "|1.��ѯĳһ�����г�Ա----------" << endl << endl;
		cout << "|2.������������ѯ�ó�Ա��Ϣ----" << endl << endl;
		cout << "|3.��ʾ����-------------------" << endl << endl;
		cout << "|4.����������ڣ���ѯ��Ա��Ϣ-" << endl << endl;
		cout << "|5.����������������ѯ���˹�ϵ-" << endl << endl;
		cout << "|6.����������������Ӻ���-----" << endl << endl;
		cout << "|7.����������ɾ���ó�Ա-------" << endl << endl;
		cout << "|8.�����������޸ĸó�Ա��Ϣ---" << endl << endl;
		cout << "|9.�˳�-----------------------" << endl << endl;
		cout << "------------------------------" << endl << endl;
		cout << "��ѡ����Ĳ�����";
		cin >> num;
		cout << endl << endl;
		if (num == 1)
		{
			cout << "������Ҫ��ѯ�ڼ�����";

			cin >> generation;
			cout << endl << endl;
			cout << "**************************" << endl;
			if (!PrintGenMember(T, generation))
				cout << "404";
		}
		else if (num == 2)
		{
			cout << "������Ҫ��ѯ���˵�������" << endl;
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
			cout << "��������ݣ�" << endl;
			cin >> year;

			if (!SearchByYear(T, year))
				cout << "404";
		}
		else if (num == 5)
		{
			cout << "�������������֣��鿴���ϵ��" << endl;
			cin >> name >> name2;
			Generation(T, name, gen1);
			Generation(T, name2, gen2);
			generation = abs(gen1 - gen2);
			switch (generation)
			{
			case 0:cout << "�ֵ�" << endl; break;
			case 1:cout << "����" << endl; break;
			case 2:cout << "����" << endl; break;
			default:cout << "������������" << endl;
			}
		}
		else if (num == 6)
		{
			cout << "������ҪΪ˭��Ӻ���" << endl;
			cin >> name;
			AddChild(T, name);
		}
		else if (num == 7)
		{
			cout << "������Ҫɾ�����˵�����" << endl;
			cin >> name;
			DeleteMember(T, name);
		}
		else if (num == 8)
		{
			cout << "������Ҫ�޸���Ϣ�˵�����" << endl;
			cin >> name;
			Modify_Info(T, name);
		}
		else if (num == 9)
			break;
		else continue;
	}


	return 0;
}