#include "game.h"
Game::Game()
{
}
Game::~Game()
{
}

void Game::loadBoard(char** board)
{



	//reset variables
	if (was_initialized)
		old_size = board_size;

	player_turn = -1;
	pawn_num = -1;
	is_board_correct = -1;
	is_game_over = -1;
	is_board_possible = -1;
	can_win_in_N_moves = -1;
	free_cells = -1;
	rows = -1;
	collumns = -1;
	start_red.clear();
	start_blue.clear();
	free_spots.clear();

	//delete free_spots


	//reset visited
	//for (int i = 0; i < rows; i++) {
		//delete[] visited[i];
	//}
	//delete[] visited;

	in_board = board;

	calculateBoardSize();

	reformatBoard();
}
void Game::reformatBoard()
{
	if (was_initialized) {
		//reset board
		if (board_size != old_size) {
			for (int i = 0; i < 2 * old_size + 1; i++) {
				delete[] this->board[i];
				delete[] this->board_copy[i];
			}
			delete[] this->board;
			delete[] this->board_copy;
			goto creating_new_board;
		}
		//reading board
		for (int i = 1; i < board_size + 1; i++) {
			for (int j = 1; j < collumns; j++) {
				board[i][j] = in_board[i - 1][j - 1];
			}
		}
		for (int i = board_size + 1; i < 2 * collumns; i++) {
			for (int j = i - board_size + 1, t = 0; j < board_size + 1; j++, t++) {
				board[i][j] = in_board[i - 1][t];
			}
		}
		//cleaning up new board
		for (int i = 0; i < board_size + 1; i++) {
			board[i][i + 1] = '.';
			board[board_size + i][i] = ',';
			board[i][0] = 'X';
			board[board_size + i][board_size + 1] = 'x';
		}
		board[board_size][board_size + 1] = 'x';
	}
	else {
	creating_new_board:
		char** newBoard = new char* [rows];
		for (int i = 0; i < rows; i++) {
			newBoard[i] = new char[collumns];
		}
		//filling up with '*'
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < collumns; j++) {
				newBoard[i][j] = '*';
			}
		}
		//reading board
		for (int i = 1; i < board_size + 1; i++) {
			for (int j = 1; j < collumns; j++) {
				newBoard[i][j] = in_board[i - 1][j - 1];
			}
		}
		for (int i = board_size + 1; i < 2 * collumns; i++) {
			for (int j = i - board_size + 1, t = 0; j < board_size + 1; j++, t++) {
				newBoard[i][j] = in_board[i - 1][t];
			}
		}
		//cleaning up new board
		for (int i = 0; i < board_size + 1; i++) {
			newBoard[i][i + 1] = '.';
			newBoard[board_size + i][i] = ',';
			newBoard[i][0] = 'X';
			newBoard[board_size + i][board_size + 1] = 'x';
		}
		newBoard[board_size][board_size + 1] = 'x';
		board = newBoard;
		was_initialized = true;
	}


	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < collumns; ++j) {
			if (board[i][j] == 'X') {
				start_red.push_back({ i, j });
			}
			if (board[i][j] == '.') {
				start_blue.push_back({ i, j });
			}
		}
	}

	board_copy = new char* [rows];
	//copy of board
	for (int i = 0; i < rows; ++i)
	{
		board_copy[i] = new char[collumns];
		for (int j = 0; j < collumns; ++j)
		{
			board_copy[i][j] = board[i][j];
		}
	}

	visited = new bool* [rows];
	for (int i = 0; i < rows; i++) {
		visited[i] = new bool[collumns];
	}
}
void Game::debug_printBoard() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j <= board_size + 1; j++) {
			std::cout << board[i][j];
		}
		std::cout << std::endl;
	}
}



