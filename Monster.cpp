#include "Monster.h"
#include "gotoxy.h"

int Monster::MonsterY[10] = {};
int Monster::MonsterX[10] = {};
int Monster::BossY[5]= {};
int Monster::BossX[5]= {};
int Monster::MonsterFlag[10]= {};
int Monster::BossFlag[5]= {};
void Monster::genMonster(int ind)		//khoi tao quai vat
{
    MonsterX[ind] = 24 + rand() % 71;  // khoi tao toa do x cho quai vat, tu (0->71) + 24(base)
}
void Monster::genBoss(int ind)			//khoi tao quai vat
{
    BossX[ind] = 22 + rand() % 72;  // khoi tao toa do x cho quai vat, tu (0->72) + 22(base)
}
void Monster::drawMonster(int ind) {		// ve quai vat.
    if (MonsterFlag[ind] == 1) {
        gotoxy(MonsterX[ind], MonsterY[ind]);	  cout << ".**.";
        gotoxy(MonsterX[ind], MonsterY[ind] + 1); cout << ".**.";
    }
}
void Monster::resetMonster(int ind) {					//reset lai quai vat
    eraseMonster(ind);
    if(score<100)
        MonsterY[ind] = 9+ rand() % 10;
    else
        MonsterY[ind] = 9+ rand() % 13;			//khoi tao lai toa do Y cua quai vat.
    genMonster(ind);
}
void Monster::eraseMonster(int ind) {					//xoa quai vat
    if (MonsterFlag[ind] == 1) {
        gotoxy(MonsterX[ind], MonsterY[ind]);	  cout << "    ";
        gotoxy(MonsterX[ind], MonsterY[ind] + 1); cout << "    ";
    }
}
void Monster::drawBoss(int ind) {								// ve boss.
    if (BossFlag[ind] == 1) {
        gotoxy(BossX[ind], BossY[ind]);	  	cout << ".o**o.";
        gotoxy(BossX[ind], BossY[ind] + 1); cout << ".****.";
        gotoxy(BossX[ind], BossY[ind] + 2); cout << "**||**";
    }
}
void Monster::eraseBoss(int ind) {					//xoa boss
    if (BossFlag[ind] == 1) {
        
        gotoxy(BossX[ind], BossY[ind]);	    cout << "      ";
        gotoxy(BossX[ind], BossY[ind] + 1); cout << "      ";
        gotoxy(BossX[ind], BossY[ind] + 2); cout << "      ";
    }
}
void Monster::resetBoss(int ind) {					//reset boss
    eraseBoss(ind);
    BossY[ind] = 9+ rand() % 11;			//khoi tao lai toa do Y cua boss
    genBoss(ind);
}
void Monster::Move_Monster()
{
    for (int i = 1; i < sl_monster; i++)
    {
        if (MonsterFlag[i] == 1)
        {
            if (i == 1)
                MonsterX[i] += 1;
            else if (i == 3)
                MonsterX[i] -= 1;
            else if (i == 5)
                MonsterX[i] -= 1;
        }
        if ( MonsterX[i] < 23 + 6||MonsterX[i] > 72 - 3)	resetMonster(i);
    }
}
