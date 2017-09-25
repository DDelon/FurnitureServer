#ifndef __GAME_HALL_H__
#define __GAME_HALL_H__

#include <vector>

class GameRoom;

class GameHall
{
public:
	GameHall();
	~GameHall();

public:
	int getId();

	void pushRoom(GameRoom *pRoom);

	GameRoom *getRoom(int roomId);

private:
	static int _count;

	int _id;
	std::vector<GameRoom *> _roomVec;
};

#endif
