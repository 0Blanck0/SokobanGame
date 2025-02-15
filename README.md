# SokobanGame

## Description
SokobanGame is a C-language implementation of the famous Sokoban puzzle game.   
The player must move crates to designated spots while following specific movement rules.   
This project also includes a level editor for creating and customizing challenges.   
This project is my first game so I got help from the OpenClassRoom tutorial (See Resources section for more information).

## Features
- Complete game with multiple predefined levels
- Saved score system
- Built-in level editor
- Simple and intuitive console-based interface

## Installation
### Prerequisites
- A C compiler (GCC, Clang, MSVC, etc.)
- A compatible operating system (Windows, Linux, macOS)

### Compilation
Clone the repository and compile the project using the following command:

```sh
 git clone https://github.com/0Blanck0/SokobanGame.git
 cd SokobanGame
 gcc -o sokoban main.c sokoban.c -Wall -Wextra
```

### Execution
Run the game with the following command:

```sh
 ./sokoban
```

## Usage
- **Arrow keys**: Move the player
- **R**: Restart the game (Warning: a known bug may cause a crash)
- **Level Editor**: Create and modify custom levels

## Known Bugs
- The **R** (Restart) key may cause the game to crash

## Author

[Alexandre ELISABETH](https://github.com/0Blanck0)

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Resources
- [OpenClassRoom](https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c)
- [Wikipedia - Sokoban](https://en.wikipedia.org/wiki/Sokoban)


