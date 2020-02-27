#include"sudoku.h"
#include<iostream>
#include<time.h>
#include<vector>
using namespace std;

Sudoku::Sudoku() {
    for(int i=0; i<sudokuSize; ++i)
        map[i] = 0;
}

Sudoku::Sudoku(const int init_map[]) {
    for(int i=0; i<sudokuSize; ++i)
        map[i] = init_map[i];
}

void Sudoku::print() {
    for(int i=0; i<sudokuSize; ++i) {
        cout << map[i];

        if(i%9 == 8) cout << endl;
        else cout << " ";
    }
}

// generate
void Sudoku::generate() {
    int map2[sudokuSize] = {
        8,0,0,0,0,0,0,0,0,
        0,0,3,6,0,0,0,0,0,
        0,7,0,0,9,0,2,0,0,
        0,5,0,0,0,7,0,0,0,
        0,0,0,0,4,5,7,0,0,
        0,0,0,1,0,0,0,3,0,
        0,0,1,0,0,0,0,6,8,
        0,0,8,5,0,0,0,1,0,
        0,9,0,0,0,0,4,0,0,
    };

    for(int i=0; i<sudokuSize; ++i)
        map[i] = map2[i];

    srand(time(NULL));
    int i = rand()%10+1;
    while(i--) {
        int x = rand()%9+1;
        int y = rand()%9+1;
        swapNum(x, y);

        x = rand()%4;
        rotate(x);

        x = rand()%2;
        flip(x);
    }

}

// transform
void Sudoku::swapNum(int x, int y) {
    for(int i=0; i<sudokuSize; ++i) {
        if(map[i] == x) map[i] = y;
        else if(map[i] == y) map[i] = x;
    }
}
void Sudoku::swapRow(int x, int y) {
    int tmp;
    for(int i=0; i<sudokuSize/3; ++i) {
        tmp = map[x*sudokuSize/3+i];
        map[x*sudokuSize/3+i] = map[y*sudokuSize/3+i];
        map[y*sudokuSize/3+i] = tmp;
    }
}
void Sudoku::swapCol(int x, int y) {
    int tmp;
    for(int i=0; i<sudokuSize/3; ++i) {
        tmp = map[x*3 + (i%9)*9 + i/9];
        map[x*3 + (i%9)*9 + i/9] = map[y*3 + (i%9)*9 + i/9];
        map[y*3 + (i%9)*9 + i/9] = tmp;
    }
}
void Sudoku::rotate(int x) {
    x %= 4;
    int tmp[sudokuSize];
    for(int i=0; i<sudokuSize; ++i) {
        tmp[i] = map[i];
    }


    if(x == 1) {
        for(int i=0; i<sudokuSize; ++i)
            map[(8-i/9) + 9*(i%9)] = tmp[i];
    } else if(x == 2) {
        for(int i=0; i<sudokuSize; ++i)
            map[sudokuSize-i-1] = tmp[i];
    } else if(x == 3) {
        for(int i=0; i<sudokuSize; ++i)
            map[72 - (i%9)*9 + (i/9)] = tmp[i];
    }
}
void Sudoku::flip(int x) {
    int tmp;
    if(x == 1)
        for(int i=0; i<(sudokuSize/9)*4; ++i) {
            tmp = map[i/9 + (i%9)*9];
            map[i/9 + (i%9)*9] = map[8 - i/9 + (i%9)*9];
            map[8 - i/9 + (i%9)*9] = tmp;
        } else if(x == 0)
        for(int i=0; i<(sudokuSize/9)*4; ++i) {
            tmp = map[i];
            map[i] = map[72 - (i/9)*9 + i%9];
            map[72 - (i/9)*9 + i%9] = tmp;
        }
}


// solve
int Sudoku::solve() {
	int newmap[sudokuSize];
    do {
        if(check())
			if(!only())
				if(!fill())
					if(!guess())
						return 0;
		if(index.empty())
			break;
    } while(ans < 2);
	return 1;
}

