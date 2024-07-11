#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N 9
#define UNASSIGNED 0

void printSudokuGrid(int grid[N][N], int difficultyLevel) {
    if (difficultyLevel == 1 || difficultyLevel == 2 || difficultyLevel == 3) {
        for (int row = 0; row < N; row++) {
            if (row % 3 == 0 && row != 0) {
                printf("---------------------\n");
            }
            for (int col = 0; col < N; col++) {
                if (col % 3 == 0 && col != 0) {
                    printf("| ");
                }
                if (grid[row][col] == UNASSIGNED) {
                    printf("  ");
                } else {
                    printf("%d ", grid[row][col]);
                }
            }
            printf("\n");
        }
    } else {
        printf("No such level exists.\n");
    }
}

bool isSafeMove(int grid[N][N], int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

bool solveSudokuGrid(int grid[N][N]) {
    int row, col;
    bool isEmptyCell = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == UNASSIGNED) {
                isEmptyCell = true;
                break;
            }
        }
        if (isEmptyCell) {
            break;
        }
    }
    if (!isEmptyCell) {
        return true;
    }
    for (int num = 1; num <= 9; num++) {
        if (isSafeMove(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudokuGrid(grid)) {
                return true;
            }
            grid[row][col] = UNASSIGNED;
        }
    }
    return false;
}

void generateSudokuPuzzle(int grid[N][N], int difficultyLevel) {
    srand(time(0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = 0;
        }
    }
    solveSudokuGrid(grid);
    int removeCount;
    if (difficultyLevel == 1) {
        removeCount = 40;
    } else if (difficultyLevel == 2) {
        removeCount = 50;
    } else if (difficultyLevel == 3) {
        removeCount = 60;
    } else {
        printf("Invalid difficulty level.\n");
        exit(1);
    }
    while (removeCount > 0) {
        int row = rand() % N;
        int col = rand() % N;
        if (grid[row][col] != 0) {
            grid[row][col] = UNASSIGNED;
            removeCount--;
        }
    }
}

int main() {
    int sudokuGrid[N][N];
    int difficultyLevel;
    
    printf("Select difficulty level (1 for easy, 2 for medium, 3 for hard): ");
    scanf("%d", &difficultyLevel);
    
    generateSudokuPuzzle(sudokuGrid, difficultyLevel);
    
    printf("Sudoku Puzzle: \n");
    printSudokuGrid(sudokuGrid, difficultyLevel);
    
    while (1) {
        int row, col, num;
        printf("Enter row, column, and number (0 to quit): ");
        scanf("%d", &row);
        if (row == 0) {
            break;
        }
        scanf("%d %d", &col, &num);
        
        if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
            printf("Invalid input. Please try again.\n");
            continue;
        }
        
        if (!isSafeMove(sudokuGrid, row - 1, col - 1, num)) {
            printf("Invalid move. Please try again.\n");
            continue;
        }
        
        sudokuGrid[row - 1][col - 1] = num;
        printf("Updated Sudoku Puzzle: \n");
        printSudokuGrid(sudokuGrid, difficultyLevel);
    }
    
    return 0;
}
