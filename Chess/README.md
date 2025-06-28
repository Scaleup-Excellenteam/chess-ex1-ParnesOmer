# Chess Engine Project

## Overview

This project is a C++ chess engine and command-line game featuring:

- **Full chess rules** (including castling, en passant, pawn promotion, check, and checkmate)
- **Strong AI move recommendations** using a multithreaded, alpha-beta pruned minimax search
- **Cross-platform command-line interface** with ASCII-art board
- **Robust architecture** with clear separation between engine logic, AI, and user interface

---

## Project Structure

- **Board**  
  The core engine, representing the chessboard, game state, and move validation logic.
- **Piece Hierarchy**  
  Abstract base class (`Piece`) and derived classes (`Pawn`, `Knight`, etc.) encapsulate piece-specific rules.
- **KingEnemies**  
  Tracks threats to each king, detects checks and maintains king safety.
- **Move & MyPriorityQueue**  
  Represents chess moves and provides a priority queue for ranking moves by evaluation.
- **EvaluateAllMoves**  
  **The AI brain.** Evaluates all legal moves using parallelized minimax with alpha-beta pruning to recommend the best moves.
- **ThreadsPool**  
  Generic thread pool for efficient parallel evaluation of moves.
- **Constants & Exceptions**  
  Centralized constants and robust error handling.
- **Chess (UI)**  
  Handles user interface, board display, and user input.
- **main.cpp**  
  Entry point.

---

## Core Flow

1. **Startup:**  
   User selects search depth and play mode (Human vs. AI or Human vs. Human).
2. **Game Loop:**
  - User inputs a move (validated and executed).
  - If AI is playing, it computes and plays the best move.
  - After each move, the board is updated and top move recommendations are displayed.
3. **AI Engine:**  
   For each possible legal move, the AI:
  - Simulates the move on a separate board copy.
  - Recursively evaluates the resulting positions to a user-specified depth (plies), using minimax with alpha-beta pruning.
  - Evaluates and scores each position (material, position, king safety, mobility, etc.).
  - Runs evaluations in parallel using a thread pool for speed.
  - Ranks moves and recommends the best options.

---

## Key Components

### Board

- Manages the full game state, move validation (including special moves and checks), and piece placement.
- Provides methods to validate, execute, and undo moves, as well as to query legal moves and game status.

### Piece Hierarchy

- Abstract `Piece` base class and derived classes for every chess piece.
- Each piece implements its specific movement and threat-checking logic, enabling polymorphic behavior.

### KingEnemies

- Tracks all threats on each king.
- Efficiently updates after every move and determines if the king is in check.

### Move & MyPriorityQueue

- `Move` objects store all relevant information for a single move, including source, destination, type, and evaluation score.
- `MyPriorityQueue` maintains a sorted list of top moves for fast retrieval and recommendation.

---

### **EvaluateAllMoves – The AI Brain** (Key Component)

This class computes the best moves using an advanced, efficient, and scalable search:

- **Move Generation:**  
  Generates all legal moves for the current player.
- **Minimax + Alpha-Beta Pruning:**  
  Recursively evaluates each move using a minimax algorithm, pruning unpromising branches to improve speed.
- **Position Evaluation:**  
  Scores each resulting position based on:
  - Material balance (using chess piece values)
  - Positional bonuses (center control, pawn structure, king safety, piece activity)
  - King threats (checks, checkmate detection)
  - Mobility (number of available moves)
- **Parallelization:**  
  Distributes move evaluations across multiple threads, dramatically speeding up analysis.
- **Early Exit:**  
  If a forced mate or overwhelmingly strong move is found, the search may exit early for efficiency.
- **Move Ordering:**  
  Prioritizes promising moves (captures, checks, centralization) to maximize pruning effectiveness.

#### Example: How AI Suggests a Move

1. **Generate all valid moves** for the current player.
2. **Evaluate each move in parallel threads** up to the chosen depth.
3. **For each move:**
  - Simulate the move on a temporary board.
  - Recursively evaluate all possible responses.
  - Assign a score to each move based on the resulting position.
4. **Rank moves and recommend the top choices** to the player.

---

### ThreadsPool

- Implements a thread pool to manage concurrent execution of move evaluations.
- Ensures thread-safe task management and efficient CPU usage.

---

### User Interface (Chess & main.cpp)

- Renders the board in the terminal (supports Windows and Unix).
- Handles all user input and output, including move entry, validation, and display of recommended moves.
- Supports both human vs. AI and two-player modes.

---

## Error Handling & Constants

- All error codes and magic numbers are managed in the `Constants` namespace.
- Custom exceptions provide clear, informative errors for invalid moves, out-of-range accesses, and queue operations.

---

## Example Usage

```bash
$ ./chess
Enter search depth (how many moves ahead to calculate):
3
Select game mode: (1) Against the computer  (2) Two players:
1
Recommended moves:
    e2e4
    d2d4
    g1f3
Player 1 (White - Capital letters) >> e2e4
...
Checkmate!!! Black Won.
Exiting
```

---

## Summary

This project demonstrates a robust, efficient, and user-friendly chess engine, built with clean C++ OOP principles and modern AI techniques.  
The **EvaluateAllMoves** class, with its parallelized, alpha-beta pruned minimax search, is the heart of the engine, enabling strong AI play and fast move recommendations.

---

## Authors

- Omer Parnes
