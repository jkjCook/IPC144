#include <stdio.h>

int main(void) {

  int toonies = 0, loonies = 0, quarters = 0, dimes = 0, nickels = 0, pennies = 0;
  int fifty = 0, twenty = 0, ten = 0, five = 0;
  float change = 0;

  printf("Please enter the number of coins in your piggy bank:\n");
  printf("Toonies: ");
  scanf("%d", &toonies);
  printf("Loonies: ");
  scanf("%d", &loonies);
  printf("Quarters: ");
  scanf("%d", &quarters);
  printf("Dimes: ");
  scanf("%d", &dimes);
  printf("Nickels: ");
  scanf("%d", &nickels);
  printf("Pennies: ");
  scanf("%d", &pennies);

  float total = toonies * 2 + loonies + quarters * 0.25 + dimes * 0.10 + nickels * 0.05 + pennies * 0.01;

  printf("You have $%.2f in your piggy bank!\n", total);

  fifty = total / 50;
  total -= (50 * fifty);
  twenty = total / 20;
  total -= (20 * twenty);
  ten = total / 10;
  total -= (10 * ten);
  five = total / 5;
  total -= (5 * five);

  printf("$50 bill: %d", fifty);
  printf("\n$20 bill: %d", twenty);
  printf("\n$10 bill: %d", ten);
  printf("\n$5 bill: %d", five);
  printf("\nYour total change: %.2f\n", total);
  system("pause");

  return 0;
}
