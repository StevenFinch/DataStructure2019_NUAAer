/*	Compiler: Visual Studio 2019
**	UpdateTime: 2019/12/18
**	ID: 161840225   */

/*
**	��һ�νӴ�EASYX����������«��ư�ʹ���
*/
#include "stdafx.h"
#include <graphics.h>
#include <algorithm>
#include <string>
#include <time.h>
#include <vector>
#include <ctime>

#define WIDTH 10
#define HEIGHT 6

#define GRID_WIDTH 60	// ���� 60 * 60

int data[HEIGHT][WIDTH] = { 0 };	// �����������
const int picCount = 4;   // ÿ��ͼƬ����ʾ����
IMAGE img[8];

// ��ʼ������
void InitData()
{
	int tmpData[HEIGHT - 2][WIDTH - 2] = { 0 };

	int picNum = 1;
	int curPicCount = 0;
	for (int j = 0; j < HEIGHT - 2; ++j)
	{
		for (int i = 0; i < WIDTH - 2; ++i)
		{
			// ��������
			tmpData[j][i] = picNum;
			curPicCount++;

			if (curPicCount == picCount)
			{
				picNum++;       // ͼƬ���꣬����һ��ͼƬ
				curPicCount = 0;
			}
		}
	}

	// �������
	std::random_shuffle((int*)tmpData, (int*)tmpData + (HEIGHT - 2) * (WIDTH - 2));

	// ������20*10������
	for (size_t i = 1; i < WIDTH - 1; i++)
	{
		for (size_t j = 1; j < HEIGHT - 1; j++)
		{
			data[j][i] = tmpData[j - 1][i - 1];
		}
	}

}

void LoadImage()
{
	for (size_t i = 0; i < _countof(img); i++)
	{
		std::string file = "./img/" + std::to_string(i + 1) + ".bmp";
		loadimage(&img[i], file.c_str());
	}
}

// �������
bool IsResembling(int x1, int y1, int x2, int y2)
{
	bool s1 = x1 != x2 || y1 != y2;//�����Լ����Լ�

	bool s2 = data[y1][x1] == data[y2][x2] && data[y1][x1] != 0 && data[y2][x2] != 0;//ͼ����ͬ

	return s1 == s2 ? true : false;
}

bool IsHLinked(int x1, int y1, int x2, int y2, std::vector<POINT>& line)
{
	if (y1 != y2)
	{
		// ������һ����
		return false;
	}

	int minX = min(x1, x2); // �ҵ���ߵĵ�
	int maxX = max(x1, x2);

	line.push_back({ x1, y1 });
	line.push_back({ x2, y2 });

	for (int i = minX + 1; i <= maxX - 1; i++)
	{
		if (data[y1][i] != 0)
		{
			line.clear();
			return false;
		}

		line.push_back({ i, y1 });
	}

	return true;
}

bool IsVLinked(int x1, int y1, int x2, int y2, std::vector<POINT>& line)
{
	if (x1 != x2)
	{
		// ������һ����
		return false;
	}

	int minY = min(y1, y2); // �ҵ���ߵĵ�
	int maxY = max(y1, y2);

	line.push_back({ x1,y1 });
	line.push_back({ x2,y2 });

	for (int i = minY + 1; i <= maxY - 1; i++)
	{
		if (data[i][x1] != 0)
		{
			line.clear();
			return false;
		}
		line.push_back({ x1, i });
	}

	return true;
}

bool IsZeroTurnLinked(int x1, int y1, int x2, int y2, std::vector<POINT>& line)
{
	if (IsHLinked(x1, y1, x2, y2, line))
	{
		return true;
	}

	if (IsVLinked(x1, y1, x2, y2, line))
	{
		return true;
	}

	return false;
}

bool IsOneTurnLinked(int x1, int y1, int x2, int y2, std::vector<std::vector<POINT> >& lines)
{
	int tmpPointX[2] = { x1, x2 };
	int tmpPointY[2] = { y2, y1 };// �ҵ�������ɫ�������



	for (size_t i = 0; i < _countof(tmpPointX); i++)
	{
		if (data[tmpPointY[i]][tmpPointX[i]] != 0)
		{
			continue;
		}
		if (IsZeroTurnLinked(tmpPointX[i], tmpPointY[i], x1, y1, lines[0])
			&& IsZeroTurnLinked(tmpPointX[i], tmpPointY[i], x2, y2, lines[1]))
		{
			return true;
		}
	}

	return false;
}

