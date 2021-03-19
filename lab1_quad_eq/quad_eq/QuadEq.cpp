#include "QuadEq.h"

using namespace std;


QuadEq::QuadEq(const double a, const double b, const double c) {
	coef.push_back(a);
	coef.push_back(b);
	coef.push_back(c);
}

double QuadEq::Det() const{
	return coef[1] * coef[1] - 4 * coef[0] * coef[2];
}

// solve linear equation kx + c = 0
double QuadEq::LinEqRoot(double k, double c) const{
	return !c ? 0 : -c / k;
}

vector <double> QuadEq::NonZeroCoefRoot() const {
	double det = Det();
	double a = coef[0];
	double b = coef[1];
	double c = coef[2];
	vector <double> res;
	if (!det)
		res.push_back(-b/(2*a));
	else if (det > 0) {
		res.push_back((-b + sqrt(det)) / (2 * a));
		res.push_back((-b - sqrt(det)) / (2 * a));
	}
	return res;
}





vector <double> QuadEq::Roots() const{
	vector <double> roots;
	if (coef.size()) {
		double a = coef[0];
		double b = coef[1];
		double c = coef[2];
		if (!a) {
			// bx + c = 0
			if (b)
				roots.push_back(LinEqRoot(b, c));
		}
		else if (!c) {
			// ax^2 = 0
			roots.push_back(0);
			// x (ax + b) = 0
			if (b)
				roots.push_back(LinEqRoot(a, b));
		}
		else {
			vector<double> non_zero_coef_roots = NonZeroCoefRoot();
			for (auto& root : non_zero_coef_roots)
				roots.push_back(root);
		}
	}
	return roots;
}


void QuadEq::PrintRoots() const{
	if (!coef.size()) {
		cout << "Coefficients havent been initialized" << endl;
		return;
	}
	vector <double> roots = Roots();
	size_t size = roots.size();
	double a = coef[0];
	double b = coef[1];
	double c = coef[2];
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

//std::ifstream& operator>>(std::ifstream& stream, QuadEq& eq);


ifstream& operator>>(ifstream& stream, QuadEq& eq) {
	double a, b, c;
	if (!(stream >> a >> b >> c)) {
		cout << "Invalid input" << endl;
		return stream;
	}
	QuadEq copy(a, b, c);
	eq = copy;
	return stream;
}