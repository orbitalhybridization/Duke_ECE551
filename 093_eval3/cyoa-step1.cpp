#include <cstdlib>

#include "foo.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Correct usage: ./cyoa-step1 [story file]" << std::endl;
    exit(EXIT_FAILURE);
  }

  Page page = Page(argv[1]);
  page.openFile();
  page.parsePage();
  std::cout << page << std::endl;  // print page
  std::cout << "OOGABOOGA" << std::endl;
  return EXIT_SUCCESS;
}
