// Justin Cook

#include <stdio.h>

int main(void) {
	int nmarks = 0, mark = 0, i = 0, counter = 1, pass = 0, fail = 0,
      highmark = 0, lowmark = 100;
  float passtotal = 0, failtotal = 0, totalmark = 0;

	printf("       ---=== IPC mark Analyser ===---\n");
	printf("Please enter the number of marks (between 3 and 40): ");
	scanf("%d", &nmarks);

	while (nmarks > 40 || nmarks < 3) {
		printf("Invalid number, enter a number between 3 and 40 inclusive: ");    
		scanf("%d", &nmarks);                                                   
	}

	for (i = 1; i <= nmarks; i++) {       
		printf("%d> ", counter);          
		scanf("%d", &mark);
		
		if (mark > 49 && mark < 101) {
			pass++;
			passtotal += mark;
			if (mark >= highmark) {		
				highmark = mark;
			}
		}
		
		if (mark < 50 && mark >= 0) {
			fail++;
			failtotal += mark;
			if (mark < lowmark) {		
				lowmark = mark;
			}
		}
		

		if (mark > 100 || mark < 0) {                                       
			printf("Error: Enter values between 0 and 100 inclusive.\n");
			i--;
		} else {
			totalmark += mark;
			counter++;
		}
	}
	passtotal /= pass;
	failtotal /= fail;
	totalmark /= nmarks;

	printf("A total of %d students passed with an avereage of %0.1f.\n", pass, passtotal); 
	printf("A total of %d students failed with an avereage of %0.1f.\n", fail, failtotal);
	printf("Highest mark in group: %d\n", highmark);
	printf("Lowest mark in group: %d\n", lowmark);
	printf("The average of all marks in this group is %0.1f.\n", totalmark);  
	printf("Program Ended.\n");
	system("pause");
}
