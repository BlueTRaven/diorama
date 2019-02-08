#include <string>
#include <locale>
#include <vector>
using namespace std;

string str_to_lower(string &str)
{
	locale loc;
	for (string::size_type i = 0; i < str.length(); ++i)
		str[i] = std::tolower(str[i], loc);

	return str;
}

vector<int> find_all_str(string str, char character)
{
	vector<int> indices;

	for (string::size_type i = 0; i < str.length(); ++i)
	{
		if (str[i] == character)
			indices.push_back(i);
	}

	return indices;
}