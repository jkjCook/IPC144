//Justin Cook

#include <stdio.h>
#include <string.h>

#define NAME_SIZE 9

int main(void) {
	char name[NAME_SIZE];

	printf("Enter your name (up to 8 characters): ");
	scanf("%9[^\n]", name);
	printf("WELCOME %s\n", name);
	strcpy(name, backup);
	
	while (strlen(name) > 0) {
		printf("Guess the password(up to 8 characters) %s:\n", name);
	}
	
	
	printf("input is: %s\n", input);
	
	printf("name is: %s\n", name);
	system("pause");
	return 0;
}