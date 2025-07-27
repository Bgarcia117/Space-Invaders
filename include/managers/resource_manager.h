#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

#include <SFML/Graphics.hpp>

class ResourceManager {
public:
	ResourceManager();

	bool loadTexture(const std::string&, const std::string& filepath);
	const sf::Texture& getTexture(const std::string& key) const;
	const sf::Vector2u getTextureSize(const std::string& key) const;

private:
	std::unordered_map<std::string, sf::Texture> textures;
};