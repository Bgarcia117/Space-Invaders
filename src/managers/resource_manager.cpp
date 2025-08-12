#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "managers/resource_manager.h"
#include "core/resource_ids.h"

ResourceManager::ResourceManager() {
    if (!loadAllTextures()) {
        throw std::runtime_error("Failed to load required game textures!");
    }

    if (!font.openFromFile("assets/fonts/font.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    /*
    // ===================== Start positions ============
    defineSpriteConfig("squid",   { ResourceKeys::alienKey, sf::IntRect({5, 4}, { 14, 16 }), {2.f,   2.f} });  // Arms Crossed
    defineSpriteConfig("crab",    { ResourceKeys::alienKey, sf::IntRect({1, 28},{ 22, 16 }), {1.75f, 1.75f} });   // Arms Up
    defineSpriteConfig("octopus", { ResourceKeys::alienKey, sf::IntRect({3, 53},{ 18, 14 }), {1.75f, 1.75f} });   // Arms Out
    defineSpriteConfig("UFO",     { ResourceKeys::alienKey, sf::IntRect({0, 77},{ 24, 14 }), {1.75f, 1.75f} });
    defineSpriteConfig("player",  { ResourceKeys::playerKey, sf::IntRect({0, 0},{ 32, 32 }), {1.75f, 1.75f} });
    */


    // =================== TEST ===========================
    defineSpriteConfig("squid",   { ResourceKeys::alienKey, sf::IntRect({5, 4}, { 14, 16 }), {1.75f, 1.75f} });  // Arms Crossed
    defineSpriteConfig("crab",    { ResourceKeys::alienKey, sf::IntRect({1, 28},{ 22, 16 }), {1.50f, 1.50f} });   // Arms Up
    defineSpriteConfig("octopus", { ResourceKeys::alienKey, sf::IntRect({3, 53},{ 18, 14 }), {1.50f, 1.50f} });   // Arms Out
    defineSpriteConfig("UFO",     { ResourceKeys::alienKey, sf::IntRect({0, 77},{ 24, 14 }), {1.25f, 1.25f} });
    defineSpriteConfig("player",  { ResourceKeys::playerKey, sf::IntRect({0, 0},{ 32, 32 }), {1.25f, 1.25f} });



    // ===================== Second position ============
    // defineSpriteConfig("squid",   { ResourceKeys::alienKey, sf::IntRect({29, 4},{ 14, 16 }), {4.0f, 4.0f} }); // Arms Open   
    // defineSpriteConfig("crab",    { ResourceKeys::alienKey, sf::IntRect({25, 28},{ 22, 16 }), {3.f, 3.f} });  // Arms Down
    // defineSpriteConfig("octopus", { ResourceKeys::alienKey, sf::IntRect({27, 53},{ 18, 14 }), {3.f, 3.f} });  // Arms Closed
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
 * @brief Gets the size of the texture
 * @param key The unique name for accessing texture
 * @return a vector of two unsigned ints, one is the width, the other is height
 * @throws std::runtime_error if texture is not found
const sf::Vector2u ResourceManager::getTextureSize(const std::string& key) const {
    auto it = textures.find(key);

    if (it == textures.end()) {
        //std::cout << "Error: Texture for " << key << "not found!" << std::endl;
        throw std::runtime_error("Texture not found: " + key);
    }

    return it->second.getSize();
}
*/

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


const SpriteConfig& ResourceManager::getSpriteConfig(const std::string& spriteKey) const {
    auto it = spriteConfigs.find(spriteKey);

    if (it == spriteConfigs.end()) {
        throw std::runtime_error("Sprite not found: " + spriteKey);
    }

    return it->second;
}