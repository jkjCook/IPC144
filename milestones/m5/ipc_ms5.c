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




/********************************************************************
Milestones 1 to 4  prototypes, definitions and etc...*/
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
/*End of milestone 1 to 4 stuff
*********************************************************************/



/********************************************************************
Milestone 5 prototypes*/


#define MAX_ITEM_NO 500   
//#define DATAFILE "ipc_ms5_short.txt" 
#define DATAFILE "items.txt"

void saveItem(struct Item item, FILE* dataFile);
int loadItem(struct Item* item, FILE* dataFile);
int saveItems(struct Item* item, char fileName[], int NoOfRecs);
int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr);

/*End of milestone 5 prototypes
*********************************************************************/




/**************************************************************************
TTTTTTTTT   EEEEEEEE   SSSSSSSS   TTTTTTTTTT   EEEEEEEEE   RRRRRRRR
TT       EE         SS             TT       EE          RR     RR
TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RRRRRRRR
TT       EE               SS       TT       EE          RR  RR
TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RR    RR
***************************************************************************
Tester for saveItem, loadItem, saveItems and loadItems:
uncomment this to test your functions prior to putting all the code together by adding a * and / here:


*/
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

/* End Main function
********************************************************************/





/********************************************************************
Milestone 5 functions*/

void saveItem(struct Item item, FILE* dataFile) {		//Writes a single item into a file
	fprintf(dataFile, "%d,%d,%d,%.2lf,%d,%s\n", item.sku, item.quantity, item.minQuantity, item.price, item.isTaxed, item.name);
}
int loadItem(struct Item* item, FILE* dataFile) {
	int ret = 0, amount = 0;
	
	amount = fscanf(dataFile, "%d,%d,%d,%lf,%d,%21[^\n]\n", &item->sku, &item->quantity, &item->minQuantity, &item->price, &item->isTaxed, item->name);
	if (amount == 6) {		//To see if 6 items were read and to change the return to true
		ret = 1;
	}
	return ret;				//The return is set to false unless 6 items are read
}
int saveItems(struct Item* item, char fileName[], int NoOfRecs) {
	int ret = 0, i;
	FILE* fp = NULL;

	fp = fopen(fileName, "w");

	if (fp != NULL) {								//Loops through and calls saveItem to write the item into the file
		for (i = 0; i < NoOfRecs; i++) {
			saveItem(item[i], fp);					//Uses the function to do multiple elements of an array
		}
		ret = 1;
	}

	fclose(fp);
	return ret;
}
int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr) {
	int ret = 1, c, i, recs = 0;
	struct Item holder;
	FILE* fp = NULL;

	fp = fopen(fileName, "r+");

	if (fp != NULL) {							//Counting the number of records in the file
		do{	
			c = fgetc(fp);
			if ((char)c != EOF) {
				if ((char)c == '\n') {
					recs++;
				}
			}
		} while (feof(fp) == 0);

		rewind(fp);								//Rewinding to the beginning of the file to loop through again

		for (i = 0; i < recs; i++) {			//Uses a holder item to save the individual records 
			ret = loadItem(&holder, fp);		//Saves the record into the right element of the array
			item[i] = holder;
		}
	}
	else {
		ret = 0;
	}
	fclose(fp);

	*NoOfRecsPtr = recs;						//Saves the number of records into the pointer to the main

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

//Prints the header for LINEAR printing method
void prnTitle(void) {
	printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
	printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
}

//Prints the footer for the LINEAR method, accepts the total of all items added together in arguments
void prnFooter(double gTotal) {
	printf("--------------------------------------------------------+----------------\n");
	if (gTotal >= 0) {																				//Print if gTotal is > 0
		printf("                                           Grand Total: | %11.2lf\n", gTotal);
	}
}

//Accepts a new line character
void clrKyb(void) {
	char choice = ' ';

	//do  {				//Loops until it reaches a return
		scanf("%c", &choice);
	//} while (choice != '\n');
}

//Uses clrKyb to create a pause in the console 
void pause(void) {
	printf("Press <ENTER> to continue...");
	clrKyb();									//Accepts an enter to end the function
}

//Gets an integer and makes sure that it is an integer
int getInt(void) {
	int validInteger, counter = 0;
	char validChar = ' ';

	while (counter == 0) {

		scanf("%d%c", &validInteger, &validChar);				//Read in your integer followed by enter
		if (validChar != '\n') {								//If the character after your int isn't a space
			clrKyb();											//Clear the keyboard
			printf("Invalid integer, please try again: ");		//Error message
		}
		else {													//To break the loop if conditions are met
			counter++;
		}
	}
	return validInteger;										//Return the valid integer 
}

//Gets a double and makes sure that it is a double
double getDbl(void) {
	double validDouble;
	int counter = 0;
	char validChar = ' ';

	while (counter == 0) {

		scanf("%lf%c", &validDouble, &validChar);				//Read in your double followed by enter
		if (validChar != '\n') {								//If the character after your int isn't a space
			clrKyb();											//Clear the keyboard
			printf("Invalid number, please try again: ");		//Error message
		}
		else {													//To break the loop if conditions are met
			counter++;
		}
	}
	return validDouble;											//Return the valid double
}

//Gets an integer and makes sure it is within a specific range, the arguments accept the lowest and highest possible numbers in the range
int getIntLimited(int lowerLimit, int upperLimit) {
	int choice = 0;

	scanf("%d", &choice);														//Prompt for an integer
	while (choice < lowerLimit || choice > upperLimit) {						//Checking if the integer is in the correct range
		printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);		//If it's not it prompts you again and tells you 
		scanf("%d", &choice);													//The correct range
	}
	return choice;
}

