//Justin Cook

#include <stdio.h>
#include <ctype.h>

void clrKyb(void);
void pause(void);
int getInt(void);
int yes(void);  // ms2
int getIntLimited(int lowerLimit, int upperLimit);
void welcome(void);
void GrocInvSys(void);  // ms2
int menu(void);  // ms2


/*int main(void) {
	GrocInvSys();
	return 0;
}*/

// implmement MS2 fucntions here

void GrocInvSys(void) {
	int counter = 0;
	int number = 0;

	while (counter == 0) {
		switch (menu()) {
		case 1:
			printf("List Items!\n");
			pause();
			break;
		case 2:
			printf("Search Items!\n");
			pause();
			break;
		case 3:
			printf("Checkout Item!\n");
			pause();
			break;
		case 4:
			printf("Stock Item!\n");
			pause();
			break;
		case 5:
			printf("Add/Update Item!\n");
			pause();
			break;
		case 6:
			printf("Delete Item!\n");
			pause();
			break;
		case 7:
			printf("Search by name!\n");
			pause();
			break;
		case 0:
			printf("Exit the program? (Y)es/(N)o : ");
			number = yes();
			if (number == 1)
				counter++;
			break;
		}
	}
}

int yes(void) {
	char choice = ' ';
	int number = 2;
	scanf("%c", &choice);
	clrKyb();
	choice = toupper(choice);
	if (choice == 'Y')
		number = 1;
	else if (choice == 'N')
		number = 0;
	while (number == 2) {
		printf("Only (Y)es or (N)o are acceptable: ");
		scanf("%c", &choice);
		clrKyb();
		choice = toupper(choice);
		if (choice == 'Y')
			number = 1;
		else if (choice == 'N')
			number = 0;
	}
	return number;
}

int menu(void) {
	int choice = 10;
	printf("1- List all items\n2- Search by SKU\n3- Checkout an item\n4- Stock an item\n5- Add new item or update item\n"
		"6- delete item\n7- Search by name\n0- Exit program\n> ");
	choice = getIntLimited(0, 7);
	return choice;
}

void clrKyb(void) {
	char choice = 'a';
	while (choice != '\n')
		scanf("%c", &choice);
}

void pause(void) {
	printf("Press <ENTER> to continue...");
	clrKyb();
}

int getInt(void) {
	int validInteger, counter = 0;
	char validChar = ' ';
	while (counter == 0) {
		scanf("%d%c", &validInteger, &validChar);
		if (validChar != '\n') {
			clrKyb();
			printf("Invalid integer, please try again: ");
		} else counter++;
	}
	return validInteger;
}

void welcome(void) {
	printf("---=== Grocery Inventory System ===---\n\n");
}

int getIntLimited(int lowerLimit, int upperLimit) {
	int choice = 0;
	choice = getInt();
	while (choice < lowerLimit || choice > upperLimit) {
		printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
		choice = getInt();
	}
	return choice;
}	

