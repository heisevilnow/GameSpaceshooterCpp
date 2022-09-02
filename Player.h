#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <iomanip>		// cho setw()
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;
class Player{
	
private:
	string name;
	int score;	
public:	
	string getname();
	int getscore();
	void setname(string ten);
	void setscore(int diem);
};