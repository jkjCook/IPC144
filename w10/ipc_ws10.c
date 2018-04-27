//Justin Cook

#include <stdio.h>
#include <string.h>

#define NAME_SIZE 9

void trim(char str[]);

int main(void) {
	char name[NAME_SIZE], backup[NAME_SIZE], password[NAME_SIZE], guess[NAME_SIZE];
	int length = 0;

	printf("Password Game\n");
	printf("=============\n");
	printf("Enter your name (up to 8 characters): ");
	scanf("%9[^\n]", name);
	printf("WELCOME %s\n", name);
	strcpy(backup, name);
	strcpy(password, name);
  length = strlen(password);

  for (int i = 0; i < length; i++)
		password[i]--;

	printf("Guess the password(up to 8 characters) %s: ", name);
	scanf("%s", guess);
	while (strlen(name) > 1 && strcmp(guess, password) != 0) {
		trim(name);
		printf("FALSE: Guess the password (up to 8 characters) %s: ", name);
		scanf("%s", guess);
	}
	if (strcmp(guess, password) == 0)
		printf("You got it, %s!!!\n", backup);
	else
		printf("Thou has failed.\n");
	printf("Game Over!\n");
	system("pause");
	return 0;
}

void trim(char str[]) {
	int length = 0;
	length = strlen(str);
	for (int i = 0; i < length; i++)
		str[length - 1] = '\0';
}

