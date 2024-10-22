#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

vector<int> naiveStringMatcher(string str, string sub)
{
	int n = str.length(); // длина строки
	int m = sub.length(); // длина искомой подстроки
	vector<int> pos;
	
	for (int i = 0; i <= (n - m); ++i)
	{
		if (str.substr(i, m) == sub)
		{
			pos.push_back(i);
		}
	}

	if (pos.empty()) pos.push_back(-1);

	return pos;
}
