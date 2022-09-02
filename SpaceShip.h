#ifndef __SPACESHIP__
#define __SPACESHIP__
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "gotoxy.h"
#include "Bullet.h"
using namespace std;
class SpaceShip: public Bullet 
{
private:
	int x;
	int y;

public:
	SpaceShip(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	int getsX();
	int getsY();
	void Draw();
	void Erase();
	void Move();
	void genBullet();

};

#endif