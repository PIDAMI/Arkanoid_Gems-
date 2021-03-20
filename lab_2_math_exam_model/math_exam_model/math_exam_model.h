#pragma once

#include <utility>
#include <vector>
#include <cmath>
#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <map>
#include <ctime>
#include <random>



class QuadEq
{
private:
	std::vector <double> _coef;
	double lin_eq_root(double k, double c) const;
	std::vector <double> non_zero_coef_root() const;
public:
	QuadEq(const double a, const double b, const double c);
	QuadEq() {};
	double det() const;
	std::vector <double> roots() const;
	std::vector<double> coef() const;
	void print_roots() const;

};

std::ifstream& operator>>(std::ifstream& stream, QuadEq& eq);


enum student_type
{
	good = 0,
	avg = 1,
	bad = 2
};



struct Tasks
{
	std::vector<QuadEq> _eqs;
	Tasks(std::ifstream& file);

};

struct Solution
{
	std::string _name;
	std::vector<double> _roots;
	QuadEq _eq;
	Solution(std::string name, std::vector<double> roots, QuadEq eq) :
	_name(std::move(name)), _roots(std::move(roots)), _eq(std::move(eq)){};
	Solution() {};
};


class Teacher
{
private:
	std::vector<Solution> _queue_solutions;
	std::map<std::string, int> _performance_table;
public:
	Teacher() {};
	void collect_solutions(const Solution& solution);
	void review_solutions() ;
	void print_table() const;
};



class Student
{
private:
	const std::string _name;
	const student_type _type;
public:
	Student(std::string name, const student_type& type) :_name(std::move(name)), _type(type) {};
	Solution solve_task(const QuadEq& eq) const;
	void send_task(Teacher& teacher, const QuadEq& eq) const;
};

std::vector<Student> init_simple_student_group();


