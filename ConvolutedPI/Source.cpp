/*
This program uses a known equation to approximate PI by generating pairs of numbers and checking their greatest common divisor (GCD).
If the GCD is 1, then the two numbers are coPrime, they share no factors. The equation to approximate PI is, PI ~= sqrt(6/k), where k
is the number of coPrime pairs p divided by the total number of pairs q. As q approaches infinity, the equation approaches PI.
*/

#include <iostream>		//cout, cin
#include <string>		//type string
#include <stdlib.h>		//srand(), rand()
#include <time.h>		//time()
#include <cmath>		//sqrt()
#include <iomanip>		//setprecision()

const int maxVal = 2147483647; //Set maximum value

int getInput();

int generateNums(int numSets);

int GCD(int num1, int num2);

double generatePI(int numSets, int numCoprime);

void printGenPI(double generatedPI);

int main()
{
	bool quit = false;

	//Loop until given input to quit
	while (!quit) {
		int numSets = getInput();
		if (numSets != -1) {
			int numCoprime = generateNums(numSets);
			double generatedPI = generatePI(numSets, numCoprime);
			printGenPI(generatedPI);
		}
		else {
			quit = true;
		}
	}

	system("pause");
	return 0;
}

int getInput()
{
	int userInput;
	std::string check;
	int quit = -1;

	std::cout << "Please specify how many sets to generate (q to quit), large values will take a longer time: \n";
	std::cin >> userInput;
	//Loop until given a natural number < maxVal or until given 'q'
	while (std::cin.fail() || userInput > maxVal || userInput < 1) {
		std::cin.clear();
		std::cin >> check;
		if (check == "q") {
			break;
		}
		else {
			std::cout << "Invalid input. Please enter a natural number less than 2^31 - 1\n";
		}
	}

	if (check != "q") {
		return userInput;
	}
	else {
		return quit;
	}
}

int generateNums(int numSets)
{
	srand((unsigned int)time(NULL));
	int num1, num2, numCoprime = 0;

	std::cout << "Generating numbers...\n";

	//Generate random pairs of numbers, then compare them to see if they have any common divisors not 1
	for (int i = 0; i < numSets; i++) {
		num1 = rand() % maxVal + 1;
		num2 = rand() % maxVal + 1;

		if (GCD(num1, num2) == 1) {
			numCoprime+=1;
		}
	}
	return numCoprime;
}

int GCD(int num1, int num2)
{
	int temp;
	while (num2 != 0) {
		temp = num1;
		num1 = num2;
		num2 = temp % num2;
	}
	return num1;
}

double generatePI(int numSets, int numCoprime)
{
	double generatedPI;
	//The equation to approximate PI ~= sqrt(6/k) where k is the number of coPrime pairs generated out of the total number of pairs generated
	double percentCoprime = (double)numCoprime / (double)numSets;
	generatedPI = sqrt(6 / percentCoprime);
	return generatedPI;
}

void printGenPI(double generatedPI)
{
	std::cout << std::setprecision(16) << "PI calculated from the generated numbers is: " << generatedPI << "\n";
}