#include <iostream>
#include <string>
#include "game_objects/alien.h"         // Header file
#include "core/game_object.h"           // Base Class
#include "managers/resource_manager.h"  // Resource/Sprite Manager
#include "core/resource_ids.h"          // Texture map keys and paths

constexpr float	ALIEN_WIDTH = 50.f;
constexpr float ALIEN_HEIGHT = 30.f;
constexpr float DEATH_TIME = 0.10f;
constexpr float SPRITE_FLIP_TIME = 1.f;
constexpr sf::Vector2f ALIEN_START_POS = { 0.f, 0.f };
constexpr sf::Color UFO_RED(223, 37, 28);

Alien::Alien(const ResourceManager& resourceManager, AlienType alienType, sf::Vector2f position) : 
	GameObject(resourceManager, getSpriteKey(alienType), position),
    spritesState(SpriteState::ARMSUP),
    type(alienType), 
    pointValue(getPointValue(alienType)),
    dying(false),
    deathTimer(DEATH_TIME),
    spriteFlipTimer(SPRITE_FLIP_TIME) { 

    if (type != AlienType::UFO) {
        // Second Sprite for "animation"
        const SpriteConfig& spriteConfig = resourceManager.getSpriteConfig(getNextSpriteKey(alienType));
        const sf::Texture& texture = resourceManager.getTexture(spriteConfig.textureKey);

        sprite2.emplace(texture);
        sprite2->setTextureRect(spriteConfig.textureRect);
        sprite2->setScale(spriteConfig.scale);
        sprite2->setPosition({ position });

        // Sprite shown upon death
        const SpriteConfig& spriteConfig2 = resourceManager.getSpriteConfig("death");
        const sf::Texture& texture2 = resourceManager.getTexture(spriteConfig2.textureKey);

        deathSprite.emplace(texture2);
        deathSprite->setTextureRect(spriteConfig2.textureRect);
        deathSprite->setScale(spriteConfig2.scale);
        deathSprite->setPosition({ position });
      
    } else {
        setSpriteColor(UFO_RED);
    }

}

// Updates sprite using deltaTime
void Alien::update(float deltaTime) {
    if (!isDying()) {
        spriteFlipTimer -= deltaTime;

        if (spriteFlipTimer <= 0) {
            if (spritesState == SpriteState::ARMSUP) {
                spritesState = SpriteState::ARMSDOWN;
            } else {
                spritesState = SpriteState::ARMSUP;
            }

            spriteFlipTimer = SPRITE_FLIP_TIME;
        }
    } else {
        spritesState = SpriteState::DEATH;
        deathTimer -= deltaTime;
    }


}

void Alien::move(sf::Vector2f offset) {
    GameObject::move(offset);

    if (!sprite2.has_value()) {
        std::cerr << "Sprite Two has not been initializied!" << std::endl;
    }
    sprite2->move({ offset.x, offset.y });
}


// TODO: Remove redundant getSprite()
const sf::Sprite& Alien::getCurrentSprite() const {
    switch(spritesState) {
        case SpriteState::ARMSUP:
            return getSprite();
        case SpriteState::ARMSDOWN:
            return *sprite2;
        case SpriteState::DEATH:
            return *deathSprite;
        default:
            return getSprite();
    }
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