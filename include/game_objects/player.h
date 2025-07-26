#pragma once
#include "core/game_object.h"
#include "managers/resource_manager.h"

class Player : public GameObject {
public:
	Player(ResourceManager& manager);
};