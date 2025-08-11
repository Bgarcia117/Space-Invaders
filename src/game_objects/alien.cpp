#include <iostream>
#include <string>
#include "game_objects/alien.h"         // Header file
#include "core/game_object.h"           // Base Class
#include "managers/resource_manager.h"  // Resource/Sprite Manager
#include "core/resource_ids.h"          // Texture map keys and paths

constexpr float	ALIEN_WIDTH = 50.f;
constexpr float ALIEN_HEIGHT = 30.f;
constexpr sf::Vector2f ALIEN_START_POS = { 0.f, 0.f };

Alien::Alien(const ResourceManager& resourceManager, AlienType alienType, sf::Vector2f position) : 
	GameObject(resourceManager, getSpriteKey(alienType), position), 
    type(alienType), pointValue(getPointValue(alienType))  { 

}


void Alien::move() {

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


int Alien::getPointValue(AlienType type) {
    switch (type) {
        case AlienType::SQUID   : return 30;
        case AlienType::CRAB    : return 20;
        case AlienType::OCTOPUS : return 30;
        case AlienType::UFO     : return 50;
    }

    return -1;
}