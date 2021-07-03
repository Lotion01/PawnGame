#pragma once
#include "util.h"
#include <string>
#include <vector>

void playMove(string move, vector<Move>& table);
void playMove(Move move);
void undoMove(Move move);
vector<Move> findLegalMove();
bool isLegalMove(string move, vector<Move> table);
void changeTurn();
bool isPlayerTurn();