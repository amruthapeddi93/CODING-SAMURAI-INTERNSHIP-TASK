#include<iostream>
using namespace std;
int main()
{
	int choice;
	cout << "Enter your choice :" << endl;
	cin >> choice;
	int a,b;
	cout << "Enter  a and b values:" << endl;
	cin >> a >> b;
	switch(choice)
	{
		case 1:
			cout << "Sum is a + b = " << a + b << endl;
		    break;
		case 2:
			cout << "Difference is a - b = " << a - b << endl;
			break;
		case 3:
			cout << "Product is a * b = " << a * b << endl;
			break;
		case 4:
			if(b != 0)
				cout << "Quotient is a / b = " << a / b << endl;
			else
				cout << "Division by zero is infinity" << endl;
			break;
		case 5:
			if(b != 0)
				cout << "Remainder is a % b = " << a % b << endl;
			else
				cout << "Division by zero is infinity" << endl;
			break;
		default:
			cout << "Invalid choice" << endl;
		    break;
	}
	return 0;
}