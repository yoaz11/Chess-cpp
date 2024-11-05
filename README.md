# Chess Game

## Overview

This project is a chess game implementation in C++, featuring AI move suggestion capabilities. The system allows users to play chess, while the AI suggests optimal moves based on the current board state.

## Features

- Full implementation of all chess pieces with their specific movement rules.
- Board management, including move validation, check, and checkmate detection.
- AI-powered move suggestion using a priority queue and depth analysis.
- Custom exception handling for invalid moves and out-of-bounds errors.
- User interaction for inputting moves and displaying the game state.

## Project Structure

The project is organized into the following directories and files:


include/
 Bishop.h,
 Board.h,
 Chess.h,
 CustomExceptions.h,
 King.h,
 Knight.h,
 Move.h,
 MoveSuggester.h,
 Pawn.h,
 Piece.h,
 PriorityQueue.h,
 Queen.h,
 Rook.h,
 TopMoves.h,

src/
 Bishop.cpp,
 Board.cpp,
 Chess.cpp,
 King.cpp,
 Knight.cpp,
 main.cpp,
 MoveSuggester.cpp,
 Pawn.cpp,
 Queen.cpp,
 Rook.cpp,
 TopMoves.cpp,
 .gitignore,
README.md


## Getting Started

### Prerequisites

- A C++ compiler supporting C++11 or higher.
- CMake for building the project.

### Building the Project

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-directory>
Create a build directory and navigate into it:

bash
mkdir build
cd build
Run CMake to generate the build files:

bash
cmake ..
Build the project:

bash
make
Running the Game
After building the project, you can run the chess game executable:

### Run the Project
bash
./main
Gameplay
The game will display the current board state and prompt the user for input.
Enter moves in the format srcRowSrcColDestRowDestCol (e.g., e2e4 for moving a piece from e2 to e4).
Type exit to quit the game.
Example Input
mathematica

Player 1 (White - Capital letters) >> e2e4
Player 2 (Black - Small letters)   >> e7e5
Customizing the Game


Contributing
Contributions are welcome! Please fork the repository and submit pull requests for any enhancements or bug fixes.