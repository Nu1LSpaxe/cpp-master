/**
 * Reference: https://www.geeksforgeeks.org/bk-tree-introduction-implementation/?ref=gcse
*/

#include <vector>
#include <string_view>
#include <iostream>
#include "Helper.h"

// Maximum number of words in dict[]
#define MAXN 100
// Define the tolerance value
#define TOL 2
// Define maximum length of a word
#define LEN 10

struct Node
{
    // stores the word of the current Node
    std::string_view word;

    // links to other Node in the tree
    int next[2 * LEN];

    // Constructors
    Node() {}
    Node(std::string_view x) : word(x)
    {
        // Initializing next[i] = 0
        for (size_t i{ 0 }; i < 2 * LEN; ++i)
            next[i] = 0;
    }
};

// Store the root Node
Node ROOT;

// Store every Node of the tree
Node tree[MAXN];

// Index for current Node of tree
int ptr;

// Edit Distance
// Dynamic-Approach: Table, O(m*n)
int editDistance(std::string_view str1, std::string_view str2)
{
    int m = str1.length(), n = str2.length();

    // the results will be stored in table
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

// Add current Node to the tree
void add(Node& root, Node& curr)
{
    if (root.word == "")
    {
        // If it's the first Node then make it the root Node
        root = curr;
        return;
    }

    // Get its edit distance from the root Node
    int dist = editDistance(curr.word, root.word);

    if (tree[root.next[dist]].word == "")
    {
        // If no Node exists at this dist from root
        // make it child of root Node

        // Incrementing the pointer for curr Node
        ++ptr;

        // Adding curr Node to the tree
        tree[ptr] = curr;

        // Curr Node as child of root Node
        root.next[dist] = ptr;
    }
    else
    {
        // Recursively find the parent for curr Node
        add(tree[root.next[dist]], curr);
    }
}

std::vector<std::string_view> getSimilarWords(Node& root, std::string_view str)
{
    std::vector<std::string_view> res;

    if (root.word == "")
        return res;

    // Calculating edit distance of str from root
    int dist = editDistance(root.word, str);

    // If dist is less than tolerance value
    // add it to similar words
    if (dist <= TOL)
        res.push_back(root.word);

    // Iterate over the string_view having tolerance in range[D-TOL, D+TOL]
    int start = dist - TOL;
    if (start < 0)
        start = 1;

    while (start <= dist + TOL)
    {
        std::vector<std::string_view> tmp = getSimilarWords(tree[root.next[start]], str);

        for (auto i : tmp)
            res.push_back(i);

        ++start;
    }

    return res;
}

int main()
{
    std::string_view dictionary[] = {
        "hell", "help", "shell", "smell", "fell",
        "felt", "oops", "pop", "oouch", "halt" };

    ptr = 0;
    int length = std::size(dictionary);

    // Add dictionary words to tree
    for (size_t i{ 0 }; i < length; ++i)
    {
        Node node = Node(dictionary[i]);
        add(ROOT, node);
    }

    std::vector<std::string_view> match;

    std::string_view str1 = "ops";
    match = getSimilarWords(ROOT, str1);
    std::cout << "Similar words in dictionary for " << str1 << ": ";
    for (auto x : match)
        std::cout << x << " ";
    std::cout << std::endl;

    std::string_view str2 = "helt";
    match = getSimilarWords(ROOT, str2);
    std::cout << "Similar words in dictionary for " << str2 << ": ";
    for (auto x : match)
        std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}