void Game::debug_printVisited(pair current, bool** visited, char** board, char player) {
	std::cout << std::endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < collumns; j++) {
			if (i == current.first && j == current.second)
				std::cout << 'X';
			else
				std::cout << (visited[i][j] ? '1' : ' ');
		}
		std::cout << ' ';
		for (int k = 0; k < collumns; k++)
		{
			if (board[i][k] == (player == 'r' ? 'b' : 'r'))
				std::cout << ' ';
			else
				std::cout << board[i][k];
		}
		std::cout << std::endl;
	}
}
bool isValid(int row, int col, int rows, int collumns) {
	return row >= 0 && row < rows && col >= 0 && col < collumns;
}
bool Game::bfs(std::vector<pair>& start_pos, char side) {
	//std::vector<std::vector<bool>> visited(rows, std::vector<bool>(collumns, false));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < collumns; j++) {
			visited[i][j] = false;
		}
	}
	Queue<pair> q;
	// Initialize the queue with starting positions
	for (const auto& pos : start_pos) {
		q.push(pos);
		visited[pos.first][pos.second] = true;
	}
	char current_cell;
	int row, col, dr, dc, nr, nc;
	while (!q.isEmpty()) {

		pair current = q.pop();
		//q.pop();

		row = current.first;
		col = current.second;
		current_cell = board[row][col];
		// Check if the current cell is on the opposite side
		//debug_printVisited(current,visited, board, side);

		if ((side == 'b' && current_cell == ',')) {
			//delete visited;
			//delete q;
			//delete &current;
			return true;  // Reached the opposite side
		}
		else if ((side == 'r' && current_cell == 'x')) {
			//delete &q;
			//delete& current;
			return true;  // Reached the opposite side
		}
		else {
			// Check all neighboring cells
			for (const auto& dir : directions) {
				dr = dir.first;
				dc = dir.second;
				nr = row + dr;
				nc = col + dc;
				// Check if neighboring cell is within bounds, unvisited, and has the same color
				if (isValid(nr, nc, rows, collumns))
					if (!visited[nr][nc] && (board[nr][nc] == side))
						if (board[nr][nc] == (side == 'r' ? 'x' : ',')) {
							q.push({ nr, nc });
							visited[nr][nc] = true;
						}
			}
		}
		//delete& current;
	}
	//delete& q;
	return false;
}

bool Game::dfs(std::vector<pair>& start_pos, char side) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < collumns; j++) {
			visited[i][j] = false;
		}
	}
	std::stack<pair> s;
	// Initialize the queue with starting positions
	for (const auto& pos : start_pos) {
		s.push(pos);
		visited[pos.first][pos.second] = true;
	}
	char current_cell;
	int row, col, dr, dc, nr, nc;
	while (!s.empty()) {
		pair current = s.top();
		s.pop();
		row = current.first;
		col = current.second;
		current_cell = board[row][col];
		// Check if the current cell is on the opposite side
		//debug_printVisited(current, visited, board, side);
		if ((side == 'b' && current_cell == ',')) {
			return true;  // Reached the opposite side
		}
		else if ((side == 'r' && current_cell == 'x')) {

			return true;  // Reached the opposite side
		}
		else {
			// Check all neighboring cells
			for (const auto& dir : directions) {
				dr = dir.first;
				dc = dir.second;
				nr = row + dr;
				nc = col + dc;
				// Check if neighboring cell is within bounds, unvisited, and has the same color
				if (isValid(nr, nc, rows, collumns))
					if (!visited[nr][nc] && ((board[nr][nc] == side) || board[nr][nc] == (side == 'r' ? 'x' : ','))) {
						s.push({ nr, nc });
						visited[nr][nc] = true;
					}
			}
		}
	}
	return false;
}

//dfs recursive
bool Game::dfs_recursive(pair current, char side) {
	visited[current.first][current.second] = true;
	char current_cell = board[current.first][current.second];
	// Check if the current cell is on the opposite side
	//debug_printVisited(current, visited, board, side);
	if ((side == 'b' && current_cell == ',')) {
		return true;  // Reached the opposite side
	}
	else if ((side == 'r' && current_cell == 'x')) {
		return true;  // Reached the opposite side
	}
	else {
		// Check all neighboring cells
		for (const auto& dir : directions) {
			int dr = dir.first;
			int dc = dir.second;
			int nr = current.first + dr;
			int nc = current.second + dc;
			// Check if neighboring cell is within bounds, unvisited, and has the same color
			if (isValid(nr, nc, rows, collumns))
				if (!visited[nr][nc] && ((board[nr][nc] == side) || board[nr][nc] == (side == 'r' ? 'x' : ','))) {
					if (dfs_recursive({ nr, nc }, side))
						return true;
				}
		}
	}
	return false;

}

