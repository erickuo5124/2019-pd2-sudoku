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
            if(x != 0 && x!=1 && x!=2 && x!=3) {
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
        } else if(x == 0)
        for(int i=0; i<(sudokuSize/9)*4; ++i) {
            tmp = map[i];
            map[i] = map[72 - (i/9)*9 + i%9];
            map[72 - (i/9)*9 + i%9] = tmp;
        }
}


// solve
int Sudoku::solve() {
    do {
        check();
        if(!only())
            if(!fill())
                break;
    } while(1);

    check();
    if(index.empty())
        return 1;
    int ans=0;
    int map2[sudokuSize];
    vector<int>::iterator it;
    it = index.begin();
    while(it != index.end()) {

        ++map[*it];

        int count[10];
        int location;

        //check row
        for(int i=0; i<10; ++i) count[i] = 0;
        for(int i=0; i<9; ++i) {
            location = (*it/9)*9 + i;
            ++count[map[location]];
            if(count[map[location]] == 2 && map[location] != 0)
                break;
        }
        if(count[map[location]] == 2 && map[location] != 0) {
            if(map[*it] == 9 && it == index.begin())
                it = index.end();
            else if(map[*it] == 9) {
                while(map[*it] == 9 && it != index.begin()) {
                    map[*it]=0;
                    --it;
                }
                if(map[*it] == 9 && it == index.begin())
                    it = index.end();
            }
            continue;
        }
        //check col
        for(int i=0; i<10; ++i) count[i] = 0;
        for(int i=0; i<9; ++i) {
            location = *it%9 + i*9;
            ++count[map[location]];
            if(count[map[location]] == 2 && map[location] != 0)
                break;
        }
        if(count[map[location]] == 2 && map[location] != 0) {
            if(map[*it] == 9 && it == index.begin())
                it = index.end();
            else if(map[*it] == 9) {
                while(map[*it] == 9 && it != index.begin()) {
                    map[*it]=0;
                    --it;
                }
                if(map[*it] == 9 && it == index.begin())
                    it = index.end();
            }
            continue;
        }
        //check cell
        for(int i=0; i<10; ++i) count[i] = 0;
        for(int i=0; i<9; ++i) {
            location = (*it/27)*27 + (*it/3)*3-(*it/9)*9 + i%3 + (i/3)*9;
            ++count[map[location]];
            if(count[map[location]] == 2 && map[location] != 0)
                break;
        }
        if(count[map[location]] == 2 && map[location] != 0) {
            if(map[*it] == 9 && it == index.begin())
                it = index.end();
            else if(map[*it] == 9) {
                while(map[*it] == 9 && it != index.begin()) {
                    map[*it]=0;
                    --it;
                }
                if(map[*it] == 9 && it == index.begin())
                    it = index.end();
            }
            continue;
        }
        ++it;
        if(it == index.end()) {
            ++ans;
            if(ans == 2) return ans;
            for(int i=0; i<sudokuSize; ++i)
                map2[i] = map[i];

            --it;
            while(map[*it] == 9) {
                map[*it]=0;
                --it;
            }
        }
    }

    if(ans == 1)
        for(int i=0; i<sudokuSize; ++i)
            map[i] = map2[i];
    return ans;
}

void Sudoku::check() {
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
}

bool Sudoku::only() {
    for(int i=0; i<sudokuSize; ++i)
        if(count[i] == 1)
            for(int j=1; j<10; ++j)
                if(candi[i][j] == 0) {
                    map[i] = j;
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
                        return 1;
                    }
                }
            }
        }

    }
    return 0;
}

