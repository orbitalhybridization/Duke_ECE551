#include "rand_story.h"

/*


Step 1
===========================================================================

Write the program story-step1, which takes one command line argument: the
name of the file to read the story template from. This program should parse
the story template by printing the story and replacing blanks with the word
"cat". Your code should call the provided function chooseWord, for this
step passing in NULL as the second argument to get return value "cat".

For example, for the input in story.txt, this program would print:

Once upon a time, there was a cat who lived in a very cat
cat.

For the format of the input file, each blank must begin and end with an
underscore '_'. If a blank begins, it must have a matching underscore on
the same line; otherwise, it is an error. If there is anything wrong with
the input file, you should print an appropriate error message and exit with
a failure status.

As you plan your code for this step, consider how you can write re-usable
code for the subsequent parts. You will want to write as much code as
possible in rand_story.c to avoid code duplication. Then you can write the
prototypes of functions in rand_story.h and include this in your
story-step1.c.

Once you have tested this step to your satisfaction, add/commit/push before
going on to the next step.

*/
