#include <stdio.h>
#include <string.h>
#include "closest_time.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    char dst[TIMEBUFSZ];
    int cnt = closest_time(argv[1], dst);
    if (cnt > 0) {
      puts(dst);
      fprintf(stderr, "count: %d\n", cnt);
      return 0;
    }
  }
  fputs("Bad input... Expected time in range [00:00, 23:59]\n", stderr);
  return 1;
}
