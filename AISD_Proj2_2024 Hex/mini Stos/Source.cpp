#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
std::string test_list[] = {
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"11",
	"16"
};

void main() {
	auto oldbuf = std::cout.rdbuf();
	//check if 2 files have the same contents, list differences if any
	
	for (std::string test : test_list) {
		bool identical = true;
		std::ifstream file1("..\\AISD_Proj2_2024 Hex\\" + test + ".out.txt");
		std::ifstream file2("..\\AISD_Proj2_2024 Hex\\" + (std::string)"my_" + test + ".out");
		//std::ofstream fileOut("..\\AISD_Proj2_2024 Hex\\test.out");
		std::ofstream fileOut(test + ".out");
		std::cout.rdbuf(fileOut.rdbuf());
		std::string line1, line2;
		int lineNum = 0;
		while (std::getline(file1, line1) && std::getline(file2, line2)) {
			lineNum++;
			if (line1 != line2) {
				identical = false;
				std::cout << "Test " << (lineNum+1)/2 << " differs:\n";
				std::cout << "File 1: " << line1 << "     ";
				std::cout << "File 2: " << line2 << std::endl;
			}
		}
		if (std::getline(file1, line1) || std::getline(file2, line2)) {
			std::cout << "Files have different number of lines";

		}
		if(identical) {
			std::cout << "Tests " + test + " are identical\n";
			std::ofstream fileOut("summary.out");
			std::cout.rdbuf(fileOut.rdbuf());
			std::cout << "Tests " + test + " are identical\n";
			std::cout.rdbuf(oldbuf);
			std::cout << "Tests " + test + " are identical\n";
		}
		else {
			std::cout << "Tests " + test + " are different\n";
			std::ofstream fileOut("summary.out");
			std::cout.rdbuf(fileOut.rdbuf());
			std::cout << "Tests " + test + " are different\n";
			std::cout.rdbuf(oldbuf);
			std::cout << "Tests " + test + " are different\n";
		}
		file1.close();
		file2.close();
	}
}