//Gets adouble and makes sure it is within a specific range, the arguments accept the lowest and highest possible numbers in the range
double getDblLimited(double lowerLimit, double upperLimit) {
	double choice = 0;

	scanf("%lf", &choice);														//Prompt for a floating point
	while (choice < lowerLimit || choice > upperLimit) {						//Checking if the floating point is in the correct range
		printf("Invalid value, %lf < value < %lf: ", lowerLimit, upperLimit);	//If it's not it prompts you again and tells you 
		scanf("%lf", &choice);													//The correct range
	}
	return choice;
}

//Accepts either a (y,Y) or an (n,N) and only accepts those characters, returns 1 for yes and 0 for no
int yes(void) {
	char choice = ' ';
	int number = 2;

	scanf(" %c", &choice);										//Initial prompt for a character
	clrKyb();
	choice = toupper(choice);									//Function to make the character uppercase always

	if (choice == 'Y') {										//Checking if the char is a Y or an N
		number = 1;
	}
	else if (choice == 'N') {
		number = 0;
	}

	while (number == 2) {										//Loop to make sure that the entered char is valid

		printf("Only (Y)es or (N)o are acceptable: ");
		scanf(" %c", &choice);
		choice = toupper(choice);
		clrKyb();
		

		if (choice == 'Y') {
			number = 1;
		}
		else if (choice == 'N') {
			number = 0;
		}
	}

	return number;												//Returns either 1 or 0 for Yes or No
}

/*In the arguments accepts the structure of item and uses the member isTaxed inside of the struct to decide whether to do a regular
total or to add tax to the items total, returns the total in double form*/
double totalAfterTax(struct Item item) {
	double total = 0;

	if (item.isTaxed == 0) {
		total = ((item.price * item.quantity) * 1);
	}
	else {
		total = item.price * item.quantity * (TAX + 1);
	}
	return total;
}

/*Accepts a struct in the arguments and uses the members quantity and minQuantity to see if quantity is lower, if it is it returns 1 (true)
if it isn't then it returns 0 (false)*/
int isLowQty(struct Item item) {
	if (item.quantity <= item.minQuantity) {					//Checks if quantity is higher than minQuantity, if it is not it returns 0
		return 1;
	}
	else {
		return 0;
	}
}

