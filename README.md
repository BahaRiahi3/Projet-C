# Memory Matching Game

## Overview
This program is a simple memory-matching game implemented in C. The goal is to match all pairs of hidden cards by selecting their coordinates on a game board. Players can choose the difficulty level, and their scores (number of attempts and time taken) are saved for future reference.

---

## Features
- **Dynamic Difficulty Levels**:
  - Easy: 2x2 board
  - Medium: 4x4 board
  - Hard: 6x6 board
- **Randomized Card Placement**: Ensures unique gameplay for every session.
- **Persistent Scores**: Saves player scores in a file (`scores.txt`).
- **Interactive Feedback**: Provides feedback on matches, invalid inputs, and overall progress.
- **Clear Screen**: Keeps the terminal display clean and organized.

---

## How to Play
1. **Choose Difficulty**:
   - Select the board size by entering the corresponding number:
     - `1` for Easy (2x2)
     - `2` for Medium (4x4)
     - `3` for Hard (6x6)
2. **Game Setup**:
   - A board is displayed with all cards hidden (`*`).
   - Your goal is to reveal matching pairs by selecting their coordinates.
3. **Making a Move**:
   - Enter the coordinates of the first card (row and column).
   - Enter the coordinates of the second card.
   - If the cards match, they remain revealed. Otherwise, they are hidden again.
4. **Win Condition**:
   - The game ends when all pairs are found.
5. **Score Recording**:
   - Enter your name to save your score.
   - View a list of previous scores.

---

## Files
- **`main.c`**: Contains the source code for the game.
- **`scores.txt`**: Stores player scores in the format:
  ```
  PlayerName Attempts Time
  ```

---

## Compilation and Execution
1. **Compile the Code**:
   ```bash
   gcc main.c -o memory_game
   ```
2. **Run the Game**:
   ```bash
   ./memory_game
   ```

---

## Dependencies
- C compiler (e.g., GCC)
- Standard C libraries: `stdio.h`, `stdlib.h`, `time.h`, `string.h`

---

## Known Limitations
- Limited input validation for coordinates.
- Requires `scores.txt` to exist in the same directory for saving scores.
- Basic ASCII-only output.
