#include <fstream>
#include <string>
#include <vector>
class Choice {
 private:
  int page_num;
  std::string description;

 public:
  Choice();                  // default ctor
  Choice(std::string line);  // constructor with a line, shoudl be parsed on construction
  virtual ~Choice();         // destructor

  Choice(const Choice & rhs);  // copy ctor

  Choice & operator=(const Choice & rhs);  // assignemnt operator

  int getPageNum();  // just get the page num of a choice

  friend std::ostream & operator<<(std::ostream & s,
                                   const Choice & rhs);  // stream insertion
};

class Page {
  const char * filename;  // save filename
  std::ifstream file;
  std::string text;             // story text of page
  std::vector<Choice> choices;  // choices from first section
  std::pair<bool, char> EOS;    // end of story (win/lose condition)
  int page_num;

  void setText();  // set text of page

  void setChoices();  // find and parse choices of a story page
 public:
  Page();  // default ctor

  Page(const char * fname);  // ctor with just a filename

  Page(const char * fname, int num);  // ctor with filename and number

  Page(const Page & rhs);  // copy ctor

  Page & operator=(const Page & rhs);  // assignemnt op

  virtual ~Page();  // destructor

  void parsePage();  // parse contents of text file

  std::string getText();  // get text of this page

  std::vector<Choice> getChoices();  // get choices of this page

  std::vector<Choice> getChoices() const;

  bool openFile();  // attempt to open associated file

  friend std::ostream & operator<<(std::ostream & s,
                                   const Page & rhs);  // stream inerstion

  void skipLine();  // skip to next line

  bool operator==(const Page & rhs) const;  // compare pages

  bool isEOS() const;  // check if is end of story

  bool isWin() const;  // check if win page

  bool isLose() const;  // check if lose page

  void setNum(int n);  // set page num

  int getNum() const;  // get page number
};

class Story {
 private:
  std::vector<Page> pages;

  std::string directory_name;

  Story();  // default ctor

  Story(std::string directory);  // ctor with directory

  void validatePages();  // validate pages under assignment criteria

  void read();  // read pages interactively

  std::vector<int>::iterator findElementInIntVector(
      int num,
      std::vector<int> & vec);  // find element

  Story & operator=(const Story & rhs);  // assignment operator

  Story(Story & rhs);  // copy ctor

  void displayPaths();  // run depth first search

  std::vector<std::vector<std::pair<int, int> > > displayPathsHelper(
      std::pair<int, int>
          start);  // helper function that does most of calls for displayPaths

  void displayPageDepths();  // run breadth-first search on pages

  int pageDepthsHelper(const Page * start,
                       const Page * end);  // helper function that finds depths

  virtual ~Story();  // destructor
};
