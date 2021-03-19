#include  "math_exam_model.h"

using namespace std;
Tasks::Tasks(ifstream& file)
{
	if (!file.is_open())
	{
		throw exception("File with tasks not found");
	}
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
	srand(static_cast<unsigned>(time(nullptr)));
	group.emplace_back("Ivanov", static_cast<student_type>(rand() % 3));
	group.emplace_back("Pertov", static_cast<student_type>(rand() % 3));
	group.emplace_back("Sidorov", static_cast<student_type>(rand() % 3));
	group.emplace_back("Kuznetsov", static_cast<student_type>(rand() % 3));
	group.emplace_back("Plotnikov", static_cast<student_type>(rand() % 3));
	return group;
}

//void give_tasks(std::vector<Student>& group, int eq_per_student, std::ifstream& tasks_file)
//{
//	try
//	{
//		Tasks eqs(tasks_file);
//		for (auto& v:eqs._eqs)
//		{
//			v.print_roots();
//			cout << endl;
//		}
//
//		const size_t num_eqs = eqs._eqs.size();
//		srand(static_cast<unsigned>(time(nullptr)));
//		for (int i = 0; i < eq_per_student; i++) {
//			for (auto& student : group)
//			{
//				student.get_task(eqs._eqs[rand() % num_eqs]);
//			}
//		}
//	} catch(exception& exc) {
//		cout << exc.what() << endl;
//	}
//
//}


void Student::get_task(const QuadEq& eq)
{
	_eq = eq;
}

Solution Student::solve_task() const
{
	vector<double> roots;
	if (_type == bad)
	{
		roots.push_back(0);
	}
	else
	{
		roots = _eq.roots();
		if (_type == avg)
		{
			srand(static_cast<unsigned>(time(nullptr)));
			if (rand() % 2)
				roots = { 0 };
		}
	}
	return { _name + to_string(_type), roots, _eq};
}

void Student::send_task(Teacher& teacher) const
{
	teacher.collect_solutions(solve_task());
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
