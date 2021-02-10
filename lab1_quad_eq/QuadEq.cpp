#include "QuadEq.h"

using namespace std;


QuadEq::QuadEq(const double a_, const double b_, const double c_) {
	a = a_;
	b = b_;
	c = c_;
	type = EqType();
}

// constructor for the case if coefficients are not known yet
QuadEq::QuadEq() {
	a = 0;
	b = 0;
	c = 0;
	type = -1;
}

double QuadEq::Det() const{
	return b * b - 4 * a * c;
}



// 0 - no roots
// 1 - root=0
// 2 - root = -b/c
// 3 - -b/2a
// 4 - root = 0 & -b/a
// 5 - 2 roots
int QuadEq::EqType() const {
	if (type == -1) // coefficients havent been initialized
		return -1;
	if (!a) {
		if (!b)
			return 0;
		else
			return (!c ? 1 : 2);
	}
	else if (!c) {
		if (!b)
			return 1;
		return 4;
	}
	else {
		double det = Det();
		if (det<0)
			return 0;
		else {
			return !det ? 3 : 5;
		}
	}
}


//size_t QuadEq::RootAmount() const{
//	if (type == -1) {
//		cout << "Coefficients havent been initialized" << endl;
//		return -1;
//	}
//	else if (!type)
//		return 0;
//	else
//		return (type < 4 ? 1 : 2);
//
//}

vector <double> QuadEq::Roots() const{
	vector <double> roots;
	if (type == 1)
		roots.push_back(0);
	else if (type == 2)
		roots.push_back(-c / b);
	else if (type == 3)
		roots.push_back(-b / (2 * a));
	else if (type==4){
		roots.push_back(0);
		roots.push_back(-b / a);
	}
	else if (type == 5){
		double det = Det();
		roots.push_back((-b + sqrt(det)) / (2 * a));
		roots.push_back((-b - sqrt(det)) / (2 * a));
	}
	return roots;
}


void QuadEq::PrintRoots() const{
	if (type == -1) {
		cout << "Coefficients havent been initialized" << endl;
		return;
	}
	vector <double> roots = Roots();
	size_t size = roots.size();
	cout << "Equation with coefficients " << a << ' ' << b << ' ' << c << " has " << size << " root";
	if (size != 1)
		cout << "s";// 0 roots and 2 roots but 1 root
	if (size) {
		cout << ": " << roots[0];
		if (size > 1)
			cout << ", " << roots[1];
	}
	cout << endl;
}

istream& operator>>(istream& stream, QuadEq& eq) {
	double a, b, c;
	if (!(stream >> a >> b >> c)) {
		cout << "Invalid input" << endl;
		return stream;
	}
	QuadEq copy(a, b, c);
	eq = copy;
	return stream;
}