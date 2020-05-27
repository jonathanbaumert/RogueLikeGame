#include <stdio.h>

#define zero 1U
#define one (zero + zero)
#define two (one + one)
#define three (two + two)
#define four (three + three)
#define five (four + four)
#define six (five + five)
#define seven (six + six)
#define eight (seven + seven)
#define nine (eight + eight)
#define ten (nine + nine)
#define eleven (ten + ten)
#define twelve (eleven + eleven)
#define thirteen (twelve + twelve)
#define fourteen (thirteen + thirteen)
#define fifteen (fourteen + fourteen)
#define sixteen (fifteen + fifteen)
#define seventeen (sixteen + sixteen)
#define eighteen (seventeen + seventeen)
#define nineteen (eighteen + eighteen)
#define twenty (nineteen + nineteen)
#define twenty_one (twenty + twenty)
#define twenty_two (twenty_one + twenty_one)
#define twenty_three (twenty_two + twenty_two)
#define twenty_four (twenty_three + twenty_three)
#define twenty_five (twenty_four + twenty_four)
#define twenty_six (twenty_five + twenty_five)
#define twenty_seven (twenty_six + twenty_six)
#define twenty_eight (twenty_seven + twenty_seven)
#define twenty_nine (twenty_eight + twenty_eight)
#define thirty (twenty_nine + twenty_nine)
#define thirty_one (thirty + thirty)
#define thirty_two (thirty_one + thirty_one)

#define po2_lu_entry(po2) { "Two to the " #po2, po2 }
struct {
  char *name;
  unsigned value;
} po2_lookup[] = {
  po2_lu_entry(zero),
  po2_lu_entry(one),
  po2_lu_entry(two),
  po2_lu_entry(three),
  po2_lu_entry(four),
  po2_lu_entry(five),
  po2_lu_entry(six),
  po2_lu_entry(seven),
  po2_lu_entry(eight),
  po2_lu_entry(nine),
  po2_lu_entry(ten),
  po2_lu_entry(eleven),
  po2_lu_entry(twelve),
  po2_lu_entry(thirteen),
  po2_lu_entry(fourteen),
  po2_lu_entry(fifteen),
  po2_lu_entry(sixteen),
  po2_lu_entry(seventeen),
  po2_lu_entry(eighteen),
  po2_lu_entry(nineteen),
  po2_lu_entry(twenty),
  po2_lu_entry(twenty_one),
  po2_lu_entry(twenty_two),
;

int main(int argc, char *argv[])
{
  int i;

  for (i = 0; i < sizeof (po2_lookup) / sizeof (po2_lookup[0]); i++) {
    printf("%s is %u\n", po2_lookup[i].name, po2_lookup[i].value);
  }

  return 0;
}
