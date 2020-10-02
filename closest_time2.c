
int add2set(char *set, char n) {
  register char c, *p = set;
  int absent = 1;
  while ((c = *p) != '\0') {
    if (c == n)
      absent = 0;
    ++p;
  }
  if (absent)
    *p++ = n, *p = '\0';
  return p - set;
}

void permutations(char *set, char *arr, int len, void (*cb)(char *)) {
  register char c, *sp, *ap;
  int lst;
  if (len < 1) {
    (*cb)(arr);
    return;
  }
  lst = len - 1;
  ap = arr + lst;
  sp = set;
  while ((c = *sp) != '\0') {
    ++sp, *ap = c;
    permutations(set, arr, lst, cb);
  }
}

void closest_time(const char *src, char *dst) {
  char set[5];
  int len;

  set[0] = '\0';

  add2set(set, src[0]);
  add2set(set, src[1]);
  add2set(set, src[3]);
  len = add2set(set, src[4]);


}

