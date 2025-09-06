#include<iostream>
#include<cstdlib>
using namespace std;
int main()
{
	int number = rand() % 100 + 1;
	int guess;
	int no_of_guesses = 0;
	cout << "....Number Guessing Game...." << endl;
	cout << "Guess a number between 1 to 100:" << endl;
	do
	{
		cin >> guess;
		no_of_guesses++;
		if (guess > number)
			cout << "Lower number=" << endl;
		else if (guess < number)
			cout << "Higher number=" << endl;
		else
			cout << "Correct Guess!" << endl;
	} while (guess != number);
	cout << "No.of Guesses=" << no_of_guesses << endl;
	return 0;
}