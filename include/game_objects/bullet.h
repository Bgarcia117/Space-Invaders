#pragma once
#include <optional>
#include <SFML/Graphics.hpp>
#include "core/game_object.h"
#include "managers/resource_manager.h"
enum class BulletOwner {PLAYER, ALIEN};

class Bullet : public GameObject {
public:
	Bullet(const ResourceManager& resourceManager, const sf::Vector2f position, BulletOwner owner);
	void update(float deltaTime) override;
	BulletOwner getOwner() const { return owner; }

	void explode();
	bool isExploding() const { return exploding; }
	bool isFinishedExploding() const { return finishedExploding; }
	const sf::Sprite& getCurrentSprite() const;

private:
	sf::Vector2f bulletSpeed = {0.f, 500.f};
	BulletOwner owner;

	std::optional<sf::Sprite> explosionSprite;
	bool exploding = false;
	bool finishedExploding = false;
	float explosionTimer = 0.0f;
};