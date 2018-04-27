//Justin Cook
#include <stdio.h>
#include <ctype.h>

#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0

/* ms1 prototypes*/
void welcome(void);
void prnTitle(void);
void prnFooter(double gTotal);
void pause(void);
void clrKyb(void);
int getInt(void);
double getDbl(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDblLimited(double lowerLimit, double upperLimit);

/* ipc_ms2 prototype*/
int yes(void);
struct Item {
	double price;
	int sku;
	int isTaxed;
	int quantity;
	int minQuantity;
	char name[21];
};

/* ms3 prototypes*/
double totalAfterTax(struct Item item);
int isLowQty(struct Item item);
struct Item itemEntry(int sku);
void dspItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);

const double TAX = 0.13;

/*int main() {
	struct Item I[21] = {
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
	double val;
	int ival;
	int searchIndex;
	val = totalAfterTax(I[0]);
	printf("totalAfterTax: yours=%lf, program's=44.000000\n", val);
	val = totalAfterTax(I[7]);
	printf("totalAfterTax: yours=%lf, program's=101.474000\n", val);
	ival = isLowQty(I[0]);
	printf("isLowQty: yours=%d, program's=0\n", ival);
	ival = isLowQty(I[14]);
	printf("isLowQty: yours=%d, program's=1\n", ival);
	pause();
	printf("itemEntry, enter the following values:\n");
	printf("        SKU: 999\n"
		"       Name: Red Apples\n"
		"      Price: 4.54\n"
		"   Quantity: 50\n"
		"Minimum Qty: 5\n"
		"   Is Taxed: n\n");
	printf("Enter the values:\n");
	I[20] = itemEntry(999);
	printf("dspItem, Linear:\nYours: ");
	dspItem(I[20], LINEAR);
	printf(" Prog: |999|Red Apples          |    4.54|   No|  50 |   5 |      227.00|\n");
	printf("dspItem, Form:\nYours:\n");
	dspItem(I[20], FORM);
	printf("Programs: \n");
	printf("        SKU: 999\n"
		"       Name: Red Apples\n"
		"      Price: 4.54\n"
		"   Quantity: 50\n"
		"Minimum Qty: 5\n"
		"   Is Taxed: No\n");
	I[20].quantity = 2;
	I[20].isTaxed = 1;
	pause();
	printf("dspItem, Linear with low value and taxed:\nYours: ");
	dspItem(I[20], LINEAR);
	printf(" Prog: |999|Red Apples          |    4.54|  Yes|   2 |   5 |       10.26|***\n");
	printf("dspItem, Form with low value:\nYours:\n");
	dspItem(I[20], FORM);
	printf("Programs: \n");
	printf("        SKU: 999\n"
		"       Name: Red Apples\n"
		"      Price: 4.54\n"
		"   Quantity: 2\n"
		"Minimum Qty: 5\n"
		"   Is Taxed: Yes\n"
		"WARNING: Quantity low, please order ASAP!!!\n");
	pause();
	printf("Listing Items: \n");
	listItems(I, 21);
	pause();
	printf("Locate Item, successful search:\n");
	printf("program: Found the item 999 at index: 20\n");
	printf("  Yours: ");
	if (locateItem(I, 21, 999, &searchIndex)) {
		printf("Found the item 999 at index: %d\n", searchIndex);
	}
	else {
		printf("No item with the sku 999 is in the array!\n");
	}

	printf("Locae Item, unsuccessful search:\n");
	printf("Progam: No item with the sku 732 is in the array!\n");
	printf(" Yours: ");
	if (locateItem(I, 21, 732, &searchIndex)) {
		printf("Found the item at index: %d\n", searchIndex);
	}
	else {
		printf("No item with the sku 732 is in the array!\n");
	}
	return 0;
}*/

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
	if (item.quantity < item.minQuantity) return 1;
	else return 0;
}

struct Item itemEntry(int sku) {
	struct Item item; 
	item.sku = sku;
	printf("        SKU: %d\n", item.sku);
	printf("       Name: ");
	scanf("%20[^\n]", item.name);
	clrKyb();
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

void dspItem(struct Item item, int linear) {
	double total = 0;
	if (linear == 1) {
		printf("|%d", item.sku);
		printf("|%-20s", item.name);
		printf("|%8.2lf", item.price);
		if (item.isTaxed == 1) {
			printf("|  Yes");
			total = totalAfterTax(item);
		}
		else {
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
	if (linear == 0) {
		printf("        SKU: %d\n", item.sku);
		printf("       Name: %s\n", item.name);
		printf("      Price: %.2lf\n", item.price);
		printf("   Quantity: %d\n", item.quantity);
		printf("Minimum Qty: %d\n", item.minQuantity);
		if (item.isTaxed == 1)
			printf("   Is Taxed: Yes\n");
		else
			printf("   Is Taxed: No\n");
		if (item.minQuantity > item.quantity)
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
	int counter = 0, i; 
	for (i = 0; i < NoOfRecs; i++) {
		if (item[i].sku == sku ) {
			*index = counter;
			return 1;
		}
		counter++;
	}
	return 0;
}
