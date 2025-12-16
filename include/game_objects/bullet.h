#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "core/game_object.h"
#include "managers/resource_manager.h"

class Bullet : public GameObject {
public:
	Bullet(const ResourceManager& resourceManager, const sf::Vector2f position);


};