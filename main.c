#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include "game.h"
#include "solver.h"

void print_usage(const char *prog_name) {
    printf("Usage: %s [mode] [args]\n", prog_name);
    printf("Modes:\n");
    printf("  (no args)           Play Wordle with a random word\n");
    printf("  <word>              Play Wordle with a specific target word\n");
    printf("  --solve             Run solver with a random word\n");
    printf("  --solve <word>      Run solver with a specific target word\n");
    printf("  --benchmark <N>     Run solver on N random words\n");
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    Dictionary *dict = load_dictionary("words.txt");
    if (!dict) {
        fprintf(stderr, "Error: Could not load dictionary 'words.txt'. Make sure it exists.\n");
        return 1;
    }
    printf("Loaded %d words.\n", dict->count);

    if (argc == 1) {
        // Play game with random word
        char *target = get_random_word(dict);
        play_game(target, dict);
        free(target);
    } else if (strcmp(argv[1], "--solve") == 0) {
        char *target;
        if (argc > 2) {
            target = strdup(argv[2]);
            if (!is_valid_guess(target, dict)) {
                printf("Warning: Target word '%s' not in dictionary.\n", target);
            }
        } else {
            target = get_random_word(dict);
        }
        solve_game(target, dict);
        free(target);
    } else if (strcmp(argv[1], "--benchmark") == 0) {
        int n = 100;
        if (argc > 2) n = atoi(argv[2]);
        printf("Running benchmark on %d words...\n", n);
        
        for(int i=0; i<n; i++) {
            char *t = get_random_word(dict);
            solve_game(t, dict);
            free(t);
            printf("--------------------------------------------------\n");
        }
    } else {
        // Assume argument is a target word
        char *target = strdup(argv[1]);
        if (!is_valid_guess(target, dict)) {
            printf("Warning: Target word '%s' not in dictionary.\n", target);
        }
        play_game(target, dict);
        free(target);
    }

    free_dictionary(dict);
    return 0;
}

