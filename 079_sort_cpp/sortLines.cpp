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

    std::string line;
    while (std::getline(std::cin, line, '\n')) {
      if (!std::cin.good()) {  // error check
        std::cin.clear();
        std::string badinput;
        std::cin >> badinput;
        if (!std::cin.good()) {
          std::cerr << "Bad read from stdin." << std::endl;
          exit(EXIT_FAILURE);
        }
        else {
          std::cerr << "Oops." << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      lines.push_back(line);  // otherwise push back line
    }
    std::sort(lines.begin(), lines.end());       // sort line
    for (size_t i = 0; i < lines.size(); i++) {  // print
      std::cout << lines[i] << std::endl;
    }
  }

  else {  // otherwise fill lines differently
    for (int i = 1; i < argc; i++) {
      lines.clear();  // clear for a new day!
      std::string line;
      std::ifstream file(argv[i]);
      // open file for reading

      while (std::getline(file, line, '\n')) {
        if (!file.good()) {  // error checking
          file.clear();
          std::string badinput;
          file >> badinput;
          if (!file.good()) {
            std::cerr << "File not opening properly" << std::endl;
            exit(EXIT_FAILURE);
          }
          else {
            std::cerr << "oops!" << std::endl;
          }
        }
        lines.push_back(line);  // otherwise add to container as normal
      }
      std::sort(lines.begin(), lines.end());  // sort lines when done and print

      for (size_t i = 0; i < lines.size(); i++) {
        std::cout << lines[i] << std::endl;
      }
    }
  }

  return EXIT_SUCCESS;
}