/*Accepts struct and either LINEAR or FORM in the arguments because this is where the item is displayed, this function prints the 
members of struct in two different ways, LINEAR and FORM*/
void dspItem(struct Item item, int linear) {
	double total = 0;

	if (linear == LINEAR) {								//Formatting for the LINEAR method of displaying items
		printf("|%d", item.sku);
		printf("|%-20s", item.name);
		printf("|%8.2lf", item.price);
		if (item.isTaxed == 1) {						//The item prints differently for if it's taxed or not
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
		if (isLowQty(item) == 1) {			//The item prints differently if it's low quantity or not
			printf("***\n");
		}
		else {
			printf("\n");
		}
	}

	if (linear == FORM) {									//The same formatting method of printing but this is the FORM way
		printf("        SKU: %d\n", item.sku);
		printf("       Name: %s\n", item.name);
		printf("      Price: %.2lf\n", item.price);
		printf("   Quantity: %d\n", item.quantity);
		printf("Minimum Qty: %d\n", item.minQuantity);
		if (item.isTaxed == 1) {
			printf("   Is Taxed: Yes\n");
		}
		else {
			printf("   Is Taxed: No\n");
		}
		if (item.minQuantity >= item.quantity) {
			printf("WARNING: Quantity low, please order ASAP!!!\n");
		}
	}
}

/*Accepts a struct array and the number of iterations in the arguments and uses the members of struct array to print all of the items in 
LINEAR mode only while adding all of the totals using the totalAfterTax function*/
void listItems(const struct Item item[], int NoOfItems) {
	int i;
	double total = 0;

	prnTitle();

	for (i = 0; i < NoOfItems; i++) {				//Loops through and displays the item in the LINEAR way
		printf("%-4d", i + 1);
		total += totalAfterTax(item[i]);			//Saves the grand total of all the items
		dspItem(item[i], LINEAR);
	}

	prnFooter(total);								//Prints the footer with the grand total of all the items included
}

/*Accepts struct array, number of iterations, sku number and a pointer of index and uses all of these arguments to look through the struct
array and locate a specific sku number while finding which element in the array this sku is and saving that to the index pointer. Returns
1 if successful and 0 if it fails to find the sku*/
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index) {
	int counter = 0, i;

	for (i = 0; i < NoOfRecs; i++) {				//Loops through and saves the current position of the counter into the index
		if (item[i].sku == sku) {
			*index = counter;
			return 1;								//Returns 1 if it was successful
		}
		counter++;
	}
	return 0;
}

/*Accepts a sku number in the arguments and allows the user to access the members of a struct and at the end the function returns 
that struct and all of the members that you entered, the function uses getIntLimited and getDblLimited to enter the numeric members*/
struct Item itemEntry(int sku) {
	struct Item item;

	item.sku = sku;

	printf("        SKU: %d\n", item.sku);	//The prompts and formatting to enter in the information
	printf("       Name: ");
	clrKyb();
	scanf("%20[^\n]", item.name);
	printf("      Price: ");
	item.price = getDblLimited(0.01, 1000.00);
	printf("   Quantity: ");
	item.quantity = getIntLimited(1, MAX_QTY);
	printf("Minimum Qty: ");
	item.minQuantity = getIntLimited(0, 100);
	printf("   Is Taxed: ");							//To see if the item is taxed or not you use the yes() function
	item.isTaxed = yes();

	return item;										//Return the item at the end
}

/*Accepts a struct array and the number of iterations, uses the struct array to search for the sku of an item in the array, if the sku is 
found the function uses dspItem to print the item in FORM mode to the console, and if not found prints an error*/
void search(const struct Item item[], int NoOfRecs) {
	int choice = 0, number;
	int index;

	while (choice < SKU_MIN || choice > SKU_MAX) {				//if the choice is not between the variables it loops to ask again
		printf("Please enter the SKU: ");
		scanf("%d", &choice);
	}
	if (locateItem(item, NoOfRecs, choice, &index) == 1) {		//if locateItem comes back as true, it displays items in FORM
		number = index;
		dspItem(item[number], FORM);
	}
	else {														//if locateItem comes back as false, it sends and error
		printf("Item not found!\n");
	}

}

//Accepts a pointer to a struct and uses this to alter parts of the items members 
void updateItem(struct Item* itemptr) {
	struct Item item;
	int choice = 0;
	printf("Enter new data:\n");
	item = itemEntry(itemptr->sku);

	printf("Overwrite old data? (Y)es/(N)o: ");			//Ask if you want to update the item
	choice = yes();

	if (choice == 1) {									//If yes overwrite the item
		printf("--== Updated! ==--\n");
		*itemptr = item;
	}
	else {												//If no abort
		printf("--== Aborted! ==--\n");
	}

}

/*Accepts a struct, pointer to the number of records and a sku number. This function uses the struct to access the members of the 
struct array and uses the number of records pointer to see if there is enough item space left to add another item, then if there is
it adds a number to the number of records and uses the sku to put into the itemEntry functions argument*/
void addItem(struct Item item[], int *NoOfRecs, int sku) {
	struct Item number;

	if (*NoOfRecs < MAX_ITEM_NO) {							//If there is space in the array
		number = itemEntry(sku);							//Call itemEntry and set it to a new item
		printf("Add Item? (Y)es/(N)o: ");
		if (yes() == 1) {									//If yes add the item to the array
			printf("--== Added! ==--\n");
			item[*NoOfRecs] = number;
			*NoOfRecs += 1;
		}
		else {												//If no abort
			printf("--== Aborted! ==--\n");
		}
	}
	else {													//If there is no space print storage is full
		printf("Can not add new item; Storage Full!\n");
	}
}

