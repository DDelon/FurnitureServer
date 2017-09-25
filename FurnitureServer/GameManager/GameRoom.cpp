#include "GameRoom.h"
#include "Player.h"

int GameRoom::_count = 0;
GameRoom::GameRoom() :
_id(_count++)
{

}

GameRoom::~GameRoom()
{

}

int GameRoom::getId()
{
	return _id;
}

void GameRoom::joinRoom(Player *player)
{
	_players.push_back(player);
}