#include <cstdlib>

#include "foo.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Correct usage: ./cyoa-step2 [directory name]" << std::endl;
    exit(EXIT_FAILURE);
  }

  Story story = Story(argv[1]);
  story.read();

  return EXIT_SUCCESS;
}
