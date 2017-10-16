#include "Player.h"
#include "CCValue.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::initPlayerData(::Value val)
{
	
	_name = val.asValueMap()["name"].asString();
	_account = val.asValueMap()["account"].asString();
	_password = val.asValueMap()["password"].asString();

	_socket = val.asValueMap()["socket"].asInt();
	_userId = val.asValueMap()["id"].asInt();
	_lv = val.asValueMap()["level"].asInt();
	_hp = val.asValueMap()["hp"].asInt();
	_mp = val.asValueMap()["mp"].asInt();
	_coin = val.asValueMap()["coin"].asInt();
	_diamond = val.asValueMap()["diamond"].asInt();

}