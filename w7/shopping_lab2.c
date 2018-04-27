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
	int size = 0, counter = 0;
	
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

void menu(void) {
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
	scanf("%d", &choice);
	while (choice < low || choice > high) {
		printf("Invalid input, try again: ");
		scanf("%d", &choice);
	}
	return choice;
}

void clear() {
	for (int i = 0; i < 40; i++ )
		printf("\n");
}

void displayInventory(const struct Item items[], const int size) {
	printf("\n\nInventory\n=========================================\n");
	printf("Sku         Price       Quanity\n");
	for (int i = 0; i < size; i++)
		printf("%01d%13.2f%8d         \n", items[i].sku_, items[i].price_, items[i].quantity_);
	printf("=========================================\n");
}

int searchInventory(const struct Item items[], const int sku_item, const int size) {
	int counter = 1;
	for (int i = 0; i < size; i++) {			
		if (items[i].sku_ == sku_item) {
			counter -= 1;
			return counter;					
		} else counter++;
	}
		if (counter >= size) {		
			counter = -1;						
			return counter;					
	}
	
}

void addItem(struct Item items[], int *size) {
	int sku;
	int quantity;
	int index;
	double price;
	
	printf("Please input a SKU number: ");
	scanf("%d", &sku);
	printf("Quantity: ");
	scanf("%d", &quantity);

	index = searchInventory(items, sku, *size);

	if (index == -1) {
		if (*size == MAX_ITEMS)
			printf("Inventory is full.\n");
		if (*size != MAX_ITEMS) {								
			printf("Price: ");
			scanf("%lf", &price);	
			items[*size].sku_ = sku;
			items[*size].quantity_ = quantity;
			items[*size].price_ = price;
			*size += 1;	
			printf("The item is successfully added to the inventory.\n");
		}
	}
	if (index > -1) {	
		printf("The item exists in the repository, quantity is updated.\n");
		items[index].quantity_ = quantity;
	}

}

void checkPrice(const struct Item items[], const int size) {
	int sku = 0, counter = 0;
	scanf("%d", &sku);
	for (int i = 0; i <= size; i++) {
		if (sku == items[i].sku_) {
			printf("Item %d costs $%0.2f\n", items[i].sku_, items[i].price_);
			counter++;
		}
	}
	if (counter == 0)
		printf("Item does not exist in the shop! Please try again.\n");
	counter = 0;
}
