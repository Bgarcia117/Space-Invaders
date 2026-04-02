#include "game_objects/player.h"        // Header file
#include "game_objects/bullet.h"
#include "core/game_object.h"           // Base Class
#include "managers/resource_manager.h"  // Resource/Sprite Manager
#include "core/resource_ids.h"          // Texture map keys and paths

constexpr float PLAYER_WIDTH = 50.f;
constexpr float PLAYER_HEIGHT = 30.f;
constexpr sf::Vector2f PLAYER_SPEED = { 150.f, 0.f };
constexpr sf::Color LIGHT_GREEN(42, 249, 50);

Player::Player(const ResourceManager& resourceManager, sf::Vector2f position) :
	GameObject(resourceManager, "player", position), lives(3) {
	setSpriteColor(LIGHT_GREEN);
}

void Player::update(float deltaTime) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) {
		move({ -PLAYER_SPEED.x * deltaTime, 0 });

		}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) {
		move({ PLAYER_SPEED.x * deltaTime, 0 });

		}

	// Returns player insides of bounds if they go outside of it
	sf::Vector2f playerPos = getPosition();
	playerPos.x = std::clamp(playerPos.x, 0.0f, 735.0f);
	setPosition(playerPos);
}

Bullet Player::shoot(const ResourceManager& resourceManager) {
	return Bullet(resourceManager, getPosition(), BulletOwner::PLAYER);
}
