#include "board.h"
#include "util.h"
#include <iostream>

using namespace std;
extern Color board[8][8];

void printBoard() {
	cout << endl;
	cout << "﹛|a |b |c |d |e |f |g |h |" << endl;
	cout << "天 天 天 天 天 天 天 天 天" << endl;
	for (int i = 7; i >= 0; i--) {
		cout << char(i + 49) << " |";
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == NONE) {
				cout << "﹛|";
			}
			else if (board[i][j] == WHITE) {
				cout << "≒|";
			}
			else {
				cout << "∞|";
			}
		}
		cout << endl;
		cout << "天 天 天 天 天 天 天 天 天" << endl;
	}
}

void boardInit() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == 1) {
				board[i][j] = WHITE;
			}
			else if (i == 6) {
				board[i][j] = BLACK;
			}
			else {
				board[i][j] = NONE;
			}
		}
	}
	/*
	string s = "00000000 02202222 20000000 00020000 00000000 11100000 00011111 00000000";
	int p = 0;
	for (auto c : s) {
		if (c == '0') {
			board[(7 - p / 8)][p % 8] = NONE;
		}
		else if (c == '1') {
			board[(7 - p / 8)][p % 8] = WHITE;
		}
		else if (c == '2') {
			board[(7 - p / 8)][p % 8] = BLACK;
		}
		else continue;
		p++;
	}
	*/
}