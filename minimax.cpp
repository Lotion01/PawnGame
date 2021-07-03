#include "evaluate.h"
#include <chrono>
#include <iostream>
#include <algorithm>
#include <random>
#include "move.h"

extern chrono::system_clock::time_point start;
extern chrono::duration<double> sec;
extern int DEPTH_MAX;
extern int timeflag;
extern Debug debug;
extern Color turn;
extern int lastMove;
extern Move bestMove;

random_device _rd;
using namespace std;

int comparePos(pair<int, int> a, pair<int, int> b) {
	if (a.first > b.first) {
		return 1;
	}
	else if (a.first == b.first) {
		if (a.second == b.second) {
			return 0;
		}
		else if ((a.first > 0 && a.second < b.second) || (a.first <= 0 && a.second > b.second)) {
			return 1;
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

pair<int, int> findBestMove(int n, pair<int, int> prevPos) {
	sec = chrono::system_clock::now() - start;
	if (sec.count() > TIME_MAX + timeflag * 10) {
		DEPTH_MAX--;
		timeflag++;
		cout << "DEPTH_MAX LOWERED" << endl;
	}
	if (n >= debug.maxDepth) debug.maxDepth = n;
	if (n == 0) debug.count = debug.evalCount = debug.cacheCount = debug.maxDepth = timeflag = 0;
	if (isGameOver()) {
		if (n % 2 == 0) return pair<int, int>(DEFEAT, n);
		else return pair<int, int>(VICTORY, n);
	}
	if (n >= DEPTH_MAX) {
		if (n % 2 == 0) return pair<int, int>(evaluatePosition(turn), n);
		else return pair<int, int>(-evaluatePosition(turn), n);
	}
	debug.count++;
	vector<Move> lm = findLegalMove();
	if (lm.empty()) {
		return pair<int, int>(0, n);
	}
	if (n == 0) shuffle(lm.begin(), lm.end(), default_random_engine(_rd()));

	if (n % 2 == 0) { // Max
		pair<int, int> posMax = pair<int, int>(POS_MIN, N);
		for (auto v : lm) {
			int prevlastMove = lastMove;
			playMove(v);
			changeTurn();
			pair<int, int> pos = findBestMove(n + 1, posMax);
			changeTurn();
			undoMove(v);
			lastMove = prevlastMove;
			if (n >= 2 && comparePos(pos, prevPos) >= 0) {
				return pair<int, int>(POS_MAX, N);
			}
			if (comparePos(pos, posMax) > 0) {
				posMax = pos;
				if (n == 0) bestMove = v;
			}
			if (n == 0) {
				if (pos.first == POS_MIN) cout << mstr(v) << " : pass" << endl;
				else cout << mstr(v) << " : " << pos.first << " " << pos.second << endl;
			}
		}
		return posMax;
	}
	else { // Min
		pair<int, int> posMin = pair<int, int>(POS_MAX, N);
		for (auto v : lm) {
			int prevlastMove = lastMove;
			playMove(v);
			changeTurn();
			pair<int, int> pos = findBestMove(n + 1, posMin);
			changeTurn();
			undoMove(v);
			lastMove = prevlastMove;
			if (comparePos(pos, prevPos) <= 0) {
				return pair<int, int>(POS_MIN, N);
			}
			if (comparePos(pos, posMin) < 0) {
				posMin = pos;
			}
		}
		return posMin;
	}
}