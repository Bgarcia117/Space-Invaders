#include "game_objects/player.h"         // Header file
#include "core/game_object.h"           // Base Class
#include "managers/resource_manager.h"  // Resource/Sprite Manager
#include "core/resource_ids.h"          // Texture map keys and paths

constexpr float PLAYER_WIDTH = 50.f;
constexpr float PLAYER_HEIGHT = 30.f;
constexpr sf::Color LIGHT_GREEN(42, 249, 50);

Player::Player(const ResourceManager& resourceManager, sf::Vector2f position) :
	GameObject(resourceManager, "player", position), lives(3) {
	setSpriteColor(LIGHT_GREEN);
}

void Player::update(float deltaTime) {

}
