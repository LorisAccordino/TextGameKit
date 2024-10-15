# TextGameKit - C Library for Text-Based Games

TextGameKit is a C library designed to make the development of text-based games easier and faster. It provides essential utilities for managing input/output, rendering in a simple text-based console interface, and handling networking (TCP/IP) for multiplayer LAN games. The library is highly customizable and works well with small to medium-sized console games that require networking capabilities.

## Features

- **Networking**: Built-in support for TCP/IP communication, making it easy to implement multiplayer functionality over a LAN.
- **Input/Output Management**: Efficient handling of user input and output in a console-based game interface.
- **Rendering**: Simple ASCII rendering functions for displaying text, tables, grids, and other common UI elements in a game.
- **Utilities**: Pre-built algorithms and helper functions to handle common game development tasks, like randomization, timing, and more.

## Installation

To use the library in your project:

1. Download or clone the `TextGameKit` repository.
2. Include the `textgamekit.h` header file in your project.
3. Link your project with the `textgamekit.c` source file.
4. Ensure that you have a C compiler set up (such as GCC or CodeBlocks) to compile your project.

### Example Setup

Here is an example of how to set up the library in your project:

1. Clone the repository into your project folder:
   ```bash
   git clone https://github.com/yourusername/TextGameKit.git

2. Include the `textgamekit.h` header in your project files:
   ```C
   #include "TextGameKit/textgamekit.h"

3. In your project's build system, ensure that the `textgamekit.c` file is included for compilation.

is included for compilation.

4. Link the compiled `textgamekit.o` (or `textgamekit.c`) in your project to access the functions.

## License
This library is open-source and released under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contributing
Feel free to open issues or pull requests if you'd like to contribute to improving the library. If you have any questions or need help, don't hesitate to reach out.

## Example Projects
The library has been used in several projects, including:

- [Battleship Game](https://github.com/LorisAccordino/Battleship-Game): A text-based game that uses `TextGameKit` for networking and rendering.
- [Sudoku Game](https://github.com/LorisAccordino/Sudoku-C-Game): A console-based Sudoku game leveraging the library for managing user input and game flow.