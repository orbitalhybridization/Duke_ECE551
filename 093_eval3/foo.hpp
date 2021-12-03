#include <string.h>

#include <cerrno>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

int validateStrInt(const char * page) {
  // check if a page number is a valid integer
  // based off of code from (man strtol(3))
  // return number, or exit failure
  // (reused from eval 2)
  char * endptr;
  long as_long = strtol(page, &endptr, 10);
  int return_int;

  // if we don't have a number at all
  if (endptr == page) {
    //return 0;
    //std::cerr << "Page number given not a number." << std::endl;
    //exit(EXIT_FAILURE);
    return 0;
  }

  // error checking specifically for valid int
  if ((as_long <= 0) || (as_long >= INT_MAX)) {
    return 0;
    //std::cerr << "Requested nunber " << as_long << " not a valid integer." << std::endl;
    //exit(EXIT_FAILURE);
  }

  // error checking from man strtol(3)
  // check if outside of range of possible long or some other error
  errno = 0;
  if ((errno == ERANGE && (as_long == LONG_MAX || as_long == LONG_MIN)) ||
      (errno != 0 && as_long == 0)) {
    return 0;
    //    std::cerr << "Requested nunber " << as_long << " not a valid integer." << std::endl;
    //exit(EXIT_FAILURE);
  }

  // otherwise we have a valid int, so return it as an int!
  return_int = as_long;

  return return_int;
}

class Choice {
 private:
  int page_num;
  std::string description;

 public:
  Choice() : page_num(-1), description("") {}  // default constructor
  Choice(std::string line) {
    // constructor with a line, should be parsed on construction
    // parse choice into page_num and description

    // find index of ':'
    int index = line.find(':');
    if (index == -1) {  // if there's no :, we have an invalid choice
      std::cerr << "No colon on line for navigation." << std::endl;
      exit(EXIT_FAILURE);
    }

    std::string page_num_s = line.substr(0, index);  // take number

    page_num =
        validateStrInt(page_num_s.c_str());  // get the c string and try to make an int

    description = line.substr(index + 1,
                              line.size() - 1);  // set description (does this have \0)?
  }

  ~Choice(){};  // destructor

  Choice(const Choice & rhs) :
      page_num(rhs.page_num),
      description(rhs.description) {}  // copy ctor

  int getPageNum() { return page_num; }
  friend std::ostream & operator<<(
      std::ostream & s,
      const Choice & rhs);  // overload << operator for Choice
};

