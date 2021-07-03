#include "cache.h"
#include "util.h"

extern Color board[8][8];
extern Color turn;
extern int lastMove;

bool canEnPassant() {
	if (lastMove == -1) return false;

	if (turn == WHITE) {
		if (lastMove >= 1 && board[4][lastMove - 1] == WHITE) return true;
		else if (lastMove <= 6 && board[4][lastMove + 1] == WHITE) return true;
		else return false;
	}
	else {
		if (lastMove >= 1 && board[3][lastMove - 1] == BLACK) return true;
		else if (lastMove <= 6 && board[3][lastMove + 1] == BLACK) return true;
		else return false;
	}

}
long long int encodeBoard() {
	long long int num = 0;
	for (int j = 0; j < 8; j++) {
		int n = 0;
		for (int i = 1; i < 7; i++) {
			n |= 1i64 << ((i - 1) * 3 + board[i][j]);
		}
		num |= codeTable[n] << (j * 7);
	}
	if (canEnPassant()) {
		num |= (long long int)(lastMove + 1) << 56;
	}
	if (turn == WHITE) {
		num |= 1i64 << 60;
	}
	return num;
}