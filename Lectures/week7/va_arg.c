#include <stdio.h>
#include <stdarg.h>

void foo(char *format, ...)
{
  va_list ap;
  int d;
  char *s;
  float f;
  char c;

  va_start(ap, format);

  while (*format) {
    switch (*format++) {
    case 's':
      s = va_arg(ap, char *);
      printf("string %s\n", s);
      break;
    case 'd':
      d = va_arg(ap, int);
      printf("int %d\n", d);
      break;
    case 'f':
      f = (float) va_arg(ap, double);
      printf("float %f\n", f);
      break;
    case 'c':
      c = (char) va_arg(ap, int);
      printf("char %c\n", c);
      break;
    }
  }

  va_end(ap);
}
