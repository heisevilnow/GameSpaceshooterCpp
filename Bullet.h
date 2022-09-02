#ifndef __BULLET__
#define __BULLET__
#include <iostream>
#include "gotoxy.h"
using namespace std;
static int bIndex = 0;
class Bullet
{
public:
	void drawBullets();
	void eraseBullets();
	void eraseBullet(int i);
	void moveBullet();
	static int bullets[20][4];
};
#endif