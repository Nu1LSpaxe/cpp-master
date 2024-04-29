#include <string>
#include <vector>
#include <iostream>
#include "Helper.h"

int editDist_Memo(std::string str1, std::string str2, int m, int n, std::vector<std::vector<int>> memo)
{
    if (m == 0) return n;   // Insert all chars of str2 into str1
    if (n == 0) return m;   // Remove all chars of str1

    // return from memo if n*m has been executed
    if (memo[m][n] != -1)
    {
        return memo[m][n];
    }

    if (str1[m - 1] == str2[n - 1])
    {
        return memo[m][n] = editDist_Memo(str1, str2, m - 1, n - 1, memo);
    }

    int insert = editDist_Memo(str1, str2, m, n - 1, memo);
    int remove = editDist_Memo(str1, str2, m - 1, n, memo);
    int replace = editDist_Memo(str1, str2, m - 1, n - 1, memo);

    return memo[m][n] = 1 + Min(insert, remove, replace);
}

void TestEditDistance_Memo()
{
    std::string str1 = "sunday";
    std::string str2 = "saturday";

    int m = str1.length();
    int n = str2.length();
    // Initialize table with -1. table.size = [m+1][n+1]
    std::vector<std::vector<int>> memo(m + 1, std::vector<int>(n + 1, -1));

    std::cout << "the minimum number of edits (operations) is "
        << editDist_Memo(str1, str2, m, n, memo) << std::endl;
}

/*
Time Complexity: O(m*n)
Auxiliary Space: O(m*n)+O(m+n) for (m*n) extra array space and (m+n) recursive stack space.
*/