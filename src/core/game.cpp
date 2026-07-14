#include <string>
#include <algorithm>
#include <optional>
#include <random>
#include <SFML/Graphics.hpp>
#include "core/game.h"
#include "managers/resource_manager.h"
#include "game_objects/player.h"
#include "game_objects/alien.h"
#include <UI/ui.h>

#include "core/resource_ids.h"

constexpr float ALIEN_SPEED = 0.038f;
constexpr sf::Vector2f ALIEN_HORIZONTAL_STEP = { 8.f, 0.f };
constexpr sf::Vector2f ALIEN_VERTICAL_STEP = { 0.f, 20.f };
constexpr float ALIEN_WIDTH = 50.f;
constexpr float ALIEN_GROUND_LIMIT = 820.f;
constexpr float	ALIEN_COLUMN_SPACING = 50.f;
constexpr float ALIEN_ROW_SPACING = 50.f;

constexpr sf::Vector2f PLAYER_START_POS = { 75.f, 870.f };
constexpr sf::Vector2f PLAYER_SPEED = { 150.f, 0.f };

constexpr float SCREEN_LEFT_EDGE = 0.f;
constexpr float SCREEN_RIGHT_EDGE = 768.f;

constexpr float BARRIER_Y = 760.f;
constexpr int NUM_OF_BARRIERS = 4;
constexpr float BARRIER_START_X_POS = 150.0f;
constexpr float BARRIER_SPACING = 132.0f;

constexpr float EXPLOSION_Y_LEVEL = 125.f;

Game::Game() : resourceManager(), 
               player(resourceManager, PLAYER_START_POS),
	           alienMoveTimer(ALIEN_SPEED),
	           ui(resourceManager, score, highScore, player.getLives()) {

}

