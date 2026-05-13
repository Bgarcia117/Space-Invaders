#include <string>
#include <algorithm>
#include <optional>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "core/game.h"
#include "managers/resource_manager.h"
#include "game_objects/player.h"
#include "game_objects/alien.h"
#include <UI/ui.h>

constexpr int MAX_SIDE_MOVES = 8;
constexpr float ALIEN_SPEED = 0.038f;
constexpr sf::Vector2f ALIEN_HORIZONTAL_STEP = { 8.f, 0.f };
constexpr sf::Vector2f ALIEN_VERTICAL_STEP = { 0.f, 20.f };
constexpr sf::Vector2f PLAYER_START_POS = { 500.f, 870.f };
constexpr sf::Vector2f PLAYER_SPEED = { 150.f, 0.f };

Game::Game() : resourceManager(), 
               player(resourceManager, PLAYER_START_POS),
	           alienMoveTimer(ALIEN_SPEED),
	           ui(resourceManager, score, highScore, player.getLives()) {

}

void Game::init() {
	initAliens();
	spawnUFO();
}

void Game::begin() {
	gameState = PLAYING;
	
}

void Game::update(sf::RenderTarget& target, float deltaTime) {
	switch (gameState) {
		case COINMENU:
			ui.updateTypeWriter(deltaTime);
			break;
		case TABLEMENU:
			ui.updateTypeWriter(deltaTime);
			break;
		case PLAYING:
			player.update(deltaTime);
			moveAliens(aliens, deltaTime);

			for (auto& bullet : bullets) {
				bullet.update(deltaTime);
			}

			for (auto& alien : aliens) {
				alien.update(deltaTime);
				target.draw(alien.getCurrentSprite());
			}

			checkBulletAlienCollision();

			// TODO: ADD EXPLOSION ANIMATION LIKE IN ORIGINAL GAME (COLOR: RED)
			// Remove bullets if they reach the top of the screen
			std::erase_if(bullets, [](Bullet& bullet) {
				return bullet.getPosition().y < 0.f;
			});

			// Manual erase so we can keep nextAlienToMove pointing at the same
			// logical alien even when indices shift due to erasure mid-cycle.
			for (auto it = aliens.begin(); it != aliens.end(); ) {
				if (it->isDead()) {
					std::size_t deadIndex = std::distance(aliens.begin(), it);
					it = aliens.erase(it);
					if (deadIndex < nextAlienToMove && nextAlienToMove > 0) {
						nextAlienToMove--;
					}
				} else {
					++it;
				}
			}

			break;
		case GAMEOVER:
			break;

	}
}

void Game::render(sf::RenderTarget& target, float deltaTime) {
	switch (gameState) {
	case COINMENU:
		ui.renderHUD(target, player, false);
		ui.renderCoinMenu(target);
		break;

	case TABLEMENU:
		ui.renderHUD(target, player, false);
		ui.renderTableMenu(target);
		break;

	case PLAYING:
		ui.renderHUD(target, player, true);

		// Draw alien after flipping sprite
		for (auto& alien : aliens) {
			target.draw(alien.getCurrentSprite());
		}

		for (auto& bullet : bullets) {
			target.draw(bullet.getSprite());
		}

		target.draw(player.getSprite());
		target.draw(ufo->getSprite()); // DEBUGGING
		break;

	default:
		ui.renderHUD(target, player, true);
		std::cout << "Default case! Check code!";

	}
}

void Game::handleInput(const sf::Event& event) {
	if (event.is<sf::Event::KeyPressed>()) {
		// Contains pointer to KeyPress struct
		const auto& key = event.getIf<sf::Event::KeyPressed>();

		switch (gameState) {
			case COINMENU:
				ui.handleMenuInput(key->code);

				if (key->code == sf::Keyboard::Key::Enter) {
					gameState = GameState::TABLEMENU;
					ui.startTypingTableMenu();
				}
				break;

			case TABLEMENU:
				if (key->code == sf::Keyboard::Key::Enter) {
					gameState = GameState::PLAYING;
				}
				break;

			case PLAYING:
				if (key->code == sf::Keyboard::Key::Space) {
					// Check if there is a player bullet in the vector
					bool playerBulletExists = false;
					for (const auto& bullet : bullets) {
						if (bullet.getOwner() == BulletOwner::PLAYER) {
							playerBulletExists = true;
							break;
						}
					}

					if (!playerBulletExists) {
						bullets.push_back(player.shoot(resourceManager));
						playerShotCount++;
					}
				}
				break;

			case GAMEOVER:
				break;

			default:
				break;
		}

	}
}

// Puts aliens in initial positions
void Game::initAliens() {
	for (int row = 4; row >= 0; row--) {
		for (int col = 0; col < 11; col++) {
			AlienType type = AlienType::SQUID;
			// Left offset + (col * spacing), Top offset + (row * spacing)
			sf::Vector2f position = { 89.f + col * 50.f, 200.f + row * 50 };

			if (row > 0 && row < 3) {
				type = AlienType::CRAB;
				position = { 84.f + col * 50.f, 200.f + row * 50 };
			}
			else if (row > 2) {
				type = AlienType::OCTOPUS;
			}

			aliens.emplace_back(resourceManager, type, position);
		}
	}

}

void Game::moveAliens(std::vector<Alien>& aliens, float deltaTime) {
	alienMoveTimer -= deltaTime;

	if (alienMoveTimer <= 0) {
		// Case: All aliens are dead
		if (aliens.empty()) {
			alienMoveTimer = ALIEN_SPEED;
			return;
		}

		if (alienMoveCounter == MAX_SIDE_MOVES) {
			for (auto& alien : aliens) {
				alien.move(ALIEN_VERTICAL_STEP);
			}
			alienMoveCounter = 0;

			if (aliensDirection == alienDirection::RIGHT) {
				aliensDirection = alienDirection::LEFT;
			} else {
				aliensDirection = alienDirection::RIGHT;
			}

			nextAlienToMove = 0;
		}
		else {
			sf::Vector2f step;
			if (aliensDirection == alienDirection::RIGHT) {
				step = ALIEN_HORIZONTAL_STEP;
			} else {
				step = sf::Vector2f{ -ALIEN_HORIZONTAL_STEP.x, ALIEN_HORIZONTAL_STEP.y };
			}

			aliens[nextAlienToMove].move(step);
			nextAlienToMove++;

			if (nextAlienToMove >= aliens.size()) {
				nextAlienToMove = 0;
				alienMoveCounter++;
			}
		}

		alienMoveTimer = ALIEN_SPEED;
	}
}

void Game::updateUFOTimer(float deltaTime) {

}

void Game::spawnUFO() {
	ufo = Alien(resourceManager, AlienType::UFO, {50.f, 150.f});
}

void Game::checkBulletAlienCollision() {
	std::erase_if(bullets, [this](const Bullet& bullet) {
		if (bullet.getOwner() != BulletOwner::PLAYER) {
			return false;
		}

		for (auto& alien : aliens) {
			if (!alien.isDying() && alien.collidesWith(bullet)) {
				alien.kill();
				return true;
			}
		}

		return false;
	});
}

std::string Game::convertScore(int score) {
	std::string strScore = std::to_string(score);

	while (strScore.length() < 4) {
		strScore = "0" + strScore;
	}

	return strScore;
}
