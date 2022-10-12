#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class LoadCSV
{
	std::string str_buf;
	std::string str_conma_buf;
	std::string input_csv_file_path;
	std::string output_csv_file_path;

	
	LoadCSV();
	void ReadCSV(std::string filename);
	void Update();
};

