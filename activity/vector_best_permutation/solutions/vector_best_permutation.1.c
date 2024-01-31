// Finds the best permutation of two vectors of variable length
// By Braedon Wooding (b.wooding@student.unsw.edu.au) (17/3/19)
// Algorithm was modified from work done on a 2521 Assignment (25/10/18)

/* == How does this work? ==
    - Link: http://www.hungarianalgorithm.com/hungarianalgorithm.php
    1) Subtract Row Minima:
        Find the smallest element in each row and subtract from row.
    2) Subtract Column Minima:
        Find the smallest element in each column and subtract from column.
    3) Cover all zeros with a minimum number of lines:
        If 'n' lines are required the algorithm stops.
    4) Create additional zeros:
        - Find the smallest element that is not covered by a line in step 3.
        - Subtract this element from all uncovered elements and add to all
          elements covered twice.
        - That is add to all the elements that are covered twice not add twice.
    On Stop) We can just find the solution that has just a single 0 in each row/col
             and then use this to compute the cost from the original matrix.

    NOTES:
    - This algorithm is more suited towards the condition when you have
      N vectors and you want to permute just the first one such that
      the sum of all the euclidean distances between the other N-1 vectors
      is minimized.
    - In a case like this you pay the extra cost of being general so it's complexity
      is O(n^3) which is significantly worse than the Andrew Taylors Solution
      that is O(n^2) and can be optimised to O(nlogn) as it is bounded on the
      sorting algorithm.
    - However it still is quite radically a different approach and is more
      representative of the type of algorithms that you will be
      writing in future years :).
*/

#include <stdio.h> // for printf/scanf
#include <math.h> // for sqrt

// the maximum dimensional size of vectors
#define MAX_VEC_LEN (100)

/*
    Just a collection of stateful arrays to make passing them around easier.
*/
typedef struct state_t {
    int *working_matrix;    // 2D: the matrix that operations are applied onto.
    int *covered_cols;      // 1D: represents what columns are 'covered' by a 0.
    int *covered_rows;      // 1D: represents what rows are 'covered' by a 0.
    int *star_matrix;       // 2D: starred rows/columns for detecting min 0's.
    int *primed_matrix;     // 2D: for priming rows to be 0'd.
    int *tmp;               // 2D: temporary copy of working_matrix.
    int *cost_matrix;       // 2D: original matrix useful to calculate costs.
    int len;                // length of one side of the square matricies.
} *State;

/*
    Scans in an array.  Returns 0 if the scanf fails for whatever reason else 1.
*/
int scanf_array(int array[], int n);

/*
    Euclidean Distance between v1 and v2.
*/
double calc_dist_sqrd(int v1[], int v2[], int n);

/*
    Optimises the problem returning the final cost
    `positions` will contain the final permutation 
*/
double optimize_problem(int v1[], int v2[], int len, int positions[]);

/*
    Prime the matrix by finding which elements have zeroes.
    And setting covered_cols/rows.
*/
void prime_matrix(State state);

/*
    Setups the problem matricies.
*/
void problem_setup(int v1[], int v2[], int len, int cost_matrix[]);

/*
    Find mininum values in each row/col and subtract it from that col/row.
    Does rows first then columns.
*/
void subtract_min_row_cols(int *working_matrix, int size);

/*
    Counts the number of columns that are '1'.
*/
int count_columns(int *cols, int size);

/*
    Covers the first zero'd col then primes matrix to adjust for it.
*/
void cover_cols(State state);

/*
    Unprimes all primes starring as appropriate.
*/
void unprime_and_star(State state, int col, int row);

/*
    Returns the final cost of the system and sets the final permutation.
*/
double get_solution(int star_matrix[], int cost_matrix[], int len, int positions[]);

/*
    Finds minimum uncovered element and adds it to all covered rows and subtracts
    from all uncovered columns.
*/
void apply_min_to_working(State state);

/*
    Homemade memcpy since we can't use std memcpy
*/
void cpy_bytes(void *dest, void *src, int total_size);

/*
    Homemade memset since we can't use std memset
*/
void set_bytes(void *dest, int value, int total_size);

int main(void) {
    int vec1[MAX_VEC_LEN];
    int vec2[MAX_VEC_LEN];
    int n;

    printf("Enter vector length: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Err: Invalid Length");
        return 1;
    }

    printf("Enter vector 1: ");
    if (!scanf_array(vec1, n)) {
        fprintf(stderr, "Err: Invalid Vector");
        return 1;
    }

    printf("Enter vector 2: ");
    if (!scanf_array(vec2, n)) {
        fprintf(stderr, "Err: Invalid Vector");
        return 1;
    }

    // we can approach it like an assignment problem
    // that is we want to choose the best assignment
    int positions[MAX_VEC_LEN];
    double cost = optimize_problem(vec1, vec2, n, positions);
    int i = 0;
    printf("Optimal permutation:");
    i = 0;
    while (i < n) {
        printf(" %d", positions[i]);
        i++;
    }

    printf("\nEuclidean distance: %lf\n", sqrt(cost));
    return 0;
}

