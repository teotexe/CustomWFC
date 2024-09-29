# WFC Path Generator with Custom Rules

This project is a Wave Function Collapse (WFC) path generator, designed to work with custom tile-based rules. The generator uses the SFML library to render tile maps based on the provided rules. The rules dictate how different tile types can be placed next to each other.

## Setup and Build

To compile the project, ensure you have SFML installed and the appropriate paths set up. Run the following commands to build and compile the project:

```bash
g++ -c WFC.cpp -I<path_to_your_SFML_include>
g++ WFC.o -o WFC -L<path_to_your_SFML_lib> -lsfml-graphics -lsfml-window -lsfml-system
