#pragma once
#include <optional>
#include <SFML/Graphics.hpp>
#include "core/game_object.h"
#include "managers/resource_manager.h"

class Barrier : public GameObject {
public:
    Barrier(const ResourceManager& resourceManager, sf::Vector2f position);
    void update(float deltaTime) override;
    void takeDamage(sf::Vector2f impactPos, sf::Sprite explosionShape, const sf::Image& effectsSpriteSheetImg);
    bool isDestroyed() const { return health <= 0; }
    const sf::Sprite& getBarrierTextureSprite() const { return *barrierTextureSprite; }
    bool collidesWith(const sf::Sprite& otherSprite);

private:
    int health = 4;
    std::optional<sf::RenderTexture> barrierTexture;
    std::optional<sf::Sprite> barrierTextureSprite;
    std::optional<sf::Image> barrierImage;          // Image for CPU
};