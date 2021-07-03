#pragma once
#include "util.h"

bool isWinner(Color turn);
bool isGameOver();
bool isPassedPawn(int i, int j, Color turn);
bool isFrozenPawn(int i, int j, Color turn);
int evaluatePosition(Color turn);