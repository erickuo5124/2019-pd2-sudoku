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
    bool guess();
    bool only();
    bool fill();
    bool check();

  private:
    int map[sudokuSize];
    std::vector<int> index;
    int ans;
    int count[sudokuSize];
    bool candi[sudokuSize][10]= {0};
};

#endif // SUDOKU_H
