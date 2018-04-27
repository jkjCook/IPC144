//Justin Cook

#include <stdio.h>
#include <ctype.h>

void searchTest();
void updateTest();
void addTest();
void addOrUpdateTest();
void adjustQtyTest();

struct Item {
	double price;
	int sku;
	int isTaxed;
	int quantity;
	int minQuantity;
	char name[21];
};

struct Item GI[21] = {
	{ 4.4,275,0,10,2,"Royal Gala Apples" },
	{ 5.99,386,0,20,4,"Honeydew Melon" },
	{ 3.99,240,0,30,5,"Blueberries" },
	{ 10.56,916,0,20,3,"Seedless Grapes" },
	{ 2.5,385,0,5,2,"Pomegranate" },
	{ 0.44,495,0,100,30,"Banana" },
	{ 0.5,316,0,123,10,"Kiwifruit" },
	{ 4.49,355,1,20,5,"Chicken Alfredo" },
	{ 5.49,846,1,3,5,"Veal Parmigiana" },
	{ 5.29,359,1,40,5,"Beffsteak Pie" },
	{ 4.79,127,1,30,3,"Curry Checken" },
	{ 16.99,238,1,10,2,"Tide Detergent" },
	{ 10.49,324,1,40,5,"Tide Liq. Pods" },
	{ 10.99,491,1,50,5,"Tide Powder Det." },
	{ 3.69,538,1,1,5,"Lays Chips S&V" },
	{ 3.29,649,1,15,5,"Joe Org Chips" },
	{ 1.79,731,1,100,10,"Allen's Apple Juice" },
	{ 6.69,984,1,30,3,"Coke 12 Pack" },
	{ 7.29,350,1,50,5,"Nestea 12 Pack" },
	{ 6.49,835,1,20,2,"7up 12 pack" }
};
int GNoOfRecs = 20;

#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0
#define MAX_ITEM_NO 21
#define MAX_QTY 999
#define SKU_MAX 999
#define SKU_MIN 100
const int TAX = 0.13;

void welcome(void) {
	printf("---=== Grocery Inventory System ===---\n\n");
}

void prnTitle(void) {
	printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
	printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
}

void prnFooter(double gTotal) {
	printf("--------------------------------------------------------+----------------\n");
	if (gTotal >= 0)
		printf("                                           Grand Total: | %11.2lf\n", gTotal);
}

void clrKyb(void) {
	char choice = 'a';
	while (choice != '\n')
		scanf("%c", &choice);
}

void pause(void) {
	printf("Press <ENTER> to continue...");
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
		} else counter++;
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

int yes(void) {
	char choice = ' ';
	int number = 2;
	scanf("%c", &choice);
	clrKyb();
	choice = toupper(choice);
	if (choice == 'Y')
		number = 1;
	else if (choice == 'N')
		number = 0;
	while (number == 2) {
		printf("Only (Y)es or (N)o are acceptable: ");
		scanf("%c", &choice);
		clrKyb();
		choice = toupper(choice);
		if (choice == 'Y')
			number = 1;
		else if (choice == 'N')
			number = 0;
	}
	return number;
}

double totalAfterTax(struct Item item) {					
	double total = 0;
	if (item.isTaxed != 0)
		total = ((item.price * item.quantity) * 1) * (TAX + 1);
	else
		total = ((item.price * item.quantity) * 1);
	return total;
}

int isLowQty(struct Item item) {
	if (item.quantity <= item.minQuantity)
		return 1;
	else
		return 0;
}

void dspItem(struct Item item, int linear) {
	double total = 0;
	if (linear == LINEAR) {
		printf("|%d", item.sku);
		printf("|%-20s", item.name);
		printf("|%8.2lf", item.price);
		if (item.isTaxed == 1) {
			printf("|  Yes");
			total = totalAfterTax(item);
		} else {
			printf("|   No");
			total = totalAfterTax(item);
		}
		printf("| %3d ", item.quantity);
		printf("| %3d ", item.minQuantity);
		printf("|%12.2f|", total);
		if (isLowQty(item) == 1)
			printf("***\n");
		else
			printf("\n");
	}
	if (linear == FORM) {
		printf("        SKU: %d\n", item.sku);
		printf("       Name: %s\n", item.name);
		printf("      Price: %.2lf\n", item.price);
		printf("   Quantity: %d\n", item.quantity);
		printf("Minimum Qty: %d\n", item.minQuantity);
		if (item.isTaxed == 1)
			printf("   Is Taxed: Yes\n");
		else
			printf("   Is Taxed: No\n");
		if (item.minQuantity >= item.quantity)
			printf("WARNING: Quantity low, please order ASAP!!!\n");
	}
}

