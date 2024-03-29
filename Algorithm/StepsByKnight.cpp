/**
 * Minimum steps to reach target by a Knight
 * This problem can be seen as the shortest path in an unweighted graph.
 *
 * reference: https://www.geeksforgeeks.org/minimum-steps-reach-target-knight/?ref=lbp
 */


 // Define reachable number of board
#include <vector>
#include <queue>
#include <iostream>
#define MAX_N 30

// Structure for storing a cell's data
struct cell
{
    int c_x, c_y, c_dis;
    cell() {}
    cell(int x, int y, int dis) : c_x(x), c_y(y), c_dis(dis) {}
};

// Check if the place lies in the board
bool isValid(int x, int y)
{
    return (x >= 1 && x <= MAX_N && y >= 1 && y <= MAX_N);
}

/**
 * @param knightPos the position of knight
 * @param targetPos the position of target
 * @param dx defined x where knight can move
 * @param dy defined y where knight can move
 */
int minStepToReachTarget(std::vector<int>& knightPos, std::vector<int>& targetPos, std::vector<int>& dx, std::vector<int>& dy)
{
    // queue for storing states of knight in board
    std::queue<cell> qu;

    cell curr;
    int x, y;
    bool visit[MAX_N + 1][MAX_N + 1];

    // Initializing
    for (size_t i{ 0 }; i <= MAX_N; ++i)
        for (size_t j{ 0 }; j <= MAX_N; ++j)
            visit[i][j] = false;

    // push starting position of knight with 0 distance
    qu.push(cell(knightPos[0], knightPos[1], 0));
    visit[knightPos[0]][knightPos[1]] = true;

    int length{ (int)std::size(dx) };

    while (!qu.empty())
    {
        curr = qu.front();
        qu.pop();

        // If current cell is equal to target cell, return its distance.
        if (curr.c_x == targetPos[0] && curr.c_y == targetPos[1])
            return curr.c_dis;

        for (size_t i{ 0 }; i < length; ++i)
        {
            x = curr.c_x + dx[i];
            y = curr.c_y + dy[i];

            // If reachable state is not yet visited, push the state into queue
            if (isValid(x, y) && !visit[x][y])
            {
                visit[x][y] = true;
                qu.push(cell(x, y, curr.c_dis + 1));
            }
        }
    }

    return -1;
}

void TestStepsByKnight()
{

    std::vector<int> knightPos{ 1, 1 };
    std::vector<int> targetPos{ 30, 30 };

    // x and y direction, where a knight can move
    std::vector<int> dx{ -2, -1, 1, 2, -2, -1, 1, 2 };
    std::vector<int> dy{ -1, -2, -2, -1, 1, 2, 2, 1 };

    std::cout << minStepToReachTarget(knightPos, targetPos, dx, dy);
}