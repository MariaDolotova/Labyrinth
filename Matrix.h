#pragma once
#include "pch.h"
#include <fstream>
#include <vector>
#include <queue>

class Matrix {


	std::vector<int> matrix;  // grid with 0 and 1
	std::vector<bool> visited; // vector with processed cells
	std::vector<bool> marked;  // vector with marked but not processed cells
	std::queue<int> waveQueue;
	int startX=0, startY=0, finishX=0, finishY=0;
	int lines=0;
	int columns=0;

public:

	Matrix(std::ifstream& file);
	void PrintMatrix();
	int MinTurns(int sx, int sy, int fx, int fy);
	int GetLines() { return lines; }
	int GetColumns() { return columns; }


};
