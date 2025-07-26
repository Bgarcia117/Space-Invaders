#pragma once
#include <string_view>

namespace ResourceKeys {
	constexpr std::string_view playerKey = "player";
	constexpr std::string_view alienKey = "alien";
	constexpr std::string_view bulletKey = "bullet";
	constexpr std::string_view barrierKey = "barrier";
}

namespace ResourcePaths {
	constexpr std::string_view playerPath;
	constexpr std::string_view alienPath =  "assets/sprites/alien.png";
	constexpr std::string_view bulletPath;
	constexpr std::string_view barrierPath;
}