#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <vector>
#include <cassert>
#include <DirectXMath.h>

class LoadCSV
{
	std::string str_buf;
	std::string str_conma_buf;
	std::string input_csv_file_path;
	std::string output_csv_file_path;

	void ReadCSV(std::string filename);
	
	void Output();
	void Input();

	LoadCSV();
	void Update();
};

