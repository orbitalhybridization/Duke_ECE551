#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char ** argv) {
  std::vector<std::string> lines;  // container for lines

  if (argc == 1) {  // read from standard input
    if (!std::cin.good()) {
      std::cerr << "Bad read from standard input." << std::endl;
      exit(EXIT_FAILURE);
    }
    std::string line;
    while (std::getline(std::cin, line, '\n')) {
      lines.push_back(line);
    }
  }

  else {  // otherwise fill lines differently
    for (int i = 1; i < argc; i++) {
      std::string line;
      std::ifstream file(argv[i]);
      // open file for reading

      if (!file.good()) {
        std::cerr << "File not opening properly" << std::endl;
        exit(EXIT_FAILURE);
      }

      while (std::getline(file, line, '\n')) {
        lines.push_back(line);
      }
    }
  }

  std::sort(lines.begin(), lines.end());  // sort lines when done and print

  for (size_t i = 0; i < lines.size(); i++) {
    std::cout << lines[i] << std::endl;
  }

  return EXIT_SUCCESS;
}
