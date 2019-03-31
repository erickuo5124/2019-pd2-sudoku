#ifndef SUDOKU_H
#define SUDOKU_H

/***************************************************
 * Finish your .cpp according to this header file. *
 * You can modify this file if needed.             *
 ***************************************************/
#include<vector>

class Sudoku {
  public:
    Sudoku();
    Sudoku(const int init_map[]);
    void print();
    bool isCorrect();
    static const int sudokuSize = 81;

    // generate
    void generate();

    // transform
    void swapNum(int x, int y);
    void swapRow(int x, int y);
    void swapCol(int x, int y);
    void rotate(int x);
    void flip(int x);

    // solve
    int solve();

  private:
    int map[sudokuSize];
    bool checkRow(std::vector<int>);
    bool checkCol(std::vector<int>);
    bool checkCell(std::vector<int>);
    bool checkUnity(int arr[]);
};

#endif // SUDOKU_H
