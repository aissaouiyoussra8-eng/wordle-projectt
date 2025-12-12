#Wordle_projectt
The solver starts from the full dictionary of valid 5‑letter words loaded from words.txt into memory.​ At each step, it considers a set of candidate words still compatible with all previous feedback.
A simple baseline strategy is:
 For the first guess, pick a word with common letters (e.g. many different vowels and frequent consonants) to maximize information.
 For subsequent guesses, always pick a word from the current candidate list (the list of words that have not been eliminated yet).
A more advanced strategy can score each candidate by how many other candidates it would eliminate on average if chosen, then pick the one with the best expected reduction.

Using feedback to eliminate possibilities. After each guess, the game returns feedback for each position:
  Green: same letter and same position as target.
  Yellow: letter appears in target but in a different position.
  Gray: letter does not appear in target (or appears fewer times than in the guess).
  
For every word in the candidate list, the solver:
  Simulates the same feedback that would be produced if that word were the secret and this guess was played (using the same function as the game).
  If the simulated feedback is different from the real feedback, the word is impossible and is removed from the candidate list.
Repeating this after each guess quickly shrinks the candidate set until only the real answer remains (or a very small number of candidates).

Why this approach is effective
  The solver never guesses randomly; every step it uses previous information to strictly reduce the candidate set.
  The elimination step is sound: only words that are inconsistent with observed feedback are removed, so the true target is always kept.
  Even with a simple “first candidate” selection policy, the candidate set tends to drop quickly in size; adding letter‑frequency or entropy‑based scoring improves it further.
The strategy is generic: changing the dictionary changes only the initial candidate set, not the algorithm.

b. Data structure justification: Data structures used:
  Array of strings for the dictionary:
  char dictionary[MAX_WORDS][WORD_LEN + 1]; Easy to load from file line by line. Direct access by index (O(1)). 
  Array of indices for candidates:
  int candidates[MAX_WORDS]; int cand_size; Each candidate is an index into dictionary. Filtering is done by scanning this array and compacting it in place.
Simple arrays for feedback and markers:
 int feedback[WORD_LEN]; int used[WORD_LEN]; Used for comparing guess vs target and handling repeated letters.

Why these choices? Arrays are sufficient because:
   The dictionary size is bounded (a few thousand words), and we mainly do sequential scans.​ Random access is simple and efficient. Using an array of indices instead of copying strings avoids repeated string allocations and simplifies filtering (only integers are moved). This keeps the implementation in pure C with basic memory management (no need for complex dynamic structures for this scale).

c. Complexity analysis
Time complexity: Let:
  N = number of words in the dictionary.
  L= length of each word (here, L=5).
  G = number of guesses the solver makes (≤ 6 for standard Wordle).
Feedback computation
  Comparing one guess with one target: Two passes over the word: O(L) time.
  This is called many times: For each guess, for each remaining candidate.
Filtering candidates after a guess. For each candidate word, we:
  Compute simulated feedback: O(L). Compare with actual feedback: O(L).So each candidate check is O(L), and filtering over all candidates is O(N·L) in the worst case (early guesses when candidate set is large).
Per game: Worst-case, for each of the G guesses we filter across up to N candidates:
Time ≈ O(G·N·L). Here, G ≤ 6 and L = 5, so complexity is effectively O(N).

Dictionary loading: Reading each word once from file: O(N·L) ≈ O(N).
Overall: A single end‑to‑end run (one game) is dominated by the filtering loops:
 Time complexity ≈ O(N) for fixed G and L.
If a more advanced scoring strategy is used (e.g., computing expected eliminations for every candidate at each step), the per‑step cost can rise towards O(N²) in the worst case, because each candidate is compared against all others to evaluate information gain.
Space complexity: Dictionary storage:
  dictionary[N][L+1] → O(N·L) = O(N).
  Candidates array: candidates[N] → O(N).
 Small auxiliary arrays (feedback, used) are constant space O(1).
Total space complexity ≈ O(N).

d. Code documentation
Below is an example of how to document the main functions in your report and in code comments.
  Example: feedback function
get_feedback(guess, target, feedback) computes Wordle’s color feedback between a guess and the secret target:
Stores 2 for green, 1 for yellow, 0 for gray at each position.
Interface (document in report + comments)
Parameters:
 const char *guess: a null‑terminated string of length 5 representing the guessed word.
 const char *target: a null‑terminated string of length 5 representing the secret word.
int feedback[WORD_LEN]: output array where each entry is set to 0, 1, or 2.
Return:
None (results stored in feedback).
Logic: First pass: mark exact matches as green (2) and mark positions used.
Second pass: for remaining letters, mark yellow (1) if same letter exists in target at an unused position.