void Game::calculateBoardSize()
{
	int size = 0;
	for (int i = 0; i < 12; i++) {

		if (in_board[i][i] == '*') {
			break;
		}
		else {
			size++;
		}
	}
	board_size = size;
	rows = 2 * board_size + 1;
	collumns = board_size + 2;
}
void Game::printBoardSize()
{
	std::cout << board_size << std::endl;
}

void Game::calculatePawnNum()
{
	int num = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < board_size + 1; j++) {
			if (board[i][j] == 'b' || board[i][j] == 'r') {
				num++;
			}
		}
	}
	pawn_num = num;
	free_cells = (board_size * board_size) - pawn_num;


	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < collumns; ++j)
		{
			if (board[i][j] == ' ')
			{
				free_spots.push_back({ i, j });
			}
		}
	}
}
void Game::printPawnNum()
{
	if (pawn_num != -1) {

		std::cout << pawn_num << std::endl;
		return;
	}
	else {
		calculatePawnNum();
		printPawnNum();
	}
}


void Game::isBoardCorrect()
{
	if (pawn_num == -1) {
		calculatePawnNum();
	}
	bool is_correct = false;
	//counting red pawns
	int redPawns = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < collumns; j++) {
			if (board[i][j] == 'r') {
				redPawns++;
			}
		}
	}
	if (!(bool)(pawn_num % 2)) {
		if (redPawns == pawn_num / 2) {
			player_turn = 'r';
			is_correct = true;
		}
	}
	else {
		if (redPawns == (pawn_num + 1) / 2) {
			player_turn = 'b';
			is_correct = true;
		}
	}
	is_board_correct = is_correct;
	return;
}
void Game::printIsBoardCorrect()
{

	if (pawn_num != -1) {
		if (is_board_correct != -1) {
			std::cout << (is_board_correct ? "YES" : "NO") << std::endl;
			return;
		}

		else {
			isBoardCorrect();
			printIsBoardCorrect();
		}
	}
	else {
		calculatePawnNum();
		printIsBoardCorrect();
	}
}

void Game::isGameOver()
{
	if (is_board_correct == -1)
		isBoardCorrect();
	if (is_board_correct == 0)
	{
		is_game_over = 0;
	}
	else {
		//bool red_connected = dfs(start_red, 'r');
		bool red_connected;
		for (const auto& start : start_red)
		{
			red_connected = dfs_recursive(start, 'r');
			//reset visited 
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < collumns; j++)
				{
					visited[i][j] = false;
				}
			}
			if (red_connected)
			{
				is_game_over = 1;
				return;
			}
		}
		//bool blue_connected = dfs(start_blue, 'b');
		bool blue_connected;
		for (const auto& start : start_blue) {
			blue_connected = dfs_recursive(start, 'b');
			//reset visited 
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < collumns; j++)
				{
					visited[i][j] = false;
				}
			}
			if (blue_connected)
			{
				is_game_over = 2;
				return;
			}
		}

		is_game_over = 0;

	}
}

void Game::printIsGameOver()
{
	if (is_game_over == -1)
	{
		isGameOver();
	}
	if (is_game_over == 1) {
		std::cout << "YES RED" << std::endl;
	}
	else if (is_game_over == 2)
	{
		std::cout << "YES BLUE" << std::endl;
	}
	else {
		std::cout << "NO" << std::endl;
	}
}

