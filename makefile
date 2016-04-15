TicTacToe.out: TicTacToe.cpp
	g++ TicTacToe.cpp -o TicTacToe.out
	
run: TicTacToe.out
	./TicTacToe.out
