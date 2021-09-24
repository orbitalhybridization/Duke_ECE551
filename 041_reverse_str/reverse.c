#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  int length = 0;
  char * left = str;

  while (*str != '\0') {  // get length of string
    str++;                // iterate through
    length++;
  }

  if ((length == 0) || (length == 1)) {
    return;
  }  // we're done if we have length 1 or 2

  char * right = str - 1;
  if (length % 2 == 1) {
    length -= 1;
  }
  for (int i = 0; i < length / 2; i++) {
    char temp1 = *left;
    char temp2 = *right;
    *right = temp1;
    *left = temp2;
    left++;
    right--;
    if (left == right) {
      break;
    }
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be "
                "no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
