#include <cstdlib>
#include <windows.h>
#include <ctime>
#include "Sudoku.h"
#include "tools.h"


int main() {
    srand(time(0));
    system("cls");
    hideCursor();
    auto s = Sudoku(40);
    s.print();
    Sleep(1000);
    s.solve(0, 0);
    return 0;
}