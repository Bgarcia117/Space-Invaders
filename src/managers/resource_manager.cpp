#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "managers/resource_manager.h"
#include "core/resource_ids.h"

ResourceManager::ResourceManager() {
    if (!loadAllTextures()) {
        std::cerr << "Failed to load required game textures!" << std::endl;
    }

    if (!font.openFromFile("assets/fonts/font.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    defineSpriteConfig("player",  { ResourceKeys::playerKey, sf::IntRect({9, 12},  { 22, 20 }), {2.5f, 2.5f} });
    defineSpriteConfig("bullet",  { ResourceKeys::bulletKey, sf::IntRect({96, 54}, {102, 84}), {1.f, 1.f} });
 
    // ===================== Alien Sprite Position One ============
    // Squid Arms Crossed
    defineSpriteConfig("squid",   { ResourceKeys::alienKey, sf::IntRect({5, 4}, { 14, 16 }), {1.75f, 1.75f} });   
    // Crab Arms Up
    defineSpriteConfig("crab",    { ResourceKeys::alienKey, sf::IntRect({1, 28},{ 22, 16 }), {1.50f, 1.50f} });   
    // Octopus Arms Out
    defineSpriteConfig("octopus", { ResourceKeys::alienKey, sf::IntRect({3, 53},{ 18, 14 }), {1.50f, 1.50f} });  
   
    defineSpriteConfig("UFO",     { ResourceKeys::alienKey, sf::IntRect({0, 77},{ 24, 14 }), {1.25f, 1.25f} });



    // ===================== Alien Sprite Position Two ============
    // Squid Arms Open   
    defineSpriteConfig("squidTwo",   { ResourceKeys::alienKey, sf::IntRect({29, 4},{ 14, 16 }),  {1.75f, 1.75f} }); 
    // Crabs Arms Down
    defineSpriteConfig("crabTwo",    { ResourceKeys::alienKey, sf::IntRect({25, 28},{ 22, 16 }), {1.50f, 1.50f} });  
    // Octopus Arms Closed
    defineSpriteConfig("octopusTwo", { ResourceKeys::alienKey, sf::IntRect({27, 53},{ 18, 14 }), {1.50f, 1.50f} });  
}



bool ResourceManager::loadFont(const std::string& filepath) {
    if (!font.openFromFile(filepath)) {
        return false;
    }

    return true;
}

/*
 * @brief Gets a reference to a previously loaded texture
 * @param key The unique name for accessing texture
 * @return const reference to the texture stored
 * @throws std::runtime_error if texture is not found
 */
const sf::Texture& ResourceManager::getTexture(const std::string& key) const {
    // Return reference to the pre-loaded texture
    auto it = textures.find(key);

    if (it == textures.end()) {
        //std::cout << "Error: Texture for: " << key << " not found!" << std::endl;
        throw std::runtime_error("Texture not found: " + key);
    }

    return it->second;
}


/*
 * @brief Loads texture from file and store it with a key
 * @param key Unique name for the texture ("alien", "player", "bullet")
 * @param filepath Path to image file relative to executable
 * @return true if texture loads successfully, false if loading fails
 */
bool ResourceManager::loadTexture(const std::string& key, const std::string& filepath) {
    // Load texture directly to the map, instead of creating temp object
    // Accesses private unordered map
    // Loads texture and checks return 
    if (!textures[key].loadFromFile(filepath)) {
        textures.erase(key); // Clean up empty texture if failed
        std::cout << "Failed to load texture from: " << filepath << std::endl;
        return false;
    }

    std::cout << "Succeeded to load texture!" << std::endl;
    return true;
}

const SpriteConfig& ResourceManager::getSpriteConfig(const std::string& spriteKey) const {
    auto it = spriteConfigs.find(spriteKey);

    if (it == spriteConfigs.end()) {
        throw std::runtime_error("Sprite not found: " + spriteKey);
    }

    return it->second;
}

// Applies texture and creates texture rect for sprite
sf::Sprite ResourceManager::createSprite(const std::string& spriteKey) const {
    const SpriteConfig& spriteConfig = getSpriteConfig(spriteKey);
    const sf::Texture& texture = getTexture(spriteConfig.textureKey);

    sf::Sprite sprite(texture);
    sprite.setTextureRect(spriteConfig.textureRect);
    sprite.setScale(spriteConfig.scale);

    return sprite;
}

/*
 * @brief Loads all game textures into memory
 * 
 * Attempts to load every texture since every single one is needed when the game starts.
 * Uses the loadTexture() helper function for loading and error handling.
 * 
 * @return true if all textures are loaded successfully, false if any fail to load.
 */
bool ResourceManager::loadAllTextures() {
    bool success = true;

    success &= loadTexture(ResourceKeys::alienKey, ResourcePaths::alienPath);
    success &= loadTexture(ResourceKeys::playerKey, ResourcePaths::playerPath);
    success &= loadTexture(ResourceKeys::bulletKey, ResourcePaths::bulletPath);
    // success &= loadTexture(ResourceKeys::barrierKey, ResourcePaths::barrierPath);

    return success;
}


void ResourceManager::defineSpriteConfig(const std::string& spriteKey, const SpriteConfig& config) {
    spriteConfigs[spriteKey] = config;
}

