/*/*
== Banking - Savings Account ==
Author	: Justin Cook
Date	: 19/10/16
Revision: 20/10/16
Workshop: #6 in-Lab
*/

#include <stdio.h>


// Structure Declaration for account
struct account
{
	int accNumber;				// Account number
	double balance;				// Balance of the account
};

double balanceUp(double balance, double amount) {

	if (amount >= 0) {				//If the amount is greater than 0 do the addition
		balance += amount;		
	}
	return balance;					//If the number isn't greater than 0 it just returns the balance as it was
}

double interestCalc(double balance, double rate) {		//Function for calculating interest
	balance *= (rate / 100);								//Math for the interest
	return balance;										//Return the new balance

}

double balanceDown(double balance, double amount) {
	if (amount > balance) {
		printf("Withdrawal failed. You only have : %.2lf in your account\n\n", balance);
	}
	else{
		balance -= amount;
		printf("Current balance is : %0.2lf\n\n", balance);
	}
	return balance;
}

int main()
{
	const int nosClients = 5;							// Number of accounts
	int option, i, choice, counter = 0;					// Hold the selection
	double addamount, calcInterest, subamount;			// Initialize the struct account array with opening balance
	const double lowcharge = 2.50;
	const double highcharge = 7.50;
	
	struct account acct[5] = { { 11111111, 123.45 },{ 22222222, 12365.50 },{ 33333333,0 },{ 44444444,1475 },{ 55555555,25000.65 } };

	printf("***** Welcome to Savings Account Banking *****\n\n");

	do
	{
		// Print the option list
		printf("1.) Deposit \n");
		printf("2.) Withdraw\n");
		printf("3.) Apply monthly interest earnings to all accounts\n");
		printf("4.) Apply service charges to all accounts\n");
		printf("5.) Account Summary\n");
		printf("0.) Log out\n\n");
		printf("Please enter an option to continue: ");

		// Waiting for the input
		scanf("%d", &option);

		switch (option)
		{
		case 0: // Exit the program
			break;

		case 1: // Deposit

			printf("\n-- Make a deposit --\n");
			printf("\nEnter account number: ");								//Promt for account number
			scanf("%d", &choice);											//Entering account number
		
			for (i = 0; i <= nosClients; i++) {								//Loop to iterate through to see if number is valid
				if (acct[i].accNumber == choice ) {							//If the number is valid
			
					printf("Enter amount to deposit (CAD): ");					//Prompt for amount you want to add
					scanf("%lf", &addamount);									//Reading in the amount you wish to add
					acct[i].balance = balanceUp(acct[i].balance, addamount);		//the function that decides if the number is valid
					printf("Current balance is : %0.2lf\n\n", acct[i].balance);		//Printing your new balance
					counter++;
				}
			}
			if (counter == 0) {
				printf("ERROR: Account number does not exist.\n\n");			//If the number isn't in the system it will error
			}

			counter = 0;
			break;

		case 2: // Withdraw funds
			printf("\n-- Withdraw funds --\n\n");									//Prompt for input
			printf("Enter account number: ");
			scanf("%d", &choice);

			for (i = 0; i < nosClients; i++) {									//Loop through clients
				if (acct[i].accNumber == choice) {	
					printf("Enter amount to withdraw (CAD): ");					//Prompt for amount to withdraw
					scanf("%lf", &subamount);								
					acct[i].balance = balanceDown(acct[i].balance, subamount);	//Subtracting the withdrawal from the balance	
					counter++;
				}
			}
			if (counter == 0) {
				printf("ERROR: Account number does not exist.\n\n");			//If the number isn't in the system it will error
			}


			break;

		case 3: // Apply interest earnings to all accounts
			printf("\n-- Add monthly interest earnings to all accounts --\n\n");
			printf("Account# New Balance Interest Earnings (M)\n-------- ----------- ---------------------\n");

			for (i = 0; i < nosClients; i++) {				//Loop to go through all the accounts and add correct interest 
				if (acct[i].balance < 500) {
					calcInterest = interestCalc(acct[i].balance, 0.99);				//Saving interest into variable
					acct[i].balance = balanceUp(acct[i].balance, calcInterest);		//Adding interest to the balance 
				}
				else if (acct[i].balance > 500 && acct[i].balance < 1500) {
					calcInterest = interestCalc(acct[i].balance, 1.66);				//Saving interest into variable
					acct[i].balance = balanceUp(acct[i].balance, calcInterest);		//Adding interest to the balance 
				}
				else if (acct[i].balance > 1500) {
					calcInterest = interestCalc(acct[i].balance, 2.49);				//Saving interest into variable
					acct[i].balance = balanceUp(acct[i].balance, calcInterest);		//Adding interest to the balance
				}

				printf("%8d %11.2lf %21.2lf\n", acct[i].accNumber, acct[i].balance, calcInterest); //Print interest info
			}
			printf("\n");
			break;

		case 4: // Apply Service Charges
			printf("\n-- Apply service charges to all accounts --\n");
			printf("\nAccount# New Balance Service charges (M)\n-------- ----------- -------------------\n");
			for (i = 0; i < nosClients; i++) {											//Loop through the clients
				if (acct[i].balance < 1500){											//If the balance is less than 1500
					acct[i].balance -= highcharge;										
					printf("%8d %11.2lf %19.2lf\n", acct[i].accNumber, acct[i].balance, highcharge);	//Print balance and charge
				}
				if (acct[i].balance > 1500) {											//If the balance is greater than 1500
					acct[i].balance -= lowcharge;		
					printf("%8d %11.2lf %19.2lf\n", acct[i].accNumber, acct[i].balance, lowcharge);		//Print balance and charge
				}
			}
			printf("\n");

			break;

		case 5: // Display Account Information
			printf("\n-- Account information --\n\n");							
			printf("Account# Balance   \n-------- ----------\n");
			for (i = 0; i < nosClients; i++) {									//Loop for printing account info
				printf("%8d %10.2lf\n", acct[i].accNumber, acct[i].balance);
			}
			printf("\n");

			break;

		default:
			printf("Error: Please enter a valid option to continue\n\n");
			break;
		}


	} while (option != 0);


	return 0;
}