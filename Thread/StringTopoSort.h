#include <vector>
#include <string>

class StringTopoSort
{
public:
	StringTopoSort(std::vector<std::string> [] ,int );
	~StringTopoSort();

	std::vector<std::string> string_topo_sort();

private:
	void visit(int index);
	int len;
	std::vector<std::string> *str_lists;
	std::vector<std::string> unsorted;
	std::vector<std::string> sorted;
	std::vector<int> *digit_eq;
	std::vector<int> digit_sorted;
	std::vector<bool> is_visited;
};