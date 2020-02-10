// LabyrinthMinTurns.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "Matrix.h"


int main()
{

	int num;
	std::string paths []= {"map.txt", "map1.txt", "map2.txt"};

	while (true) {

		// user chooses the map
		while (true) {
			std::cout << "Please choose the map number from 1 to 3 or 0 to exit and press Enter" << std::endl;
			std::cin >> num;
			if (num == 0) { return 0; }
			if (num == 1 || num == 2 || num == 3) { break; }

		}

		std::ifstream file(paths[num - 1], std::ifstream::binary);


		if (file.is_open())
		{

			Matrix m(file);

			std::cout << "Printing the map... " << std::endl << std::endl;

			m.PrintMatrix();

			// user chooses start and finish points

			int sX, sY, fX, fY;

			while (true) {
				std::cout << "Please enter X for start point and press Enter. Number should be from 0 to " << m.GetLines() - 1 << std::endl;
				std::cin >> sX;
				if (sX >= 0 && sX < m.GetLines()) { break; }

			}

			while (true) {
				std::cout << "Please enter Y for start point and press Enter. Number should be from 0 to " << m.GetColumns() - 1 << std::endl;
				std::cin >> sY;
				if (sY >= 0 && sY < m.GetColumns()) { break; }

			}

			while (true) {
				std::cout << "Please enter X for finish point and press Enter. Number should be from 0 to " << m.GetLines() - 1 << std::endl;
				std::cin >> fX;
				if (fX >= 0 && fX < m.GetLines()) { break; }

			}

			while (true) {
				std::cout << "Please enter Y for finish point and press Enter. Number should be from 0 to " << m.GetColumns() - 1 << std::endl;
				std::cin >> fY;
				if (fY >= 0 && fY < m.GetColumns()) { break; }

			}

			std::cout << std::endl;

			// obtaining count of minimum moves

			int result = m.MinTurns(sX, sY, fX, fY);
			if (result != -1) {

				std::cout << "minimum number of moves: " << result << std::endl;
				std::cout << "*************************" << std::endl;

			}

			else {

				std::cout << "there is no way from point A to point B" << std::endl;
				std::cout << "*************************" << std::endl;

			}

		}

		else { std::cout << "Cannot open the file"; }

	}
	return 0;


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
