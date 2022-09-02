#ifndef __MONSTER__
#define __MONSTER__
#include <iostream>
#include "gotoxy.h"
using namespace std;
static int score = 0;
static int sl_monster = 4;
static int sl_boss = 2;
class Monster	
{
public:
	void genMonster(int ind);
	void genBoss(int ind);
	void drawMonster(int ind);
	void resetMonster(int ind);
	void eraseMonster(int ind);
	void drawBoss(int ind);
	void eraseBoss(int ind);
	void resetBoss(int ind);
	void Move_Monster();
	static int MonsterY[10];
	static int MonsterX[10];
	static int BossY[5];
	static int BossX[5];
	static int MonsterFlag[10];
	static int BossFlag[5];

};
#endif