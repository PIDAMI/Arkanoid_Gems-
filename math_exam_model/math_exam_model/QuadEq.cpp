#include "math_exam_model.h"
using namespace std;


QuadEq::QuadEq(const double a, const double b, const double c) {
	_coef.push_back(a);
	_coef.push_back(b);
	_coef.push_back(c);
}

double QuadEq::det() const {
	return _coef[1] * _coef[1] - 4 * _coef[0] * _coef[2];
}

// solve linear equation kx + c = 0
double QuadEq::lin_eq_root(double k, double c) const {
	return !c ? 0 : -c / k;
}

vector <double> QuadEq::non_zero_coef_root() const {
	double determ = det();
	double a = _coef[0];
	double b = _coef[1];
	double c = _coef[2];
	vector <double> res;
	if (!determ)
		res.push_back(-b / (2 * a));
	else if (determ > 0) {
		res.push_back((-b + sqrt(determ)) / (2 * a));
		res.push_back((-b - sqrt(determ)) / (2 * a));
	}
	return res;
}





vector <double> QuadEq::roots() const {
	vector <double> roots;
	if (!_coef.empty()) {
		double a = _coef[0];
		double b = _coef[1];
		double c = _coef[2];
		if (!a) {
			// bx + c = 0
			if (b)
				roots.push_back(lin_eq_root(b, c));
		}
		else if (!c) {
			// ax^2 = 0
			roots.push_back(0);
			// x (ax + b) = 0
			if (b)
				roots.push_back(lin_eq_root(a, b));
		}
		else {
			vector<double> non_zero_coef_roots = non_zero_coef_root();
			for (auto& root : non_zero_coef_roots)
				roots.push_back(root);
		}
	}
	return roots;
}

std::vector<double> QuadEq::coef() const
{
	return _coef;
}




void QuadEq::print_roots() const {
	if (_coef.empty()) {
		cout << "Coefficients havent been initialized" << endl;
		return;
	}
	vector <double> root = roots();
	size_t size = root.size();
	double a = _coef[0];
	double b = _coef[1];
	double c = _coef[2];
	cout << "Equation with coefficients " << a << ' ' << b << ' ' << c << " has " << size << " root";
	if (size != 1)
		cout << "s";// 0 roots and 2 roots but 1 root
	if (size) {
		cout << ": " << root[0];
		if (size > 1)
			cout << ", " << root[1];
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