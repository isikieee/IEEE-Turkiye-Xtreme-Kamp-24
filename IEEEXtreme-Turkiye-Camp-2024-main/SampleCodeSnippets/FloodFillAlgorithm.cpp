#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void floodFill(vector<vector<int>> &grid, int x, int y, int newColor)
{
    int rows = grid.size();
    int cols = grid[0].size();
    int originalColor = grid[x][y];
    if (originalColor == newColor)
        return;

    stack<pair<int, int>> s;
    s.push({x, y});

    while (!s.empty())
    {
        auto [r, c] = s.top();
        s.pop();
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != originalColor)
            continue;

        grid[r][c] = newColor;

        s.push({r + 1, c});
        s.push({r - 1, c});
        s.push({r, c + 1});
        s.push({r, c - 1});
    }
}

int main()
{
    vector<vector<int>> grid = {
        {1, 1, 1, 1},
        {1, 1, 0, 0},
        {1, 0, 0, 1},
        {1, 1, 1, 1}};

    int x = 1, y = 1, newColor = 2;
    floodFill(grid, x, y, newColor);

    for (const auto &row : grid)
    {
        for (int cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }

    return 0;
}
