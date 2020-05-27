#include <stdio.h>

#define FOO 5

/* min() like this is great, as long as your are careful not *
 * to call it on functions                                   */
#define min(x, y) (x < y ? x : y)

/* Basic blocks get the value of their last line */
#define max(x, y) ({ \
  typeof (x) _x = x; \
  typeof (y) _y = y; \
  _x > _y ? _x : _y; \
})

#define concatenate(x, y) x ## y

#define to_string(s) #s

int main(int argc, char *argv[])
{
  printf("%d\n", FOO);

  printf("%f\n", max(foo(x), bar(y)));

  concatenate(print, f)("Hello World!\n");

  printf(to_string(Hello World!));

  return 0;
}