void listItems(const struct Item item[], int NoOfItems) {
	double total = 0;
	prnTitle();
	for (int i = 0; i < NoOfItems; i++) {
		printf("%-4d", i + 1);
		total += totalAfterTax(item[i]);
		dspItem(item[i], LINEAR);
	}
	prnFooter(total);
}

int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index) {
	int counter = 0;
	for (int i = 0; i < NoOfRecs; i++) {
		if (item[i].sku == sku) {
			*index = counter;
			return 1;								
		}
		counter++;
	}
	return 0;
}

struct Item itemEntry(int sku) {
	struct Item item;
	item.sku = sku;
	printf("        SKU: %d\n", item.sku);
	printf("       Name: ");
	scanf("%20s", item.name);
	printf("      Price: ");
	item.price = getDbl();
	printf("   Quantity: ");
	item.quantity = getInt();
	printf("Minimum Qty: ");
	item.minQuantity = getInt();
	printf("   Is Taxed: ");
	item.isTaxed = yes();
	return item;
}

void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQty(struct Item item[], int NoOfRecs, int stock);


/*End of Milestone 4 defintions and prototypes:
***************************************************************/

/*************************************************************
Main tester */
/*int main() {
	searchTest();
	updateTest();
	addTest();
	addOrUpdateTest();
	adjustQtyTest();
	return 0;
}

/*End of main tester
******************************************************************/


/***************************************************************
Milestone 4 functions to be implemented */
void search(const struct Item item[], int NoOfRecs) {
	int choice = 0, number;
	int index;

	while (choice < SKU_MIN || choice > SKU_MAX) {
		printf("Please enter the SKU: ");
		scanf("%d", &choice);
	}
	if (locateItem(item, NoOfRecs, choice, &index) == 1) {
		number = index;
		dspItem(item[number], FORM);
	} else printf("Item not found!\n");
}

void updateItem(struct Item* itemptr) {
	struct Item item;
	int choice = 0;
	printf("Enter new data:\n");
	item = itemEntry(itemptr->sku);
	printf("Overwrite old data? (Y)es/(N)o: ");
	choice = yes();
	if (choice == 1) {
		printf("--== Updated! ==--\n");
		*itemptr = item;
	} else printf("--== Aborted! ==--\n");
}

void addItem(struct Item item[], int *NoOfRecs, int sku) {
	struct Item number;
	if (*NoOfRecs < MAX_ITEM_NO) {
		number = itemEntry(sku);
		printf("Add Item? (Y)es/(N)o: ");
		if (yes() == 1) {
			printf("--== Added! ==--\n");
			item[*NoOfRecs] = number;
			*NoOfRecs += 1;
		} else printf("--== Aborted! ==--\n");
	}
	else printf("Can not add new item; Storage Full!\n"); 
}

void addOrUpdateItem(struct Item item[], int* NoOfRecs) {
	int choice = 0, index = 0, number = 0;
	while (choice < SKU_MIN || choice > SKU_MAX) {
		printf("Please enter the SKU: ");
		scanf("%d", &choice);
	}
	if (locateItem(item, *NoOfRecs, choice, &index) == 1) {
		dspItem(item[index], FORM);
		printf("Item already exists, Update? (Y)es/(N)o: ");
		clrKyb();
		number = yes();
		if (number == 1) 
      updateItem(&item[index]);
		else 
      printf("--== Aborted! ==--\n");
	} else addItem(item, NoOfRecs, choice);
}

void adjustQty(struct Item item[], int NoOfRecs, int stock) {
	int choice = 0, index = 0, value = 0, add = 0, sub = 0;
	while (choice < SKU_MIN || choice > SKU_MAX) {
		printf("Please enter the SKU: ");
		scanf("%d", &choice);
	}
	if (locateItem(item, NoOfRecs, choice, &index) == 1){
		dspItem(item[index], FORM);
		if (stock == STOCK) {
			value = MAX_QTY - item[index].quantity;												
			printf("Please enter the quantity to stock; Maximum of %d or 0 to abort: ", value);	//Accept the amount you want to add
			add = getIntLimited(0, value);
			if (add == 0)
				printf("--== Aborted! ==--\n");
			else {
				printf("--== Stocked! ==--\n");
				item[index].quantity += add;
			}
		} else {
			printf("Please enter the quantity to checkout; Maximum of %d or 0 to abort: ", item[index].quantity);	//If CHECKOUT
			sub = getIntLimited(0, item[index].quantity);					//You can only checkout valid numbers
			if (sub == 0) 
				printf("--== Aborted! ==--\n");
			else {															//If over 0 it subtracts from quantity
				printf("--== Checked out! ==--\n");
				item[index].quantity -= sub;
				if (isLowQty(item[index]) == 1)
					printf("Quantity is low, please reorder ASAP!!!\n");
			}
		}
	} else printf("SKU not found in storage!\n");
}

