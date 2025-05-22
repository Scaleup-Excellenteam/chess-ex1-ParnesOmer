# Chess Game Implementation

This project is a C++ implementation of a chess engine focused on object-oriented design, move validation, and move evaluation for simple AI play. The codebase is organized into modular classes to separate responsibilities and enable clean, maintainable logic for chess gameplay.

## Main Components

### `Board`
- **Responsibilities:**
  Manages the chessboard state, pieces' positions, turn management, move legality, move application/undo, and king threats.
- **Highlights:**
  - 2D vector of `Piece*` for board representation.
  - Tracks king positions and threats (`KingEnemies`).
  - Validates moves, applies/undoes moves, and handles pawn promotion.
  - Provides interface to get/set pieces and turn info.
  - Offers a method to recommend the top three best moves via integration with the evaluation engine.

### `EvaluateAllMoves`
- **Responsibilities:**
  Evaluates all possible legal moves for the current player, scores them, and suggests the best options.
- **Highlights:**
  - Uses a simple minimax-like recursion (with user-defined depth).
  - Simulates moves by updating a temporary `Board` instance (no deep copy per recursion).
  - Returns move recommendations for AI or hint features.

### `Move`
- **Responsibilities:**
  Represents a single chess move, including start/end coordinates, score, and move status.
- **Highlights:**
  - Stores move evaluation score for sorting/ranking.
  - Overloads `<` operator for easy use in priority queues.
  - Supports easy printing and access to move details.

### `MyPriorityQueue`
- **Responsibilities:**
  Custom priority queue template for managing moves (or any pointer type) sorted by priority (score).
- **Highlights:**
  - Internally uses a sorted `std::list`.
  - Ensures moves are always sorted for efficient selection of best moves.
  - Throws exceptions on invalid usage (e.g., pulling from an empty queue).

## Design Principles

- **Object-Oriented:** Each game concept (board, move, evaluation, queue) is encapsulated in its own class.
- **Efficiency:**
  The evaluation engine avoids excessive copying by updating a temporary board in-place during move searches.
- **Extensibility:**
  The clean separation of logic allows for future enhancements (GUI, network play, advanced AI, etc.).

## How to Read the Code

- **Start with `Board.h`:**
  Understand how the game state and rules are enforced.
- **Move to `EvaluateAllMoves.h`:**
  See how AI and move scoring is performed.
- **Refer to `Move.h` and `MyPriorityQueue.h`:**
  Learn how moves are represented and managed for selection.

## Usage

- Integrate with a UI or CLI for playing chess, move validation, and AI hints.
- Extend the evaluation logic for more advanced AI by modifying `EvaluateAllMoves`.

---

**Note:**
This implementation assumes `Piece` and `KingEnemies` classes exist and implement required chess logic for each piece and threat tracking.
