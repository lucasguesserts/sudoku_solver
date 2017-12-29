#include <vector>
#include <iostream>

using namespace std;

int main()
{
	const vector< vector<double> > x = {
		{1, 2, 3},
		{4, 5},
		{6, 7, 8}
	};

	for(auto r: x)
	{
		for(auto c: r)
		{
			cout << c << " ";
		}
	}
	cout << endl;
	//x[0][0] = 3; //compilation error!

	return 0;
}
