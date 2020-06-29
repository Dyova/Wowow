#include <vector>
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

struct sDisk
{
	int size;
	int color;
};


void gotoxy(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void setColor(int background, int text)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4 | text)));
}

enum ConsoleColor
{
	BLACK = 0,
	GREEN = 2,
	RED = 4,
	BROWN = 6,
	WHITE = 15
};

void showDisk(sDisk disk, int x, int y)
{
	int ms = 10 - disk.size;
	gotoxy(x + ms, y);
	setColor(BLACK, disk.color);
	for (int i = 0; i < 2*disk.size; i++)
	{
		cout << (char)219;
	}
	setColor(BLACK, GREEN);
}


class Game
{
private:
	vector <vector <sDisk>> towers;
	int x;
	int y;

	int sx;

	int N;
	
public:


	Game(int ringsNum)
	{
		x = 30;
		y = 15;
		sx = 3 * (ringsNum + 1);
		N = ringsNum;

		vector <sDisk> tower0;
		vector <sDisk> tower1;
		vector <sDisk> tower2;

		sDisk disk;

		disk.size = ringsNum + 1;
		disk.color = BROWN;

		tower0.push_back(disk);
		tower1.push_back(disk);
		tower2.push_back(disk);

		for (int i = N; i >= 1; i--)
		{
			disk.size = i;
			disk.color = RED;

			tower0.push_back(disk);
		}

		towers.push_back(tower0);
		towers.push_back(tower1);
		towers.push_back(tower2);
	}

	void showTowers()
	{
		int lx = x;
		int ly = y;

		gotoxy(lx, ly);

		for (int i = 0; i < towers.size(); i++)
		{
			for (int j = 0; j < towers[i].size(); j++)
			{
				showDisk(towers[i][j], lx, ly);
				ly--;
			}
			ly = y;
			lx += sx;
		}
	}

	bool shiftDisk(int sour, int dest)
	{
		sDisk disk0;
		sDisk disk1;

		sour--;
		dest--;

		disk0 = towers[sour][towers[sour].size() - 1];
		disk1 = towers[dest][towers[dest].size() - 1];

		if (disk0.size < disk1.size)
		{
			towers[sour].pop_back();
			towers[dest].push_back(disk0);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool getWin()
	{
		if (towers[1].size() == N + 1 || towers[2].size() == N + 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

int main()
{
	int ringNum;
	cout << "Enter the number of rings: ";
	cin >> ringNum;
	Game game(ringNum);

	int sour;
	int dest;

	int t = 0;

	while (true)
	{
		system("cls");
		game.showTowers();
		gotoxy(25, 0);
		cout << "To select a tower press: <1>, <2> or <3>";
		gotoxy(0, 25);
		cout << "Moves: " << t;
		gotoxy(0, 0);

		sour = _getche() - 48;         /*_getch почему-то берет (значение + 48) 0_0*/
		dest = _getche() - 48;         /*лень разбираться - заделую брешь изолентой*/

		if (sour > 3 || sour < 1 || dest > 3 || dest < 1)
		{
			gotoxy(30, 2);
			cout << "Error: you pressed wrong key";

			gotoxy(40, 3);
			cout << "FOCUS!";

			gotoxy(30, 4);
			cout << "(press any key to continue)";

			_getch();
			continue;
		}

		cout << "Moves: " << t;

		if (game.shiftDisk(sour, dest))
		{
			t++;
		}
		
		if (game.getWin())
		{
			system("cls");
			game.showTowers();
			gotoxy(0, 25);
			cout << "MOVES FOR COMPLETE: " << t;
			break;
		}
	}

	_getch();

	return 0;
}