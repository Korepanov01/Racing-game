#ifndef RACINGGAME_H
#define RACINGGAME_H

#include "Graphics.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

//--------------------------------------------------------------------------

struct LINE
{
	POINT first, second;
};

//--------------------------------------------------------------------------

class Road
{
public:
	static void createRoad(int, int);
	static void visRoad();
private:
	static vector <POINT> pointsOfRoad;
	static bool step;
};
vector<POINT> Road::pointsOfRoad;
bool Road::step;

void Road::createRoad(int heg, int wid)
{
	for (int i = 1; i <= 4; i++)
	{
		POINT position;
		position.x = wid/5*i;

		position.y = 0;
		pointsOfRoad.push_back(position);

		position.y = heg + 200;
		pointsOfRoad.push_back(position);
	}
	step = false;
}

void Road::visRoad()
{
	Graphics::Set_pen(RGB (255, 255, 255), 20);

	Graphics::Line(pointsOfRoad[0].x, pointsOfRoad[0].y, pointsOfRoad[1].x, pointsOfRoad[1].y);
	Graphics::Line(pointsOfRoad[6].x, pointsOfRoad[6].y, pointsOfRoad[7].x, pointsOfRoad[7].y);

	for (int i = 2; i <= 5; i += 2)
	{
		if (step)
		{
			for (int j = 0; j <= heg; j += heg / 4)
			{
				Graphics::Line(pointsOfRoad[i].x, pointsOfRoad[i].y + j, pointsOfRoad[i + 1].x, pointsOfRoad[i + 1].y / 10 + j);
			}
		}
		else
		{
			for (int j = 0; j <= heg; j += heg / 4)
			{
				Graphics::Line(pointsOfRoad[i].x, pointsOfRoad[i].y + j + heg / 8, pointsOfRoad[i + 1].x, pointsOfRoad[i + 1].y / 10 + j + heg / 8);
			}
		}
	}
	step = !step;
}

//----------------------------------------------------------------------------
class EnemyCar;

class Car
{
public:
	static void createCar(int, int);
	static void visCar();
	static void keyboard(char);
	static bool end();
private:
	static vector <LINE> linesOfCar;
	static vector <POINT> positions;
	static int position;
	static bool	suicide;
	friend EnemyCar;
};
vector<LINE> Car::linesOfCar;
vector<POINT> Car::positions(3);
int Car::position;
bool Car::suicide;

void Car::createCar(int heg, int wid)
{
	ifstream model("CarModel.txt");
	int countOfLines;
	model >> countOfLines;

	for (int i = 0; i < countOfLines; i++)
	{
		LINE l;
		model >> l.first.x >> l.first.y >> l.second.x >> l.second.y;
		linesOfCar.push_back(l);
	}
	model.close();

	positions[0].x = wid / 4 - 10;
	positions[0].y = heg - 350;
	positions[1].x = wid / 2 - 80;
	positions[1].y = heg - 350;
	positions[2].x = wid / 5 * 4 - 250;
	positions[2].y = heg - 350;

	position = 1;
	suicide = false;
}

void Car::visCar()
{
	int carSize = 20;
	Graphics::Set_pen(RGB(65, 105, 225), 10);

	for (int i = 0; i < linesOfCar.size(); i++)
	{
		Graphics::Line(linesOfCar[i].first.x*carSize + positions[position].x, linesOfCar[i].first.y*carSize + positions[position].y, linesOfCar[i].second.x*carSize + positions[position].x, linesOfCar[i].second.y*carSize + positions[position].y);
	}
}

void Car::keyboard(char c)
{
	switch (c)
	{
	case 77:
		if (position != 2)
		{
			position++;
		}
		break;
	case 75:
		if (position != 0)
		{
			position--;
		}
		break;
	case 27:
		suicide = true;
		break;
	}
}

bool Car::end()
{
	return suicide;
}

//-----------------------------------------------------------------------------

class EnemyCar 
{
public:
	bool crash();
	static void createEnemyCar(int, int);
	void visEnemyCar();
	void move(int);
private:
	static vector <LINE> linesOfEnemyCar;
	static vector <POINT> enemyPositions;
	int enemyPosition = rand() % 3;
};
vector<LINE> EnemyCar::linesOfEnemyCar;
vector<POINT> EnemyCar::enemyPositions(3);

