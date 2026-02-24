#include "Head.h"
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
char readCell() {
	char c;
	std::cin.ignore(2);
	c = std::cin.get();
	std::cin.ignore(2);
	return c;
}

void readBoard(char**& board) {
	char next;
	char c;
	int rows = -1	;
	int columns = 0;
	std::cin.ignore(100, '-');
	while (std::cin) {
		next = std::cin.peek();
		if (next == 'B' || next == 'P' || next == 'I' || next=='C') {
			break;
		}
		else if (next == '\n') {
			std::cin.ignore(1);
			rows++;
			columns = 0;
		}
		else if(next == '<'){
			c = readCell();
			board[rows][columns] = c;
			columns++;
		}
		else {
			std::cin.ignore(1);
		}
	}
}

void debug_printBoard(char** board) {
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 12; j++) {
			std::cout << board[i][j];
		}
		std::cout << std::endl;
	}
}
void initBoard(char**& board) {
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 12; j++) {
			board[i][j] = '*';
		}
	}
}

static void redirectStream(std::ifstream& fileIn, std::ofstream& fileOut) {
	// Redirecting cin to read from "input.txt" 
	std::cin.rdbuf(fileIn.rdbuf());
	// Redirecting cout to write to "output.txt" 
	std::cout.rdbuf(fileOut.rdbuf());
}
std::string test_list[] = {
	//"0",
	//"1",
	//"2",
	//"3",
	//"4",
	//"5",
	//"6", 
	//"7",
	//"11", 
	"16"
};

void main_loop(){
	Game game;
	char** board = new char* [21];
	for (int i = 0; i < 21; i++) {
		board[i] = new char[12];
	}
	char* input = new char[100];
	char c; 
	while (std::cin)
	{

		c = std::cin.peek();
		if (c == 'B')
		{
			std::cin >> input;
			game.printBoardSize();
			std::cout << std::endl;
			std::cin.ignore();
		}
		else if (c == 'P')
		{
			std::cin >> input;
			game.printPawnNum();
			std::cout << std::endl;
			std::cin.ignore();
		}
		else if (c == 'I')
		{
			std::cin >> input;
			if (strcmp(input, "IS_BOARD_CORRECT") == 0)
			{
				game.printIsBoardCorrect();
			}
			else if (strcmp(input, "IS_BOARD_POSSIBLE") == 0)
			{
				game.printIsBoardPossible();
			}
			else if (strcmp(input, "IS_GAME_OVER") == 0)
			{
				game.printIsGameOver();
			}
			std::cout << std::endl;
			std::cin.ignore();
		}
		else if (c == 'C')
		{
			std::cin >> input;
			if (strcmp(input, "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") == 0)
			{
				game.printCanWinInNMoves(0, 1);
			}
			else if (strcmp(input, "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") == 0)
			{
				game.printCanWinInNMoves(0, 2);
			}
			else if (strcmp(input, "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") == 0)
			{
				game.printCanWinInNMoves(1, 1);
			}
			else if (strcmp(input, "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") == 0)
			{
				game.printCanWinInNMoves(1, 2);
				std::cout << std::endl;
			}
			
			std::cin.ignore();
		}

		else
		{
			initBoard(board);
			readBoard(board);
			//debug_printBoard(board);
			game.loadBoard(board);
			//game.debug_printBoard();
			//game.printBoardSize();
			//game.printPawnNum();
			//game.printIsBoardPossible();
			//game.debug_printVisited();
		}

	}
}
int main() {
	// tester 
	auto old_cout = std::cout.rdbuf();
	auto old_cin = std::cin.rdbuf();
	for (std::string test : test_list) {
		//start timer 
		clock_t start = clock();
		std::cout<< test + ".in.txt"<<std::endl;
		std::ifstream fileIn(test+".in.txt");
		std::ofstream fileOut("my_" + test + ".out");
		redirectStream(fileIn, fileOut);
		main_loop();
		//end timer
		clock_t end = clock();
		std::cout.rdbuf(old_cout);
		std::cin.rdbuf(old_cin);
		std::cout << "done" << std::endl;
		std::cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
	}
	char* test = new char[100];
	std::cin >> test;
	
	//main_loop();
	
}