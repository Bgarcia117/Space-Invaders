#include "game_objects/barrier.h"

constexpr sf::Color LIGHT_GREEN(42, 249, 50);

Barrier::Barrier(const ResourceManager &resourceManager, sf::Vector2f position) :
    GameObject(resourceManager, "barrier", position) {
    setSpriteColor(LIGHT_GREEN);

}

void Barrier::update(float deltaTime) {

}