/*Accepts the struct array to access the members of the struct and a pointer to the number of records. This function uses the 
sku you enter to see if the sku is already inside of the struct array, if it is it will display the item and ask you if you want to
update the item where it will call the updateItem function and if not it will abort. If the item isn't found it calls addItem and you
can create a new item*/
void addOrUpdateItem(struct Item item[], int* NoOfRecs) {
	int choice = 0, index = 0, number = 0;

	while (choice < SKU_MIN || choice > SKU_MAX) {				//if the choice is not between the variables it loops to ask again
		printf("Please enter the SKU: ");
		scanf("%d", &choice);
	}
	if (locateItem(item, *NoOfRecs, choice, &index) == 1) {		//If item is found display it 
		dspItem(item[index], FORM);

		printf("Item already exists, Update? (Y)es/(N)o: ");

		clrKyb();
		number = yes();

		if (number == 1) {										//If you selected to update the item call updateItem
			updateItem(&item[index]);
		}
		else {													//If you selected no abort
			printf("--== Aborted! ==--\n");
		}
	}
	else {														//If it wasn't located call addItem
		addItem(item, NoOfRecs, choice);
	}
}

/*Accepts struct array, number of records and STOCK or CHECKOUT to see if you want to subtract or add to the value of the item that
you are accessing inside of the array, if STOCK you will add to the quantity within a set limit using getIntLimited and if CHECKOUT
you will subtract from the quantity of the item within a set limit using getIntLimited*/
void adjustQty(struct Item item[], int NoOfRecs, int stock) {
	int choice = 0, index = 0, value = 0, add = 0, sub = 0;

	while (choice < SKU_MIN || choice > SKU_MAX) {				//if the choice is not between the variables it loops to ask again
		printf("Please enter the SKU: ");
		scanf("%d", &choice);
	}

	if (locateItem(item, NoOfRecs, choice, &index) == 1) {			//If the item is located 
		dspItem(item[index], FORM);									//Diplay in FORM
		if (stock == STOCK) {										//If item is equal to STOCK
			value = MAX_QTY - item[index].quantity;
			printf("Please enter the quantity to stock; Maximum of %d or 0 to abort: ", value);	//Accept the amount you want to add
			add = getIntLimited(0, value);
			if (add == 0) {																		//If 0 it aborts
				printf("--== Aborted! ==--\n");
			}
			else {																				//If over 0 it adds the amount
				printf("--== Stocked! ==--\n");
				item[index].quantity += add;
			}
		}
		else {
			printf("Please enter the quantity to checkout; Maximum of %d or 0 to abort: ", item[index].quantity);	//If CHECKOUT
			sub = getIntLimited(0, item[index].quantity);					//You can only checkout valid numbers
			if (sub == 0) {													//If 0 it aborts
				printf("--== Aborted! ==--\n");
			}
			else {															//If over 0 it subtracts from quantity
				printf("--== Checked out! ==--\n");
				item[index].quantity -= sub;
				if (isLowQty(item[index]) == 1) {
					printf("Quantity is low, please reorder ASAP!!!\n");
				}
			}

		}
	}
	else {
		printf("SKU not found in storage!\n");								//If SKU isn't located
	}
}

//The main menu system with a switch statement for choosing which functions you would like to use, the switch loops until you choose (0)exit
void GrocInvSys(void) {
	int counter = 0, number = 0, recs = 0;
	struct Item item[MAX_ITEM_NO];

	welcome();

	if (loadItems(item, DATAFILE, &recs) != 1){				//Loading the items from the DATAFILE
		printf("Could not read from %s.\n", DATAFILE);			//Error message if the items don't load
	}
	else {														//If the items are read the menu will come up
		while (counter == 0) {
			switch (menu()) {									//Switch statement for the different options
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

//The printed menu function
int menu(void) {			//Displays the menu
	int choice = 10;
	printf("1- List all items\n2- Search by SKU\n3- Checkout an item\n4- Stock an item\n5- Add new item or update item\n"
		"0- Exit program\n> ");
	choice = getIntLimited(0, 5);		//Sets the limits of the int that it will accept
	return choice;						//Return the choice

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