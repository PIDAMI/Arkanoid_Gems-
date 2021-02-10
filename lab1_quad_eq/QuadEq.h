#pragma once
#ifndef QUADEQ
#define QUADEQ
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <istream>
class QuadEq
{
private:
	double a;
	double b;
	double c;
	int type;
	int EqType() const;

public:
	QuadEq(const double a_, const double b_, const double c_);
	QuadEq();
	double Det() const;
	//size_t RootAmount() const;
	std::vector <double> Roots() const;
	void PrintRoots() const;

};

std::istream& operator>>(std::istream& stream, QuadEq& eq);
#endif // !QUADEQ

