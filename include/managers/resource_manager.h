#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct SpriteConfig {
	std::string textureKey;
	sf::IntRect textureRect;
	sf::Vector2f scale = { 1.f, 1.f };
};

class ResourceManager {
public:
	ResourceManager();

	bool loadFont(const std::string& filepath);
	sf::Font& getFont() { return font; } // Cannot be const

	const sf::Texture& getTexture(const std::string& key) const;
	const SpriteConfig& getSpriteConfig(const std::string& spriteKey) const;
	sf::Sprite createSprite(const std::string& spriteKey) const;

	const sf::SoundBuffer& getSoundBuffer(const std::string& key) const;


private:
	sf::Font font;
	std::unordered_map<std::string, sf::Texture> textures;
	std::unordered_map<std::string, SpriteConfig> spriteConfigs;
	std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;

	bool loadTexture(const std::string&, const std::string& filepath);
	bool loadAllTextures();
	bool loadSoundBuffer(const std::string& key, const std::string& filepath);
	bool loadAllSounds();

	void defineSpriteConfig(const std::string& spriteKey, const SpriteConfig& config);
};