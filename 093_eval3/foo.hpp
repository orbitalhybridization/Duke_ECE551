#include <string>
#include <vector>

class Page {
 private:
  class Choice {
   private:
    int page_num;
    std::string description;

   public:
    std::ostream & operator<<(
        const Choice & rhs);  // overload << operator for proper printing

    Choice(std::string);  // constructor with a line, should be parsed on construction
    ~Choice();            // destructor
  };
  char * filename;  // save filename
  std::vector<std::string *> text;
  std::vector<Choice *> choices;

 public:
  Page(char * fname) : filename(fname) {  // constructor
    // open page
    // we need error checking
  }

  bool parse();  // open page, return true if done, false if not

  virtual ~Page() {  // destructor
  }

  void setText();  // set text of Page

  void getText();

  void getChoices();  // return choices

  friend std::ostream & operator<<(
      const Page & rhs);  // overload << operator for proper printing
};
