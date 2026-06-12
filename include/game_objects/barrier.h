#pragma once
#include <SFML/Graphics.hpp>
#include "core/game_object.h"
#include "managers/resource_manager.h"

class Barrier : public GameObject {
public:
    Barrier(const ResourceManager& resourceManager, sf::Vector2f position);
    void update(float deltaTime) override;
    void takeDamage() { health--; }
    bool isDestroyed() const { return health <= 0; }

private:
    int health = 4;
};