#pragma once
#include <tuple>
#include <string>
#include <chrono>

#define VICTORY 10000
#define DEFEAT -10000
#define POS_MAX 100000
#define POS_MIN -100000
#define N 1000000
#define DEFAULT_DEPTH_MAX 9
#define CACHE_TABLE_SIZE 3000000
#define TIME_MAX 28
#define TIME_MIN 5

enum Color {
	NONE,
	WHITE,
	BLACK
};

struct Debug {
	long long int count;
	int maxDepth, evalCount, cacheCount;
};

using namespace std;

typedef tuple<int, int, int, int> Move;
// Move[0] == 0 -> c4 : 0 c 3 4
// Move[0] == 1 -> cxd4 : 1 c d 4
// Move[0] == 2 -> cxd6 (En Passant) : 2 c d 6

string mstr(Move move);
void printTime(chrono::duration<double> sec);
void printDebug(Move move, pair<int, int> pos, Debug debug, chrono::duration<double> sec);