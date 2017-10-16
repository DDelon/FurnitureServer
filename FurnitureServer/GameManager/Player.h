#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include "CCValue.h"
class Player
{
public:
	Player();
	~Player();
public:
	void initPlayerData(::Value val);

private:
	std::string _account;
	std::string _password;
	std::string _name;

	int _socket;
	int _userId;
	int _lv;
	int _hp;
	int _mp;
	int _coin;
	int _diamond;
};

#endif
