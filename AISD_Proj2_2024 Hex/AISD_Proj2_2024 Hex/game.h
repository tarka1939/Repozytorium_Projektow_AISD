#pragma once

#include <iostream>
#include "list.h"
#include "string.h""
#include <math.h>
//#include <queue>
#include <stack>
#include "Queue.h"
#include <vector>
#include "Vector.h"
//#include <pair>
#include <set>
#include <windows.h>
struct pair {
	int first;
	int second;
	pair() :first(0), second(0) {};
	pair(int first, int second) :first(first), second(second) {};
	bool operator<(const pair& other) const {
		if (first == other.first) {
			return second < other.second;
		}
		return first < other.first;
	}
};
class Game
{
private:
	std::vector<pair> directions = { {1, 1}, {-1, -1}, {2, 1}, {-2, -1}, {1, 0}, {-1, 0} };
	char** in_board;
	char** board;
	char** board_copy;
	
	bool** visited;

	bool was_initialized = false;
	char player_turn = -1;
	int board_size = -1;
	int pawn_num = -1;
	int free_cells = -1;
	int is_board_correct = -1;
	int is_game_over = -1;
	int is_board_possible = -1;
	int can_win_in_N_moves = -1;
	int rows = -1;
	int columns = -1;
	int old_size = -1;
	pair* stack = new pair[13 * 13];
	Vector<pair> start_red, start_blue, free_spots;

	//std::vector<std::pair<int, int>> free_spots;
	//void debug_printVisited(pair current, bool** visited, char** board, char player);

	void calculateBoardSize();
	void calculatePawnNum();
	void isBoardCorrect();
	void isGameOver();
	void isBoardPossible();
	void reformatBoard();
	void canWinInNMoves(int player, int moves);

	//bool checkSurroundings(int x, int y, int player);
	//bool bfs(Vector <pair>& start_pos, char side);
	bool dfs(Vector <pair>& start_pos, char side);
	//bool dfs_recursive(pair current, char side);
public:

	Game();
	~Game();
	void debug_printBoard();


	void printBoardSize();
	void printPawnNum();
	void printIsBoardCorrect();
	void printIsGameOver();
	void printIsBoardPossible();
	void printCanWinInNMoves(int player, int moves);
	void loadBoard(char** board);
	//void debug_printVisited();
};