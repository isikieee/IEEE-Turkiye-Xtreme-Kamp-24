#include <iostream>
#include <vector>

using namespace std;

vector<vector<pair<int, int>>> polyominoes = {
    {{0, 0}, {1, 0}, {0, 1}, {1, 1}}, // 2x2 block
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}}  // 1x4 block
};

bool can_place(vector<vector<int>> &grid, vector<pair<int, int>> &shape, int r, int c)
{
    for (auto &[dr, dc] : shape)
    {
        int nr = r + dr, nc = c + dc;
        if (nr < 0 || nr >= grid.size() || nc < 0 || nc >= grid[0].size() || grid[nr][nc] != 0)
            return false;
    }
    return true;
}

void place(vector<vector<int>> &grid, vector<pair<int, int>> &shape, int r, int c, int val)
{
    for (auto &[dr, dc] : shape)
    {
        grid[r + dr][c + dc] = val;
    }
}

bool backtrack(vector<vector<int>> &grid, int r, int c)
{
    if (r == grid.size())
        return true;
    if (c == grid[0].size())
        return backtrack(grid, r + 1, 0);
    if (grid[r][c] != 0)
        return backtrack(grid, r, c + 1);

    for (int i = 0; i < polyominoes.size(); ++i)
    {
        if (can_place(grid, polyominoes[i], r, c))
        {
            place(grid, polyominoes[i], r, c, i + 1);
            if (backtrack(grid, r, c + 1))
                return true;
            place(grid, polyominoes[i], r, c, 0);
        }
    }
    return false;
}

bool can_tile_with_polyominoes(vector<vector<int>> &grid)
{
    return backtrack(grid, 0, 0);
}

int main()
{
    vector<vector<int>> grid = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};

    if (can_tile_with_polyominoes(grid))
    {
        cout << "The grid can be tiled with polyominoes." << endl;
    }
    else
    {
        cout << "The grid cannot be tiled with polyominoes." << endl;
    }

    return 0;
}