void EnemyCar::createEnemyCar(int heg, int wid)
{
	ifstream model("EnemyCarModel.txt");
	int countOfLines;
	model >> countOfLines;

	for (int i = 0; i < countOfLines; i++)
	{
		LINE l;
		model >> l.first.x >> l.first.y >> l.second.x >> l.second.y;
		linesOfEnemyCar.push_back(l);
	}
	model.close();

	enemyPositions[0].x = wid / 4 - 10;
	enemyPositions[0].y = -350;
	enemyPositions[1].x = wid / 2 - 80;
	enemyPositions[1].y = -350;
	enemyPositions[2].x = wid / 5 * 4 - 250;
	enemyPositions[2].y = -350;
}

void EnemyCar::visEnemyCar()
{
	int EnemyCarSize = 20;
	Graphics::Set_pen(RGB(255, 30, 30), 10);

	for (int i = 0; i < linesOfEnemyCar.size(); i++)
	{
		Graphics::Line(linesOfEnemyCar[i].first.x * EnemyCarSize + enemyPositions[enemyPosition].x, linesOfEnemyCar[i].first.y * EnemyCarSize + enemyPositions[enemyPosition].y, linesOfEnemyCar[i].second.x * EnemyCarSize + enemyPositions[enemyPosition].x, linesOfEnemyCar[i].second.y * EnemyCarSize + enemyPositions[enemyPosition].y);
	}
}

void EnemyCar::move(int step)
{
	if (enemyPositions[enemyPosition].y <= 1300)
		enemyPositions[enemyPosition].y+=step;
	else
	{
		enemyPositions[enemyPosition].y = -350;
		enemyPosition = rand() % 3;
	}
}

bool EnemyCar::crash()
{
	bool gameover;
	if (Car::position == enemyPosition && Car::positions[Car::position].y <= enemyPositions[enemyPosition].y + 350 && Car::positions[Car::position].y+ 250 >= enemyPositions[enemyPosition].y )
		gameover = true;
	else gameover = false;

	return gameover;
}

//-----------------------------------------------------------------------------

void clearConsole()
{
	Graphics::Set_pen(RGB(0, 0, 0), 3000);
	Graphics::Line(0, heg / 2, wid, heg / 2);
}

void writeGAMEOVER(int heg, int wid)
{
	int size = 50;
	POINT pos;
	pos.x = wid / 2- 400;
	pos.y = heg / 2 - 300;

	Graphics::Set_pen(RGB(255, 30, 30), 20);
	vector <LINE> linesOfWord;
	ifstream word("GAMEOVER.txt");
	int countOfLines;
	word >> countOfLines;
	for (int i = 0; i < countOfLines; i++)
	{
		LINE l;
		word >> l.first.x >> l.first.y >> l.second.x >> l.second.y;
		Graphics::Line(l.first.x * size + pos.x, l.first.y * size + pos.y, l.second.x * size + pos.x, l.second.y * size + pos.y);

	}
	word.close();
}

void RunGame()
{
	cout << "Используйте для управления машиной стрелочки на клавиатуре"
		<< endl << "Цель игры - проехать как можно дальше!"
		<< endl << "Игра закончится, если машина врежется в другую"
		<< endl << "Чтобы выйти из игры нажмите Esc" << endl
		<< endl << "Выберете сложность, нажав клавишу 1, 2 или 3"
		<< endl << "1 - легко"
		<< endl << "2 - средне"
		<< endl << "3 - сложно" << endl;

	int step;
	switch (_getch())
	{
	default:
		step = 70;
		break;
	case '1':
		step = 50;
		break;
	case '2':
		step = 70;
		break;
	case '3': 
		step = 100;
		break;
	}

	
	double score = 0;
	Road::createRoad(heg, wid);
	Car::createCar(heg, wid);
	EnemyCar::createEnemyCar(heg, wid);

	EnemyCar a, b;

	bool end = false;
	while (!a.crash() && !b.crash() && !Car::end())
	{
		clearConsole();
		Road::visRoad();
		a.move(step);
		b.move(step);
		Car::visCar();
		a.visEnemyCar();
		b.visEnemyCar();
		Sleep(100);

		score++;
		if (_kbhit())
			Car::keyboard(_getch());
	}
	clearConsole();
	writeGAMEOVER(heg, wid);
	Sleep(1500);
	clearConsole();

	cout << "GAME OVER!" << endl << "Your score: " << score;

}

#endif RACINGGAME_H