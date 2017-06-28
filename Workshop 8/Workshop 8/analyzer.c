//Justin Cook

#include <stdio.h>
#define MAX 100

struct studentMarks {
	int   id;
	float marks;
};

void welcome(void);
int get_data(struct studentMarks * ptr);
void show(struct studentMarks list[], int num);
float analyze(struct studentMarks list[], int num, float* ptr_highest, float* ptr_lowest);
void print_summary(float avg, float high, float low);

int main(void) {

	// declarations of a constant, an array and variables

	int counter = 0;
	int number = 0;
	float highest = 0, lowest = 100, average = 0;
	struct studentMarks markArray[MAX];
	struct studentMarks student; 

	// call a function to display a welcome message

	welcome();

	// 1. use a do-while loop to get student ids and student marks

	do {

		number = get_data(&student);
		markArray[counter].id = student.id;
		markArray[counter].marks = student.marks;
		counter++;

	} while (number == 0);

	// 2. print out all the student marks

	show(markArray, counter);

	// 3. data analysis

	average = analyze(markArray, counter, &highest, &lowest);

	// 4. print the result of data analysis

	print_summary(average, highest, lowest);
	
	return 0;
}

void welcome(void) {
	printf("####### Marks Analyzer V3.0 #######\n");		//Welcome function
}
int get_data(struct studentMarks * ptr) {			
	int id = 0;
	float mark = 0.0;

	printf("Enter student id and marks (e.g. 12345 89.5): ");			//Gets the ID and the Mark
	scanf("%d %f", &id, &mark);
	if (id != -1 && mark != -1) {										//If the mark isn't - 1 it saves the variables and returns 0
		ptr->id = id;
		ptr->marks = mark;
		return 0;
	}
	else {																//If the numbers come in as - 1 it returns - 1
		return -1; 
	}
	
}
void show(struct studentMarks list[], int num) {							//Uses the array for saving the marks into and num for size
	int i;

	for (i = 0; i < num - 1; i++) {											//For loop to loop through to save to every element
		printf("%d. %d, %0.2f\n", i + 1, list[i].id, list[i].marks);
	}
}
float analyze(struct studentMarks list[], int num, float* ptr_highest, float* ptr_lowest) {
	int i; 
	float average = 0.0;

	for (i = 0; i < num - 1; i++) {					//Uses num as size to iterate through the list
		if (list[i].marks > *ptr_highest) {			//If the mark of the current element is greater than the current highest mark
			*ptr_highest = list[i].marks;			//save the new highest mark
		}
		if (list[i].marks < *ptr_lowest) {			//If the mark of the current element is less than the current lowest mark
			*ptr_lowest = list[i].marks;			//save the new lowest mark
		}
		average += list[i].marks;					//Add the current mark to the overall average 
	}

	average /= num - 1;								//Calculate the average by using the size of the array - 1 for accurate results

	return average;									//Return the average
}
void print_summary(float avg, float high, float low) {
	printf("### result of marks analysis ###\n");
	printf("average: %0.2f, highest marks: %0.2f, lowest marks: %0.2f\n", avg, high, low);		//Print the results of the summary
}