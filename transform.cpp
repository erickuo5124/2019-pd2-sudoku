#include<iostream>
#include"sudoku.h"
using namespace std;

int main() {
    int map[81];
    for(int i=0; i<81; i++) cin>>map[i];
    Sudoku sudoku(map);

    int command;
    cin >> command;
    while(command) {
        switch(command) {
            int x, y;
        case 1 :
            cin >> x >> y;
            sudoku.swapNum(x, y);
            break;

        case 2 :
            cin >> x >> y;
            sudoku.swapRow(x, y);
            break;

        case 3 :
            cin >> x >> y;
            sudoku.swapCol(x, y);
            break;

        case 4 :
            cin >> x;
            sudoku.rotate(x);
            break;

        case 5 :
            cin >> x;
            sudoku.flip(x);
            break;
        }

        sudoku.print();
        cin >> command;
    }

    return 0;
}
