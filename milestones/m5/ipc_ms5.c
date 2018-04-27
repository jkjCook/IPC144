//Justin Cook

#include <stdio.h>
#include <ctype.h>

struct Item {
	double price;
	int sku;
	int isTaxed;
	int quantity;
	int minQuantity;
	char name[21];
};

#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0
#define MAX_QTY 999
#define SKU_MAX 999
#define SKU_MIN 100
const double TAX = 0.13;

void welcome(void);
void GrocInvSys(void);
int menu(void);
void prnTitle(void);
void prnFooter(double gTotal);
void clrKyb(void);
void pause(void);
int getInt(void);
double getDbl(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDblLimited(double lowerLimit, double upperLimit);
int yes(void);
double totalAfterTax(struct Item item);
int isLowQty(struct Item item);
void dspItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);
struct Item itemEntry(int sku);
void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQty(struct Item item[], int NoOfRecs, int stock);


#define MAX_ITEM_NO 500   
#define DATAFILE "items.txt"

void saveItem(struct Item item, FILE* dataFile);
int loadItem(struct Item* item, FILE* dataFile);
int saveItems(struct Item* item, char fileName[], int NoOfRecs);
int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr);

/*void prnFile() {
	FILE* tp = fopen("test.txt", "r");
	char ch;
	if (tp) {
		for (; fscanf(tp, "%c", &ch) == 1; putch(ch));
		fclose(tp);
	}
	else {
		printf("text.txt not found\n");
	}
}


int main(void) {
	int i, n;
	struct Item GI[3] = {
		{ 4.4,275,0,10,2,"Royal Gala Apples" },
		{ 5.99,386,0,20,4,"Honeydew Melon" },
		{ 3.99,240,0,30,5,"Blueberries" },
	};
	struct Item I;
	struct Item IN[3];
	printf("***********Testing saveItem:\n");
	printf("Your saveItem saved the following in test.txt: \n");
	FILE* tp = fopen("test.txt", "w");
	if (tp) {
		for (i = 0; i < 3; i++) saveItem(GI[i], tp);
		fclose(tp);
		prnFile();
	}
	printf("*******************************\nThey have to match the following:\n");
	printf("275,10,2,4.40,0,Royal Gala Apples\n");
	printf("386,20,4,5.99,0,Honeydew Melon\n");
	printf("240,30,5,3.99,0,Blueberries\n");
	printf("***********END Testing saveItem!\n\n\n");
	pause();
	printf("***********Testing loadItem:\n");
	printf("Your loadItem loaded the following from test.txt: \n");
	tp = fopen("test.txt", "r");
	if (tp) {
		for (i = 0; i < 3; i++) {
			loadItem(&I, tp);
			dspItem(I, LINEAR);
		}
		fclose(tp);
		tp = fopen("test.txt", "w");
		fclose(tp);
	}
	printf("*******************************\nThey have to match the following:\n");
	printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
	printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
	printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
	printf("***********END Testing loadItem!\n\n\n");
	pause();
	printf("***********Testing saveItems:\n");
	printf("Your saveItems saved the following in test.txt: \n");
	saveItems(GI, "test.txt", 3);
	prnFile();
	printf("*******************************\nThey have to match the following:\n");
	printf("275,10,2,4.40,0,Royal Gala Apples\n");
	printf("386,20,4,5.99,0,Honeydew Melon\n");
	printf("240,30,5,3.99,0,Blueberries\n");
	printf("***********END Testing saveItems!\n\n\n");
	pause();
	printf("***********Testing loadItems:\n");
	printf("Your loadItems loaded the following from test.txt: \n");
	loadItems(IN, "test.txt", &n);
	for (i = 0; i < n; i++) {
		dspItem(IN[i], LINEAR);
	}
	printf("***%d***", n);
	printf("*******************************\nThey have to match the following:\n");
	printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
	printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
	printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
	printf("***********END Testing loadItems!\n\n\n");
	pause();
	printf("Done!\n");
	return 0;
}

/* End MS5 functions' tester
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/


/********************************************************************
Main function to run the application
uncomment this to test your functions after putting all the code together by adding a * and / here:*/

int main(void) {
  GrocInvSys();
  return 0;
}


void saveItem(struct Item item, FILE* dataFile) {	
	fprintf(dataFile, "%d,%d,%d,%.2lf,%d,%s\n", item.sku, item.quantity, item.minQuantity, item.price, item.isTaxed, item.name);
}

