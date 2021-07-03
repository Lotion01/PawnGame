#include "move.h"
#include "cache.h"
#include <unordered_map>

extern Color turn;
extern int lastMove;
extern Color board[8][8];
extern bool cache;
extern int _cache;
extern int gameMode;
extern unordered_map<long long int, vector<Move>> posTable;

void changeTurn() {
	if (turn == WHITE) turn = BLACK;
	else turn = WHITE;
}

void playMove(string move, vector<Move>& table) {
	Move _move;
	for (auto v : table) {
		if (move == mstr(v)) {
			_move = v;
			break;
		}
	}
	playMove(_move);
}

void playMove(Move move) {
	const Color MYCOLOR = turn;
	const int k = turn == WHITE ? 1 : -1;
	const int a = get<0>(move), b = get<1>(move), c = get<2>(move), d = get<3>(move);
	lastMove = -1;

	switch (a) {
	case 0:
		board[d][b] = MYCOLOR;
		board[c][b] = NONE;
		if ((d - c) * k == 2) lastMove = b;
		break;
	case 1:
		board[d][c] = MYCOLOR;
		board[d - k][b] = NONE;
		break;
	case 2:
		board[d][c] = MYCOLOR;
		board[d - k][b] = NONE;
		board[d - k][c] = NONE;
		break;
	}
}

void undoMove(Move move) {
	const Color MYCOLOR = turn;
	const Color OPPONENT = turn == WHITE ? BLACK : WHITE;
	const int k = turn == WHITE ? 1 : -1;
	const int a = get<0>(move), b = get<1>(move), c = get<2>(move), d = get<3>(move);

	switch (a) {
	case 0:
		board[d][b] = NONE;
		board[c][b] = MYCOLOR;
		break;
	case 1:
		board[d][c] = OPPONENT;
		board[d - k][b] = MYCOLOR;
		break;
	case 2:
		board[d][c] = NONE;
		board[d - k][b] = MYCOLOR;
		board[d - k][c] = OPPONENT;
		break;
	}
}

vector<Move> findLegalMove() {
	long long int code;

	if (cache) {
		code = encodeBoard();
		auto it = posTable.find(code);
		if (it != posTable.end()) {
			_cache++;
			return it->second;
		}
	}

	vector<Move> table;
	if (turn == WHITE) {
		for (int j = 0; j < 8; j++) {
			for (int i = 1; i < 7; i++) {
				if (board[i][j] == WHITE) {
					if (board[i + 1][j] == NONE) {
						table.push_back(make_tuple(0, j, i, i + 1));
					}
					if (i == 1 && board[2][j] == NONE && board[3][j] == NONE) {
						table.push_back(make_tuple(0, j, i, i + 2));
					}
					if (j >= 1 && board[i + 1][j - 1] == BLACK) {
						table.push_back(make_tuple(1, j, j - 1, i + 1));
					}
					if (j <= 6 && board[i + 1][j + 1] == BLACK) {
						table.push_back(make_tuple(1, j, j + 1, i + 1));
					}
					if (lastMove != -1 && i == 4) {
						if (j - 1 == lastMove) {
							table.push_back(make_tuple(2, j, j - 1, i + 1));
						}
						else if (j + 1 == lastMove) {
							table.push_back(make_tuple(2, j, j + 1, i + 1));
						}
					}
				}
			}
		}
	}
	else {
		for (int j = 0; j < 8; j++) {
			for (int i = 1; i < 7; i++) {
				if (board[i][j] == BLACK) {
					if (board[i - 1][j] == NONE) {
						table.push_back(make_tuple(0, j, i, i - 1));
					}
					if (i == 6 && board[5][j] == NONE && board[4][j] == NONE) {
						table.push_back(make_tuple(0, j, i, i - 2));
					}
					if (j >= 1 && board[i - 1][j - 1] == WHITE) {
						table.push_back(make_tuple(1, j, j - 1, i - 1));
					}
					if (j <= 6 && board[i - 1][j + 1] == WHITE) {
						table.push_back(make_tuple(1, j, j + 1, i - 1));
					}
					if (lastMove != -1 && i == 3) {
						if (j - 1 == lastMove) {
							table.push_back(make_tuple(2, j, j - 1, i - 1));
						}
						else if (j + 1 == lastMove) {
							table.push_back(make_tuple(2, j, j + 1, i - 1));
						}
					}
				}
			}
		}
	}

	if (cache && posTable.size() < CACHE_TABLE_SIZE) posTable[code] = table;
	return table;
}

bool isLegalMove(string move, vector<Move> table) {
	for (auto v : table) {
		if (move == mstr(v)) return true;
	}
	return false;
}

bool isPlayerTurn() {
	return (gameMode == 0
		|| (gameMode == 1 && turn == WHITE)
		|| (gameMode == 2 && turn == BLACK));
}