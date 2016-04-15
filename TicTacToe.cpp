#include <iostream> 
#include <iomanip>
#include <cstdlib>
#include <string>

// divide into functions:
// initWithStars // put * into all array elements
// displayArray // output the array contents in console
// checkArray // validate the user input
// gameEnd // check for TicTacToe and output the winner as well
// isTTT // checks if all chars given in the array match

using namespace std; 

const int SIZE = 3;
const string DUBSKIP = "\n\n",
	PLAYER = "Player ",
	REQUEST = ": Enter your move in the format <row> <column>: ",
	WON = " has won!",
	TIE = "Game ends in a tie";
	
const char P0 = '*', P1 = 'X', P2 = 'O', NUL = '-';

void initWithStars(char arr[][SIZE]){
	for (int out =0; out < SIZE; out++)
		for (int in =0; in < SIZE; in++)
			arr[out][in] = P0;
		
}

void displayArray(char arr[][SIZE]){
	for (int out =0; out < SIZE; out++){
		for (int in =0; in < SIZE; in++)
			cout <<  arr[out][in] << " ";
		cout << endl;
	}
	cout << endl;
}

int getCount(char arr[]){
	int counter = 0;
	
	for (int out =0; out < SIZE; out++)
		for (int in =0; in < SIZE; in++)
			if (arr[SIZE*out +in] != P0) ++counter;
	return counter;
}

bool checkArray(char arr[][SIZE], int i1, int i2){
	if ((i1 >= 1 && i2 >= 1) && (i1 <= SIZE && i2 <= SIZE))
		if (arr[--i1][--i2] != P0)
			return true;
	
	return false;
}

bool isCombo(char arr[], char * out){
	bool combo = false;
	for (int i = 1; i < SIZE; i++)	// do comparisons for SIZE -1
		if (arr[0] == arr[i]) combo = true;
		else {
			* out = NUL;
			return false;
			} // jump out of function with a return value of false.
	* out = combo ? arr[0] : NUL;
	return combo;
}

bool checkDiag(char arr[],bool dir, char * out){ // dir: true = ltop to rbot. false = lbot to rtop	
	char check[SIZE];
	
	int n = dir ? SIZE +1 : SIZE -1;
	int start = dir ? 0 : 1;
	
	for (int i = start; i < SIZE; i++){
		check[i] = arr[n*i];
	}
	return isCombo(check, out);
}

bool checkHori(char arr[], char * out){
	char check[SIZE];
	bool combo = false;
	
	for (int outer =0; outer < SIZE; outer++)
		for (int in =0; in < SIZE; in++){
			check[in] = arr[SIZE*outer + in];
			combo = isCombo(check, out);
			if (combo) return combo;
		}
	return combo; // returns false
}

bool checkVert(char arr[], char * out){
	char check[SIZE];
	bool combo = false;
	
	for (int outer =0; outer < SIZE; outer++)
		for (int in =0; in < SIZE; in++){
			check[in] = arr[SIZE*in + outer];
			combo = isCombo(check, out);
			if (combo) return combo;
		}
	return combo; // returns false
}


// the check will do a diagonal sweep and then a vertical and horizontal sweep
bool gameEnd(char arr[], char * out){ // - for false. * = tie. X = p1. O =p2.
	out = NUL;
	cout << out << "y"<< '\t' << *out << 'p';
	// 2 diagonal sweeps
	if (checkDiag(arr, true, out)) return true;
	if (checkDiag(arr, false, out)) return true;
	// horizontal sweeps
	if (checkHori(arr, out)) return true;
	// vert sweeps
	if (checkVert(arr, out)) return true;
	
	if (getCount(arr) == SIZE*SIZE) {
		* out = P0;
		return true;
	}
	*out = NUL;
	return false;		
}

void arrayTo1D(char arr[SIZE][SIZE], char array[SIZE * SIZE]){
	for (int out =0; out < SIZE; out++)
		for (int in =0; in < SIZE; in++)
			array[out *SIZE+ in] = arr[out][in];
}

int main ()
{	
	char ttt[SIZE][SIZE];
	char ttt1D[SIZE*SIZE];
	char end = ' ';
	int rc[2], p = 0;
	bool finished = false, turn = true;
	string conclusion = "";
	
	initWithStars(ttt); // fill with stars

	cout << "### TIC TAC TOE GAME ###" << DUBSKIP;	
	displayArray(ttt);	
	
	while (!finished){
		switch (turn){ // turn doesn't change unless valid input is given
			case true : p=1; break;
			case false : p=2; break;
		}
		cout << PLAYER << p << REQUEST;
		cin >> rc[0] >> rc[1];
		if (checkArray(ttt, rc[0], rc[1])){ // validated so change turns and new input
			if (turn)
				ttt[--rc[0]][--rc[1]] = P1;
			else 
				ttt[--rc[0]][--rc[1]] = P2;
			turn = !turn;
		}
		arrayTo1D(ttt, ttt1D);
		finished = gameEnd(ttt1D, &end);
		cout << end << '\t' << &end;
	}
	switch (end){
			case P0 :  conclusion = TIE;break;
			case P1 : conclusion = PLAYER + "1" + WON;break;
			case P2 : conclusion = PLAYER + "2" + WON;break;
		}
	cout << conclusion << endl;
		
	return 0;
}

