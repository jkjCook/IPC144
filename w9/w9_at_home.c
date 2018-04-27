// Workshop 9 - Files

// Name: Justin Cook

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct Box {
	int id;        // the box ID
	double size[3];   // dimensions of the box (Length, Width, Height)
	double weight; // weight of the box
};

void listBoxes(const char filename[]); // lists all boxes in the file
void printBox(struct Box b);        // print one box- already implemented for you

									// returns the record number of a box with specified ID, if found
int searchBox(FILE *fp, int id2Find);


void displayBox(const char filename[], int id2Find);     // display a box, given ID
int addBox(const char filename[], const struct Box * b2Add);// add a box to file

int numberBoxes(const char filename[]);      // find the number of boxes in a file
int getRandomInt(int lower, int higher);  // get a random number
void displayBoxN(char filename[], int n); // display a box given its record number

void printBox(struct Box b) {
	printf("\nID:     %6d\n"
		"Length: %6.2lf\n"
		"Width:  %6.2lf\n"
		"Height: %6.2lf\n"
		"Weight: %6.2lf\n\n", b.id, b.size[0], b.size[1], b.size[2], b.weight);
}

int menu(void) {
	int choice = -1;

	printf("1- List all boxes\n");
	printf("2- Find a box\n");
	printf("3- Add a box\n");
	printf("4- Randomly pick a lucky box!\n");
	printf("0- Exit program\n");

	printf("Select an option: ");
	do {
		scanf("%d", &choice);
		if (choice < 0 || choice > 4)
			printf("Please enter a number between 0 and 4: ");
	} while (choice < 0 || choice > 4);
	return choice;
}


int main(void) {

	int choice, lower, higher; // , boxID, r;
	char filename[] = "storage.txt";
	//struct Box b;
	struct Box b;

	printf("Welcome to My Storage Room\n");
	printf("==========================\n");
	do {
		// get user's choice
		choice = menu();


		switch (choice) {
		case 1:
			listBoxes(filename);



			break;

		case 2:			// IN_LAB: find a box given its ID
			// ask for ID
			printf("Enter box ID: ");
			scanf("%d", &choice);

			// call displayBox
			displayBox(filename, choice);


			break;

		case 3:
			// AT_HOME: add a box
			// get user input for box's ID, size and weight
			printf("Please enter the box's ID, length, width, height and weight: ");
			scanf("%d %lf %lf %lf %lf", &b.id, &b.size[0], &b.size[1], &b.size[2], &b.weight);

			// call addBox, print message to show number of boxes added
			addBox(filename, &b);

			break;

		case 4:
			// AT_HOME: randomly pick a lucky box

			lower = 1;
			higher = numberBoxes(filename);
			// choose a random number between 1 and the number of boxes in storage


			// display the lucky box!
			printf("\nLucky box picked:\n");
			displayBoxN(filename,getRandomInt(lower, higher));


			break;


		};

	} while (choice > 0);

	return 0;
}
void listBoxes(const char filename[]) {
	FILE *fp = NULL;													//Making my fp object and declaring my variables
	int id = 0;
	double m[4];

	fp = fopen(filename, "r");											//Opening the link to the file and setting my object to the return of fopen
	if (fp != NULL) {													//If fopen doesn't return NULL go into my print
		printf("List of boxes\n");
		printf("=============\n\n");
		printf("ID Length Width Height Weight\n");
		printf("-----------------------------\n");
		while (fscanf(fp, "%d %lf %lf %lf %lf\n", &id, &m[0], &m[1], &m[2], &m[3]) != EOF) {	//While it isn't EOF
			printf("%d %6.2lf %5.2lf %6.2lf %6.2lf\n", id, m[0], m[1], m[2], m[3]);				//Print formatting 
		}
	}
	else {
		printf("Failed to open file.\n");														//Print this if the file fails to open
	}
	printf("\n");
	fclose(fp);																					//Closing the link to the file
	
}
int searchBox(FILE *fp, int id2Find) {
	int number = 0, counter = 0, flag = 0;
	struct Box b;

	if (fp != NULL) {
		rewind(fp);						//Rewind to the beginning of the file
		while (!feof(fp) && flag == 0) { //While not EOF
			fscanf(fp, "%d %lf %lf %lf %lf%*c\n", &b.id, &b.size[0], &b.size[1], &b.size[2], &b.weight);
			counter++;
			if (b.id == id2Find) {						//If the ID that you read is equal to the ID you are looking for trigger the flag
				number = counter;						//Set number to the counter which is the number of records
				flag = 1;
			}
			if (flag == 0) {							//If the flag isn't triggered set number to - 1
				number = -1;
			}
		}
	}
	else {
		printf("File unable to open.\n");
	}

	return number;

}
void displayBox(const char filename[], int id2Find) {
	FILE *fp;
	int number = 0, counter = 0, flag = 0;
	struct Box b;

	fp = fopen(filename, "r");					//Open link to the file
	rewind(fp);									//Rewind to the beginning of the file
					
	number = searchBox(fp, id2Find);			//Call searchBox 			
	
	if (number != -1) {
		printf("Found box %d as record #%d:\n", id2Find, number);		//If the box was found the number will be the 'record' of the box
		rewind(fp);
		while (!feof(fp) && flag == 0) {
			fscanf(fp, "%d %lf %lf %lf %lf%*c\n", &b.id, &b.size[0], &b.size[1], &b.size[2], &b.weight);
			counter++;
			if (counter == number) {
				printBox(b);
				flag = 1;
			}
		}
	}

	if (number == -1) {
		printf("This box is not recorded.\n\n"); //If number returns as - 1 
	}

	fclose(fp);
}
int addBox(const char filename[], const struct Box * b2Add) {
	FILE *fp;
	int number = 0, added = 0;

	fp = fopen(filename, "a+");
	if (fp != NULL) {
		number = searchBox(fp, b2Add->id);
		if (number > - 1) {
			printf("A box with this ID is already recorded.\n");			
		}
		else {				//print the line to the end of the file and add one to added variable
			fprintf(fp, "%d %.2lf %.2lf %.2lf %.2lf\n", b2Add->id, b2Add->size[0], b2Add->size[1], b2Add->size[2], b2Add->weight);
			added++;
		}
	}
	else {
		printf("Unable to open file.\n");
	}
	printf("%d box added to storage!\n\n", added);

	fclose(fp);
	return added;
}
int numberBoxes(const char filename[]) {
	int counter = 0, number = 0;
	FILE *fp;

	fp = fopen(filename, "r");
	if (fp != NULL){
		do {
			number = fgetc(fp);									//Gets a single character until it reaches a new line then it
			if (number != EOF) {								//increases the counter to count the total number of lines
				if ((char)number == '\n') {
					counter++;
				}
			}

		} while (feof(fp) == 0);
	}
	fclose(fp);
	return counter;												//Return amount of lines
}
void displayBoxN(char filename[], int n) {
	FILE *fp;
	struct Box b;
	int i = 0;

	fp = fopen(filename, "r");
	if (fp != NULL) {											//read through all the lines and find the exact line 
		for (i = 1; i <= n; i++) {
			fscanf(fp, "%d %lf %lf %lf %lf%*c\n", &b.id, &b.size[0], &b.size[1], &b.size[2], &b.weight);
		}
		printBox(b);											//print 
	}
	fclose(fp);
}
int getRandomInt(int lower, int higher) {
	return lower + rand() % (higher - lower + 1);			//Get the random int between lower and higher
}

