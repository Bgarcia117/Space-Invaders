#pragma once
#include <optional>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "core/game_object.h"
#include "managers/resource_manager.h"
enum class BulletOwner {PLAYER, ALIEN};
enum class AlienBulletType { PULSE, LIGHTNING, LIGHTNING_PULSE };

class Bullet : public GameObject {
public:
	Bullet(const ResourceManager& resourceManager, const sf::Vector2f position, BulletOwner owner,
	       AlienBulletType bulletType = AlienBulletType::PULSE);
	void update(float deltaTime) override;
	void move(sf::Vector2f offset) override;
	BulletOwner getOwner() const { return owner; }

	void explode();
	bool isExploding() const { return exploding; }
	bool isFinishedExploding() const { return finishedExploding; }
	const sf::Sprite& getCurrentSprite() const;

private:
	sf::Vector2f bulletSpeed = {0.f, 500.f};
	BulletOwner owner;

	std::vector<sf::Sprite> spriteStates;
	std::size_t currentSprite = 0;
	float spriteTimer = 0.0f;

	std::optional<sf::Sprite> explosionSprite;
	bool exploding = false;
	bool finishedExploding = false;
	float explosionTimer = 0.0f;

	std::vector<std::string> getSpriteKeys(AlienBulletType type) const;
};