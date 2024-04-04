#include "queens.h"

int main() {
    int board[N][M] = {0};
    show(board);
    solve(board, 2);
    show(board);
    return 0;
}
