# SokobanGame

## Description
SokobanGame is a C-language implementation of the famous Sokoban puzzle game. The player must move crates to designated spots while following specific movement rules. This project also includes a level editor for creating and customizing challenges.

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

## Contributing
Contributions are welcome! To propose improvements or report bugs:
1. Fork the repository
2. Create a branch (e.g., "feature/improvement")
3. Make your changes
4. Submit a pull request

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Resources
- [Wikipedia - Sokoban](https://en.wikipedia.org/wiki/Sokoban)


