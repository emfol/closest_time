#include "closest_time.h"

static int intval(const char *s) {
  int h, l;
  return (
    ((h = *s) >= '0' && h <= '9' && (l = *(s + 1)) >= '0' && l <= '9')
      ?  (h - '0') * 10 + l - '0'
      : -1
  );
}

static int is_valid_time(const char *t)
{
  int h, m;
  return (
    (h = intval(t)) >= 0 && h <= 23 &&
    (m = intval(t + 3)) >= 0 && m <= 59
  );
}

static int is_valid_time_full(const char *t) {
  return (
    *(t + 2) == ':' &&
    *(t + 5) == '\0' &&
    is_valid_time(t)
  );
}

static int timeval(const char *t) {
  return intval(t) * 60 + intval(t + 3);
}

static int timediff(const char *a, const char *b) {
  int diff;
  diff = timeval(b) - timeval(a);
  return (diff < 0) ? 24 * 60 + diff : diff;
}

static int add_if_uniq(char *s, char n) {
  int i, found;
  char c;

  for (i = 0, found = 0; (c = s[i]) != '\0'; ++i)
    if (c == n)
      found = 1;

  if (!found)
    s[i++] = n, s[i] = '\0';

  return i;
}

static void kpermutation(int n, int k, int i, int *items) {
  while (k > 0) {
    items[--k] = i % n;
    i /= n;
  }
}

static int count_kpermutations(int n, int k) {
  int r;
  for (r = n; k > 1; --k)
    r *= n;
  return r;
}

static int find_closest_time(const char *source, char *target) {
  char alphabet[4 + 1], temp[5 + 1];
  int i, alphabet_size, permutation_count, diff, min, items[4];

  alphabet[0] = '\0';
  add_if_uniq(alphabet, source[0]);
  add_if_uniq(alphabet, source[1]);
  add_if_uniq(alphabet, source[3]);
  alphabet_size = add_if_uniq(alphabet, source[4]);
  if (alphabet_size < 1) {
    return 0;
  }

  target[0] = source[0];
  target[1] = source[1];
  target[2] = temp[2] = ':';
  target[3] = source[3];
  target[4] = source[4];
  target[5] = temp[5] = '\0';

  min = 24 * 60;
  permutation_count = count_kpermutations(alphabet_size, 4);
  for (i = 0; i < permutation_count; ++i) {
    kpermutation(alphabet_size, 4, i, items);
    temp[0] = alphabet[items[0]];
    temp[1] = alphabet[items[1]];
    temp[3] = alphabet[items[2]];
    temp[4] = alphabet[items[3]];
    if (
      is_valid_time(temp) &&
      (diff = timediff(source, temp)) > 0 &&
      diff < min
    ) {
      min = diff;
      target[0] = temp[0];
      target[1] = temp[1];
      target[3] = temp[3];
      target[4] = temp[4];
    }
  }

  return 1;
}

void closest_time(const char *source, char *target) {
  if (!is_valid_time_full(source) || !find_closest_time(source, target)) {
    *target = '\0';
  }
}
