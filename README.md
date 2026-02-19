# Space Invaders

A Space Invaders clone built from scratch in C++ using SFML 3. Recreates the arcade experience with classic alien formations, animated sprites, typewriter menu effects, and a retro HUD.

---

## Features

- Classic 55-alien formation (5 rows × 11 columns) with three alien types
- Animated alien sprites that cycle between two frames
- Arcade-style typewriter text effect on menus
- Coin menu and score table screens mimicking original arcade attract mode
- HUD displaying Player 1 score, high score, and remaining lives
- Portrait orientation (768×1024) matching the original arcade cabinet aspect ratio

---

## Screenshots
<img width="300" height="1018" alt="player_menu" src="https://github.com/user-attachments/assets/9b9160c1-271a-4d17-9cf0-db64565891cb" />
<img width="300" height="1019" alt="score_table" src="https://github.com/user-attachments/assets/05b5da61-5525-45af-8b80-374d912191b5" />


---

## Getting Started

### Prerequisites

- CMake 4.0 or newer
- A C++20-compatible compiler (GCC, Clang, or MSVC)
- Internet connection (CMake fetches SFML 3.0.1 automatically)

### Building

```bash
# Clone the repository
git clone https://github.com/Bgarcia117/Space-Invaders.git
cd Space-Invaders

# Configure and build
cmake -B build
cmake --build build
```

The compiled executable and all required assets are placed in `build/bin/`.

### Running

```bash
./build/bin/SpaceInvaders
```

---

## Controls

| Action         | Keys                        |
|----------------|-----------------------------|
| Move left      | `A` or `←`                 |
| Move right     | `D` or `→`                 |
| Navigate menu  | `W` / `S` or `↑` / `↓`    |
| Confirm        | `Enter`                     |

---

## Gameplay

The game opens with a coin-insert attract screen and a score table showing the point value of each alien type before entering the main game.

| Alien   | Points |
|---------|--------|
| UFO     | 50     |
| Squid   | 30     |
| Octopus | 30     |
| Crab    | 20     |

Aliens move in the classic step-right / drop-down / step-left pattern. Collision detection, bullet firing, barriers, and a proper game-over screen are still being implemented (see [Planned Features](#planned-features)).

---

## Project Structure

```
Space-Invaders/
├── assets/
│   ├── fonts/          # Arcade-style TTF font
│   └── sprites/        # Sprite sheets (aliens, player, bullets, effects)
├── include/
│   ├── core/           # Game loop, base GameObject, resource key constants
│   ├── game_objects/   # Alien, Player, Bullet headers
│   ├── managers/       # ResourceManager header
│   └── UI/             # UI / HUD header
└── src/
    ├── core/           # game.cpp, game_object.cpp
    ├── game_objects/   # alien.cpp, player.cpp, bullet.cpp
    ├── managers/       # resource_manager.cpp
    └── UI/             # ui.cpp
```

---

## Built With

- [SFML 3.0.1](https://www.sfml-dev.org/) — Graphics, windowing, and input
- [CMake](https://cmake.org/) with FetchContent — Build system and automatic dependency management
- C++20

---

## Credits

- All sprites and source code created from scratch.
- Font: [Space Invaders Full Version](https://fontstruct.com/fontstructions/download/2438283) by chriswal1200 on FontStruct, licensed under the [SIL Open Font License](https://openfontlicense.org/)

---

## Implemented

- [x] Main game loop with fixed 60 FPS
- [x] Coin menu and score table attract screens
- [x] Typewriter text effect on menus
- [x] 55-alien formation (5 rows × 11 columns)
- [x] Alien sprite animation (two-frame cycle)
- [x] Alien step movement (right / drop / left pattern)
- [x] Player movement (left / right)
- [x] HUD (scores and lives display)
- [x] Resource manager for textures and fonts

---

## Planned Features

- [ ] Player shooting
- [ ] Collision detection (bullets ↔ aliens, aliens ↔ player)
- [ ] Destructible barriers / shields
- [ ] UFO random flyover
- [ ] Game over and restart flow
- [ ] Two-player alternating mode
- [ ] Sound effects and music
- [ ] Difficulty scaling as aliens are eliminated
