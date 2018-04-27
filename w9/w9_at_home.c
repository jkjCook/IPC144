// Workshop 9 - Files

// Name: Justin Cook

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct Box {
	int id;
	double size[3];
	double weight;
};

void listBoxes(const char filename[]);
void printBox(struct Box b);
int searchBox(FILE *fp, int id2Find);
void displayBox(const char filename[], int id2Find);
int addBox(const char filename[], const struct Box * b2Add);
int numberBoxes(const char filename[]);
int getRandomInt(int lower, int higher);
void displayBoxN(char filename[], int n);

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
	int choice, lower, higher;
	char filename[] = "storage.txt";
	struct Box b;
	printf("Welcome to My Storage Room\n");
	printf("==========================\n");
	do {
		choice = menu();
		switch (choice) {
		case 1:
			listBoxes(filename);
			break;

		case 2:
			printf("Enter box ID: ");
			scanf("%d", &choice);
			displayBox(filename, choice);
			break;

		case 3:
			printf("Please enter the box's ID, length, width, height and weight: ");
			scanf("%d %lf %lf %lf %lf", &b.id, &b.size[0], &b.size[1], &b.size[2], &b.weight);
			addBox(filename, &b);
			break;

		case 4:
			lower = 1;
			higher = numberBoxes(filename);
			printf("\nLucky box picked:\n");
			displayBoxN(filename,getRandomInt(lower, higher));
			break;
		};
	} while (choice > 0);
	return 0;
}

void listBoxes(const char filename[]) {
	FILE *fp = NULL;
	int id = 0;
	double m[4];
	fp = fopen(filename, "r");
	if (fp != NULL) {
		printf("List of boxes\n");
		printf("=============\n\n");
		printf("ID Length Width Height Weight\n");
		printf("-----------------------------\n");
		while (fscanf(fp, "%d %lf %lf %lf %lf\n", &id, &m[0], &m[1], &m[2], &m[3]) != EOF)
			printf("%d %6.2lf %5.2lf %6.2lf %6.2lf\n", id, m[0], m[1], m[2], m[3]);
	} else printf("Failed to open file.\n");
	printf("\n");
	fclose(fp);
}

int searchBox(FILE *fp, int id2Find) {
	int number = 0, counter = 0, flag = 0;
	struct Box b;
	if (fp != NULL) {
		rewind(fp);
		while (!feof(fp) && flag == 0) {
			fscanf(fp, "%d %lf %lf %lf %lf%*c\n", &b.id, &b.size[0], &b.size[1], &b.size[2], &b.weight);
			counter++;
			if (b.id == id2Find) {
				number = counter;
				flag = 1;
			}
			if (flag == 0)
				number = -1;
		}
	} else printf("File unable to open.\n");
	return number;
}

void displayBox(const char filename[], int id2Find) {
	FILE *fp;
	int number = 0, counter = 0, flag = 0;
	struct Box b;
	fp = fopen(filename, "r");
	rewind(fp);
	number = searchBox(fp, id2Find);
	if (number != -1) {
		printf("Found box %d as record #%d:\n", id2Find, number);
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
	if (number == -1)
		printf("This box is not recorded.\n\n"); //If number returns as - 1 
	fclose(fp);
}

int addBox(const char filename[], const struct Box * b2Add) {
	FILE *fp;
	int number = 0, added = 0;
	fp = fopen(filename, "a+");
	if (fp != NULL) {
		number = searchBox(fp, b2Add->id);
		if (number > - 1)
			printf("A box with this ID is already recorded.\n");			
		else {
			fprintf(fp, "%d %.2lf %.2lf %.2lf %.2lf\n", b2Add->id, b2Add->size[0], b2Add->size[1], b2Add->size[2], b2Add->weight);
			added++;
		}
	} else printf("Unable to open file.\n");
	printf("%d box added to storage!\n\n", added);
	fclose(fp);
	return added;
}

int numberBoxes(const char filename[]) {
	int counter = 0, number = 0;
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp != NULL) {
		do {
			number = fgetc(fp);									
			if (number != EOF) {								
				if ((char)number == '\n')
					counter++;
			}
		} while (feof(fp) == 0);
	}
	fclose(fp);
	return counter;
}

void displayBoxN(char filename[], int n) {
	FILE *fp;
	struct Box b;
	int i = 0;
	fp = fopen(filename, "r");
	if (fp != NULL) {
		for (i = 1; i <= n; i++)
			fscanf(fp, "%d %lf %lf %lf %lf%*c\n", &b.id, &b.size[0], &b.size[1], &b.size[2], &b.weight);
		printBox(b);											//print 
	}
	fclose(fp);
}

int getRandomInt(int lower, int higher) {
	return lower + rand() % (higher - lower + 1);
}

