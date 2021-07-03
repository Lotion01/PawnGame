#pragma once
#include <unordered_map>

using namespace std;

static unordered_map<int, long long int> codeTable = { {37449, 0}, {37450, 1}, {37452, 2}, {37457, 3}, {37473, 4}, {37513, 5}, {37641, 6},
													{37961, 7}, {38985, 8}, {41545, 9}, {49737, 10}, {70217, 11}, {135753, 12}, {37458, 13},
													{37474, 14}, {37460, 15}, {37476, 16}, {37514, 17}, {37642, 18}, {37516, 19}, {37644, 20},
													{37962, 21}, {38986, 22}, {37964, 23}, {38988, 24}, {41546, 25}, {49738, 26}, {41548, 27},
													{49740, 28}, {70218, 29}, {135754, 30}, {70220, 31}, {135756, 32}, {37521, 33}, {37649, 34},
													{37537, 35}, {37665, 36}, {37969, 37}, {38993, 38}, {37985, 39}, {39009, 40}, {41553, 41},
													{49745, 42}, {41569, 43}, {49761, 44}, {70225, 45}, {135761, 46}, {70241, 47}, {135777, 48},
													{38025, 49}, {39049, 50}, {38153, 51}, {39177, 52}, {41609, 53}, {49801, 54}, {41737, 55},
													{49929, 56}, {70281, 57}, {135817, 58}, {70409, 59}, {135945, 60}, {42057, 61}, {50249, 62},
													{43081, 63}, {51273, 64}, {70729, 65}, {136265, 66}, {71753, 67}, {137289, 68}, {74313, 69},
													{139849, 70}, {82505, 71}, {148041, 72}, };

bool canEnPassant();
long long int encodeBoard();