#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<vector<int>> processInput() {
    vector<vector<int>> grid;
    vector<int> row;
    string line;

    while (cin >> line) {
        for (char c : line) {
            row.push_back(c - '0');
        }
        grid.push_back(row);
        row.clear();
    }

    return grid;
}

bool isValidMove(vector<vector<int>>& grid, pair<int, int> pos, int dx, int dy) {
    int newX = pos.first + dx;
    int newY = pos.second + dy;

    return newX >= 0 && 
            newX < grid.size() && 
            newY >= 0 && 
            newY < grid[0].size() && 
            grid[newX][newY] == grid[pos.first][pos.second] + 1;
}

pair<set<pair<int, int>>, int> solution(vector<vector<int>>& grid, pair<int, int> pos) {
    if (grid[pos.first][pos.second] == 9) {
        return {{pos}, 1};
    }

    set<pair<int, int>> ans1;
    int ans2 = 0;
    vector<int> dX = {0, 1, 0, -1};
    vector<int> dY = {1, 0, -1, 0};
    int n = 4;

    for (int i = 0; i < n; i++) {
        if (isValidMove(grid, pos, dX[i], dY[i])) {
            pair<set<pair<int, int>>, int> temp = solution(grid, {pos.first + dX[i], pos.second + dY[i]});

            ans1.insert(temp.first.begin(), temp.first.end());
            ans2 += temp.second;
        }
    }
    return {ans1, ans2};
}

void looper(vector<vector<int>>& grid) {
    int ans1 = 0, ans2 = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 0) {
                pair<set<pair<int, int>>, int> temp = solution(grid, {i, j});
                ans1 += temp.first.size();
                ans2 += temp.second;
            }
        }
    }

    cout << ans1 << endl;
    cout << ans2 << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    vector<vector<int>> grid = processInput();

    looper(grid);
}