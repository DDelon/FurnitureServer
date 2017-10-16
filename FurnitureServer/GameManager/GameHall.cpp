#include "GameHall.h"
#include "GameRoom.h"

int GameHall::_count = 0;
GameHall::GameHall() :
_id(_count++)
{

}

GameHall::~GameHall()
{

}

int GameHall::getId()
{
	return _id;
}

void GameHall::pushRoom(GameRoom *pRoom)
{
	_roomVec.push_back(pRoom);
}

GameRoom *GameHall::getRoom(int roomId)
{
	for (auto iter : _roomVec)
	{
		
	}
}
