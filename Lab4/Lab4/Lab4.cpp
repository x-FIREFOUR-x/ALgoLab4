#include "Interface.h"
#include <ctime>
#include <vector>
using namespace std;
int main()
{
    srand(time(NULL));
    Interface iface;
    iface.console_interface();

	/*
    vector<int> pr1 (8, 100);
	vector<int> pr2(8, 200);

	int point = 1;
	vector<int> line1;
	auto it_l1_begin = line1.begin();
	auto it_pr_begin = pr1.begin();
	auto it_pr_p = it_pr_begin + point;
	
	vector<int> line2;
	auto it_l2_begin = line2.begin();
	auto it_pr2_begin = pr2.begin() + point;
	auto it_pr2_p = pr2.begin()+8;


	line1.insert(it_l1_begin, it_pr_begin, it_pr_p);
	line2.insert(it_l2_begin, it_pr2_begin, it_pr2_p);

	for (int i = 0; i < line1.size(); i++)
	{
		cout << line1[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < line2.size(); i++)
	{
		cout << line2[i] << " ";
	}
	cout << endl;
	*/

    return 0;
}
