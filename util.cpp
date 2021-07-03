#include "util.h"
#include <iostream>

using namespace std;

string mstr(Move move) {
	// convert coordinates into actual move in game
	string m;
	const int a = get<0>(move), b = get<1>(move), c = get<2>(move), d = get<3>(move);
	if (a == 0) {
		m += char(b + 97);
		m += char(d + 1 + 48);
	}
	else {
		m += char(b + 97);
		m += 'x';
		m += char(c + 97);
		m += char(d + 1 + 48);
	}
	return m;
}

void printTime(chrono::duration<double> sec) {
	cout << "took " << sec.count() << " seconds " << endl;
}

void printDebug(Move move, pair<int, int> pos, Debug debug, chrono::duration<double> sec) {
	cout << mstr(move) << " (winning : " << pos.first
		<< ", depth : " << pos.second << ", count : " << debug.count
		<< ", maxDepth : " << debug.maxDepth << ", evalcount : " << debug.evalCount
		<< ", cache : " << debug.cacheCount << ")" << endl;
	printTime(sec);
}