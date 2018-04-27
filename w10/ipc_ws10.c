//Justin Cook

#include <stdio.h>
#include <string.h>

#define NAME_SIZE 9

void trim(char str[]);

int main(void) {
	char name[NAME_SIZE];								//defines for all used strings
	char backup[NAME_SIZE];
	char password[NAME_SIZE];
	char guess[NAME_SIZE];
	int length = 0, i;

	printf("Password Game\n");							//opening inputs and greetings
	printf("=============\n");
	printf("Enter your name (up to 8 characters): ");
	scanf("%9[^\n]", name);
	printf("WELCOME %s\n", name);

	strcpy(backup, name);								//saving my input to the eventual password string and the backup
	strcpy(password, name);

	length = strlen(password);							//loop to create the password by minusing 1 from every letter
	for (i = 0; i < length; i++) {
		password[i]--;
	}
	
	printf("Guess the password(up to 8 characters) %s: ", name);
	scanf("%s", guess);
	while (strlen(name) > 1 && strcmp(guess, password) != 0) {					//loop for guessing the password
		trim(name);
		printf("FALSE: Guess the password (up to 8 characters) %s: ", name);
		scanf("%s", guess);
		
	}

	if (strcmp(guess, password) == 0) {				//if/else for the correct display message for if you won or lost
		printf("You got it, %s!!!\n", backup);
	}
	else {
		printf("Thou has failed.\n");
	}

	printf("Game Over!\n");

	system("pause");
	return 0;
}

void trim(char str[]) {
	int length = 0, i;

	length = strlen(str);

	for (i = 0; i < length; i++) {
		str[length - 1] = '\0';
	}

}

