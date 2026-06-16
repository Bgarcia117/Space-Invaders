#include "game_objects/player.h"        // Header file
#include "game_objects/bullet.h"
#include "core/game_object.h"           // Base Class
#include "managers/resource_manager.h"  // Resource/Sprite Manager
#include "core/resource_ids.h"          // Texture map keys and paths

constexpr float PLAYER_WIDTH = 55.f;
constexpr float PLAYER_HEIGHT = 50.f;
constexpr float BULLET_OFFSET = -11.f;
constexpr sf::Vector2f PLAYER_SPEED = { 150.f, 0.f };
constexpr sf::Color LIGHT_GREEN(42, 249, 50);

constexpr float DEATH_DURATION = 1.5f;
constexpr float DEATH_FLIP_TIME = 0.1f;

Player::Player(const ResourceManager& resourceManager, sf::Vector2f position) :
	GameObject(resourceManager, "player", position),
	lives(3),
	spriteState(SpriteState::ALIVE),
	dying(false),
    deathTimer(DEATH_DURATION),
	spriteFlipTimer(DEATH_FLIP_TIME) {
	setSpriteColor(LIGHT_GREEN);
	shootSound.emplace(resourceManager.getSoundBuffer(ResourceKeys::playerShootSoundKey));

	deathSpriteOne = resourceManager.createSprite("player_death_one");
	deathSpriteOne->setPosition(position);
	deathSpriteOne->setColor(LIGHT_GREEN);

	deathSpriteTwo = resourceManager.createSprite("player_death_two");
	deathSpriteTwo->setPosition(position);
	deathSpriteTwo->setColor(LIGHT_GREEN);
}

void Player::update(float deltaTime) {
	if (dying) {
		deathTimer -= deltaTime;
		spriteFlipTimer -= deltaTime;

		if (spriteFlipTimer <= 0.0f) {
			if (spriteState == SpriteState::DEATH_ONE) {
				spriteState = SpriteState::DEATH_TWO;
			} else {
				spriteState = SpriteState::DEATH_ONE;
			}
			spriteFlipTimer = DEATH_FLIP_TIME;
		}
		return;
	}

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

void Player::move(sf::Vector2f offset) {
	GameObject::move(offset);

	if (deathSpriteOne) {
		deathSpriteOne->move(offset);
	}

	if (deathSpriteTwo) {
		deathSpriteTwo->move(offset);
	}
}

Bullet Player::shoot(const ResourceManager& resourceManager) {
	Bullet bullet(resourceManager, getPosition(), BulletOwner::PLAYER);
	float bulletWidth = bullet.getSprite().getGlobalBounds().size.x;

	sf::Vector2f bulletPos = getPosition();
	bulletPos.x += PLAYER_WIDTH / 2.f - bulletWidth / 2.f + BULLET_OFFSET;
	bullet.setPosition(bulletPos);

	shootSound->play();
	return bullet;
}

void Player::kill() {
	if (dying) {
		return;
	}

	dying = true;
	deathTimer = DEATH_DURATION;
	spriteFlipTimer = DEATH_FLIP_TIME;
	spriteState = SpriteState::DEATH_ONE;
}

void Player::respawn(sf::Vector2f position) {
	dying = false;
	spriteState = SpriteState::ALIVE;
	deathTimer = DEATH_DURATION;
	spriteFlipTimer = DEATH_FLIP_TIME;
	setPosition(position);

	if (deathSpriteOne) {
		deathSpriteOne->setPosition(position);
	}

	if (deathSpriteTwo) {
		deathSpriteTwo->setPosition(position);
	}
}

const sf::Sprite& Player::getCurrentSprite() const {
	switch (spriteState) {
		case SpriteState::ALIVE:
			return getSprite();
		case SpriteState::DEATH_ONE:
			return *deathSpriteOne;
		case SpriteState::DEATH_TWO:
			return *deathSpriteTwo;
		default:
			return getSprite();
	}
}