void Game::init() {
	initAliens();
	initBarriers();
	spawnUFO();
	alienExplosionSound.emplace(resourceManager.getSoundBuffer(ResourceKeys::alienExplosionSoundKey));
	playerDeathSound.emplace(resourceManager.getSoundBuffer(ResourceKeys::playerDeathSoundKey));
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

			if (!player.isDying()) {
				moveAliens(aliens, deltaTime);
				updateAlienShots(deltaTime);

				for (auto& alien : aliens) {
					alien.update(deltaTime);
					target.draw(alien.getCurrentSprite());
				}
			}

			if (aliensReachedGround()) {
				gameState = GameState::GAMEOVER;
				ui.startTypingGameOver();
			}

			for (auto& bullet : bullets) {
				bullet.update(deltaTime);
			}

			checkBulletAlienCollision();
			checkBulletPlayerCollision();
			checkBulletBarrierCollision();

			if (player.isDead()) {
				player.loseLife();

				if (player.getLives() <= 0) {
					gameState = GameState::GAMEOVER;
					ui.startTypingGameOver();
				} else {
					player.respawn(PLAYER_START_POS);
				}
			}

			// TODO: ADD EXPLOSION ANIMATION LIKE IN ORIGINAL GAME (COLOR: RED)
			for (auto& bullet : bullets) {
				if (bullet.getOwner() == BulletOwner::PLAYER && !bullet.isExploding() &&
					bullet.getPosition().y < EXPLOSION_Y_LEVEL) {
					bullet.explode();
				}
			}

			// Remove bullets once explosion animation is finished
			std::erase_if(bullets, [](Bullet& bullet) {
				if (bullet.isExploding()) {
					return bullet.isFinishedExploding();
				}

				return bullet.getPosition().y > 1024.0f;
			});

			// Manually erases aliens so we can keep nextAlienToMove synced with the vector
			// Keeps aliens in formation after aliens die
			for (std::size_t i = 0; i < aliens.size();) {
				if (aliens[i].isDead()) {
					aliens.erase(aliens.begin() + i);

					if (i < static_cast<std::size_t>(nextAlienToMove)) {
						nextAlienToMove--;
					}
				} else {
					i++;
				}
			}
			if (aliens.empty()) {
				gameState = GameState::ROUNDWON;
			}

			std::erase_if(barriers, [](const Barrier& barrier) {
				return barrier.isDestroyed();
			});

			break;
		case GAMEOVER:
			ui.updateTypeWriter(deltaTime);
			break;
		case ROUNDWON:
			resetGame();
			gameState = GameState::PLAYING;
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

		for (auto& barrier : barriers) {
			target.draw(barrier.getBarrierTextureSprite());
		}

		// Draw alien after flipping sprite
		for (auto& alien : aliens) {
			target.draw(alien.getCurrentSprite());
		}

		for (auto& bullet : bullets) {
			target.draw(bullet.getCurrentSprite());
		}

		target.draw(player.getCurrentSprite());

		if (ufo) {
			target.draw(ufo->getSprite()); // DEBUGGING
		}
		break;
	case ROUNDWON:
		break;

	case GAMEOVER:
		ui.renderHUD(target, player, false);
		ui.renderGameOver(target);
		break;

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

					if (!playerBulletExists && !player.isDying()) {
						bullets.push_back(player.shoot(resourceManager));
						playerShotCount++;
					}
				}
				break;

			case GAMEOVER:
				if (key->code == sf::Keyboard::Key::Enter) {
					player.resetLives();
					score = 0;
					ui.setP1Score(score);
					resetGame();
					gameState = GameState::COINMENU;
					ui.startTypingCoinMenu();
				}
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
			sf::Vector2f position = { 89.f + col * ALIEN_COLUMN_SPACING, 200.f + row * ALIEN_ROW_SPACING };

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

		// Find the left most and right most aliens
		float leftAlien = aliens[0].getPosition().x;
		float rightAlien = aliens[0].getPosition().x;

		for (auto& alien : aliens) {
			float alienPos = alien.getPosition().x;
			if (alienPos < leftAlien) {
				leftAlien = alienPos;
			}
			if (alienPos > rightAlien) {
				rightAlien = alienPos;
			}
		}

		// Checks if we have reached the screen edge
		bool atRightEdge = (aliensDirection == alienDirection::RIGHT) &&
			               (rightAlien + ALIEN_WIDTH >= SCREEN_RIGHT_EDGE);

		bool atLeftEdge  = (aliensDirection == alienDirection::LEFT) &&
			               (leftAlien <= SCREEN_LEFT_EDGE);

		if (atRightEdge || atLeftEdge) {
			// Move down first
			for (auto& alien : aliens) {
				alien.move(ALIEN_VERTICAL_STEP);
			}

			// Switch directions
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
			}
		}

		// Increases speed as aliens die
		float speedScalar = aliens.size() / 55.f;

		// Prevents speed from dropping below 30% of base speed
		if (speedScalar < 0.3f) {
			speedScalar = 0.3f;
		}
		alienMoveTimer = ALIEN_SPEED * speedScalar;
	}
}

void Game::initBarriers() {
	barriers.reserve(NUM_OF_BARRIERS);

	for (int i = 0; i < NUM_OF_BARRIERS; i++) {
		float barrierPos = BARRIER_START_X_POS + i * BARRIER_SPACING;
		barriers.emplace_back(resourceManager, sf::Vector2f{barrierPos, BARRIER_Y});
	}
}

void Game::updateUFOTimer(float deltaTime) {

}

void Game::spawnUFO() {
	ufo = Alien(resourceManager, AlienType::UFO, {50.f, 150.f});
}

void Game::checkBulletAlienCollision() {
	std::erase_if(bullets, [this](const Bullet& bullet) {
		if ((bullet.getOwner() != BulletOwner::PLAYER) || bullet.isExploding()) {
			return false;
		}

		for (auto& alien : aliens) {
			if (!alien.isDying() && alien.collidesWith(bullet)) {
				score += alien.getPointValue();
				ui.setP1Score(score);
				alien.kill();
				alienExplosionSound->play();
				return true;
			}
		}

		return false;
	});
}

void Game::checkBulletPlayerCollision() {
	if (player.isDying()) {
		return;
	}

	std::erase_if(bullets, [this](const Bullet& bullet) {
		if (bullet.getOwner() != BulletOwner::ALIEN) {
			return false;
		}

		if (player.collidesWith(bullet)) {
			player.kill();
			playerDeathSound->play();
			return true;
		}

		return false;
	});
}

