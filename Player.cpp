#ifndef __PLAYER__
#define __PLAYER__
#include "Player.h"
	string Player::getname()
	{
		return name;
	}
	int Player::getscore()
	{
		return score;
	}
	void Player::setname(string ten)
	{
		name=ten;
	}
	void Player::setscore(int diem)
	{
		score = diem;
	}

#endif