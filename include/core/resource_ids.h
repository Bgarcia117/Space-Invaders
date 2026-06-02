#pragma once
#include <string>

namespace ResourceKeys {
	const std::string playerKey = "player";
	const std::string alienKey = "alien";
	const std::string bulletKey = "bullet";
	const std::string barrierKey = "barrier";
	const std::string effectsKey = "effect";
	const std::string playerShootSoundKey = "player_shoot";
	const std::string alienExplosionSoundKey = "alien_explosion";
}

namespace ResourcePaths {
	const std::string playerPath = "assets/sprites/player_sheet.png";
	const std::string alienPath =  "assets/sprites/alien_sprites.png";
	const std::string bulletPath = "assets/sprites/bullets.png";
	const std::string barrierPath;
	const std::string effectsPath = "assets/sprites/effects.png";
	const std::string playerShootSoundPath = "assets/sounds/player_bullet.wav";
	const std::string alienExplosionSoundPath = "assets/sounds/alien_explosion.wav";
}