void Game::checkBulletBarrierCollision() {
	for (auto& bullet : bullets) {
		if (bullet.isExploding()) {
			continue;
		}

		for (auto& barrier : barriers) {
			if (barrier.isDestroyed()) {
				continue;
			}

			const sf::Sprite& bulletSprite = bullet.getCurrentSprite();
			if (barrier.collidesWith(bulletSprite)) {
				// Algins the sprite states to carve out the barrier from the center of the bullet instead of the edge
				auto barrierBounds = barrier.getSprite().getGlobalBounds();
				auto bulletBounds = bulletSprite.getGlobalBounds();
				auto overlap = barrierBounds.findIntersection(bulletBounds);

				// Center of overlap in world coordinates
				sf::Vector2f impactPos;
				impactPos.x = overlap->position.x + overlap->size.x / 2.f;
				impactPos.y = (bullet.getOwner() == BulletOwner::PLAYER) ? bulletBounds.position.y :
				                                                           bulletBounds.position.y + bulletBounds.size.y;

				const std::string explosionKey = (bullet.getOwner() == BulletOwner::PLAYER) ? "player_bullet_explosion" : "alien_bullet_explosion";
				sf::Sprite explosion = resourceManager.createSprite(explosionKey);
				barrier.takeDamage(impactPos, explosion, resourceManager.getEffectsSpriteSheetImg());
				bullet.explode();
				break;
			}
		}
	}
}

void Game::updateAlienShots(float deltaTime) {
	if (aliens.empty()) {
		return;
	}

	alienShootTimer -= deltaTime;
	if (alienShootTimer > 0.f) {
		return;
	}

	// Aliens are stored from bottom first and relies on this
	std::vector<std::size_t> bottomAliensPerColumn;
	std::vector<int> columnsSeen;          // Avoids copying another alien in same column
	bottomAliensPerColumn.reserve(11);  // Only 11 bottom level aliens are possible
	columnsSeen.reserve(11);            // Only 11 columns exists

	for (std::size_t i = 0; i < aliens.size(); i++) {
		if (!aliens[i].isDying()) {
			// Finds the column number of the current alien
			int columnNum = static_cast<int>(aliens[i].getPosition().x / ALIEN_COLUMN_SPACING);

			// Check if an alien has already been seen on this column
			if (std::find(columnsSeen.begin(), columnsSeen.end(), columnNum) == columnsSeen.end()) {
				columnsSeen.push_back(columnNum);
				bottomAliensPerColumn.push_back(i);
			}
		}
	}

	if (bottomAliensPerColumn.empty()) {
		return;
	}

	// Random number generator
	static std::random_device rd;
	static std::mt19937 gen(rd());

	// Equally distribute chances among all bottom aliens
	std::uniform_int_distribution<std::size_t> distribute(0, bottomAliensPerColumn.size() - 1);

	// Picking the alien to shoot
	const Alien& shooter = aliens[bottomAliensPerColumn[distribute(gen)]];

	// Starting position for the bullet
	sf::Vector2f pos = shooter.getPosition();
	pos.x += 20.f;   // Center bullet with alien
	pos.y += 40.f;   // Move bullet down to start at bottom of alien

	std::uniform_int_distribution<int> typeDistribution(0, 2);
	AlienBulletType bulletType = static_cast<AlienBulletType>(typeDistribution(gen));
	bullets.emplace_back(resourceManager, pos, BulletOwner::ALIEN, bulletType);

	alienShootTimer = alienShootInterval;
}

std::string Game::convertScore(int score) {
	std::string strScore = std::to_string(score);

	while (strScore.length() < 4) {
		strScore = "0" + strScore;
	}

	return strScore;
}

void Game::resetGame() {
	bullets.clear();
	aliens.clear();
	barriers.clear();
	initAliens();
	initBarriers();
	aliensDirection = alienDirection::RIGHT;
	nextAlienToMove = 0;
	alienMoveTimer = ALIEN_SPEED;
	player.respawn(PLAYER_START_POS);
}

bool Game::aliensReachedGround() const {
	for (const auto& alien : aliens) {
		if (alien.getPosition().y >= ALIEN_GROUND_LIMIT) {
			return true;
		}
	}

	return false;
}
