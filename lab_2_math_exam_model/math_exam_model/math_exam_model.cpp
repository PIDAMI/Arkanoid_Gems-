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

vector<Student*> init_simple_student_group()
{
	vector<Student*> group;
	const vector<string> names = { "Ivanov" ,"Pertov" ,"Sidorov" ,"Kuznetsov" ,"Plotnikov" };
	for (int i = 0; i < 5; i++) {
		int type = rand() % 3;
		if (type == 0)
			group.push_back(new GoodStudent(names[i]));
		else if (type == 1)
			group.push_back(new AvgStudent(names[i]));
		else
			group.push_back(new BadStudent(names[i]));
	}
	return group;
}

//Solution GoodStudent::solve_task(const QuadEq& eq) const
//{
//	vector<double> roots;
//	if (_type == bad)
//	{
//		roots.push_back(0);
//	}
//	else
//	{
//		roots = eq.roots();
//		if (_type == avg)
//		{
//			if (rand() % 2)
//				roots = { 0 };
//		}
//	}
//	return { get_name, roots,S eq };
//}

Solution GoodStudent::solve_task(const QuadEq& eq) const
{
	return { get_name(), eq.roots(),eq};
}

Solution AvgStudent::solve_task(const QuadEq& eq) const
{
	vector<double> roots = eq.roots();
	if (rand() % 2)
		roots = { 0 };
	return { get_name(), roots,eq };
}

Solution BadStudent::solve_task(const QuadEq& eq) const
{
	return { get_name(), {0}, eq };
}


void Student::send_task(Teacher& teacher, const QuadEq& eq) const
{
	teacher.collect_solutions(solve_task(eq));
}


void Teacher::collect_solutions(const Solution& solution) 
{
	_queue_solutions.push_back(solution);
}


Table Teacher::get_table()
{
	map<string,int> table;

	for (const auto& sol:_queue_solutions)
	{
		table[sol._name];
		if (sol._eq.roots() == sol._roots)
			table[sol._name]++;
	}
	_queue_solutions.clear();
	return Table(table);
}

void Table::print() const
{
	if (_performance_table.empty())
		cout << "empty table";
	
	for (const auto& [student,num]:_performance_table)
		cout << student << ": " << num << endl;
}