class Page {
  // Private members
  void setText() {
    // set text of Page
    // return true if set properly, otherwise return false

    // ignore the stuff we don't want, everything after #
    skipLine();

    // get lines of story, just read until eof
    while (file.peek() != -1) {
      text += file.get();
      if (!file.good()) {
        std::cerr << "Could not read file!" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  }

  void setChoices() {
    // find and parse choices of a story page
    // this is the first thing we do when creating a page

    // read a line
    std::string current_line;
    while (file.peek() != '#') {                // go until we get to page description
      std::getline(file, current_line, '\n');   // get line of choice
      choices.push_back(Choice(current_line));  // add choice
      current_line.clear();                     // empty for next line
      if (!file.good()) {
        std::cerr << "File choices could not be read!" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  }

  const char * filename;  // save filename
  std::ifstream file;
  std::string text;             // story text of page
  std::vector<Choice> choices;  // choices from first section
  std::pair<bool, char> EOS;    // end of story (win/lose condition)
  int page_num;

 public:
  Page() :
      //      filename(strdup("")),
      filename(""),
      file(NULL),
      text(""),
      EOS(std::make_pair(false, '\0')),
      page_num(0) {}  // default ctor

  Page(const char * fname) :
      //filename(strdup(fname)),
      filename(fname),
      text(""),
      EOS(std::make_pair(false, '\0')) {  // constructor
  }

  Page(const char * fname, int num) :
      //filename(strdup(fname)),
      filename(fname),
      text(""),
      EOS(std::make_pair(false, '\0')),
      page_num(num) {  // constructor
  }

  void parsePage() {
    // try to open
    if (!file.is_open()) {
      std::cerr << "File not open!" << std::endl;
      exit(EXIT_FAILURE);
    }

    // check for a win/lose condition by peeking
    char first_char = file.peek();
    if ((first_char == 'L') or (first_char == 'W')) {
      if (!file.good()) {  // do error checking
        std::cerr << "File could not be read/opened!" << std::endl;
        exit(EXIT_FAILURE);
      }

      EOS.first = true;
      EOS.second = first_char;
      skipLine();  // skip win/lose line
    }
    else {  // otherwise we have choices so set them
      setChoices();
    }

    // then set the text
    setText();
    file.close();
  }

  Page(const Page & rhs) :
      //      filename(strdup(rhs.filename)),
      filename(rhs.filename),
      file(rhs.filename),
      text(rhs.text),
      choices(rhs.choices),
      EOS(rhs.EOS),
      page_num(rhs.page_num) {}  // copy ctor

  virtual ~Page() {  // destructor
  }
  std::string getText() { return text; }
  // get private field, text

  std::vector<Choice> getChoices() { return choices; }
  // get private field, choices

  std::vector<Choice> getChoices() const { return choices; }
  bool openFile() {
    // attempt to open file
    file.open(filename);
    if (file.good()) {
      return true;
    }
    return false;
  }

  friend std::ostream & operator<<(std::ostream & s,
                                   const Page & rhs);  // overload << operator for Page

  void skipLine() {
    // skip to next line
    // from istream ignore in c plusplus ref
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  bool operator==(const Page & rhs) const {
    //define == operator
    if (strcmp(rhs.filename, filename) == 0) {
      return true;
    }
    return false;
  }

  bool isEOS() const { return EOS.first; }

  bool isWin() const { return EOS.second == 'W'; }

  bool isLose() const { return EOS.second == 'L'; }

  void setNum(int n) { page_num = n; }

  int getNum() const { return page_num; }
};

class Story {
 private:
  std::vector<Page> pages;
  std::string directory_name;

 public:
  Story();
  Story(std::string directory) : directory_name(directory) {
    // containers for building filename
    // std::string page_number_s;
    int page_number_i = 1;
    std::string page_filename;
    std::stringstream page_number_s;  // page number in string forme
    // read pages
    // we can read pages as long as they're valid ints
    while (page_number_i <= INT_MAX) {
      //while (validateStrInt(page_number_s.str().c_str())) {
      // build filename
      page_number_s << page_number_i;
      page_filename = directory_name + "/page" + page_number_s.str() + ".txt";

      Page new_page =
          Page(page_filename.c_str(), page_number_i);  // create page from filename

      // check if we can open
      bool open_success = new_page.openFile();

      if ((!open_success) && (page_number_i == 1)) {  // check if there's a page 1
        std::cerr << "Page 1 doesn't exist!" << std::endl;
        exit(EXIT_FAILURE);
      }

      if (!open_success) {  // if we haven't a consecutive page then we're done with the story
        break;
      }

      // otherwise increment page number and add page to list
      new_page.parsePage();  // fill members/fields
      //new_page.setNum(page_number_i);
      page_number_i++;
      page_number_s.str("");  // empty container
      pages.push_back(new_page);
    }
    if (page_number_i == INT_MAX) {
      std::cout << "Reached all readable story pages. This is a long ass story!"
                << std::endl;
    }
    validatePages();
  }

  void validatePages() {
    //make sure every page referenced by a choice is valid

    // set up variables that willl help us validate this story!
    bool win = false;
    bool lose = false;  // keep track of whether we have a win/loss

    // page_ref : a vector for keeping track of which pages are referenced
    std::vector<int> page_ref;
    for (size_t i = 2; i <= pages.size(); i++) {
      page_ref.push_back(i);
    }

    for (size_t i = 0; i < pages.size(); i++) {  // loop through all pages

      pages[i];
      if (pages[i].isWin()) {  // check for win/loss
        win = true;
      }
      else if (pages[i].isLose()) {
        lose = true;
      }

      // loop through choices and make sure they reference valid pages
      for (size_t j = 0; j < pages[i].getChoices().size(); j++) {
        Choice curr_choice = pages[i].getChoices()[j];
        if (curr_choice.getPageNum() > int(pages.size())) {
          std::cerr << "Choice references invalid page " << curr_choice.getPageNum()
                    << std::endl;
          exit(EXIT_FAILURE);
        }

        // remove referenced page from page_ref
        std::vector<int>::iterator index =
            findElementInIntVector(curr_choice.getPageNum(), page_ref);
        if (index != page_ref.end()) {  // check if it's in the page ref
          page_ref.erase(index);
        }
      }
    }

    if ((!win) || (!lose)) {  // check if win or loss
      std::cerr << "No win or loss page." << std::endl;
      exit(EXIT_FAILURE);
    }

    if (!page_ref.empty()) {  // check if all pages references
      std::cerr << "Some pages aren't referenced : \n";
      for (size_t i = 0; i < page_ref.size(); i++) {
        std::cerr << "\t- " << page_ref[i] << "\n";
      }
      std::cerr << std::endl;
    }
  }

  void read() {
    int page_int = 0;
    //display page1

    std::cout << pages[page_int] << std::endl;

    while (!pages[page_int].isEOS()) {  // go until final page

      // otherwise read a number from the user (if not a number or not a valid choice
      // e.g. it is larger than the length of pages vector)
      std::string user_response;
      getline(std::cin, user_response);  // read input

      if (!std::cin.good()) {
        std::cerr << "Something went wrong with input." << std::endl;
        exit(EXIT_FAILURE);
      }

      int response_int = validateStrInt(user_response.c_str());
      if ((response_int == 0) || (response_int > int(pages.size()))) {  // not valid int
        std::cout << "That is not a valid choice, please try again." << std::endl;
        continue;
        // repeat until valid choice
      }

      // otherwise we have a valid integer so we can just continue the loop
      else {  // find the page of the choice chosen and print it
        page_int = pages[page_int].getChoices()[response_int - 1].getPageNum() - 1;
        std::cout << pages[page_int] << std::endl;
      }
    }
  }

  std::vector<int>::iterator findElementInIntVector(int num, std::vector<int> & vec) {
    for (std::vector<int>::iterator i = vec.begin(); i != vec.end(); i++) {
      if (*i == num) {
        return i;
      }
    }
    return vec.end();
  }
  Story & operator=(const Story & rhs) {
    directory_name = rhs.directory_name;
    // containers for building filename
    // std::string page_number_s;
    int page_number_i = 1;
    std::string page_filename;
    std::stringstream page_number_s;  // page number in string forme
    // read pages
    // we can read pages as long as they're valid ints
    while (page_number_i <= INT_MAX) {
      //while (validateStrInt(page_number_s.str().c_str())) {
      // build filename
      page_number_s << page_number_i;
      page_filename = directory_name + "/page" + page_number_s.str() + ".txt";

      Page new_page =
          Page(page_filename.c_str(), page_number_i);  // create page from filename

      // check if we can open
      bool open_success = new_page.openFile();

      if ((!open_success) && (page_number_i == 1)) {  // check if there's a page 1
        std::cerr << "Page 1 doesn't exist!" << std::endl;
        exit(EXIT_FAILURE);
      }

      if (!open_success) {  // if we haven't a consecutive page then we're done with the story
        break;
      }

      // otherwise increment page number and add page to list
      new_page.parsePage();  // fill members/fields
      //      new_page.setNum(page_number_i);
      page_number_i++;
      page_number_s.str("");  // empty container
      pages.push_back(new_page);
    }
    if (page_number_i == INT_MAX) {
      std::cout << "Reached all readable story pages. This is a long ass story!"
                << std::endl;
    }
    validatePages();
    return *this;
  }

  Story(Story & rhs) : directory_name(rhs.directory_name) {
    // containers for building filename
    // std::string page_number_s;
    int page_number_i = 1;
    std::string page_filename;
    std::stringstream page_number_s;  // page number in string forme
    // read pages
    // we can read pages as long as they're valid ints
    while (page_number_i <= INT_MAX) {
      //while (validateStrInt(page_number_s.str().c_str())) {
      // build filename
      page_number_s << page_number_i;
      page_filename = directory_name + "/page" + page_number_s.str() + ".txt";

      Page new_page =
          Page(page_filename.c_str(), page_number_i);  // create page from filename

      // check if we can open
      bool open_success = new_page.openFile();

      if ((!open_success) && (page_number_i == 1)) {  // check if there's a page 1
        std::cerr << "Page 1 doesn't exist!" << std::endl;
        exit(EXIT_FAILURE);
      }

      if (!open_success) {  // if we haven't a consecutive page then we're done with the story
        break;
      }

      // otherwise increment page number and add page to list
      new_page.parsePage();  // fill members/fields
      page_number_i++;
      page_number_s.str("");  // empty container
      pages.push_back(new_page);
    }
    if (page_number_i == INT_MAX) {
      std::cout << "Reached all readable story pages!" << std::endl;
    }

    validatePages();

  }  // copy ctor

  void displayPaths() {
    // here I used the dfs example from the book 25.3.3
    // build the multiple paths
    std::vector<Choice> choices_from_start = pages[0].getChoices();
    bool unwinnable = true;  // story unwinnable unless proven otherwise

    for (size_t i = 0; i < choices_from_start.size();
         i++) {  // iterate through choices from start
      std::vector<std::vector<std::pair<int, int> > > paths = displayPathsHelper(
          std::make_pair(0, i));  // make a pair for each choice from start

      for (size_t k = 0; k < paths.size(); k++) {
        std::vector<std::pair<int, int> > path = paths[k];

        for (size_t j = 0; j < path.size(); j++) {  // print path if viable
          if (path[j].first == -1) {                // if not viable path, skip printing
            continue;
          }
          else {
            unwinnable = false;
            std::cout << path[j].first + 1 << "(";

            if (path[j].second == -1) {  // win case
              std::cout << "win"
                        << ")" << std::endl;
            }

            else {  // regular case
              std::cout << path[j].second + 1 << "),";
            }
          }
        }
      }
    }
    // if no viable paths from start, story is unwinnable
    if (unwinnable) {
      std::cout << "This story is unwinnable!" << std::endl;
    }
  }

  std::vector<std::vector<std::pair<int, int> > > displayPathsHelper(
      std::pair<int, int> start) {
    // helper function that does the queue calls
    // here I used the bfs example from the book 25.3.3

    // vector for winning paths since there can be multiple paths per divergence from start
    std::vector<std::vector<std::pair<int, int> > > winning_paths;

    std::vector<std::pair<int, int> > startingPath;
    startingPath.push_back(start);  // create initial path with just start node
    std::stack<std::vector<std::pair<int, int> > > paths;  // stack for paths
    std::set<std::pair<int, int> > visited;
    paths.push(startingPath);

    while (!paths.empty()) {
      std::vector<std::pair<int, int> > currentPath = paths.top();
      paths.pop();
      std::pair<int, int> currentPage = *(currentPath.end() - 1);

      if (pages[currentPage.first].isWin()) {  // if we're at a winning page, then add
        winning_paths.push_back(currentPath);
        continue;  // continue because we dont need to process
      }

      if (visited.find(currentPage) == visited.end()) {  // if not in visited
        visited.insert(visited.end(), currentPage);      // add to end
      }

      std::vector<Choice> choices = pages[currentPage.first].getChoices();

      // get the page this is leading to
      int next_page_num = choices[currentPage.second].getPageNum() - 1;

      //      std::cout << "Current page " << currentPage.first + 1 << "." << std::endl;
      //      std::cout << "Choice number is " << currentPage.second + 1 << "." << std::endl;

      std::vector<Choice> next_page_choices = pages[next_page_num].getChoices();
      //      std::cout << "So next page " << next_page_num + 1 << "." << std::endl;

      if (pages[next_page_num]
              .isWin()) {  // if we're at a win, just add it to current path
        std::vector<std::pair<int, int> > newPath = currentPath;
        newPath.push_back(std::make_pair(next_page_num, -1));
        paths.push(newPath);
      }

      else {  // otherwise add all possible choices
        for (size_t i = 0; i < next_page_choices.size();
             i++) {  // add paths with other nodes

          std::vector<std::pair<int, int> > newPath = currentPath;
          //  std::cout << "Adding choice " << i + 1 << " of page " << next_page_num + 1
          //                    << " which is page " << next_page_choices[i].getPageNum()
          //        << std::endl;
          newPath.push_back(std::make_pair(next_page_num, i));
          paths.push(newPath);
        }
      }
    }
    // end while loop
    if (winning_paths.empty()) {  // case: no winning paths
      std::vector<std::pair<int, int> > no_path;
      no_path.push_back(std::make_pair(-1, -1));  // no valid path

      std::vector<std::vector<std::pair<int, int> > > no_path_vec;

      no_path_vec.push_back(no_path);
      return no_path_vec;
    }
    else {
      return winning_paths;
    }
  }

  void displayPageDepths() {
    // run breadth first search on pages
    std::vector<int> depths;
    for (size_t i = 0; i < pages.size(); i++) {
      // do bfs for all pages
      int depth = pageDepthsHelper(&pages[0], &pages[i]);
      std::cout << "Page " << i + 1;
      if (depth >= 0) {  // print normally if page is reachable
        std::cout << ":" << depth << std::endl;
      }
      else {
        std::cout << " is not reachable" << std::endl;
      }
    }
    return;
  }

  int pageDepthsHelper(const Page * start, const Page * end) {
    // helper function that does the queue calls
    // here I used the bfs example from the book 25.3.3
    std::vector<const Page *> startingPath;
    startingPath.push_back(start);  // create initial path with just start node
    std::queue<std::vector<const Page *> > paths;  // queue for paths
    std::set<const Page *> visited;
    paths.push(startingPath);
    while (!paths.empty()) {
      std::vector<const Page *> currentPath = paths.front();
      //      std::cout << currentPath.size() << std::endl;
      paths.pop();
      const Page * currentPage = *(currentPath.end() - 1);
      if (currentPage->getNum() ==
          end->getNum()) {  // if we're at desired, then we're done
        return currentPath.size() - 1;
      }
      if (visited.find(currentPage) == visited.end()) {  // if not in visited
        visited.insert(visited.end(), currentPage);      // add to end
      }
      std::vector<Choice> choices = currentPage->getChoices();
      for (size_t i = 0; i < choices.size(); i++) {  // add paths with other nodes
        //        Choice choice = choices[i];
        //Page * page_to_add = &pages[choice.getPageNum() - 1];
        std::vector<const Page *> newPath = currentPath;
        //        currentPath.push_back(&page_to_add);
        //newPath.push_back(&page_to_add);
        newPath.push_back(&pages[choices[i].getPageNum() - 1]);
        paths.push(newPath);
      }
    }
    return -1;  // case, no valid path
  }

  ~Story(){};
};

std::ostream & operator<<(std::ostream & s,
                          const Page & rhs) {  // overload << operator for proper printing

  // print story text
  s << rhs.text << std::endl;

  if (!rhs.EOS.first) {  // if not win or lose then print choices

    s << "What would you like to do?"
      << "\n"
      << std::endl;

    for (size_t i = 0; i < rhs.choices.size() - 1; i++) {
      s << " " << i + 1 << ". " << rhs.choices[i] << std::endl;
    }
    // the last one doesn't have a newline
    s << " " << rhs.choices.size() << ". " << rhs.choices[rhs.choices.size() - 1];
  }

  else {  // otherwise we've won/lost
    if (rhs.EOS.second == 'W') {
      s << "Congratulations! You have won. Hooray!";
    }
    else if (rhs.EOS.second == 'L') {
      s << "Sorry, you have lost. Better luck next time!";
    }
  }

  return s;
}

std::ostream & operator<<(std::ostream & s,
                          const Choice & rhs) {  // print choices as outlined in README
  s << rhs.description;

  return s;
}
