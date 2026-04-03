#include <string>
#include <SFML/Graphics.hpp>
#include "game_objects/bullet.h"
#include "core/game_object.h"

Bullet::Bullet(const ResourceManager& resourceManager, sf::Vector2f position, BulletOwner owner) :
	GameObject(resourceManager, "bullet", position), owner(owner)  {

}

void Bullet::update(float deltaTime) {
	if (owner == BulletOwner::PLAYER) {
		move({bulletSpeed.x, -bulletSpeed.y * deltaTime});
	} else {
		move({bulletSpeed.x, bulletSpeed.y * deltaTime});
	}
}
