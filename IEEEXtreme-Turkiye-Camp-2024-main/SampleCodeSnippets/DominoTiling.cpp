#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 100;
bool grid[MAXN][MAXN];
bool visited[MAXN][MAXN];
int match[MAXN][MAXN];
int N, M; // Dimensions of the grid

bool is_valid(int x, int y)
{
    return x >= 0 && x < N && y >= 0 && y < M;
}

bool bpm(int x, int y)
{
    if (visited[x][y])
        return false;
    visited[x][y] = true;

    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};

    for (int d = 0; d < 4; ++d)
    {
        int nx = x + dx[d], ny = y + dy[d];
        if (is_valid(nx, ny) && !grid[nx][ny])
        {
            if (match[nx][ny] == -1 || bpm(match[nx][ny] / M, match[nx][ny] % M))
            {
                match[nx][ny] = x * M + y;
                return true;
            }
        }
    }
    return false;
}

bool can_tile_grid()
{
    memset(match, -1, sizeof(match));

    int matches = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            if (!grid[i][j])
            {
                memset(visited, 0, sizeof(visited));
                if (bpm(i, j))
                    ++matches;
            }
        }
    }

    return matches * 2 == N * M;
}

int main()
{
    N = 4;
    M = 4;
    bool grid_input[MAXN][MAXN] = {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}};

    memcpy(grid, grid_input, sizeof(grid_input));

    if (can_tile_grid())
    {
        cout << "The grid can be tiled with dominos." << endl;
    }
    else
    {
        cout << "The grid cannot be tiled with dominos." << endl;
    }

    return 0;
}