void Game::isBoardPossible()
{
	if (is_board_correct == -1)
	{
		isBoardCorrect();
	}
	if (is_board_correct == 0)
	{
		is_board_possible = 0;
	}
	else
	{
		if (is_game_over == -1)
		{
			isGameOver();
		}
		if (is_game_over == 0)
		{
			is_board_possible = 1;
		}
		else
		{
			if (is_game_over == 1 && player_turn == 'r')
			{
				is_board_possible = 0;
			}
			else if (is_game_over == 2 && player_turn == 'b')
			{
				is_board_possible = 0;
			}
			else
			{
				is_board_possible = 0;
				//save original over status
				int original_over = is_game_over;

				std::vector<pair> pawns;
				for (int i = 0; i < rows; ++i)
				{
					for (int j = 0; j < collumns; ++j)
					{
						if (board[i][j] == (player_turn == 'r' ? 'b' : 'r'))
						{
							pawns.push_back({ i, j });
						}
					}
				}
				//copy of board
				char** board_copy = new char* [rows];
				for (int i = 0; i < rows; ++i)
				{
					board_copy[i] = new char[collumns];
					for (int j = 0; j < collumns; ++j)
					{
						board_copy[i][j] = board[i][j];
					}
				}

				for (auto pawn : pawns) {
					//remove pawn and check if game is over
					board[pawn.first][pawn.second] = ' ';
					isGameOver();
					if (is_game_over == 0)
					{
						is_board_possible = 1;
						//restore pawn
						board[pawn.first][pawn.second] = (player_turn == 'r' ? 'b' : 'r');
						break;
					}
					else {
						//restore pawn
						board[pawn.first][pawn.second] = (player_turn == 'r' ? 'b' : 'r');
					}

				}
				//delete copy of board
				for (int i = 0; i < rows; ++i)
				{
					delete[] board_copy[i];
				}
				delete[] board_copy;
				//restore original over status
				is_game_over = original_over;

			}
		}
	}

}
void Game::printIsBoardPossible()
{
	if (is_board_possible == -1)
	{
		isBoardPossible();
	}
	if (is_board_possible == 1) {
		std::cout << "YES" << std::endl;
	}
	else {
		std::cout << "NO" << std::endl;
	}
}

void Game::canWinInNMoves(int player, int moves)
{
	char c_player = (player == 0 ? 'r' : 'b');
	if (is_game_over == -1)
	{
		isGameOver();
	}
	if (is_game_over == 1 || is_game_over == 2)
	{
		can_win_in_N_moves == 0;
		return;
	}
	if (is_board_correct == -1) {
		isBoardCorrect();
	}
	if (is_board_correct == 0)
	{
		can_win_in_N_moves = 0;
		return;
	}

	if (pawn_num < 2 * board_size - 4)
	{
		can_win_in_N_moves = 0;
		return;
	}
	if (c_player == player_turn)
	{
		if (moves == 1)
		{
			if (free_cells < 1)
			{
				can_win_in_N_moves = 0;
				return;
			}
		}
		else {
			if (free_cells < 3)
			{
				can_win_in_N_moves = 0;
				return;
			}

		}
	}
	else
	{

		if (moves == 1) {
			if (free_cells < 2)
			{
				can_win_in_N_moves = 0;
				return;
			}
		}
		else
		{
			if (free_cells < 4)
			{
				can_win_in_N_moves = 0;
				return;
			}
		}

	}

	//save original over status
	int original_over = is_game_over;

	//adding player pawn/pawns and checking if the game is over
	for (auto spot : free_spots)
	{
		board[spot.first][spot.second] = c_player;
		isGameOver();
		if (is_game_over == 1 && c_player == 'r')
		{
			can_win_in_N_moves = 1;
		}
		else if (is_game_over == 2 && c_player == 'b')
		{
			can_win_in_N_moves = 1;
		}
		if (moves > 1)
		{
			canWinInNMoves(player, moves - 1);
		}
		//restore pawn
		board[spot.first][spot.second] = ' ';
		if (can_win_in_N_moves == 1)
		{
			break;
		}
	}
	//restore original over status
	is_game_over = original_over;

}

void Game::printCanWinInNMoves(int player, int moves)
{
	can_win_in_N_moves = -1;
	canWinInNMoves(player, moves);
	if (can_win_in_N_moves == 1)
	{
		std::cout << "YES" << std::endl;
	}
	else
	{
		std::cout << "NO" << std::endl;
	}
}
