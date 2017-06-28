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
		switch (menu()) {						//Switch statement for the different options
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
			printf("Exit the program? (Y)es/(N)o : ");		//Uses the yes function to take either a Y or N for exiting
			number = yes();
			if (number == 1) {
				counter++;
			}
			break;
		}


	}
}
int yes(void) {
	char choice = ' ';
	int number = 2;

	scanf("%c", &choice);										//Initial prompt for a character
	clrKyb();
	choice = toupper(choice);									//Function to make the character uppercase always

	if (choice == 'Y') {										//Checking if the char is a Y or an N
		number = 1;
	}
	else if (choice == 'N') {
		number = 0;
	}

	while (number == 2) {										//Loop to make sure that the entered char is valid

		printf("Only (Y)es or (N)o are acceptable: ");
		scanf("%c", &choice);
		clrKyb();
		choice = toupper(choice);

		if (choice == 'Y') {
			number = 1;
		}
		else if (choice == 'N') {
			number = 0;
		}
	}

	return number;												//Returns either 1 or 0 for Yes or No
}
int menu(void) {			//Displays the menu
	int choice = 10;
	printf("1- List all items\n2- Search by SKU\n3- Checkout an item\n4- Stock an item\n5- Add new item or update item\n"
		"6- delete item\n7- Search by name\n0- Exit program\n> ");
	choice = getIntLimited(0, 7);		//Sets the limits of the int that it will accept
	return choice;						//Return the choice

}

// copy MS1 functions here

void clrKyb(void) {
	char choice = 'a';

	while (choice != '\n') {				//Loops until it reaches a return
		scanf("%c", &choice);
	}
}
void pause(void) {
	printf("Press <ENTER> to continue...");
	clrKyb();										//Accepts an enter to end the function
}
int getInt(void) {
	int validInteger, counter = 0;
	char validChar = ' ';

	while (counter == 0) {

		scanf("%d%c", &validInteger, &validChar);				//Read in your integer followed by enter
		if (validChar != '\n') {								//If the character after your int isn't a space
			clrKyb();											//Clear the keyboard
			printf("Invalid integer, please try again: ");		//Error message
		}
		else {													//To break the loop if conditions are met
			counter++;
		}
	}
	return validInteger;										//Return the valid integer 
}
void welcome(void) {
	printf("---=== Grocery Inventory System ===---\n\n");
}
int getIntLimited(int lowerLimit, int upperLimit) {
	int choice = 0;

	choice = getInt();														//Prompt for an integer chicking if actually valid
	while (choice < lowerLimit || choice > upperLimit) {						//Checking if the integer is in the correct range
		printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);		//If it's not it prompts you again and tells you 
		choice = getInt();														//Prompt for an integer again
	}
	return choice;
}	

