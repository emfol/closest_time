#include "closest_time.h"

static int add2set(char *set, char n) {
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

static int permutations(char *set, char *arr, int len, void *ctx, void (*cb)(void *, char *)) {
  register char c, *sp, *ap;
  int lst, cnt = 0;
  if (len < 1) {
    (*cb)(ctx, arr);
    cnt = 1;
  } else {
    lst = len - 1;
    ap = arr + lst;
    sp = set;
    while ((c = *sp) != '\0') {
      ++sp, *ap = c;
      cnt += permutations(set, arr, lst, ctx, cb);
    }
  }
  return cnt;
}

static int ival(const char *str, int cnt) {
  int i, c, r = 0;
  for (i = 0; i < cnt; ++i) {
    c = *(str + i) - '0';
    if (c < 0 || c > 9) {
      r = -1;
      break;
    }
    r = r * 10 + c;
  }
  return r;
}

static int is_time(int h, int m) {
  return h >= 0 && h <= 23 && m >= 0 && m <= 59;
}

static void arr2time(char *arr, char *str) {
  int i;
  for (i = 0; i < 5; ++i)
    *(str + i) = (i == 2) ? ':' : *arr++;
  *(str + i) = '\0';
}

struct context {
  char *str;
  int curr;
  int next;
};

static void each(struct context *ctx, char *arr) {
  int n, d, h, m;
  h = ival(arr, 2);
  m = ival(arr + 2, 2);
  if (is_time(h, m)) {
    n = h * 100 + m;
    d = n - ctx->curr;
    if (d < 0)
      d += ctx->curr + 2400;
    if (d != 0 && d < ctx->next) {
      ctx->next = d;
      arr2time(arr, ctx->str);
    }
  }
}

int closest_time(const char *src, char *dst) {
  struct context ctx;
  char set[5] = { 0 }, arr[5] = { 0 };
  int h, m, c = 0;

  h = ival(src, 2);
  m = (h < 0) ? -1 : ival(src + 3, 2);

  if (is_time(h, m)) {
    add2set(set, src[0]);
    add2set(set, src[1]);
    add2set(set, src[3]);
    add2set(set, src[4]);
    ctx.str = dst;
    ctx.curr = h * 100 + m;
    ctx.next = 4800;
    c = permutations(set, arr, 4, &ctx, (void (*)(void *, char *))each);
    if (c == 1)
      arr2time(arr, dst);
  }

  return c;
}
