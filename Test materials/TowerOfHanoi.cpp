#include<iostream>
#include<time.h>
using namespace std;

// tower of HANOI function implementation
void moveDisk(int n, char Original, char Aux, char Dest)
{
	/*
	* Please implement this function with a given I/O format.
	*
	*/

	// ANSWER BELOW 
	if (n == 0)
		return;

	moveDisk(n - 1, Original, Dest, Aux);

	cout << "Move Disk " << n << " " << "from " << Original << " to " << Dest << endl;
	
	moveDisk(n - 1, Aux, Original, Dest);
	// ANSWER ABOVE 
}

// main program
int main()
{
	int n;
	time_t start, end;

	cout << "Enter the number of disks:";
	cin >> n;

	// calling the moveDisk
	time(&start);
	moveDisk(n, 'A', 'B', 'C');
	time(&end);

	double elapse = difftime(end, start);
	cout << "The elapsed time is " << elapse << " seconds" << " for moving " << n << " disks " << endl;

	return 0;
}