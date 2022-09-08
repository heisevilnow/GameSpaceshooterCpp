#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include <iomanip>		// cho setw()
#include <windows.h>
#include <string>
#include <fstream>
#include "SpaceShip.h"
#include "Monster.h"
#include "Bullet.h"
#include "Player.h"
using namespace std;

static int hp_boss[5];
static int hp = 3;
static int boss_die = 0;
static int level = 1;
static int kill_monster = 0;
static int kill_boss = 0;
static int temp = 1;
static string ten;

void HideCursor()	//Ham an con tro.
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &cci);
}
void TextColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void WelcomeMessage()
{
	int x = 48;
	int y = 9;
for (int i = 0; i < 10; i++) 
{
	TextColor(i);
	Sleep(100);
	gotoxy(x, y);     cout << " _____                    _____ _           _           ";
	TextColor(i+1);
	Sleep(100);
	gotoxy(x, y + 1); cout << "|   __|___ ___ ___ ___   |   __| |_ ___ ___| |_ ___ ___ ";
	TextColor(i+2);
	Sleep(100);
	gotoxy(x, y + 2); cout << "|__   | . | .'|  _| -_|  |__   |   | . | . |  _| -_|  _|";
	TextColor(i+3);
	Sleep(100);
	gotoxy(x, y + 3); cout << "|_____|  _|__,|___|___|  |_____|_|_|___|___|_| |___|_|  ";
	TextColor(i+5);
	Sleep(100);
	gotoxy(x, y + 4); cout << "      |_| \n";
}
}
void Title(int x, int y)
{

	int i = 9;
	TextColor(i);
	gotoxy(x, y);     cout << " _____                    _____ _           _           ";
	TextColor(i+1);
	gotoxy(x, y + 1); cout << "|   __|___ ___ ___ ___   |   __| |_ ___ ___| |_ ___ ___ ";
	TextColor(i+2);
	gotoxy(x, y + 2); cout << "|__   | . | .'|  _| -_|  |__   |   | . | . |  _| -_|  _|";
	TextColor(i+3);
	gotoxy(x, y + 3); cout << "|_____|  _|__,|___|___|  |_____|_|_|___|___|_| |___|_|  ";
	TextColor(i+5);
	gotoxy(x, y + 4); cout << "      |_| \n";

}
void Menu()
{
	int x = 65;
	int y = 16;
	gotoxy(x, y);     cout << "1. Play Game";
	gotoxy(x, y + 1); cout << "2. High Score";
	gotoxy(x, y + 2); cout << "3. Instruction";
	gotoxy(x, y + 3); cout << "4. Exit";
}
void Khung_Game(int x1, int y1, int x2, int y2)		 // Ham ve khung hinh chu nhat cho tro choi.
{
	//ax,bx la cot ben trai va ben phai. ay,by la dong ben tren va ben duoi.
	TextColor(3);
	for (int i = x1; i < x2; i++)
	{
		gotoxy(i, y1); cout << char(205);	//ve ki tu assci 205 ben tren
		gotoxy(i, y2); cout << char(205);		//ve ki tu assci 205 ben duoi
	}

	for (int i = y1; i < y2; i++)
	{
		gotoxy(x1, i); cout << char(186);
		gotoxy(x2, i); cout << char(186);
	}
	//	Ki tu cho cac goc.
	gotoxy(x1, y1); cout << char(201);
	gotoxy(x2, y1); cout << char(187);
	gotoxy(x1, y2); cout << char(200);
	gotoxy(x2, y2); cout << char(188);
	TextColor(7);
}
void Khung_Game_HP_SCORE()					//Gioi han kich thuoc cua game.
{
	Khung_Game(21, 8, 99, 34);
	for (int i = 107; i < 116; i++)
	{
		TextColor(4);
		gotoxy(i, 10); cout << (char)254;
		gotoxy(i, 14); cout << (char)254;
	}
	for (int i = 11; i <= 13; i++)
	{
		TextColor(4);
		gotoxy(105, i); cout << (char)222;
		gotoxy(116, i); cout << (char)222;
	}
	gotoxy(110, 11); cout << "HP";			//toa do cua HP
	////////////////////////////////////
	gotoxy(0, 0);
	for (int i = 0; i < 133; i++)
	{
		TextColor(i);
		cout << (char)205;
	}
	gotoxy(0, 6);
	for (int i = 133; i >=0; i--)
	{
		TextColor(i);
		cout << (char)205;
	}
	Title(40,1);
	/////////////////////////////////////
	for (int i = 127; i < 136; i++)
	{
		TextColor(2);
		gotoxy(i, 10); cout << (char)254;
		gotoxy(i, 14); cout << (char)254;
	}
	for (int i = 11; i <= 13; i++)
	{
		TextColor(2);
		gotoxy(125, i); cout << (char)222;
		gotoxy(136, i); cout << (char)222;
	}

	TextColor(2);
	gotoxy(128, 11); cout << "SCORE";	//toa do cua SCORE
	TextColor(7);
}
int bulletHitMonster(class Monster &ms, class Bullet &bl) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 4; j += 2) {
			if (bl.bullets[i][j] != 0)
			{
				for (int k = 0; k < sl_monster; k++) {
					if (bl.bullets[i][j] >= ms.MonsterY[k] && bl.bullets[i][j] <= ms.MonsterY[k] + 2)
					{
						if (bl.bullets[i][j + 1] >= ms.MonsterX[k] && bl.bullets[i][j + 1] <= ms.MonsterX[k] + 3)
						{
							bl.eraseBullet(i);
							bl.bullets[i][j] = 0;
							gotoxy(ms.MonsterX[k], ms.MonsterY[k] + 1); cout << "X"; Sleep(50); cout << "  ";
							ms.resetMonster(k);
							kill_monster++;
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}
int bulletHitBoss(Monster ms, Bullet bl) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 4; j += 2) {
			if (bl.bullets[i][j] != 0)
			{
				for (int k = 0; k < sl_boss; k++) {
						if (bl.bullets[i][j] >= ms.BossY[k] && bl.bullets[i][j] <= ms.BossY[k] + 3)
						{
							if (bl.bullets[i][j + 1] >= ms.BossX[k] && bl.bullets[i][j + 1] <= ms.BossX[k] + 6)
							{
								hp_boss[k]--;
								ms.eraseBoss(k);
								bl.eraseBullet(i);
								bl.bullets[i][j] = 0;
								return 1;
							}
						}
				}
			}
		}
	}
	return 0;
}
int collision(SpaceShip &ss, Monster &ms) {							//va cham
	for (int i = 0; i < sl_monster; i++)
	{
		if ((ms.MonsterX[i] >= ss.getsX()) && (ms.MonsterX[i] <= ss.getsX() + 6) && (ms.MonsterY[i] + 1 >= ss.getsY()) && (ms.MonsterY[i] + 1 <= ss.getsY() + 3)) 
		{
			ss.Erase();
			Sleep(50);
			ms.eraseMonster(i);
			ms.resetMonster(i);
			return 1;
		}
	}
	for (int i = 0; i < sl_boss; i++)
	{
		if ((ms.BossX[i] >= ss.getsX()) && (ms.BossX[i] <= ss.getsX() + 6) && (ms.BossY[i] + 2 >= ss.getsY()) && (ms.BossY[i] + 2 <= ss.getsY() + 3)) 
		{
			ss.Erase();
			Sleep(50);
			ms.eraseBoss(i);
			ms.resetBoss(i);
			return 1;
		}
	}	
}
void updateScore() {
	gotoxy(130, 13); cout << score << endl;
}
void displayHP() {
	for (int i = 0; i < hp; i++)
	{
		gotoxy(109 + i, 13); cout << "   ";
		gotoxy(109 + i, 13); cout << char(003);
	}
}
void DisplayHighScore(Player listplayer[], int n)
{
	int x=47;
	int y=7;
	Player temp;
	for(int i = 0; i < n - 1; i++)
	{	for(int j = i+1;j<n;j++)
		{
			if(listplayer[i].getscore() < listplayer[j].getscore())
			{
				temp=listplayer[i];
				listplayer[i] = listplayer[j];
				listplayer[j] = temp;
			}
		}
	}
	gotoxy(x,y);cout << "---------------------------------------------" << endl;
	gotoxy(x,y+1);cout << "\t\t\tHigh Score" << endl;
	gotoxy(x,y+2);cout << "---------------------------------------------" << endl;
	gotoxy(x,y+3);cout << setw(5) << "STT" << setw(18) << "Name" << setw(17) << "Score"<<endl;
	for (int i = 0; i < n; i++)
	{
	gotoxy(x,y+4);cout << setw(5) << i + 1 << setw(18) << listplayer[i].getname() << setw(17) << listplayer[i].getscore()<< endl;
	y++;
	}
	TextColor(7);
	gotoxy(x+3,y+6);cout << "Press the X key to exit...";
}
void Them_Player_list(Player listplayer[], int &n, int vt, Player &x)
{
	for (int i = n - 1; i >= vt; i--)
	{
		listplayer[i + 1] = listplayer[i];
	}
	listplayer[vt] = x;
	n++;
}
void GHI_FILE(ofstream& fileout,Player listplayer[], int n)
{
	int dem = 0;
	for (int i = 0; i < n; i++)
	{
		fileout << listplayer[i].getname() << "," << listplayer[i].getscore();
		dem++;
		if (dem < n)
		{
			fileout<< "\n";
		}
	}
}
void DOC_FILE_Highscore(ifstream& filein, Player &player)
{
	string ten;
	getline(filein, ten, ',');
	player.setname(ten);
	int diem;
	filein >> diem;
	player.setscore(diem);
}
void DOC_FILE(ifstream& filein, Player listplayer[], int &n, int vt)
{
	while (filein.eof() == false)
	{
		Player player1;	
		DOC_FILE_Highscore(filein, player1);
		string tam;
		getline(filein, tam);		// xuong dong
		Them_Player_list(listplayer, n, vt, player1);
		vt++;
	}
}
void Khung_Ingame()
{
	for (int i = 60; i <81; i++)
	{
		TextColor(8);
		gotoxy(i, 14); cout << (char)254;
		gotoxy(i, 18); cout << (char)254;
	}
	for (int i = 15; i <= 17; i++)
	{
		TextColor(8);
		gotoxy(59, i); cout << (char)222;
		gotoxy(81, i); cout << (char)222;
		gotoxy(69, i); cout << (char)222;
	}
	TextColor(7);	
	gotoxy(60, 16); cout << " Ingame" ;
}
void Displaylevel()
{
	for (int i = 107; i < 116+19; i++)
	{
		TextColor(11);
		gotoxy(i, 10+7); cout << (char)254;
		gotoxy(i, 14+7); cout << (char)254;
	}
	for (int i = 11+7; i <= 13+7; i++)
	{
		TextColor(11);
		gotoxy(105, i); cout << (char)222;
		gotoxy(116+19, i); cout << (char)222;
	}
	TextColor(11);
	gotoxy(118, 11+7); cout << "LEVEL: " << level;	
}
void GameOver()
{
	for (int i = 60; i <80+6; i++)
	{
		TextColor(8);
		gotoxy(i, 14); cout << (char)254;
		gotoxy(i, 23); cout << (char)254;
	}
	for (int i = 15; i <= 17+5; i++)
	{
		TextColor(8);
		gotoxy(59, i); cout << (char)222;
		gotoxy(80+6, i); cout << (char)222;
	}
	TextColor(7);
	if(score>=1000)	
	{
	TextColor(10);
	gotoxy(70, 16); cout << "  WIN" ;
	TextColor(7);
	}
	else
	{
	TextColor(4);
	gotoxy(70, 16); cout << "DEFEAT" ;
	TextColor(7);
	}
	gotoxy(61, 18); cout <<	" Ingame         "<< ten ;
	gotoxy(61, 19); cout <<	" Score	       "<< score ;
	gotoxy(61, 20); cout << " Kill Monster     "<< kill_monster ;
	gotoxy(61, 21); cout << " Kill Boss        "<< kill_boss ;

}
void DisplayControl()
{
	TextColor(9);
	gotoxy(107+12, 23); cout <<"CONTROL";
	TextColor(7);
	gotoxy(107+15, 25); cout <<"W";
	gotoxy(107+15, 26);	cout <<char(030);
	gotoxy(107+6, 28); cout <<"A <-";
	gotoxy(107+22, 28);cout <<"-> D";
	gotoxy(107+15, 31); cout <<"S";
	gotoxy(107+15, 30); cout <<char(031);
	gotoxy(107+8, 33); cout <<"SPACE <-> SHOOT";
	
}
void Introdution()
{
	for (int i = 60-6; i <83; i++)
	{
		TextColor(8);
		gotoxy(i, 13); cout << (char)254;
		gotoxy(i, 18+5); cout << (char)254;
	}
	for (int i = 14; i <= 17+5; i++)
	{
		TextColor(8);
		gotoxy(59-6, i); cout << (char)222;
		gotoxy(83, i); cout << (char)222;
	}
	TextColor(14);	
	gotoxy(63, 15); cout << " Intruction" ;
	gotoxy(57, 17); cout << "Name:    Nguyen Nhat Hien" ;
	gotoxy(57, 18); cout << "ID:      19119176" ;
	gotoxy(57, 19); cout << "Class:   OOP C++" ;
	gotoxy(57, 20); cout << "Teacher: Thay Ha" ;
	TextColor(7);
	gotoxy(55, 24); cout << "Press the X key to exit..." ;
	
}
int main()
{
	HideCursor();
	WelcomeMessage();
	int end;
	do{
	system("cls");
	Title(48,9);
	Menu();
	Player player;
	Player listplayer[50];
	int n = 0;
	int vt = 0;
	ifstream filein;
	filein.open("..\\GameSpaceShooter\\highscore.txt", ios_base::in);
	DOC_FILE(filein, listplayer, n, vt);
	filein.close();
	char c = _getch();
	if(c == '4')  {cout << endl; break;}
	while(c == '3') {
		system("cls");		
	 	Introdution();
		char x = _getch();
		if(x=='x'||x=='X') {end = 1; c = ' ';}	 	
	}
	while(c == '2'){
		system("cls");	
		DisplayHighScore(listplayer, n);
		char x = _getch();
		if(x=='x'||x=='X') {end = 1; c = ' ';}
	}
	if(c == '1'){
	score = 0;
	hp = 3;
	sl_monster=4;
	sl_boss=2;
	kill_monster = 0;
	kill_boss = 0;
	system("cls");
	Title(48,9);
	Khung_Ingame();
	gotoxy(72,16);
	getline(cin,ten);
	system("cls");
	Khung_Game_HP_SCORE();
	updateScore();
	displayHP();
	Displaylevel();
	DisplayControl();
	SpaceShip ss = SpaceShip(57, 30);
	Monster ms;
	Bullet bl;
	for (int i = 0; i < sl_monster; i++)
	{	
		ms.MonsterFlag[i] = 1;
	}	

	for (int i = 0; i < sl_monster; i++)
	{	
		ms.MonsterY[i] = 9;   		// khoi tao monster tai line 9
	}	
		//boss
	for (int i = 0; i < sl_boss; i++)
	{
		ms.BossFlag[i] = 1;
		ms.BossY[i] = 9;
	}
	for (int i = 0; i < sl_monster; i++)
	{
		ms.genMonster(i);
	}
	for (int i = 0; i < sl_boss; i++)
	{ 	
		hp_boss[i]=9;
	}
	for (int i = 0; i < 20; i++) {
		bl.bullets[i][0] = bl.bullets[i][1] = 0;
	}
	while (score<1000) {
		ss.Move();
		for (int i = 0; i < sl_monster; i++)
		{
			TextColor(i+2);
			ms.drawMonster(i);
			TextColor(7);
		}
		gotoxy(107, 11+9); cout << "Monster: "<<sl_monster;
		gotoxy(125, 11+9); cout << "Boss: "<<sl_boss;	
		if( score == 500 && temp==1)
		{	
			temp=0;
			for(int i = 0; i < sl_boss; i++)
				{	
					ms.genBoss(i);
				}
		}
		if (score > 500 && score < 800)
		{
			level = 4;
			gotoxy(118, 11+7); cout << "LEVEL: "<< level;
			for(int i = 0; i < sl_boss; i++)
				{	
					ms.drawBoss(i);
				}
		}
		if(score>=800 && sl_boss == 5)
		{	
			for(int i = 0; i < sl_boss; i++)
				ms.drawBoss(i);
		}
		bl.drawBullets();
		if (collision(ss,ms) == 1)
		{
			hp--;
			displayHP();
			if (hp == 0) {
				system("cls");
				GameOver();
				player.setname(ten);
				player.setscore(score);
				Them_Player_list(listplayer, n, vt, player);
				ofstream fileout;
				fileout.open("..\\GameSpaceShooter\\highscore.txt", ios_base::out);
				GHI_FILE(fileout,listplayer,n);
				fileout.close();
				gotoxy(61, 25); cout << "Press the X key to exit...";
				while(1)
				{
					char c = _getch();
					if(c=='X'||c=='x')	{
						end = 1; 
						break;
					}
				}
				break;
			}
		}
		if (bulletHitMonster(ms, bl) == 1)
		{
			score += 10;
			updateScore();
		}
		if (bulletHitBoss(ms, bl) == 1 )
		{
			for(int i=0;i<sl_boss;i++)
			{
				if(hp_boss[i]==0)
				{
				score += 20;
				updateScore();
				gotoxy(ms.BossX[i], ms.BossY[i] + 1); cout << "X.X"; Sleep(40); cout << "   ";
				kill_boss++;
				ms.BossFlag[i]=0;
				}
			}
		}
		if(score<200) Sleep(100);
		else if(score>=200 || score<400)	Sleep(90);
		else if(score>=800) Sleep(75);
		ss.Move();
		bl.eraseBullets();
		for (int i = 0; i < sl_monster; i++)
		{
			ms.eraseMonster(i);
		}
		for (int i = 0; i < sl_boss; i++)
		{
			ms.eraseBoss(i);
		}
		bl.moveBullet();
		for (int i = 0; i < sl_monster; i++)
		{
			if (ms.MonsterFlag[i] == 1)
				{
					ms.MonsterY[i] += 1;
				}
		}
		if(score>150 && sl_monster==4)
		{
			level = 2;
			gotoxy(118, 11+7); cout << "LEVEL: "<< level;
			sl_monster = 7;
			for (int i = 4; i < sl_monster; i++)
			{	
				ms.MonsterFlag[i] = 1;
				ms.resetMonster(i);
			}		
		}
		if (score >= 800 && sl_boss == 5)
		{
			for (int i = 0; i < sl_boss; i++)
			{
				if (ms.BossFlag[i] == 1)
					{
						ms.BossY[i] += 1;
					}
			}
		}	
		if (score >= 300)	
		{
			level = 3;
			ms.Move_Monster();
			gotoxy(118, 11+7); cout << "LEVEL: "<< level;
		}
		if (score > 500 && score < 800)
		{
			for(int i=0;i<sl_boss;i++)
			{
				if (ms.BossFlag[i] == 1)
					{
						ms.BossY[i] += 1;
					}
			}
		}
		if(score >= 800 && sl_boss == 2)
		{
			level = 5;
			sl_boss = 5;
			gotoxy(118, 11+7); cout << "LEVEL: "<< level;
			for (int i = 2; i < sl_boss; i++)
			{
				ms.BossFlag[i] = 1;
				hp_boss[i]=9;
				ms.resetBoss(i);
			}
		}
		
		for (int i = 0; i < sl_boss; i++)
		{
		if (ms.BossY[i] > 29)
			ms.resetBoss(i);
		}
		for (int i = 0; i < sl_monster; i++)
		{
			if (ms.MonsterY[i] >= 32)
				ms.resetMonster(i);
		}
	}
	/////////////
	if(score>=1000)
	{
		Sleep(2000);
		GameOver();		
		player.setname(ten);
		player.setscore(score);
		Them_Player_list(listplayer, n, vt, player);
		ofstream fileout;
		fileout.open("..\\GameSpaceShooter\\highscore.txt", ios_base::out);
		GHI_FILE(fileout,listplayer,n);
		fileout.close();
		gotoxy(61, 25); cout << "Press the X key to exit...";
		while(1)
		{
			char c = _getch();
			if(c=='x'||c=='X')	{end = 1; break;}
		}
	}
  }
 }while(end>0);
 system("pause");
 return 0;
}
