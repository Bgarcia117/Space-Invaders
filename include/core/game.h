#pragma once
#include "managers/resource_manager.h"

class Game {
public:
	Game();
	void begin();

private:
	ResourceManager resourceManager;
	bool gameOver;
	int score;
};