bool Sudoku::guess() {
	//find min
	vector<int>::iterator it = index.begin();

	vector<int>::iterator minn = it;
	for(; it != index.end(); ++it)
		if(count[*minn] > count[*it])
			minn = it;
	//fill
	it = minn;
	cout << *it;
	for(int i=1; i<10; ++i){
		if(candi[*it][i] == 0){
			//check row
			//check col
			//checl cell
			map[*it] = i;
			cout << " " << i << endl;
			return solve();
		}
	}
	//no sol
	map[*it] = 0;
	return 0;
}

bool Sudoku::only() {
    for(int i=0; i<sudokuSize; ++i)
        if(count[i] == 1)
            for(int j=1; j<10; ++j)
                if(candi[i][j] == 0) {
                    map[i] = j;
					cout << " %" << i << " " << j << endl;
                    return 1;
                }
    return 0;
}

bool Sudoku::fill() {
    for(int k=0; k<9; ++k) {
        int location;
        int count3[10];
        int itt;

        //row
        for(int i=0; i<10; i++) count3[i]=0;
        itt = k*9;
        for(int i=0; i<9; i++) {
            location = itt + i;
            if(count[location]) {//如果是空著
                for(int j=1; j<10; j++)//將候選數數量做統計
                    if(candi[location][j]==0)
                        count3[j]++;
            }
        }
        for(int i=1; i<10; i++) {
            if(count3[i] == 1) {
                for(int j=0; j<9; j++) {
                    location = itt + j;
                    if(count[location] && !candi[location][i]) {
                        map[location] = i;
						cout << "#1#" << location << " " << i << endl;
                        return 1;
                    }
                }
            }
        }

        //col
        for(int i=0; i<10; i++) count3[i]=0;
        itt = k;
        for(int i=0; i<9; i++) {
            location = itt + i*9;
            if(count[location])
                for(int j=1; j<10; j++)
                    if(candi[location][j]==0)
                        count3[j]++;
        }
        for(int i=1; i<10; i++) {
            if(count3[i] == 1) {
                for(int j=0; j<9; j++) {
                    location = itt + j*9;
                    if(count[location] && !candi[location][i]) {
                        map[location] = i;
						cout << "#2#" << location << " " << i << endl;
                        return 1;
                    }
                }
            }
        }

        //cell
        for(int i=0; i<10; i++) count3[i]=0;
        itt = (itt/3)*27 + (itt%3)*3;
        for(int i=0; i<9; i++) {
            location = itt + i%3 + (i/3)*9;
            if(count[location])
                for(int j=1; j<10; j++)
                    if(candi[location][j]==0)
                        count3[j]++;
        }
        for(int i=1; i<10; i++) {
            if(count3[i] == 1) {
                for(int j=0; j<9; j++) {
                    location = itt + j%3 + (j/3)*9;
                    if(count[location] && !candi[location][i]) {
                        map[location] = i;
						cout << "#3#" << location << " " << i << endl;
                        return 1;
                    }
                }
            }
        }

    }
    return 0;
}

bool Sudoku::check() {
    for(int i=0; i<sudokuSize; ++i)
        count[i] = 0;
    index.clear();
    for(int i=0; i<sudokuSize; ++i)
        if(!map[i])
            index.push_back(i);

    vector<int>::iterator it;
    for(it = index.begin(); it != index.end(); it++) {
        int location;
        //row
        for(int i=0; i<9; i++) {
            location = (*it/9)*9 + i;
            if(map[location])
                candi[*it][map[location]]=1;
        }
        //col
        for(int i=0; i<9; i++) {
            location = *it%9 + i*9;
            if(map[location])
                candi[*it][map[location]]=1;
        }
        //cell
        for(int i=0; i<9; i++) {
            location = (*it/27)*27 + (*it/3)*3-(*it/9)*9 + i%3 + (i/3)*9;
            if(map[location])
                candi[*it][map[location]]=1;
        }
        //count
        for(int i=1; i<10; i++)
            if(candi[*it][i] == 0)
                count[*it]++;
    }

	if(index.empty())
		return 0;
	else
		return 1;
}
