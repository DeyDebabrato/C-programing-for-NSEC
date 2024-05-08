#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void printSolution(int *board, int N);
bool isSafe(int *board, int row, int col, int N);
bool solveNQUtil(int *board, int col, int N);
bool solveNQ(int N);

void printSolution(int *board, int N) {
    for (int i = 0; i < N * N; i++) {
        if (board[i])
            printf("Q ");
        else
            printf(". ");
        if ((i + 1) % N == 0)
            printf("\n");
    }
}

bool isSafe(int *board, int row, int col, int N) {
    int i, j;

    for (i = 0; i < col; i++)
        if (board[row * N + i])
            return false;

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i * N + j])
            return false;

    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i * N + j])
            return false;

    for (i = row, j = col; j < N && i >= 0; i--, j++)
        if (board[i * N + j])
            return false;

    return true;
}

bool solveNQUtil(int *board, int col, int N) {
    if (col >= N)
        return true;

    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col, N)) {
            board[i * N + col] = 1;
            if (solveNQUtil(board, col + 1, N))
                return true;
            board[i * N + col] = 0;
        }
    }
    return false;
}

bool solveNQ(int N) {
    int *board = (int *)malloc(N * N * sizeof(int));
    if (board == NULL) {
        printf("Memory allocation failed\n");
        return false;
    }

    for (int i = 0; i < N * N; i++)
        board[i] = 0;

    if (solveNQUtil(board, 0, N) == false) {
        printf("Solution does not exist");
        free(board);
        return false;
    }

    printSolution(board, N);

    free(board);
    return true;
}

int main() {
    int N;
    printf("Enter the size of the chessboard: ");
    scanf("%d", &N);
    if (N <= 0) {
        printf("Invalid size!\n");
        return 1;
    }
    solveNQ(N);
    return 0;
}
