#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<vector<char>> processInput()
{
    vector<vector<char>> grid;
    string line;
    while (getline(cin, line))
    {
        vector<char> row;
        for (char c : line)
        {
            row.push_back(c);
        }
        grid.push_back(row);
    }
    return grid;
}

pair<int, int> part1(vector<vector<char>> &grid, vector<vector<bool>> &visited, int i, int j)
{
    vector<int> dx = {0, 1, 0, -1};
    vector<int> dy = {1, 0, -1, 0};
    int n = 4;

    int area = 1, perimeter = 4;
    char current = grid[i][j];
    grid[i][j] = '.';
    visited[i][j] = 1;

    for (int k = 0; k < n; k++)
    {
        int x = i + dx[k];
        int y = j + dy[k];
        if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size())
        {
            continue;
        }
        else if (visited[x][y])
        {
            perimeter--;
        }
        else if (grid[x][y] == current)
        {
            pair<int, int> temp = part1(grid, visited, x, y);
            area += temp.first;
            perimeter = perimeter - 1 + temp.second;
        }
    }

    return {area, perimeter};
}

pair<int, int> part2(vector<vector<char>> &grid, vector<vector<bool>> &visited, int i, int j)
{
    char current = grid[i][j];
    grid[i][j] = '.';
    visited[i][j] = 1;

    vector<int> dx = {0, 1, 0, -1};
    vector<int> dy = {1, 0, -1, 0};
    vector<bool> continues_in_dx_dy;
    int n = 4;

    int area = 1, perimeter = 4, c = 0;

    for (int k = 0; k < n; k++)
    {
        int x = i + dx[k];
        int y = j + dy[k];
        if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size())
        {
            continues_in_dx_dy.push_back(0);
        }
        else if (visited[x][y])
        {
            continues_in_dx_dy.push_back(1);
            c++;
        }
        else if (grid[x][y] == current)
        {
            pair<int, int> temp = part2(grid, visited, x, y);
            area += temp.first;
            perimeter = perimeter + temp.second;
            continues_in_dx_dy.push_back(1);
            c++;
        }
        else
        {
            continues_in_dx_dy.push_back(0);
        }
    }

    if ((c == 2) &&
        ((continues_in_dx_dy[0] && continues_in_dx_dy[2]) ||
         (continues_in_dx_dy[1] && continues_in_dx_dy[3])))
    {
        perimeter -= 4;
    }
    else if (c == 1)
    {
        perimeter -= 2;
    }
    else {
        for (int k = 0; k < n; k++) {
            int x = i + dx[k] + dx[(k + 1) % n];
            int y = j + dy[k] + dy[(k + 1) % n];

            if (continues_in_dx_dy[k] ^ continues_in_dx_dy[(k + 1) % n]) {
                perimeter--;
            } else if (continues_in_dx_dy[k] && continues_in_dx_dy[(k + 1) % n]) {
                if ((grid[x][y] == current) || visited[x][y]) {
                    perimeter--;
                }
            }
        }
    }

    return {area, perimeter};
}

void looper(vector<vector<char>> grid, bool isPart1)
{
    int price = 0;

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] != '.')
            {
                vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), 0));
                pair<int, int> dimensions;
                if (isPart1)
                {
                    dimensions = part1(grid, visited, i, j);
                }
                else
                {
                    dimensions = part2(grid, visited, i, j);
                }
                price += (dimensions.first * dimensions.second);
            }
        }
    }
    cout << price << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    vector<vector<char>> grid = processInput();

    looper(grid, 1);
    looper(grid, 0);
}

// try implementing with union find