# Space Invaders

A Space Invaders clone built from scratch in C++ using SFML 3. Recreates the arcade experience with classic alien formations, animated sprites, typewriter menu effects, and a retro HUD.

---

## Features

- Classic 55-alien formation (5 rows × 11 columns) with three alien types
- Animated alien sprites that cycle between two frames
- UFO flyovers with dynamic point values and death animation
- Destructible barriers with pixel-level damage
- Player and alien shooting with bullet animation
- Arcade-style typewriter text effect on menus
- Coin menu, score table, and "PLAY PLAYER<1>" attract screens
- HUD displaying Player 1 score, high score, credits, and remaining lives
- Persistent high score saved between sessions
- Sound effects for shots, explosions, UFO flyover, and death
- Portrait orientation (768×1024) that matches the original arcade cabinet aspect ratio

---

## Screenshots
<img width="450" height="1018" alt="player_menu" src="https://github.com/user-attachments/assets/9b9160c1-271a-4d17-9cf0-db64565891cb" />
<img width="450" height="1019" alt="score_table" src="https://github.com/user-attachments/assets/05b5da61-5525-45af-8b80-374d912191b5" />


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
| Shoot          | `Space`                     |
| Navigate menu  | `W` / `S` or `↑` / `↓`    |
| Advance screen | `Enter`                     |
| Quit game      | `Esc`                       |

---

## Gameplay

The game opens with a coin-insert attract screen and a score table showing the point value of each alien type before entering the main game.

| Alien   | Points |
|---------|--------|
| UFO     | ???    |
| Squid   | 30     |
| Octopus | 30     |
| Crab    | 20     |

Aliens move in the classic step-right / drop-down / step-left pattern, speeding up as their numbers thin out. Destroy the mystery UFO for a variable point bonus — see if you can figure out the pattern.

---

## Project Structure

```
Space-Invaders/
├── assets/
│   ├── fonts/          # Arcade-style TTF font
│   ├── sprites/        # Sprite sheets (aliens, player, bullets, effects)
│   └── sounds/         # WAV files (shots, explosions, UFO, death)
├── include/
│   ├── core/           # Game loop, base GameObject, resource key constants
│   ├── game_objects/   # Alien, Barrier, Bullet, Player headers
│   ├── managers/       # ResourceManager header
│   └── UI/             # UI / HUD header
└── src/
    ├── core/           # game.cpp, game_object.cpp
    ├── game_objects/   # alien.cpp, barrier.cpp, bullet.cpp, player.cpp
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

## Future Work

- Two-player alternating mode
- Additional difficulty scaling and tuning
