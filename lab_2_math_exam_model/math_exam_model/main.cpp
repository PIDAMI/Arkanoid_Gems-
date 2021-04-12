#include "math_exam_model.h"
#include <iostream>

using namespace std;


int main()
{


	
	ifstream file("tasks.txt");
	if (!file.is_open())
	{
		cout << "File with tasks not found";
		exit(1);
	}

	
	srand(static_cast<unsigned>(time(nullptr)));
	auto group = init_simple_student_group();
	const Tasks tasks(file);
	int num_eqs = tasks._eqs.size();
	Teacher teacher;
	int eq_per_student = 5;
	for (int i = 0; i < eq_per_student; i++)
	{
		for (auto& student : group)
		{
			student->send_task(teacher, tasks._eqs[rand() % num_eqs]);
		}
	}
	teacher.review_solutions();
	teacher.print_table();

	return 0;
}