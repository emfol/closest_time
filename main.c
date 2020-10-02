#include <stdio.h>
#include <string.h>
#include "closest_time.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    char target[TIMEBUFSZ];
    closest_time(argv[1], target);
    if (strlen(target) > 0) {
      puts(target);
      return 0;
    } else fputs("Bad input...\n", stderr);
  }
  return 1;
}

