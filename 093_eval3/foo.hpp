#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

class Page {
 private:
  // Private classes
  class Choice {
   private:
    int page_num;
    std::string description;

   public:
    Choice(
        std::string line) {  // constructor with a line, should be parsed on construction
      // parse choice into page_num and description
      // find index of ':'
      int index = line.find(':');
      if (index == -1) {  // if there's no :, we have an invalid choice
        throw();
      }
      std::string page_num_s = line.substr(0, index);
      try {  // try to parse an int
        page_num = stoi(page_num_s);
      }
      catch (std::out_of_range & e) {
        std::cout << e.what() << std::endl;
      }
      catch (std::invalid_argument & e) {
        std::cout << e.what() << std::endl;
      }
      description = line.substr(index + 1,
                                line.size() - 1);  // set description (does this have \0)?
    }
    ~Choice();  // destructor
  };

  // Private members
  void setText() {  // set text of Page

    //    ignore the stuff we don't want, everything after #
    file.ignore(std::numeric_limits<std::streamsize>::max(),
                '\n');  // from basic stream ignore example
    // might have to do a get() here to pass \n
    std::getline(file, );
  }

  void setChoices() {
    // find and parse choices of a story page
    // this is the first thing we do when creating a page

    // read a line
    std::string current_line;
    while (file.peek() != '#') {  // go until we get to page description
      std::getline(file, current_line, '\n');
      Choice(current_line);
      current_line.clear();  // empty for next line
    }
  }

  const char * filename;  // save filename
  std::ifstream file;
  std::vector<std::string> text;  // story text of page
  std::vector<Choice *> choices;
  bool EOS;  // end of story (win/lose condition)

 public:
  Page(const char * fname) try : filename(fname),
                                 file(fname),
                                 EOS(false) {  // constructor
    file.exceptions(std::ifstream::failbit);   // from basic_ios exceptions cppreference

    char first_char = file.peek();
    // check for a win/lose condition by peeking
    if ((first_char == 'L') or (first_char == 'W')) {
      EOS = true;
    }
    else {  // otherwise we have choices so set them
      setChoices();
    }
    setText();
  }
  // error checking
  catch (const std::ios_base::failure & e) {  // from basic ios exceptions cppreference
    std::cout << e.what() << std::endl;
  }
}

  bool validateFileStream(std::fstream & stream) {
  if (!stream.good()) {
    return 0;
  }
}
bool parse();  // open page, return true if done, false if not

virtual ~Page() {  // destructor
}

void parseChoice();

void getText();

void getChoices();  // return choices

friend std::ostream & operator<<(
    std::ostream & s,
    const Choice & rhs);  // overload << operator for proper printing
}
;

std::ostream & operator<<(std::ostream & s,
                          const Page & rhs);  // overload << operator for proper printing

std::ostream & operator<<(std::ostream & s, const Page::Choice & rhs);
