#include <vector>
#include <iostream>

using namespace std;

int main()
{
	vector< vector<double> > x = {
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

	return 0;
}
