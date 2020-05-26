#include <stdio.h>
#include <ctype.h>

char *words[] = {
  "apricot",
  "balogna",
  "champaigne",
  "dougo",
  "elephants",
  "fire",
  "gdb",
  "helix",
  "inertia",
  "joker",
  "klein bottle",
  "lambast",
  "melon",
  "nope",
  "otter",
  "potter",
  "Queen",
  "rockabilly",
  "slackware",
  "tomatoe",
  "uvula",
  "valgrind",
  "water buffalo",
  "xylephone",
  "y",
  "zoolander"
};

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Please enter a letter.\n");

    return 1;
  }

  printf("%s begins with %c!\n", words[tolower(argv[1][0]) - 'a'], argv[1][0]);

  return 0;
}
