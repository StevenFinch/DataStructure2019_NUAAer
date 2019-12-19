/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/18
**	ID: 161840225   */

#include <cstdio>
#include <iostream>
#include <ctime>

char op[5] = { '#','+','-','*','/', };//0号位闲置

//计算两个数的运算结果

double cal(double x, double y, int op)
{
	switch (op)
	{
	case 1:
		return x + y;
	case 2:
		return x - y;
	case 3:
		return x * y;
	case 4:
		return x / y;
	}
}

//每一种遍历情况下的运算顺序（括号的位置）

double cal_m1(double i, double j, double k, double t, int op1, int op2, int op3)
{
	double r1, r2, r3;
	r1 = cal(i, j, op1);
	r2 = cal(r1, k, op2);
	r3 = cal(r2, t, op3);
	return r3;
}

double cal_m2(double i, double j, double k, double t, int op1, int op2, int op3)
{
	double r1, r2, r3;
	r1 = cal(i, j, op1);
	r2 = cal(k, t, op3);
	r3 = cal(r1, r2, op2);
	return r3;
}

double cal_m3(double i, double j, double k, double t, int op1, int op2, int op3)
{
	double r1, r2, r3;
	r1 = cal(j, k, op2);
	r2 = cal(i, r1, op1);
	r3 = cal(r2, t, op3);
	return r3;
}

double cal_m4(double i, double j, double k, double t, int op1, int op2, int op3)
{
	double r1, r2, r3;
	r1 = cal(k, t, op3);
	r2 = cal(j, r1, op2);
	r3 = cal(i, r2, op1);
	return r3;
}

double cal_m5(double i, double j, double k, double t, int op1, int op2, int op3)
{
	double r1, r2, r3;
	r1 = cal(j, k, op2);
	r2 = cal(r1, t, op3);
	r3 = cal(i, r2, op1);
	return r3;
}

//符号位全排列

int get_24(int i, int j, int k, int t)
{
	for (int op1 = 1; op1 <= 4; op1++)
	{
		for (int op2 = 1; op2 <= 4; op2++)
		{
			for (int op3 = 1; op3 <= 4; op3++)
			{
				if (cal_m1(i, j, k, t, op1, op2, op3) == 24)
				{
					printf("((%d%c%d)%c%d)%c%d\n", i, op[op1], j, op[op2], k, op[op3], t);
					return 1;
				}
				if (cal_m2(i, j, k, t, op1, op2, op3) == 24)
				{
					printf("(%d%c%d)%c(%d%c%d)\n", i, op[op1], j, op[op2], k, op[op3], t);
					return 1;
				}
				if (cal_m3(i, j, k, t, op1, op2, op3) == 24)
				{
					printf("(%d%c(%d%c%d))%c%d\n", i, op[op1], j, op[op2], k, op[op3], t);
					return 1;
				}
				if (cal_m4(i, j, k, t, op1, op2, op3) == 24)
				{
					printf("%d%c(%d%c(%d%c%d))\n", i, op[op1], j, op[op2], k, op[op3], t);
					return 1;
				}
				if (cal_m5(i, j, k, t, op1, op2, op3) == 24)
				{
					printf("%d%c((%d%c%d)%c%d)\n", i, op[op1], j, op[op2], k, op[op3], t);
					return 1;
				}

			}
		}
	}
	return 0;
}

//数据读取及遍历数字位

int main()
{
	int a[4];
	int t1, t2, t3, t4;
	int flag;
	int n = 10;
	while (n--)
	{
		for (int i = 0; i < 4; i++)
		{
			a[i] = (rand() % 13) + 1;
			printf("%d ", a[i]);
		}
		printf("    ");
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (j == i)
					continue;
				for (int k = 0; k < 4; k++)
				{
					if (i == k || j == k)
						continue;
					for (int t = 0; t < 4; t++)
					{
						if (t == i || t == j || t == k)
							continue;
						t1 = a[i], t2 = a[j], t3 = a[k], t4 = a[t];

						flag = get_24(t1, t2, t3, t4);

						if (flag == 1)
							break;
					}
					if (flag == 1)
						break;
				}
				if (flag == 1)
					break;
			}
			if (flag == 1)
				break;
		}
		printf("\n");
		if (flag == 0)
			printf("-1\n");
	}
	return 0;
}