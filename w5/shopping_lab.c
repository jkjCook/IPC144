//Justin Cook

#include <stdio.h>
#define MAX_ITEMS 10

struct Item {
	int sku_;
  int quantity_;
	float price_;
};

int menu(void) {
	int choice = 0;
	printf("Please select from the following options:\n");
	do {
		printf("1) Display the inventory.\n");
		printf("2) Add to shop.\n");
		printf("0) Exit.\n");
		printf("Select:");
		scanf("%d", &choice);
		if (choice > 2 || choice < 0)
			printf("Invalid input, try again: Please select from the following options:\n");

	} while (choice < 0 || choice > 2);

	return choice;

} 

int main(void){
	struct Item item[MAX_ITEMS];
	int sku, quantity, size = 0, i, end = 0, counter = 0;
	float price;

	printf("Welcome to the Shop\n===================\n");

	while (end == 0) {
		switch (menu()) {
		case 2:
			printf("Please input a SKU number:");
			scanf("%d", &sku);
			printf("Quantity:");
			scanf("%d", &quantity);
			if (size == MAX_ITEMS) {
				printf("The inventory is full\n");
				counter++;
			}
			for (i = 0; i <= size; i++) {
				if (sku == item[i].sku_) {
					printf("The item exists in the repository, quanity is updated.\n");
					item[i].quantity_ += quantity;
					counter++;
				}
				
			}
			if (counter == 0) {
				printf("Price:");				
				scanf("%f", &price);
				item[size].sku_ = sku;
				item[size].quantity_ = quantity;
				item[size].price_ = price;
				printf("The item is successfully added to the inventory.\n");
				size++;	
			}
			counter = 0;                       
			break;
		case 1:
			printf("\n\nInventory\n=========================================\n");
			printf("Sku         Price       Quanity\n");
			
			for (i = 0; i <= size - 1; i++)
				printf("%01d%13.2f%8d         \n", item[i].sku_, item[i].price_, item[i].quantity_);			
			printf("=========================================\n");
			break;
		case 0:
			printf("Good bye!\n");			//ending the program
			end = 1;
			break;
		}
	}
	return 0;

}
