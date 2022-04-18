#include <iostream>
#include <vector>

using namespace std;

void print_subset(const vector<int>& cur_set)
{
	std::cout << "{";
	for (int e : cur_set)
		std::cout << e << " ";
	
	std::cout << "}" << std::endl;
};

void get_subset(vector<int>& numbers, vector<int>& cur_set)
{
	if (numbers.size() == 0)
	{
		print_subset(cur_set);
	}
	else
	{
		int val = numbers[numbers.size()-1];

		numbers.pop_back();


		cur_set.push_back(val);
		get_subset(numbers, cur_set);

		cur_set.pop_back();
		get_subset(numbers, cur_set);

		numbers.push_back(val);
	}
};

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "input any numbers" <<std::endl;
		exit(1);
	}

	vector<int> numbers;

	for (int i = 1; i < argc; i++)
	{
		char* ptr_end;
		int val = (int)std::strtol(argv[i], &ptr_end, 10);

		if (ptr_end != argv[i])
			numbers.push_back(val);
	}


	vector<int> cur_set;

	get_subset(numbers, cur_set);

	return 0;
}
