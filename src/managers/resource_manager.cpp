#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "managers/resource_manager.h"
#include "core/resource_ids.h"

// Sprite Rectangles
// IntRect: {{x, y}  {width, height}} where {x, y} denote the top left corner of the sprite on the sheet
constexpr sf::IntRect PLAYER_RECT = sf::IntRect({ 9, 12 }, { 22, 20 });
constexpr sf::IntRect BULLET_RECT = sf::IntRect({ 96, 54 }, { 6, 30 });
constexpr sf::IntRect SQUID_RECT = sf::IntRect({ 5, 4 }, { 14, 16 });
constexpr sf::IntRect CRAB_RECT = sf::IntRect({ 1, 28 }, { 22, 16 });
constexpr sf::IntRect OCTOPUS_RECT = sf::IntRect({ 3, 53 }, { 18, 14 });
constexpr sf::IntRect UFO_RECT = sf::IntRect({ 0, 77 }, { 24, 14 });
constexpr sf::IntRect BARRIER_RECT = sf::IntRect({ 7, 9 }, { 18, 14 });

constexpr sf::IntRect SQUID_TWO_RECT = sf::IntRect({ 29, 4 }, { 14, 16 });
constexpr sf::IntRect CRAB_TWO_RECT = sf::IntRect({ 25, 28 }, { 22, 16 });
constexpr sf::IntRect OCTOPUS_TWO_RECT = sf::IntRect({ 27, 53 }, { 18, 14 });

constexpr sf::IntRect PLAYER_DEATH_RECT_ONE = sf::IntRect({ 40, 12 }, { 15, 8 });
constexpr sf::IntRect PLAYER_DEATH_RECT_TWO = sf::IntRect({ 8, 44 }, { 16, 8 });
constexpr sf::IntRect ALIEN_DEATH_RECT = sf::IntRect({ 252, 54 }, { 78, 42 });
constexpr sf::IntRect EXPLOSION_RECT = sf::IntRect({ 72, 66 }, { 48, 48 });

// Sprite Scales
constexpr sf::Vector2f PLAYER_SCALE = { 2.5f, 2.5f };
constexpr sf::Vector2f BULLET_SCALE = { 0.3f, 0.4f };
constexpr sf::Vector2f BARRIER_SCALE = {4.0f, 4.0f };

constexpr sf::Vector2f SQUID_SCALE = { 1.75f, 1.75f };
constexpr sf::Vector2f CRAB_SCALE = { 1.50f, 1.50f };
constexpr sf::Vector2f OCTOPUS_SCALE = { 1.50f, 1.50f };
constexpr sf::Vector2f UFO_SCALE = { 2.0f, 1.75f };

constexpr sf::Vector2f SQUID_TWO_SCALE = { 1.75f, 1.75f };
constexpr sf::Vector2f CRAB_TWO_SCALE = { 1.50f, 1.50f };
constexpr sf::Vector2f OCTOPUS_TWO_SCALE = { 1.50f, 1.50f };

constexpr sf::Vector2f PLAYER_DEATH_SCALE = {1.0f, 1.0f };
constexpr sf::Vector2f ALIEN_DEATH_SCALE = { 0.45f, 0.55f };
constexpr sf::Vector2f EXPLOSION_SCALE = {0.5f, 0.5f };





ResourceManager::ResourceManager() {
    if (!loadAllTextures()) {
        std::cerr << "Failed to load required game textures!" << std::endl;
    }

    if (!loadAllSounds()) {
        std::cerr << "Failed to load all sounds!" << std::endl;
    }

    if (!font.openFromFile("assets/fonts/font.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    defineSpriteConfig("player", { ResourceKeys::playerKey, PLAYER_RECT, PLAYER_SCALE });
    defineSpriteConfig("bullet",  { ResourceKeys::bulletKey, BULLET_RECT, BULLET_SCALE });
    defineSpriteConfig("barrier", {ResourceKeys::barrierKey, BARRIER_RECT, BARRIER_SCALE});

    // TESTING
    defineSpriteConfig("alien_death", { ResourceKeys::effectsKey, ALIEN_DEATH_RECT, ALIEN_DEATH_SCALE });
 
    // ===================== Alien Sprite Position One ============
    // Squid Arms Crossed
    defineSpriteConfig("squid", { ResourceKeys::alienKey, SQUID_RECT, SQUID_SCALE });
    // Crab Arms Up
    defineSpriteConfig("crab",    { ResourceKeys::alienKey, CRAB_RECT, CRAB_SCALE });   
    // Octopus Arms Out
    defineSpriteConfig("octopus", { ResourceKeys::alienKey, OCTOPUS_RECT, OCTOPUS_SCALE });  
   
    defineSpriteConfig("UFO",     { ResourceKeys::alienKey, UFO_RECT, UFO_SCALE });



    // ===================== Alien Sprite Position Two ============
    // Squid Arms Open   
    defineSpriteConfig("squidTwo",   { ResourceKeys::alienKey, SQUID_TWO_RECT,  SQUID_TWO_SCALE }); 
    // Crabs Arms Down
    defineSpriteConfig("crabTwo",    { ResourceKeys::alienKey, CRAB_TWO_RECT, CRAB_TWO_SCALE });  
    // Octopus Arms Closed
    defineSpriteConfig("octopusTwo", { ResourceKeys::alienKey, OCTOPUS_TWO_RECT, OCTOPUS_TWO_SCALE });

    // ==================== Effects =================================
    defineSpriteConfig("explosion", {ResourceKeys::effectsKey, EXPLOSION_RECT, EXPLOSION_SCALE});
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
        // std::cout << "Error: Texture for: " << key << " not found!" << std::endl;
        throw std::runtime_error("Texture not found: " + key);
    }

    return it->second;
}


/*
 * @brief Loads texture from file and stores it in a map with a key
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

const sf::SoundBuffer &ResourceManager::getSoundBuffer(const std::string &key) const {
    auto it = soundBuffers.find(key);

    if (it == soundBuffers.end()) {
        throw std::runtime_error("Sound buffer not found: " + key);
    }

    return it->second;
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

    // loadTexture returns a boolean which affects the value of success if it fails
    success &= loadTexture(ResourceKeys::alienKey, ResourcePaths::alienPath);
    success &= loadTexture(ResourceKeys::playerKey, ResourcePaths::playerPath);
    success &= loadTexture(ResourceKeys::bulletKey, ResourcePaths::bulletPath);
    success &= loadTexture(ResourceKeys::barrierKey, ResourcePaths::barrierPath);
    success &= loadTexture(ResourceKeys::effectsKey, ResourcePaths::effectsPath);


    return success;
}

bool ResourceManager::loadSoundBuffer(const std::string &key, const std::string &filepath) {
    if (!soundBuffers[key].loadFromFile(filepath)) {
        soundBuffers.erase(key);
        std::cout << "Failed to load sound from: " << filepath << std::endl;
        return false;
    }

    std::cout << "Succeeded to load sound!" << std::endl;
    return true;
}

bool ResourceManager::loadAllSounds() {
    bool success = true;

    success &= loadSoundBuffer(ResourceKeys::playerShootSoundKey, ResourcePaths::playerShootSoundPath);
    success &= loadSoundBuffer(ResourceKeys::alienExplosionSoundKey, ResourcePaths::alienExplosionSoundPath);
    success &= loadSoundBuffer(ResourceKeys::playerDeathSoundKey, ResourcePaths::playerDeathSoundPath);

    return success;
}


void ResourceManager::defineSpriteConfig(const std::string& spriteKey, const SpriteConfig& config) {
    spriteConfigs[spriteKey] = config;
}

