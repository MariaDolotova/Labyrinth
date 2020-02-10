#include "pch.h"
#include "Matrix.h"
#include <iostream>

Matrix::Matrix(std::ifstream& file) {

	file >> lines;
	file >> columns;

	matrix.reserve(lines*columns);

	for (unsigned l = 0; l < lines; ++l)  	// filling vector with data from file
	{
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		for (unsigned c = 0; c < columns; ++c)
		{

			int x = (int)file.get();
			matrix.push_back(x - 48);
			visited.push_back(false);
			marked.push_back(false);

		}
	}



}


void Matrix::PrintMatrix() {

	std::cout << std::endl << "lines" << lines << std::endl;
	std::cout << "columns" << columns << std::endl << std::endl;

	for (unsigned l = 0; l < lines; ++l) 	// printing matrix
	{
		for (size_t c = 0; c < columns; c++)
		{

			std::cout << matrix[l*columns + c];

		}
		std::cout << "\n";

	}

	std::cout << std::endl;


};



int Matrix::MinTurns(int sx, int sy, int fx, int fy) {

	startX = sx, startY = sy, finishX = fx, finishY = fy;
	int res = -1;
	int index = startX * columns + startY; // index of current cell
	int indexFinish = finishX * columns + finishY; // index of finish cell
	int maxRight, maxLeft, maxUp, maxDown, // count of steps which could be made from current cell to different directions
		lastFront = 0, // total counts of wavefronts
		lastfrontCount = 1, // count of cells to be processed in current wavefront
		nextFrontCount = 0; // count of cells in the next wavefront
	bool foundNeighbour = false;  // flag to be set if a free neighbour cell has been found
	waveQueue.push(index);
	marked[index] = true;

	while (!waveQueue.empty()) {

		for (size_t i = 0; i < lastfrontCount; i++)
		{
			index = waveQueue.front();
			waveQueue.pop();

			if (!visited[index]) {  // checking if the cell hasn't been processed before

				// counting number of steps to each direction
				maxRight = (columns - index % columns);
				maxLeft = index % columns + 1;
				maxUp = index / lines + 1;
				maxDown = (lines - index / lines);


				// check neighbours from right
				for (size_t i = 1; i < maxRight; i++)
				{
					if (matrix[index + i] != 1 && !marked[index + i]) {  // if neighbour cell is not 1 and hasn't been marked put it in a queue
						waveQueue.push(index + i);
						marked[index + i] = true; // mark the neighbour cell
						nextFrontCount++;  //increment the counter for next wavefront
						foundNeighbour = true;
						if (index + i == indexFinish) { return ++lastFront; } // if the neighbour cell is finish cell return number of wavefronts
					}
					else if (matrix[index + i] != 1 && marked[index + i]) { continue; } // continue if the cell was marked before
					else {
						break;
					}
				}


				// check neighbours from left

				for (size_t i = 1; i < maxLeft; i++)
				{
					if (matrix[index - i] != 1 && !marked[index - i]) {
						waveQueue.push(index - i);
						marked[index - i] = true;
						nextFrontCount++;
						foundNeighbour = true;
						if (index - i == indexFinish) { return ++lastFront; }

					}
					else if (matrix[index - i] != 1 && marked[index - i]) { continue; }
					else { break; }
				}



				// check up neighbours 

				for (size_t i = 1; i < maxUp; i++)
				{
					if (matrix[index - columns * i] != 1 && !marked[index - columns * i]) {
						waveQueue.push(index - columns * i);
						marked[index - columns * i] = true;
						nextFrontCount++;
						foundNeighbour = true;
						if (index - columns * i == indexFinish) { return ++lastFront; }
					}
					else if (matrix[index - columns * i] != 1 && marked[index - columns * i]) { continue; }
					else { break; }
				}


				// check down neighbours 

				for (size_t i = 1; i < maxDown; i++)
				{
					if (matrix[index + columns * i] != 1 && !marked[index + columns * i]) {
						waveQueue.push(index + columns * i);
						marked[index + columns * i] = true;
						nextFrontCount++;
						foundNeighbour = true;
						if (index + columns * i == indexFinish) { return ++lastFront; }
					}
					else if (matrix[index + columns * i] != 1 && marked[index + columns * i]) { continue; }
					else { break; }
				}


			}

			visited[index] == true;  // mark the cell as processed

		}
		if (foundNeighbour) { lastFront++; }
		lastfrontCount = nextFrontCount;  // prepare counters for the next loop
		nextFrontCount = 0;
		foundNeighbour = false;
	}
	return res;

}