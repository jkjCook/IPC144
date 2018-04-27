//Justin Cook

#include <stdio.h>
#define MAX_ITEMS 10

struct Item {
	int sku_;
	float price_;
	int quantity_;
};

void menu(void);
int validate(const int high, const int low);
void clear();
void displayInventory(const struct Item items[], const int size);
int searchInventory(const struct Item items[], const int sku_item, const int size);
void addItem(struct Item items[], int *size);
void checkPrice(const struct Item items[], const int size);

int main(void) {
	struct Item item[MAX_ITEMS];

	int size = 0;
	int counter = 0;
	
	clear();
	printf("Welcome to the Shop\n===================\n");
	
	while (counter == 0) {
		menu();
		switch (validate(4,0)) {
		case 1:
			displayInventory(item, size);
			break;
		case 2:
			addItem(item, &size);
			break;
		case 3:
			printf("Please input the sku number of the item:\n");
			checkPrice(item, MAX_ITEMS);
			break;
		case 4:
			clear();
			break;
		case 0:
			printf("Goobye!\n");
			counter++;
			return 0;
			break;
		}
	}
	system("pause");
	

}

void menu(void) {  // The function displays the menu
	printf("Please select from the following options:\n");


		printf("1) Display the inventory.\n");
		printf("2) Add to shop.\n");
		printf("3) Price check.\n");
		printf("4) Clear screen.\n");
		printf("0) Exit.\n");
		printf("Select: ");

}
int validate(const int high, const int low) {
	int choice;
	
	scanf("%d", &choice);								//prompt for your integer
	
	while (choice < low || choice > high) {			//checks if it is in the range and loops until a valid number is entered
		printf("Invalid input, try again: ");
		scanf("%d", &choice);
	}
	return choice;
}
void clear() {
	int i;

	for (i = 0; i < 40; i++ ) {						//Loops 40 new lines
		printf("\n");
	}
}
void displayInventory(const struct Item items[], const int size) {
	int i;

	printf("\n\nInventory\n=========================================\n");		//displaying the inventory
	printf("Sku         Price       Quanity\n");

	for (i = 0; i < size; i++) {
		printf("%01d%13.2f%8d         \n", items[i].sku_, items[i].price_, items[i].quantity_);
	}
	printf("=========================================\n");
}
int searchInventory(const struct Item items[], const int sku_item, const int size) {
	int i;
	int counter = 1;

	for (i = 0; i < size; i++) {					//Looping through to see if the sku is found
		if (items[i].sku_ == sku_item) {			//If the sku is found it returns the counter - 1 so that it reflects the 
			counter -= 1;
			return counter;							//correct index number
		}
		else {
			counter++;
		}
	}
		if (counter >= size) {					//Checking if the counter is equal to the size of the array to see if 
			counter = -1;						//It has ran through the loop completely
			return counter;						//And returning the - 1 if it has not found any results
	}
	
}
void addItem(struct Item items[], int *size) {
	int sku;
	int quantity;
	int index;
	double price;
	
	printf("Please input a SKU number: ");								//Inputs
	scanf("%d", &sku);
	printf("Quantity: ");
	scanf("%d", &quantity);

	index = searchInventory(items, sku, *size);							//Saving the index number to a holder variable			

	if (index == -1) {													//If the index is -1 it means it isn't in the array
		if (*size == MAX_ITEMS) {										//Checking if full
			printf("Inventory is full.\n");
		}
		if (*size != MAX_ITEMS){										//If not full then add the new elements to the next
			printf("Price: ");											//element of the array
			scanf("%lf", &price);	
			items[*size].sku_ = sku;
			items[*size].quantity_ = quantity;
			items[*size].price_ = price;
			*size += 1;	//incrementing the size for the next element
			printf("The item is successfully added to the inventory.\n");
		}
	}
	if (index > -1){															//Updating the array if the sku is found
		printf("The item exists in the repository, quantity is updated.\n");
		items[index].quantity_ = quantity;
	}

}
void checkPrice(const struct Item items[], const int size) {
	int sku = 0, counter = 0, i = 0;								//checking if the item is in the array
	scanf("%d", &sku);												//then checking what the price of the item is

	for (i = 0; i <= size; i++) {
		if (sku == items[i].sku_) {
			printf("Item %d costs $%0.2f\n", items[i].sku_, items[i].price_);
			counter++;
		}
	}

	if (counter == 0) {
		printf("Item does not exist in the shop! Please try again.\n");
	}

	counter = 0;
}
