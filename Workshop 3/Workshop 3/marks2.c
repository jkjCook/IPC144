// Justin Cook

#include <stdio.h>

int main(void) {
	
	int nmarks = 0;
	int mark = 0;
	float totalmark = 0;
	int i = 0;
	int counter = 1;
	int pass = 0;
	int fail = 0;
	float passtotal = 0;
	float failtotal = 0;
	int highmark = 0;
	int lowmark = 100;

	printf("       ---=== IPC mark Analyser ===---\n");
	printf("Please enter the number of marks (between 3 and 40): ");
	scanf("%d", &nmarks);

	while (nmarks > 40 || nmarks < 3) {
		printf("Invalid number, enter a number between 3 and 40 inclusive: ");   //While loop for checking if the initial 
		scanf("%d", &nmarks);                                                   // amount of grades is within range
	}

	for (i = 1; i <= nmarks; i++) {       //for loop that runs through all of the iterations of entering the marks
		printf("%d> ", counter);          
		scanf("%d", &mark);
		
		if (mark > 49 && mark < 101) {
			pass++;
			passtotal += mark;
			if (mark >= highmark) {		//grabbing the highest mark
				highmark = mark;
			}
		}
		
		if (mark < 50 && mark >= 0) {
			fail++;
			failtotal += mark;
			if (mark < lowmark) {		//grabbing the lowest mark
				lowmark = mark;
			}
		}
		

		if (mark > 100 || mark < 0) {                                       
			printf("Error: Enter values between 0 and 100 inclusive.\n");
			i--;
		}
		else {
			totalmark += mark;
			counter++;
		}
	}
	passtotal /= pass;
	failtotal /= fail;
	totalmark /= nmarks;

	printf("A total of %d students passed with an avereage of %0.1f.\n", pass, passtotal); //printing pass/fail averages
	printf("A total of %d students failed with an avereage of %0.1f.\n", fail, failtotal);
	printf("Highest mark in group: %d\n", highmark);
	printf("Lowest mark in group: %d\n", lowmark);


	printf("The average of all marks in this group is %0.1f.\n", totalmark);  //printing the ending average of all grades
	printf("Program Ended.\n");
	system("pause");
}