int loadItem(struct Item* item, FILE* dataFile) {
	int ret = 0, amount = 0;	
	amount = fscanf(dataFile, "%d,%d,%d,%lf,%d,%21[^\n]\n", &item->sku, &item->quantity, 
    &item->minQuantity, &item->price, &item->isTaxed, item->name);
	if (amount == 6)
		ret = 1;
	return ret;
}

int saveItems(struct Item* item, char fileName[], int NoOfRecs) {
	int ret = 0, i;
	FILE* fp = NULL;
	fp = fopen(fileName, "w");
	if (fp != NULL) {					
		for (i = 0; i < NoOfRecs; i++)
			saveItem(item[i], fp);
		ret = 1;
	}
	fclose(fp);
	return ret;
}

int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr) {
	int ret = 1, c, recs = 0;
	struct Item holder;
	FILE* fp = NULL;
	fp = fopen(fileName, "r+");
	if (fp != NULL) {
		do {	
			c = fgetc(fp);
			if ((char)c != EOF) {
				if ((char)c == '\n')
					recs++;
			}
		} while (feof(fp) == 0);
		rewind(fp);
		for (int i = 0; i < recs; i++) {
			ret = loadItem(&holder, fp);
			item[i] = holder;
		}
	} else ret = 0;
	fclose(fp);
	*NoOfRecsPtr = recs;
	return ret;
}

/*End of milestone 5 functions
*********************************************************************/

/********************************************************************
Milestones 1  to 4 functions*/
//Prints the welcome message
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

//The main menu system with a switch statement for choosing which functions you would like to use, the switch loops until you choose (0)exit
void GrocInvSys(void) {
	int counter = 0, number = 0, recs = 0;
	struct Item item[MAX_ITEM_NO];
	welcome();
	if (loadItems(item, DATAFILE, &recs) != 1)
		printf("Could not read from %s.\n", DATAFILE);
	else {
		while (counter == 0) {
			switch (menu()) {									
			case 1:
				listItems(item, recs);
				pause();
				clrKyb();
				break;
			case 2:
				search(item, recs);
				pause();
				clrKyb();
				break;
			case 3:
				adjustQty(item, recs, CHECKOUT);
				if (saveItems(item, DATAFILE, recs) == 0) {
					printf("could not update data file %s\n", DATAFILE);
				}
				pause();
				clrKyb();
				break;
			case 4:
				adjustQty(item, recs, STOCK);
				if (saveItems(item, DATAFILE, recs) == 0) {
					printf("could not update data file %s\n", DATAFILE);
				}
				pause();
				clrKyb();
				break;
			case 5:
				addOrUpdateItem(item, &recs);
				if (saveItems(item, DATAFILE, recs) == 0) {
					printf("could not update data file %s\n", DATAFILE);
				}
				pause();
				break;
			case 6:
				printf("Not implemented!\n");
				pause();
				break;
			case 7:
				printf("Not implemented!\n");
				pause();
				break;
			case 0:
				printf("Exit the program? (Y)es/(N)o): ");		//Uses the yes function to take either a Y or N for exiting
				number = yes();
				if (number == 1) {
					counter++;
				}
				break;
			}


		}
	}
}

int menu(void) {
	int choice = 10;
	printf("1- List all items\n2- Search by SKU\n3- Checkout an item\n4- Stock an item\n5- Add new item or update item\n"
		"0- Exit program\n> ");
	choice = getIntLimited(0, 5);
	return choice;

}


/*End of milestone 1 to 4 functions
*********************************************************************/

/* ms5 Tester output

***********Testing saveItem:
Your saveItem saved the following in test.txt:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
*******************************
They have to match the following:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
***********END Testing saveItem!


Press <ENTER> to continue...
***********Testing loadItem:
Your loadItem loaded the following from test.txt:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
*******************************
They have to match the following:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
***********END Testing loadItem!


Press <ENTER> to continue...
***********Testing saveItems:
Your saveItems saved the following in test.txt:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
*******************************
They have to match the following:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
***********END Testing saveItems!


Press <ENTER> to continue...
***********Testing loadItems:
Your loadItems loaded the following from test.txt:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
*******************************
They have to match the following:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
***********END Testing loadItems!


Press <ENTER> to continue...
Done!


*/
