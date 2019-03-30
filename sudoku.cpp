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

        if(i%9 == 8) cout << "\n";
        else cout << " ";
    }
}
bool Sudoku::checkUnity(int arr[]) {
    int arr_unity[9]; // counters

    for(int i=0; i<9; ++i)
        arr_unity[i] = 0; // initialize
    for(int i=0; i<9; ++i)
        ++arr_unity[arr[i]-1]; // count
    for(int i=0; i<9; ++i)
        if(arr_unity[i] != 1) // all element
            return false; // must be 1
    return true;
}

bool Sudoku::isCorrect() {
    bool check_result;
    int check_arr[9];
    int location;
    for(int i=0; i<81; i+=9) { // check rows
        for(int j=0; j<9; ++j)
            check_arr[j] = map[i+j];
        check_result = checkUnity(check_arr);
        if(check_result == false)
            return false;
    }
    for(int i=0; i<9; ++i) { // check columns
        for(int j=0; j<9; ++j)
            check_arr[j] = map[i+9*j];
        check_result = checkUnity(check_arr);
        if(check_result == false)
            return false;
    }

    for(int i=0; i<9; ++i) { // check cells
        for(int j=0; j<9; ++j) {
            location = 27*(i/3) + 3*(i%3)
                       +9*(j/3) + (j%3);
            check_arr[j] = map[location];
        }
        check_result =
            checkUnity(check_arr);
        if(check_result == false)
            return false;
    }
    return true;
}

// generate
void Sudoku::generate() {
    int map2[sudokuSize]= {3,7,2,1,4,5,6,9,8,
                           8,4,1,2,9,6,5,3,7,
                           9,5,6,3,7,8,2,1,4,
                           1,9,4,6,8,2,7,5,3,
                           6,3,8,5,1,7,9,4,2,
                           5,2,7,4,3,9,8,6,1,
                           7,1,9,8,5,3,4,2,6,
                           2,8,3,9,6,4,1,7,5,
                           4,6,5,7,2,1,3,8,9,
                          };

    srand(time(NULL));
    int count=17;
    while(count>0)
        for(int i=0; i<sudokuSize; ++i) {
            int x = rand()%5;
            if(x != 0 && x!=2) {
                map[i] = map2[i];
                count--;
            }
        }
    int i=rand()%3+2;
    while(i--) {
        int x = rand()%9+1;
        int y = rand()%9+1;
        swapNum(x, y);
        x = rand()%3;
        y = rand()%3;
        swapRow(x, y);

        x = rand()%3;
        y = rand()%3;
        swapCol(x, y);

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
        } else
        for(int i=0; i<(sudokuSize/9)*4; ++i) {
            tmp = map[(i%9)*9 + i%9];
            map[(i%9)*9 + i%9] = map[72 - (i%9)*9 + i%9];
            map[72 - (i%9)*9 + i%9] = tmp;
        }
}


// solve

int Sudoku::solve() {
	int ans=0;
	int map2[sudokuSize];
	vector<int> index;
	vector<int>::iterator it;

	for(int i=0; i<sudokuSize; ++i)
		if(!map[i]) index.push_back(i);

	it = index.begin();
	while(it != index.end()){
		++map[*it];
		int count[10];
		int location;

		//check row
		for(int i=0; i<10; ++i) count[i] = 0;
		for(int i=0; i<9; ++i){
			location = (*it/9)*9 + i;
			++count[map[location]];
			if(count[map[location]] == 2 && map[location] != 0)
				break;
		}
		if(count[map[location]] == 2 && map[location] != 0){
			if(map[*it] == 9 && it == index.begin() && ans == 1)
				it = index.end();
			else if(map[*it] == 9 && it == index.begin() && ans == 0)
				return 0;
			else if(map[*it] == 9){
				while(map[*it] == 9) 
				{map[*it]=0;--it;}
			}
			continue;
		}

		//check cell
		for(int i=0; i<10; ++i) count[i] = 0;
		for(int i=0; i<9; ++i){
			location = *it%9 + i*9;
			++count[map[location]];
			if(count[map[location]] == 2 && map[location] != 0)
				break;
		}
		if(count[map[location]] == 2 && map[location] != 0){
			if(map[*it] == 9 && it == index.begin() && ans == 1)
				it = index.end();
			if(map[*it] == 9 && it == index.begin() && ans == 0)
				return 0;
			else if(map[*it] == 9){
				while(map[*it] == 9) 
				{map[*it]=0;--it;}
			}
			continue;
		}

		//check cell
		for(int i=0; i<10; ++i) count[i] = 0;
		for(int i=0; i<9; ++i){
			location = (*it/27)*27 + (*it/3)*3-(*it/9)*9 + i%3 + (i/3)*9;
			++count[map[location]];
			if(count[map[location]] == 2 && map[location] != 0)
				break;
		}
		if(count[map[location]] == 2 && map[location] != 0){
			if(map[*it] == 9 && it == index.begin() && ans == 1)
				it = index.end();
			if(map[*it] == 9 && it == index.begin() && ans == 0)
				return 0;
			else if(map[*it] == 9){
				while(map[*it] == 9) 
				{map[*it]=0;--it;}
			}

			continue;
		}

		++it;
		if(it == index.end()){
			++ans;
			if(ans == 2) return ans;
			for(int i=0; i<sudokuSize; ++i)
				map2[i] = map[i];
			
			--it;
			while(map[*it] == 9) {map[*it]=0;--it;}
		}
	}

	if(ans == 1)
		for(int i=0; i<sudokuSize; ++i)
			map[i] = map2[i];
	return ans;
}
