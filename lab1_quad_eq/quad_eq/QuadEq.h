#pragma once

#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
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

std::ifstream& operator>>(std::ifstream& stream, QuadEq& eq);


