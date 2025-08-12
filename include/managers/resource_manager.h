#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

struct SpriteConfig {
	std::string textureKey;
	sf::IntRect textureRect;
	sf::Vector2f scale = { 1.f, 1.f };
};

class ResourceManager {
public:
	ResourceManager();

	bool loadFont(const std::string& filepath);
	const sf::Font& getFont() const { return font; }

	const sf::Texture& getTexture(const std::string& key) const;
	// const sf::Vector2u getTextureSize(const std::string& key) const;
	const SpriteConfig& getSpriteConfig(const std::string& spriteKey) const;


private:
	sf::Font font;
	std::unordered_map<std::string, sf::Texture> textures;
	std::unordered_map<std::string, SpriteConfig> spriteConfigs;

	bool loadTexture(const std::string&, const std::string& filepath);
	bool loadAllTextures();
	void defineSpriteConfig(const std::string& spriteKey, const SpriteConfig& config);
};