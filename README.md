# Chess Game Implementation in C++

This project is a console-based chess game implemented in C++ that allows two players to play against each other. The game follows the standard rules of chess and includes features such as move validation, check detection, and a simple command-line interface for interacting with the game.

## Project Structure

1. **Game Initialization**
    - Setting up the board
    - Placing pieces in their initial positions
    - Initializing game state variables

2. **Game Loop**
    - Displaying the board
    - Accepting and processing player input
    - Validating moves
    - Updating the game state
    - Checking for game end conditions (checkmate, stalemate, draw)

3. **Move Validation**
    - Ensuring moves follow the rules for each piece
    - Detecting and preventing illegal moves (e.g., moving into check)
    - Handling special moves (castling, en passant, pawn promotion)

4. **Check Detection**
    - Identifying checks, checkmates, and stalemates
    - Updating the game state based on checks

5. **User Interface**
    - Displaying the board and game state
    - Accepting user input for moves
    - Providing feedback on move validity and game state

## Game Initialization

<img width="1000" src="assets/Intial Screen.PNG" alt="Intail Screen"/>


### Setting Up the Board

The board is represented as an 8x8 grid with each cell containing information about the piece occupying it, if any.

### Placing Pieces in Initial Positions

The pieces are placed in their standard starting positions at the beginning of the game.

### Initializing Game State Variables

Variables to keep track of the current player, move history, and game state are initialized.

## Game Loop

### Displaying the Board

The board is displayed in the console with pieces represented by their standard chess notation (e.g., 'K' for king, 'Q' for queen).

<img width="1000" src="assets/Intial Board.PNG" alt="Intail Screen"/>

### Accepting and Processing Player Input

Players input their moves in a standard format (e.g., "e2 e4" to move a piece from e2 to e4).

### Validating Moves

The game checks whether the moves are valid according to the rules of chess.

### Updating the Game State

The game state is updated based on the valid moves made by the players.

### Checking for Game End Conditions

The game continuously checks for checkmate, stalemate, and draw conditions to determine if the game should end.

## Move Validation

### Ensuring Moves Follow the Rules

Each type of piece has its own movement rules, which are enforced by the game.

<img width="1000" src="assets/Possible Moves.PNG" alt="Intail Screen"/>

### Detecting and Preventing Illegal Moves

The game ensures that no illegal moves are made, such as moving a piece into a position that would leave the player's king in check.

### Handling Special Moves

Special moves such as castling, en passant, and pawn promotion are implemented and validated.

## Check Detection

### Identifying Checks, Checkmates, and Stalemates

The game identifies when a king is in check and determines if the check leads to checkmate or stalemate.

<img width="1000" src="assets/King Danger.PNG" alt="Intail Screen"/>

### Updating the Game State

The game state is updated based on the detection of checks and their outcomes.

## User Interface

### Displaying the Board and Game State

The board and current game state are displayed in the console.

### Accepting User Input

Users input their moves via the console.

### Providing Feedback

The game provides feedback on the validity of moves and the current state of the game (e.g., check, checkmate).

## References
- Chess rules and piece movements were referenced from [Wikipedia](https://en.wikipedia.org/wiki/Rules_of_chess).
- [Standard Chess Rules](https://www.chess.com/learn-how-to-play-chess)
- [Algebraic Notation](https://en.wikipedia.org/wiki/Algebraic_notation_(chess))
- [Chess Programming Wiki](https://www.chessprogramming.org/Main_Page)
