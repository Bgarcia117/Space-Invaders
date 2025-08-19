#include <iostream>
#include <string>
#include "game_objects/alien.h"         // Header file
#include "core/game_object.h"           // Base Class
#include "managers/resource_manager.h"  // Resource/Sprite Manager
#include "core/resource_ids.h"          // Texture map keys and paths

constexpr float	ALIEN_WIDTH = 50.f;
constexpr float ALIEN_HEIGHT = 30.f;
constexpr float SPRITE_FLIP_TIME = 1.f;
constexpr sf::Vector2f ALIEN_START_POS = { 0.f, 0.f };

Alien::Alien(const ResourceManager& resourceManager, AlienType alienType, sf::Vector2f position) : 
	GameObject(resourceManager, getSpriteKey(alienType), position), 
    type(alienType), 
    pointValue(getPointValue(alienType)),
    useSprite1(true),
    spriteFlipTimer(SPRITE_FLIP_TIME) { 

    const SpriteConfig& spriteConfig = resourceManager.getSpriteConfig(getNextSpriteKey(alienType));
    const sf::Texture& texture = resourceManager.getTexture(spriteConfig.textureKey);

    sprite2.emplace(texture);
    sprite2->setTextureRect(spriteConfig.textureRect);
    sprite2->setScale(spriteConfig.scale);
    sprite2->setPosition({ position });

}

void Alien::update(float deltaTime) {
    spriteFlipTimer -= deltaTime;

    if (spriteFlipTimer <= 0) {
        useSprite1 = !useSprite1;
        spriteFlipTimer = SPRITE_FLIP_TIME;
    }
}


void Alien::move() {

}

const sf::Sprite& Alien::getCurrentSprite() const {
    return useSprite1 ? getSprite() : *sprite2;
}

std::string Alien::getSpriteKey(AlienType type) {
    switch (type) {
        case AlienType::SQUID   : return "squid";
        case AlienType::CRAB    : return "crab";
        case AlienType::OCTOPUS : return "octopus";
        case AlienType::UFO     : return "UFO";
    }

    return "squid";
}

// Gets sprite key for second position of sprite
std::string Alien::getNextSpriteKey(AlienType type) {
    switch (type) {
        case AlienType::SQUID   : return "squidTwo";
        case AlienType::CRAB    : return "crabTwo";
        case AlienType::OCTOPUS : return "octopusTwo";
        case AlienType::UFO     : return "UFO";
    }

    return "squid";
}


int Alien::getPointValue(AlienType type) {
    switch (type) {
        case AlienType::SQUID   : return 30;
        case AlienType::CRAB    : return 20;
        case AlienType::OCTOPUS : return 30;
        case AlienType::UFO     : return 50;
    }

    return -1;
}