#include<iostream>
#include"sudoku.h"
using namespace std;

int main() {
    int map[81];
    for(int i=0; i<81; i++) cin>>map[i];
    Sudoku sudoku(map);

    switch(sudoku.solve()) {
    case 0:
        printf("0\n");
        break;
    case 1:
        printf("1\n");
        sudoku.print();
        break;
    case 2:
        printf("2\n");
        break;
    }
    return 0;
}