bool IsTwoTurnLinked(int x1, int y1, int x2, int y2, std::vector<std::vector<POINT> >& lines)
{
	// ˳��ͼ1���ӳ�������������е�
	for (size_t j = 0; j < HEIGHT; j++)
	{
		int tmpX1 = x1;
		int tmpY1 = j;

		if (j == y1)
		{
			continue;   // ��ͼ1�غ�
		}

		if (tmpX1 == x2 && tmpY1 == y2)
		{
			continue;   // ��ͼ2�غ�
		}

		int tmpX2 = x2;
		int tmpY2 = tmpY1;   // ��һ���������

		if (data[tmpY1][tmpX1] != 0
			|| data[tmpY2][tmpX2] != 0)
		{
			continue;
		}
		lines[0].clear();
		lines[1].clear();
		lines[2].clear();

		if (IsZeroTurnLinked(tmpX1, tmpY1, tmpX2, tmpY2, lines[0])
			&& IsZeroTurnLinked(tmpX1, tmpY1, x1, y1, lines[1])
			&& IsZeroTurnLinked(tmpX2, tmpY2, x2, y2, lines[2]))
		{
			return true;
		}
	}

	// ˳��ͼ1���ӳ��ߺ���������е�
	for (size_t j = 0; j < WIDTH; j++)
	{
		int tmpX1 = j;
		int tmpY1 = y1;

		if (j == x1)
		{
			continue;   // ��ͼ1�غ�
		}

		if (tmpX1 == x2 && tmpY1 == y2)
		{
			continue;   // ��ͼ2�غ�
		}

		int tmpX2 = tmpX1;
		int tmpY2 = y2;   // ��һ���������

		if (data[tmpY1][tmpX1] != 0
			|| data[tmpY2][tmpX2] != 0)
		{
			continue;
		}
		lines[0].clear();
		lines[1].clear();
		lines[2].clear();
		if (IsZeroTurnLinked(tmpX1, tmpY1, tmpX2, tmpY2, lines[0])
			&& IsZeroTurnLinked(tmpX1, tmpY1, x1, y1, lines[1])
			&& IsZeroTurnLinked(tmpX2, tmpY2, x2, y2, lines[2]))
		{
			return true;
		}
	}

	return false;
}

bool IsLinked(int x1, int y1, int x2, int y2, std::vector<std::vector<POINT> >& lines)
{
	lines.resize(3);

	if (IsZeroTurnLinked(x1, y1, x2, y2, lines[0]) && IsResembling(x1, y1, x2, y2))
	{
		return true;
	}

	if (IsOneTurnLinked(x1, y1, x2, y2, lines) && IsResembling(x1, y1, x2, y2))
	{
		return true;
	}

	if (IsTwoTurnLinked(x1, y1, x2, y2, lines) && IsResembling(x1, y1, x2, y2))
	{
		return true;
	}

	return false;

}


// �����
bool Click(int& x, int& y)
{
	static bool isLDown = false;

	x = -1;
	y = -1;

	bool isClicked = false;

	while (MouseHit())
	{
		MOUSEMSG msg = GetMouseMsg();

		if (msg.mkLButton)
		{
			isLDown = true;
			continue;
		}

		if (!msg.mkLButton && isLDown)
		{
			// ���
			isLDown = false;

			x = msg.x / GRID_WIDTH;
			y = msg.y / GRID_WIDTH;

			isClicked = true;
		}
	}


	return isClicked;
}

int main()
{
	initgraph(800, 500);

	srand(time(0));
	InitData();
	LoadImage();

	setlinecolor(0x15C8FC);
	setlinestyle(PS_SOLID, 5);

	int picNum = 0;
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;

	clock_t start, stop;
	double duration;

	start = clock();
	while (true)
	{
		clearrectangle(0, 0, 2000, 1000);

		for (int j = 0; j < HEIGHT; ++j)
		{
			for (int i = 0; i < WIDTH; ++i)
			{
				// ��ʾͼƬ
				if (data[j][i] == 0)
				{
					continue;
				}

				putimage(i * GRID_WIDTH, j * GRID_WIDTH, &img[data[j][i] - 1]);

			}
		}

		int mouseX = 0;
		int mouseY = 0;
		if (Click(mouseX, mouseY))
		{
			if (picNum == 0)
			{

				if (data[mouseY][mouseX] != 0)
				{
					x1 = mouseX;
					y1 = mouseY;
					picNum = 1;
				}

			}
			else if (picNum == 1)
			{
				if (data[mouseY][mouseX] != 0)
				{
					x2 = mouseX;
					y2 = mouseY;

					picNum = 0;

					std::vector<std::vector<POINT> > lines;

					if (IsLinked(x1, y1, x2, y2, lines))
					{
						for (size_t i = 0; i < lines.size(); i++)
						{

							for (size_t j = 0; j < lines[i].size(); j++)
							{
								if (j == 0)
								{
									moveto(lines[i][j].x * GRID_WIDTH + GRID_WIDTH / 2, lines[i][j].y * GRID_WIDTH + GRID_WIDTH / 2);
								}
								else
								{
									lineto(lines[i][j].x * GRID_WIDTH + GRID_WIDTH / 2, lines[i][j].y * GRID_WIDTH + GRID_WIDTH / 2);
								}
							}
						}

						Sleep(100);

						data[y1][x1] = 0;
						data[y2][x2] = 0;
					}

				}

			}

		}

		//�ж��Ƿ����
		bool flag = true;
		for (int j = 0; j < HEIGHT; ++j)
		{
			for (int i = 0; i < WIDTH; ++i)
			{
				if (data[j][i] != 0)
				{
					flag = false;
					break;
				}
			}
		}
		if (flag)
		{
			stop = clock();
			duration = ((double)(stop - start) / CLK_TCK);	/* CLK_TCK�ǻ���û�뾭����tick */

			clearrectangle(0, 0, 2000, 1000);

			RECT r = { 0, 0, 639, 479 };
			std::string str = "Hello World. " + std::to_string(duration) + "s is your time, " + "You're too young too simple.";

			drawtext(_T(str.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			Sleep(7000);
			break;
		}
		Sleep(30);
	}//end while

	closegraph();
	return 0;
}

