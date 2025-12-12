#Wordle_projectt

Description of the project: This project is a Wordle game and solver implemented in C. It reads a dictionary of valid 5‑letter words, selects a random secret word, and lets a human player or an automated solver guess it in up to six attempts. The solver uses algorithmic filtering based on feedback (green / yellow / gray letters) to eliminate impossible words and converge to the correct answer in as few guesses as possible.

Clone the Github repository: https://github.com/aissaouiyoussra8-eng/wordle-projectt.git

Example 1: Human mode
=== WORDLE (Human Mode) ===
Guess the 5-letter word in 6 attempts.

Attempt 1/6 - enter a 5-letter word: table
   [_][Y][Y][_][_]

Attempt 2/6 - enter a 5-letter word: trace
   [G][G][Y][_][G]

Attempt 3/6 - enter a 5-letter word: track
   [G][G][G][G][G]

Congratulations! You found the word 'track' in 3 attempts.


Example 2: Solver mode


=== WORDLE (Solver Mode) ===
Target word chosen randomly from dictionary.

AI guess 1: arise
   [_][Y][_][Y][_]
Remaining candidates: 120

AI guess 2: stone
   [G][G][_][G][_]
Remaining candidates: 5

AI guess 3: stomp
   [G][G][G][G][G]

AI found the word 'stomp' in 3 attempts.
