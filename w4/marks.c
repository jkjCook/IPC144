#include <stdio.h>

int main(void) {

	int nstudents = 0, i = 1, counter = 1, totalmark = 0, counter2 = 1, j = 1;
	float avgmark = 0, passtotal = 0, failtotal = 0;
	int stdno[40], stdmark[40], pass = 0, fail = 0, highmark = 0, lowmark = 100;

	printf("       ---=== IPC mark Analyser V2.0 ===---\n");           //opening prompt for number of students
	printf("Please enter the number of students(between 3 and 40): ");
	scanf("%d", &nstudents);

	while (nstudents > 40 || nstudents < 3) {
		printf("Invalid number, enter a number between 3 and 40 inclusive: ");   //While loop for checking if the initial value is valid
		scanf("%d", &nstudents);
	}
	
	printf("Row   Std No  Mrk\n--- --------- ---\n");
	
	for (i = 0; i < nstudents; i++) {
															//first loop for inputting student numbers and marks for students
		printf("    _________ ___\r%3d ", counter);
		scanf("%d %d", &stdno[i], &stdmark[i]);

		if (stdno[i] > 999999999 || stdno[i] < 10000000) {
			printf("Error: Enter student number values between 10000000 and 999999999 inclusive.\n");
			i--;
		}

		else if (stdmark[i] > 100 || stdmark[i] < 0) {                          //checking if the mark is within valid range
			printf("Error: Enter mark values between 0 and 100 inclusive.\n");
			i--;
		}
		else {

			totalmark += stdmark[i];                     //adding the marks to the total marks
			counter++;
		}

	}

	for (i = 0; i < nstudents; i++) {
		if (stdmark[i] >= 50) {               //finding how many passed and failed and adding their respective totals
			pass++;
			passtotal += stdmark[i];
		}
		else {
			fail++;
			failtotal += stdmark[i];
		}

		if (stdmark[i] > highmark) {           //finding highest and lowest marks through the loop
			highmark = stdmark[i];
		}
		if (stdmark[i] < lowmark) {
			lowmark = stdmark[i];
		}
	}
	passtotal /= pass;
	failtotal /= fail;

	printf("=================\n");
	printf("Marks entered, printing results:\n");
	
	printf("Row   Std No  Mrk\n--- --------- ---\n");

	for (j = 0; j < nstudents; j++) {                    //second loop for printing all of the students info in order
		printf("%03d %09d %3d", counter2, stdno[j], stdmark[j]);

		if (stdmark[j] == highmark) {             //finding where the highest mark wil be printed and printing
			printf("***Highest mark***\n");
		}
		else if (stdmark[j] == lowmark) {        //finding where the lowest mark wil be printed and printing
			printf("***Lowest mark***\n");
		}
		else {
			printf("\n");
		}

		counter2++;
	}

	avgmark = totalmark;
	avgmark /= nstudents;
	
	printf("=================\n");
	printf("A total of %d students passed with an average of %0.1f.\n", pass, passtotal); //printing pass/fail averages
	printf("A total of %d students failed with an average of %0.1f.\n", fail, failtotal);
	printf("Highest mark in group: %d\n", highmark);
	printf("Lowest mark in group: %d\n", lowmark);
	printf("The average of all students in this group is %0.1f.\n", avgmark);         // calculating the average grade
	printf("Program Ended.\n");

	return 0;

}