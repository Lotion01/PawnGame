#include "evaluate.h"
#include <cmath>

extern Color board[8][8];
extern Debug debug;

bool isWinner(Color turn) {
	if (turn == WHITE) {
		for (int j = 0; j < 8; j++) {
			if (board[7][j] == WHITE) {
				return true;
			}
		}
	}
	else if (turn == BLACK) {
		for (int j = 0; j < 8; j++) {
			if (board[0][j] == BLACK) {
				return true;
			}
		}
	}
	else {
		for (int j = 0; j < 8; j++) {
			if (board[7][j] == WHITE || board[0][j] == BLACK) {
				return true;
			}
		}
	}
	return false;
}

bool isGameOver() {
	return isWinner(NONE);
}

bool isPassedPawn(int i, int j, Color turn) {
	if (turn == WHITE) {
		for (int ii = i + 1; ii < 8; ii++) {
			if (board[ii][j] == BLACK) {
				return false;
			}
			if (j >= 1 && board[ii][j - 1] == BLACK) {
				return false;
			}
			if (j <= 6 && board[ii][j + 1] == BLACK) {
				return false;
			}
		}
	}
	else {
		for (int ii = i - 1; ii >= 0; ii--) {
			if (board[ii][j] == WHITE) {
				return false;
			}
			if (j >= 1 && board[ii][j - 1] == WHITE) {
				return false;
			}
			if (j <= 6 && board[ii][j + 1] == WHITE) {
				return false;
			}
		}
	}
	return true;
}

bool isFrozenPawn(int i, int j, Color turn) {
	if (turn == WHITE) {
		if ((j >= 1 && board[i + 1][j - 1] == BLACK) || (j <= 6 && board[i + 1][j + 1] == BLACK)) return false;
		if (i == 1) {
			if (board[2][j] != NONE || (j >= 1 && board[1][j - 1] == WHITE) || (j <= 6 && board[1][j + 1] == WHITE)) return false;
			if ((j >= 1 && board[3][j - 1] == BLACK) || (j <= 6 && board[3][j + 1] == BLACK)) return true;
			if (board[3][j] != NONE || (j >= 1 && board[2][j - 1] == WHITE) || (j <= 6 && board[2][j + 1] == WHITE)) return false;
			if ((j >= 1 && board[4][j - 1] == BLACK) || (j <= 6 && board[4][j + 1] == BLACK)) return true;
		}
		else {
			if (board[3][j] != NONE || (j >= 1 && (board[1][j - 1] == WHITE || board[2][j - 1] == WHITE))
				|| (j <= 6 && (board[1][j + 1] == WHITE || board[2][j + 1] == WHITE))) return false;
			if ((j >= 1 && board[4][j - 1] == BLACK) || (j <= 6 && board[4][j + 1] == BLACK)) return true;
		}
	}
	else {
		if ((j >= 1 && board[i - 1][j - 1] == WHITE) || (j <= 6 && board[i - 1][j + 1] == WHITE)) return false;
		if (i == 6) {
			if (board[5][j] != NONE || (j >= 1 && board[6][j - 1] == BLACK) || (j <= 6 && board[6][j + 1] == BLACK)) return false;
			if ((j >= 1 && board[4][j - 1] == WHITE) || (j <= 6 && board[4][j + 1] == WHITE)) return true;
			if (board[4][j] != NONE || (j >= 1 && board[5][j - 1] == BLACK) || (j <= 6 && board[5][j + 1] == BLACK)) return false;
			if ((j >= 1 && board[3][j - 1] == WHITE) || (j <= 6 && board[3][j + 1] == WHITE)) return true;
		}
		else {
			if (board[4][j] != NONE || (j >= 1 && (board[6][j - 1] == BLACK || board[5][j - 1] == BLACK))
				|| (j <= 6 && (board[6][j + 1] == BLACK || board[5][j + 1] == BLACK))) return false;
			if ((j >= 1 && board[3][j - 1] == WHITE) || (j <= 6 && board[3][j + 1] == WHITE)) return true;
		}
	}
	return false;
}

int evaluatePosition(Color turn) {
	debug.evalCount++;
	int p = 0;
	constexpr int pawnScore = 4;
	constexpr int passedPawnScore = 2;
	constexpr int passedPawnRatio = 4;
	constexpr int frozenPawnScore = -8;
	int whitepass = -1;
	int blackpass = -1;
	for (int i = 1; i < 7; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == WHITE) {
				p += pawnScore + i / 2;
				if (isPassedPawn(i, j, WHITE)) {
					p += passedPawnScore * pow(passedPawnRatio, i - 1);
					if (i - 1 > whitepass) whitepass = i - 1;
				}
				if (i <= 2 && isFrozenPawn(i, j, WHITE)) {
					p += frozenPawnScore;
				}
			}
			else if (board[i][j] == BLACK) {
				p -= pawnScore + (7 - i) / 2;
				if (isPassedPawn(i, j, BLACK)) {
					p -= passedPawnScore * pow(passedPawnRatio, 6 - i);
					if (6 - i > blackpass) blackpass = 6 - i;
				}
				if (i >= 5 && isFrozenPawn(i, j, BLACK)) {
					p -= frozenPawnScore;
				}
			}
		}
	}
	if (whitepass != -1 && whitepass == blackpass) {
		if (turn == WHITE) p += pow(passedPawnRatio, whitepass);
		else p -= pow(passedPawnRatio, whitepass);
	}
	return turn == WHITE ? p : -p;
}