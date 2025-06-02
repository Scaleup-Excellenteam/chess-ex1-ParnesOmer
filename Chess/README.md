# Chess Game Parallel Engine

This project is an advanced C++ implementation of a chess engine, combining **object-oriented design**, **modular architecture**, and **parallel move evaluation** for high performance and extensibility.

---

## Main Components

### `Board`
- **Responsibilities:**
  - Manages the chessboard state: all pieces, their types, and positions.
  - Controls turn management, move legality, move application and undo, pawn promotion, and threat detection.
  - Tracks king positions and threats (via `KingEnemies`).
  - Provides the interface to query and modify pieces and turn info.
  - Integrates with the evaluation engine for top-move recommendations.
- **Highlights:**
  - Uses a 2D vector of `Piece*` for board representation.
  - Efficiently applies and undoes moves, maintaining full game state.
  - Validates complex chess rules (including check, checkmate, castling, etc.).

### `Piece` and `KingEnemies`
- **`Piece`:**
  - Abstract base class for all chess pieces.
  - Each derived piece (Pawn, Knight, Bishop, Rook, Queen, King) implements its own movement logic and value.
- **`KingEnemies`:**
  - Manages threat tracking to the kings for efficient legality checking (e.g., check, checkmate, stalemate).
  - Used internally by `Board` for quick threat evaluation.

### `Move`
- **Responsibilities:**
  - Represents a single chess move: start and end coordinates, move status, and evaluation score.
  - Overloads `<` for sorting by move quality (priority).
  - Provides easy access to move details and convenient printing.

### `MyPriorityQueue` & `ThreadSafePriorityQueue`
- **`MyPriorityQueue`:**
  - Custom priority queue template for managing moves (or any pointer type) sorted by priority (score).
  - Internally uses a sorted `std::list` for fast insertion and retrieval.
  - Throws exceptions on invalid usage (e.g., pulling from an empty queue).
  - Now uses smart pointers for robust memory management.
- **`ThreadSafePriorityQueue`:**
  - Thread-safe wrapper around `MyPriorityQueue`, using `std::mutex` for safe concurrent access.
  - Used for parallel move evaluation when running with multiple threads.

### `ThreadsPool`
- **Responsibilities:**
  - Simple thread pool for running tasks in parallel.
  - Public API is thread-safe; manages worker threads, task queue, and graceful shutdown.
  - Used to parallelize move evaluation in the engine.
  - Implements stop flag and safe joining of threads (bonus).
  - Easily configurable for different thread counts.

### `EvaluateAllMoves`
- **Responsibilities:**
  - Evaluates all possible legal moves for the current player, scores them, and suggests the best options.
  - Uses a minimax-like recursion (with user-defined depth) to consider both player's best responses.
  - Can run move evaluations in parallel using the thread pool and thread-safe queue.
  - Returns move recommendations for AI or hint features.

### `Chess`
- **Responsibilities:**
  - Main interface for playing the game: manages game flow, user interaction, and board display.
  - Allows for both automatic (AI vs AI) and manual (player vs player/computer) play modes.
  - Handles user input, move validation, and displays the board and recommended moves.
  - Provides tools for benchmarking (timing Auto-play with various thread counts).

---

## Design Principles

- **Object-Oriented:**
  Each game concept (board, piece, move, evaluation, queue) is encapsulated in its own class, following SOLID principles.
- **Efficiency:**
  The evaluation engine avoids excessive copying by updating a temporary board in-place during move searches, and now supports parallel computation.
- **Extensibility:**
  The clean separation of logic allows for future enhancements (adding a GUI, network play, or advanced AI).
- **Modular and Readable:**
  Each component is in its own file/class, with clear responsibilities and documentation.
- **Thread-Safety:**
  All data structures used in parallel execution are protected for safe concurrent access.

---

## How to Read and Extend the Code

- **Start with `Board.h`:**
  Understand how the game state and rules are enforced.
- **Move to `Piece.h` and its derivatives:**
  See how piece movements and values are implemented.
- **Check `EvaluateAllMoves.h`:**
  See how AI and move scoring is performed.
- **Refer to `Move.h` and `MyPriorityQueue.h`:**
  Learn how moves are represented and prioritized.
- **Look at `ThreadsPool.h` and `ThreadSafePriorityQueue.h`:**
  Understand parallelization and thread-safety.
- **`Chess.h`:**
  Main game loop, user interface, and integration of all components.

---

## Usage

- **Build** with CMake (recommended):
  ```
  mkdir build
  cd build
  cmake ..
  make
  ```
- **Run:**
  ```
  ./chess
  ```
- **Select Mode:**
  - **Automatic:** Let the AI play against itself, measuring run time with different thread counts (for benchmarking).
  - **Manual:** Enter moves as a player; get move validation and AI hints.
- **Extend:**
  Modify `EvaluateAllMoves` for advanced AI, or `Chess` for different UI or networking.

---

## Benchmark Results

**Measured at depth 3:**

| Threads | Time (sec)  |
|---------|-------------|
| 1       | 1.9578      |
| 2       | 1.07567     |
| 4       | 0.716098    |
| 8       | 0.513724    |

*Parallel move evaluation achieves significant speedup as thread count increases.*

---

## Extensibility

- **Add a GUI:**
  The current CLI can be replaced or extended with a graphical interface.
- **Advanced AI:**
  Plug in more sophisticated evaluation or search algorithms.
- **Network Play:**
  Add online multiplayer support by building on the clean, modular engine.

---

## Notes

- The implementation assumes `Piece` and `KingEnemies` classes exist and implement required chess logic for each piece and threat tracking.
- All core logic is easily testable and maintainable due to strong modularity.

---

For any questions or suggestions, please refer to the code comments or open an issue.
