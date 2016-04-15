#include <iostream> 
#include <iomanip>
#include <cstdlib>
#include <string>

// divide into functions:
// initWithStars // put * into all array elements
// displayArray // output the array contents in console
// checkArray // validate the user input
// gameEnd // check for TicTacToe and output the winner as well

using namespace std; 

const int SIZE = 3;
const string DUBSKIP = "\n\n",
	PLAYER = "Player ",
	REQUEST = ": Enter your move in the format <row> <column>: ",
	WON = " has won!",
	TIE = "Game ends in a tie";
	
const char P0 = '*', P1 = 'X', P2 = 'O', NUL = '-';

// fill with stars
// CHECKED
void initWithStars(char arr[SIZE][SIZE]){
	for (int out =0; out < SIZE; out++)
		for (int in =0; in < SIZE; in++)
			arr[out][in] = P0;
		
}

// CHECKED
void displayArray(char arr[SIZE][SIZE]){
	for (int out =0; out < SIZE; out++){
		for (int in =0; in < SIZE; in++)
			cout <<  arr[out][in] << " ";
		cout << endl;
	}
	cout << endl;
}

// check if the value entered is even valid
// only call after init the ttt array
// CHECKED
bool checkArray(char arr[SIZE][SIZE], int i1, int i2){
	if ((i1 >= 1 && i2 >= 1) && (i1 <= SIZE && i2 <= SIZE))
		if (arr[--i1][--i2] == P0)
			return true; // jumps out
		
	return false;
}

// get all elements filled with user input
// needs the array to be converted into 1D // easier to handle
// CHECKED
int getCount(char arr[]){
	int counter = 0;
	
	for (int out =0; out < SIZE; out++)
		for (int in =0; in < SIZE; in++)
			if (arr[SIZE*out +in] != P0) ++counter;
	return counter;
}

// change the 2D array to 1D
// CHECKED
void arrayTo1D(char arr[SIZE][SIZE], char array[SIZE * SIZE]){
	for (int out =0; out < SIZE; out++)
		for (int in =0; in < SIZE; in++)
			array[out *SIZE+ in] = arr[out][in];
}

// takes the input array checks if tictactoe combo and returns bool value 
// and which char has the combo
// CHECKED
bool isCombo(char& out, char arr[SIZE]){
	bool combo = false;
	for (int i = 1; i < SIZE; i++)	// do comparisons for SIZE -1
		if (arr[0] != P0 && arr[0] == arr[i]) combo = true;  // don't count * * * combos
		else {
			out = NUL;
			return false;
			} // jump out of function with a return value of false.
	out = combo ? arr[0] : NUL;
	return combo;
}

// sweeps the diagonals to check for combos
// CHECKED
bool checkDiag(char& out, char arr[],bool dir){ // dir: true = ltop to rbot. false = lbot to rtop	
	char check[SIZE];
	
	int n = dir ? SIZE +1 : SIZE -1;
	int start = dir ? 0 : 1;
	
	for (int i = start; i < SIZE + start; i++){
		check[i-start] = arr[n*i];
	}
	return isCombo(out, check);
}

// check horizontal and vertical
// CHECKED
bool checkStraight(char& out, char arr[], bool dir){ // dir: true = hori. false = vertical
	char check[SIZE];
	bool combo = false;
	int loop = 0;
	
	for (int outer =0; outer < SIZE; outer++){
		for (int in =0; in < SIZE; in++){
			loop = dir ? SIZE*outer + in : SIZE*in + outer;
			check[in] = arr[loop];
		}
	combo = isCombo(out, check);
			if (combo) return combo;
	}
	return combo; // returns false
}

// the check will do a diagonal sweep and then a vertical and horizontal sweep
// CHECKED
bool gameEnd(char& out, char arr[]){ // - for false. * = tie. X = p1. O =p2.
	// 2 diagonal sweeps
	if (checkDiag(out, arr, true)) return true;
	if (checkDiag(out, arr, false)) return true;
	// horizontal
	if (checkStraight(out, arr, true)) return true;
	// vertical
	if (checkStraight(out, arr, false)) return true;
	
	if (getCount(arr) == SIZE*SIZE) { // if all slots filled and no one has won then tie
		out = P0;
		return true;
	}
	out = NUL;
	return false;		
}

int main ()
{	
	char ttt[SIZE][SIZE];
	char ttt1D[SIZE*SIZE];
	char end = ' ';
	int r, c;
	int p = 0;
	bool finished = false, turn = true;
	string conclusion = "";
	
	initWithStars(ttt); // fill with stars
	
	cout << "### TIC TAC TOE GAME ###" << DUBSKIP;	
	displayArray(ttt); // first output
	while (!finished){
		p = turn ? 1 : 2;		
		cout << PLAYER << p << REQUEST;
		cin >> r>> c;
		if (checkArray(ttt, r, c)){ // validated so change turns and new input
			if (turn)
				ttt[--r][--c] = P1;
			else 
				ttt[--r][--c] = P2;
			turn = !turn;
		}
		cout << endl; // skip line before displaying the board
		displayArray(ttt);
		arrayTo1D(ttt, ttt1D);
		
		finished = gameEnd(end, ttt1D);		
	}
	switch (end){
			case P0 :  conclusion = TIE;break;
			case P1 : conclusion = PLAYER + "1" + WON;break;
			case P2 : conclusion = PLAYER + "2" + WON;break;
			default: conclusion = "DEBUG!!"; break;
		}
	cout << conclusion << endl;
	
	return 0;
}
