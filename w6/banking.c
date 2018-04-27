/*/*
== Banking - Savings Account ==
Author	: Justin Cook
Date	: 19/10/16
Revision: 20/10/16
Workshop: #6 in-Lab
*/

#include <stdio.h>

struct account
{
	int accNumber;				
	double balance;				
};

double balanceUp(double balance, double amount) {
	if (amount >= 0)
		balance += amount;		
	return balance;
}

double interestCalc(double balance, double rate) {
	balance *= (rate / 100);
	return balance;
}

double balanceDown(double balance, double amount) {
	if (amount > balance)
		printf("Withdrawal failed. You only have : %.2lf in your account\n\n", balance);
	else {
		balance -= amount;
		printf("Current balance is : %0.2lf\n\n", balance);
	}
	return balance;
}

int main() {
	const int nosClients = 5;
	int option, i, choice, counter = 0;
	double addamount, calcInterest, subamount;
	const double lowcharge = 2.50;
	const double highcharge = 7.50;
	struct account acct[5] = { { 11111111, 123.45 },{ 22222222, 12365.50 },{ 33333333,0 },{ 44444444,1475 },{ 55555555,25000.65 } };
	printf("***** Welcome to Savings Account Banking *****\n\n");

	do {
		printf("1.) Deposit \n");
		printf("2.) Withdraw\n");
		printf("3.) Apply monthly interest earnings to all accounts\n");
		printf("4.) Apply service charges to all accounts\n");
		printf("5.) Account Summary\n");
		printf("0.) Log out\n\n");
		printf("Please enter an option to continue: ");
		scanf("%d", &option);

		switch (option) {
		case 0:
			break;

		case 1: 
			printf("\n-- Make a deposit --\n");
			printf("\nEnter account number: ");
			scanf("%d", &choice);
			for (i = 0; i <= nosClients; i++) {
				if (acct[i].accNumber == choice ) {
					printf("Enter amount to deposit (CAD): ");
					scanf("%lf", &addamount);
					acct[i].balance = balanceUp(acct[i].balance, addamount);
					printf("Current balance is : %0.2lf\n\n", acct[i].balance);
					counter++;
				}
			}
			if (counter == 0)
				printf("ERROR: Account number does not exist.\n\n");
			counter = 0;
			break;

		case 2:
			printf("\n-- Withdraw funds --\n\n");
			printf("Enter account number: ");
			scanf("%d", &choice);
			for (i = 0; i < nosClients; i++) {
				if (acct[i].accNumber == choice) {	
					printf("Enter amount to withdraw (CAD): ");
					scanf("%lf", &subamount);								
					acct[i].balance = balanceDown(acct[i].balance, subamount);
					counter++;
				}
			}
			if (counter == 0)
				printf("ERROR: Account number does not exist.\n\n");
			break;

		case 3:
			printf("\n-- Add monthly interest earnings to all accounts --\n\n");
			printf("Account# New Balance Interest Earnings (M)\n-------- ----------- ---------------------\n");
			for (i = 0; i < nosClients; i++) { 
				if (acct[i].balance < 500) {
					calcInterest = interestCalc(acct[i].balance, 0.99);
					acct[i].balance = balanceUp(acct[i].balance, calcInterest);
				}
				else if (acct[i].balance > 500 && acct[i].balance < 1500) {
					calcInterest = interestCalc(acct[i].balance, 1.66);
					acct[i].balance = balanceUp(acct[i].balance, calcInterest);
				}
				else if (acct[i].balance > 1500) {
					calcInterest = interestCalc(acct[i].balance, 2.49);
					acct[i].balance = balanceUp(acct[i].balance, calcInterest);
				}
				printf("%8d %11.2lf %21.2lf\n", acct[i].accNumber, acct[i].balance, calcInterest);
			}
			printf("\n");
			break;

		case 4:
			printf("\n-- Apply service charges to all accounts --\n");
			printf("\nAccount# New Balance Service charges (M)\n-------- ----------- -------------------\n");
			for (i = 0; i < nosClients; i++) {
				if (acct[i].balance < 1500) {
					acct[i].balance -= highcharge;										
					printf("%8d %11.2lf %19.2lf\n", acct[i].accNumber, acct[i].balance, highcharge);
				}
				if (acct[i].balance > 1500) {
					acct[i].balance -= lowcharge;		
					printf("%8d %11.2lf %19.2lf\n", acct[i].accNumber, acct[i].balance, lowcharge);
				}
			}
			printf("\n");
			break;

		case 5:
			printf("\n-- Account information --\n\n");							
			printf("Account# Balance   \n-------- ----------\n");
			for (i = 0; i < nosClients; i++) {
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
