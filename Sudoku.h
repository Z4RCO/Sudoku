

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H


#include <vector>

class Sudoku {
private:
    int numbers_;
    int **grid_;
    bool rowContains(int row, int elem);
    bool columnContains(int col, int elem);
    bool squareContains(int x, int y, int elem);
    bool checkPosition(int i, int j, int elem);

    void fillSquare(int row, int col);
    bool fillRest(int i, int j);
public:
    Sudoku(int numbers);

    void fill();

    void print();

    void removeNumbers();

    bool solve(int row, int col);
};


#endif //SUDOKU_SUDOKU_H
