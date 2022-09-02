
#include "SpaceShip.h"

int SpaceShip::getsX() { return x; }
int SpaceShip::getsY() { return y; }
void SpaceShip::Draw()			//Ham hien thi hinh tau chien.
{
    gotoxy(x, y);   cout << "   " << char(30);
    gotoxy(x, y + 1); cout << "  " << char(207) << char(4) << char(207);
    gotoxy(x, y + 2); cout << char(17) << char(254) << char(30) << char(223) << char(30) << char(254) << char(16);
}
void SpaceShip::Erase()		//Ham xoa hinh tau chien.	
{
    gotoxy(x, y);     cout << "       ";
    gotoxy(x, y + 1); cout << "       ";
    gotoxy(x, y + 2); cout << "       ";
}
void SpaceShip::Move()			//Ham di chuyen
{
    if (_kbhit()) {
        char key = _getch();
        Erase();
        if (key == 'a' || key == 'A') {
            if (x > 23)
                x -= 2;
        }
        else if (key == 'd' || key == 'D') {
            if (x < 91)
                x += 2;
        }
        else if (key == 'w' || key == 'W') {
            if (y > 9)
                y -= 1;
        }
        else if (key == 's' || key == 'S') {
            if (y < 31)
                y += 1;
        }
        if (key == 32) {
            genBullet();
        }
    }
    Draw();
}
	void SpaceShip::genBullet(){				//khoi tao vien dan
    bullets[bIndex][0] = y + 1; 		// toa do y cua vien dan 1	
    bullets[bIndex][1] = x + 2;			//  toa do x cua vien dan 1	 
    bullets[bIndex][2] = y + 1;			// toa do y cua vien dan 2
    bullets[bIndex][3] = x + 4;  		//toa do x cua vien dan thu 2
    bIndex++;
    if (bIndex == 20)					//mang 20 4
        bIndex = 0;
}
