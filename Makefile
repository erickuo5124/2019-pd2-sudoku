All: solve.o transform.o generate.o sudoku.o
	g++ -o generate generate.o sudoku.o
	g++ -o transform transform.o sudoku.o
	g++ -o solve solve.o sudoku.o

solve.o: solve.cpp sudoku.h
	g++ -c solve.cpp
	
transform.o: transform.cpp sudoku.h
	g++ -c transform.cpp

generate.o: generate.cpp sudoku.h
	g++ -c generate.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -c sudoku.cpp

clean:
	rm *.o
