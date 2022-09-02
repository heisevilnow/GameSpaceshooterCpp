#include "Bullet.h"

int Bullet::bullets[20][4] = {};

void Bullet::drawBullets() {						//ve dan
    for (int i = 0; i < 20; i++) {
        if (bullets[i][0] > 9) {
            gotoxy(bullets[i][1], bullets[i][0]); cout << "^";	//ve vien dan tai toa do cua vien dan thu 1.
            gotoxy(bullets[i][3], bullets[i][2]); cout << "^";	//ve vien dan tai toa do cua vien dan thu 2.
        }						
    }						 		
}
void Bullet::eraseBullets() {						//xoa dan
    for (int i = 0; i < 20; i++) {
        if (bullets[i][0] >= 9) {
            gotoxy(bullets[i][1], bullets[i][0]); cout << " ";
            gotoxy(bullets[i][3], bullets[i][2]); cout << " ";
        }
    }
}
void Bullet::eraseBullet(int i) {					//xoa dan khi dan ban trung vao monster va boss
    gotoxy(bullets[i][1], bullets[i][0]); 	  cout << " ";
    gotoxy(bullets[i][3], bullets[i][2]); 	  cout << " ";
}

void Bullet::moveBullet() {							// di chuyen dan
    for (int i = 0; i < 20; i++) {
        if (bullets[i][0] > 9)
            bullets[i][0]--;
        else
            bullets[i][0] = 0;

        if (bullets[i][2] > 9)
            bullets[i][2]--;
        else
            bullets[i][2] = 0;
    }
}
