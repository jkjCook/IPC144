#include <stdio.h>

int main(void) {

	int nstudents = 0, i = 1, counter = 1, totalmark = 0, counter2 = 1, j = 1;
	float avgmark = 0, passtotal = 0, failtotal = 0;
	int stdno[40], stdmark[40], pass = 0, fail = 0, highmark = 0, lowmark = 100;

	printf("       ---=== IPC mark Analyser V2.0 ===---\n");
	printf("Please enter the number of students(between 3 and 40): ");
	scanf("%d", &nstudents);

	while (nstudents > 40 || nstudents < 3) {
		printf("Invalid number, enter a number between 3 and 40 inclusive: ");
		scanf("%d", &nstudents);
	}
	
	printf("Row   Std No  Mrk\n--- --------- ---\n");
	
	for (i = 0; i < nstudents; i++) {
		printf("    _________ ___\r%3d ", counter);
		scanf("%d %d", &stdno[i], &stdmark[i]);

		if (stdno[i] > 999999999 || stdno[i] < 10000000) {
			printf("Error: Enter student number values between 10000000 and 999999999 inclusive.\n");
			i--;
		}

		else if (stdmark[i] > 100 || stdmark[i] < 0) {
			printf("Error: Enter mark values between 0 and 100 inclusive.\n");
			i--;
		} else {
			totalmark += stdmark[i];                     
			counter++;
		}

	}

	for (i = 0; i < nstudents; i++) {
		if (stdmark[i] >= 50) {
			pass++;
			passtotal += stdmark[i];
		} else {
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

	for (j = 0; j < nstudents; j++) {
		printf("%03d %09d %3d", counter2, stdno[j], stdmark[j]);

		if (stdmark[j] == highmark) {
			printf("***Highest mark***\n");
		}
		else if (stdmark[j] == lowmark) {
			printf("***Lowest mark***\n");
		} else {
			printf("\n");
		}

		counter2++;
	}

	avgmark = totalmark;
	avgmark /= nstudents;
	
	printf("=================\n");
	printf("A total of %d students passed with an average of %0.1f.\n", pass, passtotal);
	printf("A total of %d students failed with an average of %0.1f.\n", fail, failtotal);
	printf("Highest mark in group: %d\n", highmark);
	printf("Lowest mark in group: %d\n", lowmark);
	printf("The average of all students in this group is %0.1f.\n", avgmark);
	printf("Program Ended.\n");

	return 0;

}
