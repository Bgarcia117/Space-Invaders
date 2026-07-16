#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "game_objects/bullet.h"
#include "core/game_object.h"

constexpr float EXPLOSION_DURATION = 0.2f;
constexpr float EXPLOSION_X_OFFSET = -10.f;
constexpr float SPRITE_DURATION = 0.25f;
constexpr sf::Color RED(233, 37, 28);
constexpr sf::Color WHITE(255, 255, 255);
constexpr sf::Color GREEN(42, 249, 50);

constexpr float TOP_RED_BAND_MAX_Y = 200.f;
constexpr float BOTTOM_GREEN_BAND_MIN_Y = 700.f;

Bullet::Bullet(const ResourceManager& resourceManager, sf::Vector2f position, BulletOwner owner,
               AlienBulletType bulletType) :
	GameObject(resourceManager, "bullet", position), owner(owner)  {

	if (owner == BulletOwner::PLAYER) {
		explosionSprite = resourceManager.createSprite("player_bullet_explosion");
		explosionSprite->setColor(RED);
		return;
	}

	explosionSprite = resourceManager.createSprite("alien_bullet_explosion");
	explosionSprite->setColor(GREEN);

	for (const auto& key : getSpriteKeys(bulletType)) {
		sf::Sprite sprite = resourceManager.createSprite(key);

		// Centering origins to flip sprite
		auto bounds = sprite.getLocalBounds();
		sprite.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});
		sprite.setPosition(position);
		spriteStates.push_back(sprite);
	}

	// Creating flipped lightning sprite
	if ((bulletType == AlienBulletType::LIGHTNING || bulletType == AlienBulletType::LIGHTNING_PULSE)
		&& !spriteStates.empty()) {
		sf::Sprite flippedSprite = spriteStates[0];
		flippedSprite.setScale({ -flippedSprite.getScale().x, flippedSprite.getScale().y });
		spriteStates.push_back(flippedSprite);
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

		if (spriteStates.size() > 1) {
			spriteTimer += deltaTime;

			if (spriteTimer >= SPRITE_DURATION) {
				spriteTimer = 0.0f;
				currentSprite = (currentSprite + 1) % spriteStates.size();
			}
		}
	}

	// Updates the color of the bullet depending on its y level
	float bulletYPosition = getPosition().y;

	sf::Color bulletColor = WHITE;
	if (bulletYPosition <= TOP_RED_BAND_MAX_Y) {
		bulletColor = RED;
	} else if (bulletYPosition >= BOTTOM_GREEN_BAND_MIN_Y) {
		bulletColor = GREEN;
	}

	setSpriteColor(bulletColor);

	for (auto& sprite : spriteStates) {
		sprite.setColor(bulletColor);
	}
}

void Bullet::move(sf::Vector2f offset) {
	GameObject::move(offset);

	for (auto& sprite : spriteStates) {
		sprite.move(offset);
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

	if (!spriteStates.empty()) {
		return spriteStates[currentSprite];
	}

	return getSprite();
}

std::vector<std::string> Bullet::getSpriteKeys(AlienBulletType alienType) const {
	switch (alienType) {
		case AlienBulletType::PULSE:
			return { "bullet_pulse_one", "bullet_pulse_two",
				     "bullet_pulse_three", "bullet_pulse_four" };

		case AlienBulletType::LIGHTNING:
			return { "lightning_bullet_one", "lightning_bullet_two",
				     "lightning_bullet_three", "lightning_bullet_four" };

		case AlienBulletType::LIGHTNING_PULSE:
			return { "lightning_pulse_one", "lightning_pulse_two",
				     "lightning_pulse_three", "lightning_pulse_four" };
	}

	return { "bullet_pulse_one" };
}
