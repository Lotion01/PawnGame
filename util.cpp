#include "util.h"

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