#include <cerrno>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

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
    page_num = validatePageInteger(
        page_num_s.c_str());  // get the c string and try to make an int

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

  int validatePageInteger(const char * page) {
    // check if a category name is a number
    // based off of code from (man strtol(3))
    // return 0 if not, otherwise return number
    // (reused from eval 2)
    char * endptr;
    long as_long = strtol(page, &endptr, 10);

    // if we don't have a number at all
    if (endptr == page) {
      return 0;
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
};

class Page {
  // Private members
  void setText() {
    // set text of Page

    //    ignore the stuff we don't want, everything after #
    file.ignore(std::numeric_limits<std::streamsize>::max(),
                '\n');  // from istream ignore in cpp reference
                        // might have to do a get() here to pass \n

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
      file.ignore(std::numeric_limits<std::streamsize>::max(),  // skip to # line
                  '#');  // from istream ignore in cpp reference
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
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
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
