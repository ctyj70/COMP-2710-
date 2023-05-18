//=============================================================================
// Name        : project1_young_cty0008.cpp
// Author      : Chris CJ Young (cty0008)
// Version     : 8/29/2021
// 
//  COMP2710 Project 1 (Loans for Stereo System)
//=============================================================================

#include <iostream>
using namespace std;

int main() {

	// Format for Currency
	cout.setf(ios::fixed);

	cout.setf(ios::showpoint);

	cout.precision(2);

	// Variable names
	float loan = -1;

	float interest = -1;

	float payments = -1;

	// Get Loan and Interest
	while (loan <= 0) {

		cout << "\nLoan Amount: ";
		cin >> loan;
	}

	while (interest <= -1) {

		cout << "Interest Rate (% per year): ";
		cin >> interest;
	}

	// Initial Formulas/Calculations for interest and payment 
	float interest_rate = interest / 12 / 100;

	while (payments <= 0 || payments <= loan * interest_rate) {

		cout << "Monthly Payments: ";
		cin >> payments;
	}

	cout << endl;

	// Amortization Table
	cout << "*****************************************************************\n"
		<< "\tAmortization Table\n"
		<< "*****************************************************************\n"
		<< "Month\tBalance\t  Payment\tRate\tInterest\tPrincipal\n";

	int cur_month = 0;
	float interest_total = 0;

	while (loan > 0) {
		if (cur_month == 0) {

			cout << cur_month++ << "\t$" << loan;
			if (loan < 1000) cout << "\t";
			cout << "  N/A\t\tN/A\tN/A\t\tN/A\n";
		}
		else {

			float interest_payment = loan * interest_rate;
			float principal_payment = payments - interest_payment;
			loan -= principal_payment;
			interest_total += interest_payment;

			if (loan < 0) {

				principal_payment += loan;
				payments += loan;
				loan = 0;
			}

			cout << cur_month++ << "\t$" << loan;
			if (loan < 1000) cout << "\t";
			cout << "  $" << payments << "\t" << interest_rate * 100 << "\t$" << interest_payment << "\t\t$" << principal_payment << "\n";
		}
	}

	cout << "****************************************************************\n";
	cout << "\nIt takes " << --cur_month << " months to pay off "
		<< "the loan.\n"
		<< "Total interest paid is: $" << interest_total;
	cout << endl << endl;

	return 0;
}
