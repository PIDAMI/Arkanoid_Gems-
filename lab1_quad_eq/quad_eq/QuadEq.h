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
	std::vector <double> coef;
	double LinEqRoot(double k, double c) const;
	std::vector <double> NonZeroCoefRoot() const;
public:
	QuadEq(const double a, const double b, const double c);
	QuadEq() {};
	double Det() const;
	std::vector <double> Roots() const;
	void PrintRoots() const;

};

std::istream& operator>>(std::istream& stream, QuadEq& eq);
#endif // !QUADEQ

