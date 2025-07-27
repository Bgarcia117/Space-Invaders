#include <SFML/Graphics.hpp>
#include "managers/resource_manager.h"
#include "core/resource_ids.h"

ResourceManager::ResourceManager() {
    
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
 */
const sf::Vector2u ResourceManager::getTextureSize(const std::string& key) const {
    auto it = textures.find(key);

    if (it == textures.end()) {
        //std::cout << "Error: Texture for " << key << "not found!" << std::endl;
        throw std::runtime_error("Texture not found: " + key);
    }

    return it->second.getSize();
}