#include <SFML/Graphics.hpp>
#include "core/game_object.h"
#include "managers/resource_manager.h"

GameObject::GameObject(ResourceManager& spriteManager, GameObjectConfig& config) {
	sprite.emplace(spriteManager.getTexture(config.textureKey));
	sprite->setScale({ config.size.x, config.size.y });
	sprite->setPosition({ config.position.x, config.position.y });
}

const sf::Sprite& GameObject::getSprite() const {
	if (!sprite.has_value()) {
		throw std::runtime_error("Texture has not been loaded!");
	}

	return *sprite;
}