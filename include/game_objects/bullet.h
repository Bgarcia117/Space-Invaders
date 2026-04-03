#pragma once
#include <SFML/Graphics.hpp>
#include "core/game_object.h"
#include "managers/resource_manager.h"
enum class BulletOwner {PLAYER, ALIEN};

class Bullet : public GameObject {
public:
	Bullet(const ResourceManager& resourceManager, const sf::Vector2f position, BulletOwner owner);
	void update(float deltaTime) override;
	BulletOwner getOwner() const { return owner; }

private:
	sf::Vector2f bulletSpeed = {0.f, 500.f};
	BulletOwner owner;
};