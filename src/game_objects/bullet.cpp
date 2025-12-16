#include <string>
#include <SFML/Graphics.hpp>
#include "game_objects/bullet.h"
#include "core/game_object.h"

Bullet::Bullet(const ResourceManager& resourceManager, sf::Vector2f position ) : 
	GameObject(resourceManager, "bullet", position)  {

}