#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#ifndef QUEENS_H
#define QUEENS_H

#endif // QUEENS_H

#define N 8
#define M N

bool spaceIsUnmarked(int [N][M], int, int);

void markSpace(int [N][M], int, int, int);

void unmarkSpace(int [N][M], int, int, int);

bool isFinished(int);

bool isUnsolvable(int, int, int);

void drawLine();

void show(int [N][M]);

void markRow(int [N][M], int, int);

void markCol(int [N][M], int, int);

void markDiag(int [N][M], int, int, int);

void markReverseDiag(int [N][M], int, int, int);

void unmarkRow(int [N][M], int, int);

void unmarkCol(int [N][M], int, int);

void unmarkDiag(int [N][M], int, int, int);

void unmarkReverseDiag(int [N][M], int, int, int);

bool spaceIsUnmarked(int board[N][M], int row, int col) {
    return board[row][col] == 0;
}

void markSpace(int board[N][M], int row, int col, int counter) {
    board[row][col] = counter;
    markRow(board, row, counter);
    markCol(board, col, counter);
    markDiag(board, row, col, counter);
    markReverseDiag(board, row, col, counter);
}

void

unmarkSpace(int board[N][M], int row, int col, int counter) {
    board[row][col] = 0;
    unmarkRow(board, row, counter);
    unmarkCol(board, col, counter);
    unmarkDiag(board, row, col, counter);
    unmarkReverseDiag(board, row, col, counter);
}

void moveForward(int *row, int *col, int *counter) {
    *row = 0;
    *col += 1;
    *counter += 1;
}

void moveBackward(int board[N][M], int *row, int *col, int *counter) {
    *col -= 1;
    *counter -= 1;
    for (int i = 0; i < M; i++) {
        if (board[i][*col] == *counter) {
            *row = i;
            return;
        }
    }
}

bool isFinished(int col) {
    return col == M - 1;
}

bool isUnsolvable(int row, int startRow, int col) {
    return row == startRow && col == 0;
}

bool solve(int board[N][M], int startRow) {
    markSpace(board, startRow, 0, 1);
    int row = 0;
    int col = 1;
    int counter = 2;
    while (true) {
        if (row < N && spaceIsUnmarked(board, row, col)) {
            markSpace(board, row, col, counter);
            if (isFinished(col)) {
                return true;
            }
            moveForward(&row, &col, &counter);
        } else {
            row += 1;
            if (isUnsolvable(row, startRow, col)) {
                return false;
            }
            if (row >= N) {
                moveBackward(board, &row, &col, &counter);
                unmarkSpace(board, row, col, counter);
                row += 1;
            }
        }
    }
}

void drawLine() {
    for (int i = 0; i < M; i++) {
        printf("+----");
    }
    printf("+\n");
}

void show(int board[N][M]) {
    fflush(stdout);
    drawLine();
    for (int i = 0; i < N; i++) {
        fflush(stdout);
        for (int j = 0; j < M; j++) {
            printf("| %2d ", board[i][j]);
        }
        printf("|\n");
        drawLine();
    }
    printf("\n");
}

void markRow(int board[N][M], int row, int counter) {
    for (int col = 0; col < M; col++) {
        if (spaceIsUnmarked(board, row, col)) {
            board[row][col] = -counter;
        }
    }
}

void markCol(int board[N][M], int col, int counter) {
    for (int row = 0; row < N; row++) {
        if (spaceIsUnmarked(board, row, col)) {
            board[row][col] = -counter;
        }
    }
}

void markDiag(int board[N][M], int row, int col, int counter) {
    int startRow = (row < col) ? 0 : row - col;
    int startCol = (row < col) ? col - row : 0;

    for (int i = startRow, j = startCol; i < N && j < N; i++, j++) {
        if (spaceIsUnmarked(board, i, j)) {
            board[i][j] = -counter;
        }
    }
}

void markReverseDiag(int board[N][M], int row, int col, int counter) {
    int startRow = (row + col < N) ? 0 : row + col - (N - 1);
    int startCol = (row + col < N) ? row + col : N - 1;

    for (int i = startRow, j = startCol; i < N && j >= 0; i++, j--) {
        if (spaceIsUnmarked(board, i, j)) {
            board[i][j] = -counter;
        }
    }
}

void unmarkRow(int board[N][M], int row, int counter) {
    for (int col = 0; col < M; col++) {
        if (board[row][col] == -counter) {
            board[row][col] = 0;
        }
    }
}

void unmarkCol(int board[N][M], int col, int counter) {
    for (int row = 0; row < N; row++) {
        if (board[row][col] == -counter) {
            board[row][col] = 0;
        }
    }
}

void unmarkDiag(int board[N][M], int row, int col, int counter) {
    int startRow = (row < col) ? 0 : row - col;
    int startCol = (row < col) ? col - row : 0;

    for (int i = startRow, j = startCol; i < N && j < N; i++, j++) {
        if (board[i][j] == -counter) {
            board[i][j] = 0;
        }
    }
}

void unmarkReverseDiag(int board[N][M], int row, int col, int counter) {
    int startRow = (row + col < N) ? 0 : row + col - (N - 1);
    int startCol = (row + col < N) ? row + col : N - 1;

    for (int i = startRow, j = startCol; i < N && j >= 0; i++, j--) {
        if (board[i][j] == -counter) {
            board[i][j] = 0;
        }
    }
}
