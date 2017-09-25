#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <vector>

class GameHall;

class GameManager
{
private:
	GameManager();
	~GameManager();

public:
	static GameManager *getInstance();

private:
	void registerParser();

private:
	static GameManager *_pInstance;

	std::vector<GameHall *> _hallVec;
};

#endif
