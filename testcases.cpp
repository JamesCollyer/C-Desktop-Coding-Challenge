#include <iostream>
#include <fstream>
#include "testcases.h"
#include "cMain.h"

using namespace std;

int test::compile_return(void){
	// Passes command line arguments to compile and run user_program,
	// Then store the output in result.txt
	
	std::system("g++ user_program.cpp -o user_exe");
	std::system("./user_exe > result.txt");

	// Get string from result.txt and convert to int
	int usr_output;
	std::string str_usr_output;
	std::ifstream result("result.txt");
	if (std::getline(result, str_usr_output))
		{
			usr_output = std::stoi(str_usr_output);
			return usr_output;
		}
	else
		return 100001;
	
}

// Correct solution to the problem:
int test::test_case_p1(int num, int target){
	int count = 0;
	int current = num;
	// First we determine if its possible or not
	bool is_possible = false;
	if (target % num == 0)
		is_possible = true;
	if (is_possible == false)
		return -1;
	// Now we multiply as many times as possible
	while (current * num < target)
	{
		current *= num;
		count += 1;
	}
	// Finally we add until we reach the target
	while (current != target)
	{
		current += num;
		count += 1;
	}
	return count;
}

int test::test_case_p2(int arr[][4], int height){
	int coordinates[height * 4][2];
	int count = 0;

	// check if a number is a 1 -> store its coordinates
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			if(arr[y][x] == 1)
			{
				coordinates[count][0] = x;
				coordinates[count][1] = y;
				count ++;
			}
		}
	}

	// for each coordinate, compare agianst all coordinates in the array
	int nbrs;
	int current_x;
	int current_y;
	int current_length;
	int current_cor = 0;
	int comp_coords;

	while(current_cor < count)
	{
		nbrs = 0;
		for(comp_coords = 0; comp_coords < count; comp_coords++)
			{		
				current_x = coordinates[current_cor][0] - coordinates[comp_coords][0];
				current_y = coordinates[current_cor][1] - coordinates[comp_coords][1];
				current_length = (current_x * current_x) + (current_y * current_y);

				if(current_length == 1)
				{
					nbrs ++;
				}

			}
		// removing all 1s that are not strongly connected
		if(nbrs == 0 || nbrs == 1)
			{
				// remove the coordinate from the array
				// we move the values up the array and decrement count
				for(int start = current_cor; start < count; start++)
				{
					coordinates[start][0] = coordinates[start + 1][0];
					coordinates[start][1] = coordinates[start + 1][1];
				}
 				count --;
				current_cor = 0;
				comp_coords = 0;
			}
		else
			current_cor ++;

	}
	// we now have an array of length count that containes the coordinates of strongly connected 1s
	return count;
}


