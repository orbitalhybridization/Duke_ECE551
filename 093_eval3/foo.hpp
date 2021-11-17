#include <cerrno>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

int validateStrInt(const char * page) {
  // check if a page number is a valid integer
  // based off of code from (man strtol(3))
  // return number, or exit failure
  // (reused from eval 2)
  char * endptr;
  long as_long = strtol(page, &endptr, 10);

  // if we don't have a number at all
  if (endptr == page) {
    //return 0;
    std::cerr << "Page number given not a number." << std::endl;
    exit(EXIT_FAILURE);
  }

  // error checking specifically for valid int
  if ((as_long <= 0) || (as_long >= ((pow(2, 8 * sizeof(int)) / 2) - 1))) {
    std::cerr << "Requested nunber " << as_long << " not a valid integer." << std::endl;
    exit(EXIT_FAILURE);
  }

  // error checking from man strtol(3)
  // check if outside of range of possible long or some other error
  errno = 0;
  if ((errno == ERANGE && (as_long == LONG_MAX || as_long == LONG_MIN)) ||
      (errno != 0 && as_long == 0)) {
    std::cerr << "Requested nunber " << as_long << " not a valid integer." << std::endl;
    exit(EXIT_FAILURE);
  }

  // otherwise we have a valid int, so return it as an int!
  int return_int = as_long;
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

  friend std::ostream & operator<<(
      std::ostream & s,
      const Choice & rhs);  // overload << operator for Choice
};

class Page {
  // Private members
  void setText() {
    // set text of Page

    //    ignore the stuff we don't want, everything after #
    skipLine();

    // get lines of story, just read until eof
    while (file.peek() != -1) {
      text += file.get();
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
    }
  }

  const char * filename;  // save filename
  std::ifstream file;
  //std::vector<std::string> text;  // story text of page
  std::string text;             // story text of page
  std::vector<Choice> choices;  // choices from first section
  std::pair<bool, char> EOS;    // end of story (win/lose condition)

 public:
  Page() :
      filename(""),
      file(NULL),
      text(""),
      EOS(std::make_pair(false, '\0')) {}  // default ctor

  Page(const char * fname) try : filename(fname),
                                 file(fname),
                                 text(""),
                                 EOS(std::make_pair(false, '\0')) {  // constructor

    // get exceptions from init
    file.exceptions(std::ifstream::failbit);  // from basic_ios exceptions cppreference

    // check for a win/lose condition by peeking
    char first_char = file.peek();
    if ((first_char == 'L') or (first_char == 'W')) {
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
  // error checking
  // also might be std::ios_base::failure
  catch (const std::ifstream::failure & e) {  // from ifstream exceptions cppreference
    std::cerr << "Unable to open/read " << fname << std::endl;
    //    exit(EXIT_FAILURE);
    throw;  // rethrow to caller (story)
  }

  Page(const Page & rhs) :
      filename(rhs.filename),
      file(rhs.filename),
      text(rhs.text),
      choices(rhs.choices),
      EOS(rhs.EOS) {}  // copy ctor

  virtual ~Page() {  // destructor
  }
  std::string getText() { return text; }
  // get private field, text

  std::vector<Choice> getChoices() { return choices; }
  // get private field, choices

  friend std::ostream & operator<<(std::ostream & s,
                                   const Page & rhs);  // overload << operator for Page

  void skipLine() {
    // skip to next line
    // from istream ignore in c plusplus ref
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
};

class Story {
 private:
  std::vector<Page> pages;
  std::string directory_name;

 public:
  Story();
  Story(std::string directory) try : directory_name(directory) {
    std::string page_number_s = "1";
    int page_number_i = 1;
    std::string page_filename = "story1.txt";
    std::stringstream s;
    // read pages
    // we can read pages as long as they're valid ints
    while (validateStrInt(page_number_s.c_str())) {
      Page new_page = Page(page_filename.c_str());  // create page from filename

      s << page_number_i;
      page_number_s = s.str();
      page_filename = "story" + s.str() + ".txt";

      // check if we can open

      //      if (!checkPage && (page_number_i == 1)) {
      //std::cerr << "Page 1 doesn't exist!" << std::endl;
      //exit(EXIT_FAILURE);
      //}

      if (!checkPage) {
        break;
      }

      // otherwise increment page number and add page to list
      page_number_i++;
      pages.push_back(new_page);
    }

    validatePages();
  }
  // error check files opening
  catch (const std::ifstream::failure & e) {  // from ifstream exceptions cppreference
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }

  bool validatePages(){

      //make sure every page referenced by a choice is valid

      // every page (except 1) must be referenced by some other pages choices

      // must have a win page and a los page

  };

  void read() {
    //current_page = page1;
    //display page1

    // while page.win[0] == False {
    // if WIN or LOSE exit successfully

    // otherwise read a number from the user (if not a number or not a valid choice
    // e.g. it is larger than the length of pages vector)
    // then prompt with message "That is not a valid choice, please try again."
    // repeat until valid choice

    // current_page = cin page;
  }

  ~Story(){};
  //friend std::ostream & operator<<(std::ostream & s, const Story & rhs);
};

//std::ostream & operator<<(std::ostream & s, const Story & rhs) {
return s;
//}

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
