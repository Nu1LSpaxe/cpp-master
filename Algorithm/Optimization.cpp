// To fill a row in DP array we require only one row.
// for example, in order to get i=10, we need to get value of 9th first.


#include <vector>
#include <iostream>
#include "Helper.h"

void PrintVecInt(std::vector<int> v)
{
    for (size_t i{ 0 }; i < v.size(); ++i)
    {
        std::cout << v.at(i) << " ";
    }
    std::cout << std::endl;
}


int editDist_Opt(std::string str1, std::string str2, int m, int n)
{
    std::vector<int> prev(n + 1, 0), curr(n + 1, 0);

    for (size_t j{ 0 }; j <= n; ++j)
        prev[j] = j;

    for (size_t i{ 0 }; i <= m; ++i)
    {
        curr[0] = i;
        for (size_t j{ 1 }; j <= n; ++j)
        {
            if (str1[i - 1] == str2[j - 1])
                curr[j] = prev[j - 1];
            else
                // Insert Remove Replace
                curr[j] = 1 + Min(curr[j - 1], prev[j - 1], prev[j]);
        }
        prev = curr;
    }
    return prev[n];
}

void TestEditDistance_Opt()
{
    std::string str1 = "sunday";
    std::string str2 = "saturday";

    std::cout << "the minimum number of edits (operations) is "
        << editDist_Opt(str1, str2, str1.length(), str2.length()) << std::endl;
}