void cpy_bytes(void *dest, void *src, int total_size) {
    // copy in single byte chunks
    int i = 0;
    // unsigned char is just an 8 bit integer that can't be negative
    // just typically the type that we use to copy 'raw' bytes
    unsigned char *dest_bytes = dest;
    unsigned char *src_bytes = src;

    while (i < total_size) {
        dest_bytes[i] = src_bytes[i];
        i++;
    }
}

void set_bytes(void *dest, int value, int total_size) {
    // potential narrow cast problems (int -> unsigned char) but this is
    // occurrent in memset as well
    // copy in single byte chunks
    int i = 0;
    // unsigned char is just an 8 bit integer that can't be negative
    // just typically the type that we use to copy 'raw' bytes
    unsigned char *dest_bytes = dest;

    while (i < total_size) {
        dest_bytes[i] = value;
        i++;
    }
}

double calc_dist_sqrd(int v1[], int v2[], int n) {
    double sum = 0;
    int i = 0;
    while (i < n) {
        // square the difference
        sum += (v2[i] - v1[i]) * (v2[i] - v1[i]);
        i++;
    }
    return sum;
}

int scanf_array(int array[], int n) {
    int i = 0;
    while (i < n) {
        if (scanf("%d", array + i) != 1) {
            return 0;
        }
        i++;
    }
    return 1;
}

void problem_setup(int v1[], int v2[], int len, int cost_matrix[]) {
    // Setup Matrix like
    /*
          v1[1]                 v1[1]               ...     v1[n]
    v0[0] (v0[0]-v1[0])^2   (v0[1] - v1[0])^2
    v0[1] ...
    ...
    v0[n]

    To expand it to the general (N vectors) case you just have to have it so that
    the rows represent the sum of the differences between all vectors at that coord
    i.e.
    (i = col, j = row)
    A_ij = Sum(m = 1 -> N) (v_0[j] - v_m[i])^2
    So in the case of N = 1 it is just the matrix shown above :).
    */
    int col = 0;
    while (col < len) {
        int row = 0;
        while (row < len) {
            int euclidian_sqrd = (v2[col] - v1[row]) * (v2[col] - v1[row]);
            cost_matrix[row * len + col] = euclidian_sqrd;
            row++;
        }
        col++;
    }
}

void subtract_min_row_cols(int *working_matrix, int size) {
    // we have to fully finish row before we do column as to not have double ups
    // i.e. a row removal could make the lowest value in this column == 0
    // so we wouldn't want to then further remove from that to make it negative.
    int col = 0;
    int row;
    while (col < size) {
        int min = working_matrix[col];
        row = 1;
        while (row < size) {
            if (working_matrix[row * size + col] < min) {
                min = working_matrix[row * size + col];
            }
            row++;
        }
        row = 0;
        while (row < size) {
            working_matrix[row * size + col] -= min;
            row++;
        }
        col++;
    }

    row = 0;
    while (row < size) {
        int min = working_matrix[row * size];
        col = 1;
        while (col < size) {
            if (working_matrix[row * size + col] < min) {
                min = working_matrix[row * size + col];
            }
            col++;
        }
        col = 0;
        while (col < size) {
            working_matrix[row * size + col] -= min;
            col++;
        }
        row++;
    }
}

double get_solution(int star_matrix[], int cost_matrix[], int len, int positions[]) {
    // write out solution to solution array.
    double cost = 0;
    int row = 0;
    while (row < len) {
        int col = 0;
        while (col < len) {
            if (star_matrix[row * len + col]) {
                positions[col] = row;
                cost += cost_matrix[row * len + col];
                break;
            }
            col++;
        }
        row++;
    }

    return cost;
}

int count_columns(int *cols, int size) {
    int count = 0;
    int col = 0;
    while (col < size) {
        if (cols[col]) {
            count++;
        }
        col++;
    }
    return count;
}

void cover_cols(State state) {
    // find the first star'd # (0) and cover its column
    int col = 0;
    while (col < state->len) {
        int row = 0;
        while (row < state->len) {
            if (state->star_matrix[row * state->len + col]) {
                state->covered_cols[col] = 1;
                break;
            }
            row++;
        }
        col++;
    }

    // check if we have to do another cycle or if we are finished
    if (count_columns(state->covered_cols, state->len) != state->len) {
        prime_matrix(state);
    }
}

