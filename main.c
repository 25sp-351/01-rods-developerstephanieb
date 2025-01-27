#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PIECES 100
#define BUFFER_SIZE 256

typedef struct {
    int length;
    int value;
} Piece;

/**
 * Reads until EOF and stores values in `pieces`.
 * Returns the count of pieces read.
 */
int read_file(Piece *pieces, int max_count)
{
    char line[BUFFER_SIZE];
    int count = 0;

    while (fgets(line, sizeof(line), stdin)) {
        int length;
        int value;

        if (sscanf(line, "%d , %d", &length, &value) == 2) {
            pieces[count].length = length;
            pieces[count].value = value;
            count++;
            if (count >= max_count) {
                fprintf(stderr, "Reached maximum pieces allowed (%d)\n", max_count);
                break;
            }
        }
    }

    return count;
}

/**
 * Performs the rod-cutting DP to compute:
 *    best_value[i] = maximum total value for a rod of length i
 *    choice[i]     = index of the piece chosen at rod length i
 */
void rod_cut(int rod_length, const Piece *pieces, int piece_count,
              int *best_value, int *choice)
{
    for (int i = 0; i <= rod_length; ++i) {
        best_value[i] = 0; 
        choice[i] = -1; 
    }

    for (int i = 1; i <= rod_length; ++i) {
        best_value[i] = best_value[i - 1]; 
        choice[i] = -1;

        for (int j = 0; j < piece_count; ++j) {
            int piece_length = pieces[j].length;
            int piece_value = pieces[j].value;

            if (piece_length <= i) {
                int potential_value = best_value[i - piece_length] + piece_value;
                if (potential_value > best_value[i]) {
                    best_value[i] = potential_value;
                    choice[i] = j;
                }
            }
        }
    }
}

/**
 * Finds the rod length that yields the maximum best value.
 * Returns that length. 
 */
int find_best_length(int rod_length, const int *best_value)
{
    int best_length = 0;
    for (int i = 1; i <= rod_length; ++i) {
        if (best_value[i] > best_value[best_length]) {
            best_length = i;
        }
    }
    return best_length;
}

/**
 * Constructs the pieces to find best solution:
 *    usage[j] = how many times pieces[j] was used. 
 */
void construct_pieces(int used_length, const int *choice,
                         const Piece *pieces, int piece_count,
                         int *usage)
{
    for (int j = 0; j < piece_count; j++) {
        usage[j] = 0;
    }

    while (used_length > 0 && choice[used_length] != -1) {
        int j = choice[used_length];
        usage[j]++;
        used_length -= pieces[j].length;
    }
}

/**
 * Prints the final solution: cuts, remainder, and total value. 
 */
void print_solution(int best_i, int rod_length, const int *usage,
                   const Piece *pieces, int piece_count, int total_value)
{
    for (int j = 0; j < piece_count; j++) {
        if (usage[j] > 0) {
            int subtotal_value = usage[j] * pieces[j].value;
            printf("%d @ %d = %d\n", usage[j], pieces[j].length, subtotal_value);
        }
    }

    int remainder = rod_length - best_i;
    printf("Remainder: %d\n", remainder);

    printf("Value: %d\n", total_value);
}

/**
 * MAIN: parses arguments, finds the solution, constructs, and prints.
 */
int main(int argc, char *argv[])
{
    int rod_length = atoi(argv[1]);

    Piece *pieces = malloc(sizeof(Piece) * MAX_PIECES);
    int piece_count = read_file(pieces, MAX_PIECES);

    if (piece_count == 0) {
        fprintf(stderr, "No valid piece data found.\n");
        free(pieces);
        return 1;
    }

    int *best_value = calloc(rod_length + 1, sizeof(int));
    int *choice    = calloc(rod_length + 1, sizeof(int));

    rod_cut(rod_length, pieces, piece_count, best_value, choice);

    int best    = find_best_length(rod_length, best_value);
    int max_value  = best_value[best];

    int *usage = calloc(piece_count, sizeof(int));
    construct_pieces(best, choice, pieces, piece_count, usage);

    print_solution(best, rod_length, usage, pieces, piece_count, max_value);

    free(pieces);
    free(best_value);
    free(choice);
    free(usage);

    return 0;
}