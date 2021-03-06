// includes go here
//Justin Cook
#include <stdio.h>


void welcome(void);
void prnTitle(void);
void prnFooter(double gTotal);
void clrKyb(void);
void pause(void);
int getInt(void);
double getDbl(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDblLimited(double lowerLimit, double upperLimit);

/* 1- comment out the main when submitting milestone one
2- Your final milestone one should run perfectly with the following tester program.
To comment out the main() delete the next two characters after the arrow ->

int main(void) {
	int iVal;
	double dVal;
	welcome();

	// testing prnTitle() 
	printf("listing header and footer with grand total:\n");
	prnTitle();



	// Testing prnFooter()  
	prnFooter(1234.5678);
	printf("listing header and footer without grand total:\n");
	prnTitle();
	prnFooter(-1);
	// Testing Pause() and clrKyb() 

	pause();

	// Testing getInt()
	printf("Enter an integer: ");
	iVal = getInt();
	printf("You entered: %d\n", iVal);

	// Testing Get Int Limited
	printf("Enter an integer between 10 an 20: ");
	iVal = getIntLimited(10, 20);
	printf("Your entered %d\n", iVal);

	// Testing Get Double
	printf("Enter a floating point number: ");
	dVal = getDbl();
	printf("You entered: %0.2lf\n", dVal);
	
	// Tesing Get Double Limited
	printf("Enter a floating point number between 10.00 an 20.00: ");
	dVal = getDblLimited(10.0, 20.0);
	printf("You entered: %0.2lf\n", dVal);



	printf("End of tester program for milestone one!\n");
	system("pause");
	}
	
	/* End Commenting out the main out*/

	// implement your functions for milestone one down here: 

void welcome(void) {
	printf("---=== Grocery Inventory System ===---\n\n");
}

void prnTitle(void) {
	printf(">Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn<\n");
	printf(">----+---+--------------------+--------+-----+-----+-----+------------|---<\n");
}

void prnFooter(double gTotal) {
	printf(">--------------------------------------------------------+----------------<\n");
	if (gTotal >= 0)
		printf(">                                           Grand Total: | %12.2lf\n", gTotal);
}

void clrKyb(void) {
	char choice = 'a';
	while (choice != '\n')
		scanf("%c", &choice);
}

void pause(void) {
	printf(">Press <ENTER> to continue...<");
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

double getDbl(void) {
	double validDouble;
	int counter = 0;
	char validChar = ' ';
	while (counter == 0) {
		scanf("%lf%c", &validDouble, &validChar);
		if (validChar != '\n') {
			clrKyb();
			printf("Invalid number, please try again: ");
		}
		else counter++;
	}
	return validDouble;
}

int getIntLimited(int lowerLimit, int upperLimit) {
	int choice = 0;
	scanf("%d", &choice);
	while (choice < lowerLimit || choice > upperLimit) {
		printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
		scanf("%d", &choice);
	}
	return choice;
}

double getDblLimited(double lowerLimit, double upperLimit) {
	double choice = 0;
	scanf("%lf", &choice);
	while (choice < lowerLimit || choice > upperLimit) {
		printf("Invalid value, %lf < value < %lf: ", lowerLimit, upperLimit);
		scanf("%lf", &choice);
	}
	return choice;
}
