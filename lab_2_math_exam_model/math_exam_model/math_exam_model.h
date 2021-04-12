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
	Solution(const std::string& name,const std::vector<double>& roots,const QuadEq& eq) :
	_name(name), _roots(roots), _eq(eq){};
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
public:
	Student(const std::string& name) :_name(name) {};
	virtual Solution solve_task(const QuadEq& eq) const = 0;
	void send_task(Teacher& teacher, const QuadEq& eq) const;
	std::string get_name() const { return _name; };
};

std::vector<Student*> init_simple_student_group();

class GoodStudent :public Student {
public:
	GoodStudent(const std::string& name) :Student(name) {};
	Solution solve_task(const QuadEq& eq) const;
};

class AvgStudent :public Student {
public:
	AvgStudent(const std::string& name) :Student(name) {};
	Solution solve_task(const QuadEq& eq) const;
};


class BadStudent :public Student {
public:
	BadStudent(const std::string& name) :Student(name) {};
	Solution solve_task(const QuadEq& eq) const;
};
