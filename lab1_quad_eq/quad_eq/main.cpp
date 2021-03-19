#include "QuadEq.h"
#include <sstream>
using namespace std;


int main() {
	

	ifstream str("d.txt");
	if (str.is_open())
	{
		QuadEq q;
		str >> q;
		
	}
	
	//// invalid arguement
	//stringstream invalid_arg("12 4.4 invalid_arguement");
	//QuadEq ia;
	//invalid_arg >> ia;
	//ia.PrintRoots();

	//// no roots
	//stringstream empty("0 0 0");
	//QuadEq e;
	//empty >> e;
	//e.PrintRoots();

	//// no roots
	//stringstream constant("0 0 3.14");
	//QuadEq cons;
	//constant >> cons;
	//cons.PrintRoots();

	//// 5.44601
	//stringstream linear("0 2.13 -11.6");
	//QuadEq lin;
	//linear >> lin;
	//lin.PrintRoots();

	//// 0
	//stringstream zero_b("0 14.88 0");
	//QuadEq zb;
	//zero_b >> zb;
	//zb.PrintRoots();

	//// 0
	//stringstream zero_a("-2.1 0 0");
	//QuadEq za;
	//zero_a >> za;
	//za.PrintRoots();

	//// no roots
	//stringstream neg_det("2 -1.1 4.5");
	//QuadEq nd;
	//neg_det >> nd;
	//nd.PrintRoots();

	//// 1
	//stringstream full_square("1 2 1");
	//QuadEq fs;
	//full_square >> fs;
	//fs.PrintRoots();

	//// 0.3421 -10.7171
	//stringstream two_roots("1.2 12.45 -4.4");
	//QuadEq tr;
	//two_roots >> tr;
	//tr.PrintRoots();


	


	return 0;
}