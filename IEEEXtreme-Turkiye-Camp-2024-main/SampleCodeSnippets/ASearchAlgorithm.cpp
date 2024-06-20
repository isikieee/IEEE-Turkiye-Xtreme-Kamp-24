#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct Node
{
    int x, y, cost, heuristic;
    bool operator>(const Node &other) const
    {
        return cost + heuristic > other.cost + other.heuristic;
    }
};

int heuristic(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

vector<pair<int, int>> aStarSearch(vector<vector<int>> &grid, pair<int, int> start, pair<int, int> end)
{
    int rows = grid.size();
    int cols = grid[0].size();

    priority_queue<Node, vector<Node>, greater<Node>> openList;
    unordered_set<int> closedList;

    openList.push({start.first, start.second, 0, heuristic(start.first, start.second, end.first, end.second)});

    vector<vector<int>> cost(rows, vector<int>(cols, INT_MAX));
    cost[start.first][start.second] = 0;

    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));

    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!openList.empty())
    {
        Node current = openList.top();
        openList.pop();

        if (current.x == end.first && current.y == end.second)
        {
            vector<pair<int, int>> path;
            while (current.x != start.first || current.y != start.second)
            {
                path.push_back({current.x, current.y});
                tie(current.x, current.y) = parent[current.x][current.y];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        int currentIndex = current.x * cols + current.y;
        if (closedList.count(currentIndex))
            continue;
        closedList.insert(currentIndex);

        for (auto &dir : directions)
        {
            int nx = current.x + dir[0];
            int ny = current.y + dir[1];
            if (nx < 0 || nx >= rows || ny < 0 || ny >= cols || grid[nx][ny] == 1)
                continue;

            int newCost = cost[current.x][current.y] + 1;
            if (newCost < cost[nx][ny])
            {
                cost[nx][ny] = newCost;
                openList.push({nx, ny, newCost, heuristic(nx, ny, end.first, end.second)});
                parent[nx][ny] = {current.x, current.y};
            }
        }
    }

    return {}; // No path found
}

int main()
{
    vector<vector<int>> grid = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}};

    pair<int, int> start = {0, 0};
    pair<int, int> end = {4, 4};

    vector<pair<int, int>> path = aStarSearch(grid, start, end);

    if (!path.empty())
    {
        for (const auto &p : path)
        {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    }
    else
    {
        cout << "No path found" << endl;
    }

    return 0;
}
