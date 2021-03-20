#include  "math_exam_model.h"

using namespace std;
Tasks::Tasks(ifstream& file)
{
	//if (!file.is_open())
	//{
	//	throw exception("File with tasks not found");
	//}
	QuadEq eq;
	while (!file.eof())
	{
		file >> eq;
		_eqs.push_back(eq);
	}
}

vector<Student> init_simple_student_group()
{
	vector<Student> group;
	group.emplace_back("Ivanov", static_cast<student_type>(rand() % 3));
	group.emplace_back("Pertov", static_cast<student_type>(rand() % 3));
	group.emplace_back("Sidorov", static_cast<student_type>(rand() % 3));
	group.emplace_back("Kuznetsov", static_cast<student_type>(rand() % 3));
	group.emplace_back("Plotnikov", static_cast<student_type>(rand() % 3));
	return group;
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
	_queue_solutions.clear();
}

void Teacher::print_table() const
{
	for (const auto& [student,num]:_performance_table)
	{
		cout << student << ": " << num << endl;
	}
}
