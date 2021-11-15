#include <cstdlib>

#include "foo.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Correct usage: ./cyoa-step2 [directory name]" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << Story(argv[1]) << std::endl;  // print page

  return EXIT_SUCCESS;
}
