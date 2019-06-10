#include "Utilities.h"


//TODO : change the method we compute factorial with 

long double Utilities::Cparta(int K, int r) {
	return (this->factorial(K) / this->factorial(K - r)) / this->factorial(r);
}
long double Utilities::Cpartb( int N, int n ) {
	return (this->factorial(N) / this->factorial(N - n)) / this->factorial(n);
}
long double Utilities::Cpartc(int N , int K, int n, int r) {
	return (this->factorial(N - K) / this->factorial(N - K - n + r)) / this->factorial(n - r);
}

long double Utilities::factorial(int n)     //eh max number momken nekon benhsbalo factorial ? ! 3lshan da akhro 20 
{
	if (this->factorialDB[n] != 0)
		return factorialDB[n];
	long double factorialnum;
	factorialnum = n * factorial(n - 1);
	this->factorialDB[n] = factorialnum;
	return factorialnum;
	
}

// creating rectangular for NcR by Ahmed Osman
void Utilities::makeTriangle() {
	int i, j;

	// initialize the first row
	triangle[0][0] = 1; // C(0, 0) = 1

	for (i = 1; i < MAX; i++) {
		triangle[i][0] = 1; // C(i, 0) = 1
		for (j = 1; j <= i; j++) {
			triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
		}
	}
}

//calculating C 
long double Utilities::C(int n, int r) {
	return triangle[n][r];
}

void Utilities::setFactorialDB()
{
	for (int i = 0; i < 100; i++) {
			this->factorialDB[i] = 0;
	}
	this->factorialDB[0] = 1;
	this->factorialDB[1] = 1;
}

Utilities::Utilities()
{
	this->makeTriangle();
//	this->setFactorialDB();
}


Utilities::~Utilities()
{
}



