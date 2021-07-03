#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <unordered_map>
#include "evaluate.h"
#include "move.h"
#include "cache.h"
#include "minimax.h"
#include "board.h"

using namespace std;

int DEPTH_MAX = DEFAULT_DEPTH_MAX;
bool cache = true;

chrono::system_clock::time_point start;
chrono::duration<double> sec;

unordered_map<long long int, vector<Move>> posTable;

// a1 : board[0][0], h1 : board[0][7], a8 : board[7][0], h8 : board[7][7]
// a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7
Color board[8][8];
Color turn = WHITE;

Move bestMove;
int lastMove = -1; // if en passant is available, cache the last move
int gameMode = 3; // 0 : PvP, 1 : PvC with WHITE, 2 : PvC with BLACK, 3 : CvC

int _evalcount = 0;
int _cache = 0;
long long int _count = 0;
int _maxDepth = 0;
int timeflag = 0;

double alltime;
int moves[100];
double sumtime[100];

int main(void) {
	boardInit();

	bool flag = true;
	int turnCount = 1;
	int game = 0;
	int whitewin = 0;
	int blackwin = 0;
	int draw = 0;
	double alltime = 0;
	string curMove;
	vector<Move> legalMove;

	if (isPlayerTurn() || gameMode == 3) printBoard();

	while (true) {
		posTable.clear();

		if (turnCount <= 2) {
			if (sec.count() < TIME_MIN && DEPTH_MAX < DEFAULT_DEPTH_MAX) DEPTH_MAX++;
		}
		else {
			if (sec.count() < TIME_MIN) DEPTH_MAX++;
		}

		if (!flag) {
			DEPTH_MAX = DEFAULT_DEPTH_MAX;
			boardInit();
			turn = WHITE;
			moves[game] = turnCount;
			turnCount = 1;
			sumtime[game] = alltime;
			alltime = 0;
			cout << "<result> " << whitewin << " : " << blackwin << " (draw : " << draw << ")" << endl;
			for (int i = 0; i <= game; i++) {
				cout << "game " << i << " : " << sumtime[i] << " seconds, " << moves[i] << " moves" << endl;
			}
			flag = true;
			game += 1;
			continue;
		}

		legalMove = findLegalMove();

		cout << "game " << game << endl;
		cout << "move " << turnCount << endl;
		if (turn == WHITE) cout << "WHITE TURN" << endl;
		else cout << "BLACK TURN" << endl;

		cout << "position winning : " << evaluatePosition(turn) << endl;

		if (legalMove.empty()) {
			cout << "STALEMATE : There is no legal moves." << endl;
			cout << "total took " << alltime << " seconds" << endl;
			draw += 1;
			flag = false;
			continue;
			//break;
		}
		else {
			cout << "all legal moves : ";
			for (auto v : legalMove) {
				cout << mstr(v) << " ";
			}
			cout << endl;
		}

		if (isPlayerTurn()) {
			cout << "move : ";
			cin >> curMove;

			if (curMove == "quit") {
				break;
			}
			else if (curMove == "find") {
				start = chrono::system_clock::now();
				auto pos = findBestMove(0, pair<int, int>(POS_MIN, N));
				sec = chrono::system_clock::now() - start;
				cout << "best move is " << mstr(bestMove) << " (winning : " << pos.first
					<< ", depth : " << pos.second << ", count : " << _count << ", maxDepth : " << _maxDepth << ", evalcount : " << _evalcount << ", cache : " << _cache << ")" << endl;
				cout << "took " << sec.count() << " seconds " << endl;
			}
			else if (curMove == "finddepth") {
				cout << "depth : ";
				cin >> DEPTH_MAX;
				start = chrono::system_clock::now();
				auto pos = findBestMove(0, pair<int, int>(POS_MIN, N));
				sec = chrono::system_clock::now() - start;
				cout << "best move is " << mstr(bestMove) << " (winning : " << pos.first
					<< ", depth : " << pos.second << ", count : " << _count << ", maxDepth : " << _maxDepth << ", evalcount : " << _evalcount << ", cache : " << _cache << ")" << endl;
				cout << "took " << sec.count() << " seconds " << endl;
			}
			else if (curMove == "test") {
				cout << "findLegalMove 1,000,000 test" << endl;
				start = chrono::system_clock::now();
				for (int i = 1; i <= 1000000; i++) {
					legalMove = findLegalMove();
				}
				sec = chrono::system_clock::now() - start;
				cout << "took " << sec.count() << " seconds " << endl;

				cout << "evaluatePosition 10,000,000 test" << endl;
				start = chrono::system_clock::now();
				for (int i = 1; i <= 10000000; i++) {
					int p = evaluatePosition(turn);
				}
				sec = chrono::system_clock::now() - start;
				cout << "took " << sec.count() << " seconds " << endl;
				
				cout << "encodeBoard 10,000,000 test" << endl;
				start = chrono::system_clock::now();
				for (int i = 1; i <= 10000000; i++) {
					long long int p = encodeBoard();
				}
				sec = chrono::system_clock::now() - start;
				cout << "took " << sec.count() << " seconds " << endl;
			}
			else if (curMove == "eval") {
				auto pos = evaluatePosition(turn);
				cout << "winning : " << pos << endl;
			}
			else if (!isLegalMove(curMove, legalMove)) {
				cout << "illegal move!" << endl;
			}
			else {
				playMove(curMove, legalMove);
				if (turn == BLACK) turnCount++;
				if (gameMode == 0) printBoard();
				changeTurn();
			}
		}
		else {
			start = chrono::system_clock::now();
			pair<int, int> pos;
			cout << "DEPTH_MAX is " << DEPTH_MAX << endl;
			pos = findBestMove(0, pair<int, int>(POS_MIN, N));
			sec = chrono::system_clock::now() - start;

			playMove(bestMove);

			printBoard();
			if (gameMode == 3) {
				if (turn == WHITE) cout << "White played ";
				else cout << "Black played ";
			}
			else cout << "Your opponent played ";
			cout << mstr(bestMove) << " (winning : " << pos.first
				<< ", depth : " << pos.second << ", count : " << _count << ", maxDepth : " << _maxDepth << ", evalcount : " << _evalcount << ", cache : " << _cache << ")" << endl;
			cout << "took " << sec.count() << " seconds" << endl;
			alltime += sec.count();
			if (turn == BLACK) turnCount++;
			changeTurn();
		}

		if (isWinner(WHITE)) {
			cout << "WHITE WON!!" << endl;
			cout << "total took " << alltime << " seconds" << endl;
			whitewin += 1;
			flag = false;
		}
		else if (isWinner(BLACK)) {
			cout << "BLACK WON!!" << endl;
			cout << "total took " << alltime << " seconds" << endl;
			blackwin += 1;
			flag = false;
		}
	}
	cout << "<result> " << whitewin << " : " << blackwin << endl;

	return 0;
}