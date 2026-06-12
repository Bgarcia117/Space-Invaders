#include <string>
#include <SFML/Graphics.hpp>
#include "game_objects/bullet.h"
#include "core/game_object.h"

constexpr float EXPLOSION_DURATION = 0.2f;
constexpr float EXPLOSION_X_OFFSET = -10.f;
constexpr sf::Color RED(233, 37, 28);

Bullet::Bullet(const ResourceManager& resourceManager, sf::Vector2f position, BulletOwner owner) :
	GameObject(resourceManager, "bullet", position), owner(owner)  {

	if (owner == BulletOwner::PLAYER) {
		explosionSprite = resourceManager.createSprite("explosion");
		explosionSprite->setColor(RED);
	}
}

void Bullet::update(float deltaTime) {
	if (exploding) {
		explosionTimer -= deltaTime;

		if (explosionTimer <= 0.0f) {
			finishedExploding = true;
		}

		return; // Stop bullet from moving
	}


	if (owner == BulletOwner::PLAYER) {
		move({bulletSpeed.x, -bulletSpeed.y * deltaTime});
	} else {
		move({bulletSpeed.x, bulletSpeed.y * deltaTime});
	}
}

void Bullet::explode() {
	// Case: Already exploding
	if (exploding) {
		return;
	}

	exploding = true;
	explosionTimer = EXPLOSION_DURATION;

	if (explosionSprite) {
		explosionSprite->setPosition({getPosition().x + EXPLOSION_X_OFFSET,
		                                 getPosition().y});
	}
}

const sf::Sprite &Bullet::getCurrentSprite() const {
	if (exploding && explosionSprite) {
		return *explosionSprite;
	}

	return getSprite();
}