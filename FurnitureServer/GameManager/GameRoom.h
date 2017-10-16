#ifndef __GAME_ROOM_H__
#define __GAME_ROOM_H__

#include <vector>

class Player;

class GameRoom
{
public:
	GameRoom();
	~GameRoom();

public:
	int getId();

	void joinRoom(Player *player);

private:
	static int _count;

	int _id;
	std::vector<Player *> _players;
};

#endif
