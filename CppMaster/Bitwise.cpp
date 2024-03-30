#include <iostream>

int main()
{
	long tiles(0'111'111'110);
	std::cout << tiles << std::endl;

	int amount = 0;

	for (int bit{ 0 }; bit < 9; bit++)
	{
		amount += (tiles >> (bit * 3)) & 0'7;
		std::cout << amount << std::endl;
	}

	system("pause");
	return 0;
}