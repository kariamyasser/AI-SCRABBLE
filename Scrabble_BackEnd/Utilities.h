#pragma once
# define MAX 100 
class Utilities {
	long double factorialDB[100];
	long long triangle[MAX + 1][MAX + 1];
public:
	long double Cparta(int K, int r);
	long double Cpartb(int N, int n);
	long double Cpartc(int N, int K, int n, int r);
	void makeTriangle();
	long double factorial(int n);
	long  double C(int n, int r);
	void setFactorialDB();
	Utilities();
	~Utilities();
};





