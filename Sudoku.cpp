//
// Created by Sergio on 21/10/2024.
//

#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include "Sudoku.h"
#include "tools.h"

Sudoku::Sudoku(int numbers) : numbers_(numbers) {
    grid_ = new int *[9];
    for (int i = 0; i < 9; ++i) {
        grid_[i] = new int[9];
    }
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            grid_[i][j] = 0;
        }
    }
    fill();
    removeNumbers();

}

bool Sudoku::rowContains(int row, int elem) {
    for (int i = 0; i < 9; ++i) {
        if (grid_[row][i] == elem)return true;
    }
    return false;
}

bool Sudoku::columnContains(int col, int elem) {
    for (int i = 0; i < 9; ++i) {
        if (grid_[i][col] == elem)return true;
    }
    return false;
}

bool Sudoku::squareContains(int x, int y, int elem) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid_[x + i][y + j] == elem) {
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::checkPosition(int i, int j, int elem) {
    return !rowContains(i, elem) &&
           !columnContains(j, elem) &&
           !squareContains(i - i % 3, j - j % 3, elem);
}

void Sudoku::fillSquare(int row, int col) {
    int num;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            do {
                num = rand() % 9 + 1;
            } while (squareContains(row, col, num));
            grid_[row + i][col + j] = num;
        }
    }
}

void Sudoku::fill() {
    fillSquare(0, 0);
    fillSquare(3, 3);
    fillSquare(6, 6);

    fillRest(0,2);
}

bool Sudoku::fillRest(int i, int j) {
    if (j >= 9 && i < 8) {
        i++;
        j = 0;
    }
    if (i >= 9 && j >= 9) {
        return true;
    }
    if (i < 3) {
        if (j < 3) {
            j = 3;
        }
    }
    else if (i < 6) {
        if (j == (int)(i / 3) * 3) {
            j += 3;
        }
    }
    else {
        if (j == 6) {
            j = 0;
            if (++i >= 9) {
                return true;
            }
        }
    }
    for (int num = 1; num <= 9; num++) {
        if (checkPosition(i, j, num)) {
            grid_[i][j] = num;
            if (fillRest(i, j + 1)) {
                return true;
            }
            grid_[i][j] = 0;
        }
    }
    return false;
}

void Sudoku::removeNumbers() {
    int remaining = 81 - numbers_;
    while (remaining > 0) {
        int i = rand() % 9;
        int j = rand() % 9;
        if (grid_[i][j] != 0) {
            grid_[i][j] = 0;
            remaining--;
        }
    }
}

void Sudoku::print() {

    for(int i = 0; i < 43; ++i){
        moveCursor(i,8);
        printf("%c", 205);
        moveCursor(i,18);
        printf("%c", 205);
    }

    for(int i = 0; i < 27; ++i){
        moveCursor(13,i);
        printf("%c", 186);
        moveCursor(29,i);
        printf("%c", 186);
    }
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            moveCursor(5 * j + j / 3, 3 * i + i / 3);
            if(grid_[i][j] == 0)setConsoleColor(4);
            printf("%d", grid_[i][j]);
            setConsoleColor(7);
        }
    }
}

bool Sudoku::solve(int row, int col) {
    if(row == 9){
        setConsoleColor(7);
        return true;
    }
    if(col == 9){
        return solve(row + 1, 0);
    }
    if(grid_[row][col] != 0){
        return solve(row, col + 1);
    }
    for(int num = 1; num <= 9; num++){
        moveCursor(5 * col + col / 3, 3 * row + row / 3);
        setConsoleColor(9);
        printf("%d", num);
        Sleep(100);
        if(checkPosition(row, col, num)){
            grid_[row][col] = num;
            if(solve(row, col + 1))return true;
            setConsoleColor(12);
            moveCursor(5 * col + col / 3, 3 * row + row / 3);
            printf("%d", 0);
            grid_[row][col] = 0;
        }
    }
    setConsoleColor(12);
    moveCursor(5 * col + col / 3, 3 * row + row / 3);
    printf("%d", 0);

    return false;
}