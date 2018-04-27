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
	int counter = 0, number = 0;
	float highest = 0, lowest = 100, average = 0;
	struct studentMarks markArray[MAX];
	struct studentMarks student; 
	welcome();
	do {
		number = get_data(&student);
		markArray[counter].id = student.id;
		markArray[counter].marks = student.marks;
		counter++;
	} while (number == 0);
	show(markArray, counter);
	average = analyze(markArray, counter, &highest, &lowest);
	print_summary(average, highest, lowest);
	return 0;
}

void welcome(void) {
	printf("####### Marks Analyzer V3.0 #######\n");
}

int get_data(struct studentMarks * ptr) {			
	int id = 0;
	float mark = 0.0;
	printf("Enter student id and marks (e.g. 12345 89.5): ");
	scanf("%d %f", &id, &mark);
	if (id != -1 && mark != -1) {
		ptr->id = id;
		ptr->marks = mark;
		return 0;
	}
	else return -1; 
}

void show(struct studentMarks list[], int num) {
	for (int i = 0; i < num - 1; i++)
		printf("%d. %d, %0.2f\n", i + 1, list[i].id, list[i].marks);
}

float analyze(struct studentMarks list[], int num, float* ptr_highest, float* ptr_lowest) {
	float average = 0.0;
	for (int i = 0; i < num - 1; i++) {
		if (list[i].marks > *ptr_highest)
			*ptr_highest = list[i].marks;
		if (list[i].marks < *ptr_lowest)
			*ptr_lowest = list[i].marks;
		average += list[i].marks;
	}
	average /= num - 1;
	return average;
}

void print_summary(float avg, float high, float low) {
	printf("### result of marks analysis ###\n");
	printf("average: %0.2f, highest marks: %0.2f, lowest marks: %0.2f\n", avg, high, low);
}