void unprime_and_star(State state, int col, int row) {
    // make temporary so we can change but still refer to old state.
    cpy_bytes(state->tmp, state->star_matrix, sizeof(int) * state->len * state->len);
    state->tmp[row * state->len + col] = 1;

    // col/row in star_matrix
    int s_col = col;
    int s_row = 0;
    while (s_row < state->len && !state->star_matrix[s_row * state->len + s_col]) {
        s_row++;
    }

    while (s_row < state->len) {
        state->tmp[s_row * state->len + s_col] = 0;
        // row/col in primed_matrix
        int p_row = s_row;
        int p_col = 0;
        while (p_col < state->len &&
               !state->primed_matrix[p_row * state->len + p_col]) {
            p_col++;
        }
        state->tmp[p_row * state->len + p_col] = 1;
        s_col = p_col;
        s_row = 0;
        while (s_row < state->len &&
               !state->star_matrix[s_row * state->len + s_col]) {
            s_row++;
        }
    }
    // 'commit' temporary changes
    cpy_bytes(state->star_matrix, state->tmp,sizeof(int) * state->len * state->len);
    set_bytes(state->primed_matrix, 0, sizeof(int) * state->len * state->len);
    set_bytes(state->covered_rows, 0, sizeof(int) * state->len);
    cover_cols(state);
}

void apply_min_to_working(State state) {
    int min = __INT_MAX__;
    // find minimum uncovered row and col
    int row = 0;
    int col = 0;
    while (row < state->len) {
        if (!state->covered_rows[row]) {
            col = 0;
            while (col < state->len) {
                if (!state->covered_cols[col]) {
                    if (state->working_matrix[row * state->len + col] < min) {
                        min = state->working_matrix[row * state->len + col];
                    }
                }
                col++;
            }
        }
        row++;
    }

    // bit of a cool trick, if we add to all covered rows 
    // add to all covered rows and if it turns out that it isn't covered on
    // the column then it'll remove it afterwards in next loop.
    row = 0;
    while (row < state->len) {
        if (state->covered_rows[row]) {
            col = 0;
            while (col < state->len) {
                state->working_matrix[row * state->len + col] += min;
                col++;
            }
        }
        row++;
    }

    // remove from all uncovered cols
    col = 0;
    while (col < state->len) {
        if (!state->covered_cols[col]) {
            row = 0;
            while (row < state->len) {
                state->working_matrix[row * state->len + col] -= min;
                row++;
            }
        }
        col++;
    }

    prime_matrix(state);
}

void prime_matrix(State state) {
    int zeros_found = 1;
    while (zeros_found) {
        zeros_found = 0;
        int col = 0;
        while (col < state->len) {
            if (!state->covered_cols[col]) {
                int row = 0;
                while (row < state->len) {
                    if (!state->covered_rows[row] &&
                        state->working_matrix[row * state->len + col] == 0) {
                        // prime the zero and then cover
                        state->primed_matrix[row * state->len + col] = 1;
                        int s_col = 0;
                        int star = state->star_matrix[row * state->len + s_col];
                        while (s_col < state->len && !star) {
                            s_col++;
                            star = state->star_matrix[row * state->len + s_col];
                        }
                        // at end col then unprime and star it
                        if (s_col == state->len) {
                            // step 4
                            unprime_and_star(state, col, row);
                            return;
                        } else {
                            // cover the row and uncover the s_col
                            state->covered_rows[row] = 1;
                            state->covered_cols[s_col] = 0;
                            zeros_found = 1;
                            break;
                        }
                    }
                    row++;
                }
            }
            col++;
        }
    }

    apply_min_to_working(state);
}

double optimize_problem(int v1[], int v2[], int len, int positions[]) {
    // look at the struct definition for state to find meanings for all of these.
    // static memory (allocated at startup and not bounded to stack limits)
    // is better in this case because it allows our arrays to be bigger.
    // an even better solution would be to have these as dynamically allocated
    // arrays (malloc) :).
    static int working_matrix[MAX_VEC_LEN * MAX_VEC_LEN] = {0};
    static int covered_cols[MAX_VEC_LEN] = {0};
    static int covered_rows[MAX_VEC_LEN] = {0};
    static int star_matrix[MAX_VEC_LEN * MAX_VEC_LEN] = {0};
    static int primed_matrix[MAX_VEC_LEN * MAX_VEC_LEN] = {0};
    static int tmp[MAX_VEC_LEN * MAX_VEC_LEN] = {0};
    static int cost_matrix[MAX_VEC_LEN * MAX_VEC_LEN] = {0};

    // this is just to make it so we don't have to pass
    // so many different arrays to each and every function.
    struct state_t state = { working_matrix, covered_cols, covered_rows,
                             star_matrix, primed_matrix, tmp, cost_matrix, len };

    // setup cost matrix and then copy it to working.
    problem_setup(v1, v2, len, cost_matrix);
    cpy_bytes(working_matrix, cost_matrix, sizeof(int) * len * len);

    // do initial subtraction to get atleast a single 0 in each row/col
    subtract_min_row_cols(working_matrix, len);

    // setup initial covered cols and star '0's
    int row = 0;
    while (row < len) {
        int col = 0;
        while (col < len) {
            if (working_matrix[row * len + col] == 0 && !covered_cols[col]) {
                star_matrix[row * len + col] = 1;
                covered_cols[col] = 1;
                break;
            }
            col++;
        }
        row++;
    }

    // if we can't come to a solution already
    // then begin the cycle
    if (count_columns(covered_cols, len) != len) {
        prime_matrix(&state);
    }

    return get_solution(star_matrix, cost_matrix, len, positions);
}