void searchTest() {
	printf("================Search Test:\n");
	printf("Enter 731: \n");
	search(GI, GNoOfRecs);
	printf("Enter 222: \n");
	search(GI, GNoOfRecs);
}

void updateTest() {
	struct Item I = { 11.11,111,1,11,1,"Ones!" };
	printf("================Update Test:\n");
	printf("Enter the follwoing: \n");
	printf(
		"         SKU: 111\n"
		"        Name: Grape\n"
		"      Price : 22.22\n"
		"   Quantity : 22\n"
		"Minimum Qty : 2\n"
		"   Is Taxed : y\n"
		"Overwrite old data? (Y)es/(N)o: n\n");
	updateItem(&I);
	printf("Unchanged Item Data:\n");
	dspItem(I, FORM);
	printf("Enter the follwoing: \n");
	printf(
		"         SKU: 111\n"
		"        Name: Grape\n"
		"      Price : 22.22\n"
		"   Quantity : 22\n"
		"Minimum Qty : 2\n"
		"   Is Taxed : y\n"
		"Overwrite old data? (Y)es/(N)o: y\n");
	updateItem(&I);
	printf("Updated Item: \n");
	dspItem(I, FORM);
}

void addTest() {
	printf("================Add Test:\n");
	printf("Total items in Storage: %d, Max no: %d\n", GNoOfRecs, MAX_ITEM_NO);
	printf("Enter the follwoing: \n");
	printf(
		"         SKU: 222\n"
		"        Name: Grape\n"
		"      Price : 22.22\n"
		"   Quantity : 22\n"
		"Minimum Qty : 2\n"
		"   Is Taxed : y\n"
		"Add Item? (Y)es/(N)o: n\n");
	addItem(GI, &GNoOfRecs, 222); //n
	printf("Garbage here! Nothing is added, No of items in storage: %d\n", GNoOfRecs);
	dspItem(GI[GNoOfRecs], FORM);
	printf("Enter the follwoing: \n");
	printf(
		"         SKU: 222\n"
		"        Name: Grape\n"
		"      Price : 22.22\n"
		"   Quantity : 22\n"
		"Minimum Qty : 2\n"
		"   Is Taxed : y\n"
		"Add Item? (Y)es/(N)o: y\n");
	addItem(GI, &GNoOfRecs, 222); //y
	printf("New item is added, No of itemsinstorage: %d\n", GNoOfRecs);
	dspItem(GI[GNoOfRecs - 1], FORM);
	printf("Adding 333: \n");
	addItem(GI, &GNoOfRecs, 333);
}
void addOrUpdateTest() {
	GNoOfRecs = MAX_ITEM_NO;
	printf("================AddOrUpdate Test:\n");
	printf("Enter 731 and then \'n\':\n");
	addOrUpdateItem(GI, &GNoOfRecs); 
	printf("Enter 731, \'y\' and then:\n"
		"       Name: Apple\n"
		"      Price: 1.80\n"
		"   Quantity: 101\n"
		"Minimum Qty: 11\n"
		"   Is Taxed: n\n"
		"Overwrite old data? (Y)es/(N)o: y\n");
	addOrUpdateItem(GI, &GNoOfRecs); 
	printf("Updated Item: \n");
	dspItem(GI[16], FORM);
	printf("Enter 444: \n");
	addOrUpdateItem(GI, &GNoOfRecs); 
}

void adjustQtyTest() {
	printf("================AdjustQty Test:\n");
	printf("Invalid SKU Test; Enter 444:\n");
	adjustQty(GI, GNoOfRecs, STOCK);
	printf("Aborting Entry test; Enter 731 and then 0:\n");
	adjustQty(GI, GNoOfRecs, CHECKOUT);
	printf("Checking out with low quantity warning; Enter 731 and then 90:\n");
	adjustQty(GI, GNoOfRecs, CHECKOUT);
	printf("Stocking; Enter 731 and then 50:\n");
	adjustQty(GI, GNoOfRecs, STOCK);
	dspItem(GI[16], FORM);
}
