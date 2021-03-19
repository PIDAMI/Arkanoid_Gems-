#include "math_exam_model.h"
#include <iostream>

using namespace std;


int main()
{
	ifstream file("tasks.txt");
	if (!file.is_open())
	{
		cout << "tasks file not found" << endl;
		exit(1);
	}

	try
	{
		auto group = init_simple_student_group();
		const Tasks eqs(file);
		give_tasks(group, eqs);
		Teacher t;
		/*for (auto& st:group)
		{
			st.send_task(t);
		}
		give_tasks(group, eqs);
		for (auto& st : group)
		{
			st.send_task(t);
		}
		t.review_solutions();
		t.print_table();



		cout << endl;
		give_tasks(group, eqs);
		for (auto& st : group)
		{
			st.send_task(t);
		}*/
		Student s("kek", avg);
		s.get_task({ 0,4,1 });
		s.send_task(t);
		s.get_task({ 0,4,0 });
		s.send_task(t);
		s.get_task({ 0,4,3 });
		s.send_task(t);
		s.get_task({ 0,4,9 });
		s.send_task(t);
		t.review_solutions();
		t.print_table();
	} catch(exception& exc) {
		cout << exc.what() << endl;
	}

	
	return 0;
}