/*ver.2
int Sudoku::solve() {
    int ans=0;
    int map2[sudokuSize];
	vector<int> index;
    vector<int>::iterator it;
    vector<int> index2;

    for(int i=0; i<sudokuSize; ++i)
        if(!map[i]) index2.push_back(i);

    //sort index
    int count2[sudokuSize]= {0};
    bool candi[sudokuSize][10]= {0};
    for(it = index2.begin(); it != index2.end(); ++it) {
        int location;
        //row
        for(int i=0; i<9; ++i) {
            location = (*it/9)*9 + i;
            if(map[location])
                candi[*it][map[location]]=1;
        }
        //col
        for(int i=0; i<9; ++i) {
            location = *it%9 + i*9;
            if(map[location])
                candi[*it][map[location]]=1;
        }
        //cell
        for(int i=0; i<9; ++i) {
            location = (*it/27)*27 + (*it/3)*3-(*it/9)*9 + i%3 + (i/3)*9;
            if(map[location])
                candi[*it][map[location]]=1;
        }
        //count
        for(int i=1; i<10; i++)
            if(candi[*it][i] == 0)
                ++count2[*it];
    }

    vector<int>::iterator minn=index2.begin();
    //find min
    for(int i=0; i<index2.size(); ++i) {
        minn = index2.begin();
        while(!count2[*minn]) ++minn;

        for(it = index2.begin(); it != index2.end(); ++it) {
            if(count2[*minn] > count2[*it] && count2[*it])
                minn = it;
        }

		index.push_back(*minn);

        count2[*minn] = 0;
    }//sort index


	for(it = index.begin(); it != index.end(); it++){
		printf("%2d :", *it);
		for(int i=1; i<10; i++)
			if(candi[*it][i] == 0)
				cout << " " << i;
		cout << endl;
	}

	return 0;

	//fill number
    it = index.begin();
    while(it != index.end()) {

			++map[*it];


		if(*it == 14 || *it == 27 || *it == 36){
		cout<<endl;
		cout << *it <<" "<< map[*it];
		}

        int count[10];
        int location;

        //check row
        for(int i=0; i<10; ++i) count[i] = 0;
        for(int i=0; i<9; ++i) {
            location = (*it/9)*9 + i;
            ++count[map[location]];
            if(count[map[location]] == 2 && map[location] != 0)
                break;
        }
        if(count[map[location]] == 2 && map[location] != 0) {
            if(map[*it] == 9 && it == index.begin())
                it = index.end();
            else if(map[*it] == 9) {
                while(map[*it] == 9 && it != index.begin()) {
                    map[*it]=0;
                    --it;
                }
                if(map[*it] == 9 && it == index.begin())
                    it = index.end();
            }
            continue;
        }
		if(*it == 14 || *it == 27 || *it == 36)
		cout << "#";
        //check col
        for(int i=0; i<10; ++i) count[i] = 0;
        for(int i=0; i<9; ++i) {
            location = *it%9 + i*9;
            ++count[map[location]];
            if(count[map[location]] == 2 && map[location] != 0)
                break;
        }
        if(count[map[location]] == 2 && map[location] != 0) {
            if(map[*it] == 9 && it == index.begin())
                it = index.end();
            else if(map[*it] == 9) {
                while(map[*it] == 9 && it != index.begin()) {
                    map[*it]=0;
                    --it;
                }
                if(map[*it] == 9 && it == index.begin())
                    it = index.end();
            }
            continue;
        }
		if(*it == 14 || *it == 27 || *it == 36)
		cout << "#";
        //check cell
        for(int i=0; i<10; ++i) count[i] = 0;
        for(int i=0; i<9; ++i) {
            location = (*it/27)*27 + (*it/3)*3-(*it/9)*9 + i%3 + (i/3)*9;
            ++count[map[location]];
            if(count[map[location]] == 2 && map[location] != 0)
                break;
        }
        if(count[map[location]] == 2 && map[location] != 0) {
            if(map[*it] == 9 && it == index.begin())
                it = index.end();
            else if(map[*it] == 9) {
                while(map[*it] == 9 && it != index.begin()) {
                    map[*it]=0;
                    --it;
                }
                if(map[*it] == 9 && it == index.begin())
                    it = index.end();
            }
            continue;
        }
		if(*it == 14 || *it == 27 || *it == 36)
		cout << "#";
        ++it;
        if(it == index.end()) {
            ++ans;
            if(ans == 2) return ans;
            for(int i=0; i<sudokuSize; ++i)
                map2[i] = map[i];

            --it;
            while(map[*it] == 9) {
                map[*it]=0;
                --it;
            }
        }
    }

    if(ans == 1)
        for(int i=0; i<sudokuSize; ++i)
            map[i] = map2[i];
    return ans;
}
*/
