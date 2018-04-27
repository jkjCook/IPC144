/*Justin Cook - Workshop 1*/

#include <stdio.h>

int main(void) {
  char name[12] = "";
  int age = 0;

  printf("Please input your first name (Maximum 12 characters)\n");
  scanf("\n%s", name);
  printf("\nHello %s, Please input your age: ", name);
  scanf("%d", age);

  return 0;
}
