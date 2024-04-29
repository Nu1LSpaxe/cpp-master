/* Buttom Up */

#include <iostream>
#include "Helper.h"

int editDist_Table(std::string str1, std::string str2, int m, int n)
{
    int** table = new int* [m + 1];
    for (size_t i{ 0 }; i <= m; ++i)
        table[i] = new int[n + 1];

    // fill the table with bottom-up manner
    for (size_t i{ 0 }; i <= m; ++i)
    {
        for (size_t j{ 0 }; j <= n; ++j)
        {
            if (i == 0) table[i][j] = j;
            else if (j == 0) table[i][j] = i;

            else if (str1[i - 1] == str2[j - 1]) table[i][j] = table[i - 1][j - 1];

            else table[i][j] = 1 + Min(table[i][j - 1], table[i - 1][j], table[i - 1][j - 1]);  // Insert Remove Replace
        }
    }
    return table[m][n];
}

void TestEditDistance_Table()
{
    std::string str1 = "sunday";
    std::string str2 = "saturday";

    std::cout << "the minimum number of edits (operations) is "
        << editDist_Table(str1, str2, str1.length(), str2.length()) << std::endl;
}

/*
Time Complexity: O(m*n)
Auxiliary Space: O(m*n)
*/