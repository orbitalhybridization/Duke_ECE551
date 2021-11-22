#include <cstdlib>

#include "foo.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Correct usage: ./cyoa-step2 [directory name]" << std::endl;
    exit(EXIT_FAILURE);
  }

  Story story(argv[1]);
  story.bfs();  // do bfs on story pages

  return EXIT_SUCCESS;
}
