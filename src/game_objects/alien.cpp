#include <SFML/Graphics.hpp>
#include <optional> // Testing
#include "core/game_object.h" // Testing
#include "game_objects/alien.h"
#include "managers/resource_manager.h"
#include "core/resource_ids.h"

constexpr float	ALIEN_WIDTH = 50.f;
constexpr float ALIEN_HEIGHT = 30.f;

Alien::Alien(ResourceManager& resourceManager) {

	// Scale texture image down
	const sf::Vector2u textureSize = resourceManager.getTextureSize(ResourceKeys::alienKey);
	const float scaleAlienX = ALIEN_WIDTH / textureSize.x;
	const float scaleAlienY = ALIEN_HEIGHT / textureSize.y;
	
	/*
	sprite.emplace(resourceManager.getTexture(ResourceKeys::alienKey));
	sprite->setScale({ scaleAlienX, scaleAlienY });
	sprite->setPosition({ 100.f, 25.f });
	*/
}


void Alien::move() {

}