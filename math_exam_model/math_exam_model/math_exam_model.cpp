#include  "math_exam_model.h"

using namespace std;
Tasks::Tasks(ifstream& file)
{
	if (!file.is_open())
	{
		throw exception("File with tasks not found");
	}
	QuadEq eq;
	int num;
	while (!file.eof())
	{
		file >> num;
		file >> eq;
		_eqs.emplace_back(num,eq);
	}
	
}


Solution Student::solve_task(const QuadEq& eq) const
{
	vector<double> roots;
	if (_type == bad)
	{
		roots.push_back(0);
	}
	else
	{
		roots = eq.roots();
		if (_type == avg)
		{
			srand(time(0));
			if (rand() % 2)
				roots = { 0 };
		}
	}
	return { _name, roots, eq};
}

void Student::send_task(Teacher& teacher, const QuadEq& eq) const
{
	teacher.collect_solutions(solve_task(eq));
}


void Teacher::collect_solutions(const Solution& solution) 
{
	
	_queue_solutions.push_back(solution);
	
}


void Teacher::review_solutions() 
{
	for (const auto& sol:_queue_solutions)
	{
		_performance_table[sol._name];
		if (sol._eq.roots() == sol._roots)
			_performance_table[sol._name]++;
	}
}

void Teacher::print_table() const
{
	for (const auto& [student,num]:_performance_table)
	{
		cout << student << ": " << num << endl;
	}
}
