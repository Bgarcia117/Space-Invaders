#include "core/game.h"
#include "managers/resource_manager.h"

// ======== Testing =========
#include "game_objects/alien.h"



Game::Game() : resourceManager(), gameOver(false), score(0) {

}

void Game::begin() {
	Alien alien(resourceManager);
	alien.setPosition({500.f, 500.f});

}