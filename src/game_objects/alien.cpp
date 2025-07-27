#include <string>

#include <SFML/Graphics.hpp>

#include "game_objects/alien.h"         // Header file
#include "core/game_object.h"           // Base Class
#include "managers/resource_manager.h"  // Resource/Sprite Manager
#include "core/resource_ids.h"          // Texture map keys and paths

constexpr float	ALIEN_WIDTH = 50.f;
constexpr float ALIEN_HEIGHT = 30.f;

Alien::Alien(const ResourceManager& resourceManager) : 
	GameObject(resourceManager, ResourceKeys::alienKey, {ALIEN_HEIGHT, ALIEN_WIDTH}) {

}


void Alien::move() {

}