#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void insertion_sort(int *a, int n)
{
  int i, j, t;

  for (i = 1; i < n; i++) {
    for (t = a[i], j = i - 1; j > -1 && a[j] > t; j--) {
      a[j + 1] = a[j];
    }
    a[j + 1] = t;
  }
}

void generic_insertion_sort(void *data, int n, size_t s,
                            int (*compare)(void *, void *))
{
  char *a;
  int i, j;
  void *t;

  a = data;
  t = malloc(s);

  for (i = 1; i < n; i++) {
    for (memcpy(t, a + (i * s), s), j = i - 1;
         j > -1 && compare(a + (j * s), t) > 0;
         j--) {
      memcpy(a + ((j + 1) * s), a + (j * s), s);
    }
    memcpy(a + ((j + 1) * s), t, s);
  }

  free(t);
}

int compare_int(void *v1, void *v2)
{
  return *((int *) v1) - *((int *) v2);
}

int compare_str(const void *v1, const void *v2)
{
  return strcmp(*(char **) v1, *(char **) v2);
}

int main(int argc, char *argv[])
{
  int a[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
  int i;
  char *s[] = {
    "zero", "one", "two", "three", "four",
    "five", "six", "seven", "eight", "nine"
  };

  for (i = 0; i < 10; i++) {
    printf("%d ", a[i]);
  }
  putchar('\n');

  generic_insertion_sort(a, 10, sizeof (a[0]), compare_int);

  for (i = 0; i < 10; i++) {
    printf("%d ", a[i]);
  }
  putchar('\n');


  for (i = 0; i < 10; i++) {
    printf("%s ", s[i]);
  }
  putchar('\n');

  /*
  generic_insertion_sort(s, sizeof (s) / sizeof (s[0]),
                         sizeof (s[0]), compare_str);
  */
  qsort(s, sizeof (s) / sizeof (s[0]), sizeof (s[0]), compare_str);

  for (i = 0; i < 10; i++) {
    printf("%s ", s[i]);
  }
  putchar('\n');

  return 0;
}
