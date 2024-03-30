#include <iostream>
#include <set>
#include <vector>

int main()
{
	std::set<int> unionSet;
	std::vector<int> mainVec{ 3, 4, 5 };

	for (int i{ 0 }; i < 6; ++i)
	{
		std::vector<int> vals{ i, i + 1, i + 2 };

		for (auto& val : vals)
		{
			unionSet.insert(val);
		}
		for (auto& val : mainVec)
		{
			unionSet.insert(val);
		}

		for (auto& val : unionSet)
		{
			std::cout << val << " ";
		}
		std::cout << ", Size: " << unionSet.size() << std::endl;
	}

	system("pause");
	return 0;
}