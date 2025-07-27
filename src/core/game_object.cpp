#include <string>
#include <SFML/Graphics.hpp>
#include "core/game_object.h"
#include "managers/resource_manager.h"

GameObject::GameObject(const ResourceManager& spriteManager, const std::string& textureKey, const sf::Vector2f scaler) {
	// Load texture onto sprite
	sprite.emplace(spriteManager.getTexture(textureKey));

	// Scale down sprite to desired size
	sf::Vector2f textureSize = static_cast<sf::Vector2f>(spriteManager.getTextureSize(textureKey));
	sf::Vector2f scaledSize = { textureSize.x / scaler.x, textureSize.y / scaler.y };
	sprite->setScale({ scaledSize.x, scaledSize.y });
}

const sf::Sprite& GameObject::getSprite() const {
	if (!sprite.has_value()) {
		throw std::runtime_error("Texture has not been loaded!");
	}

	return *sprite;
}

void GameObject::setPosition(sf::Vector2f pos) {
	if (!sprite.has_value()) {
		throw std::runtime_error("Sprite has not been initializied!");
	}

	sprite->setPosition(pos);
}