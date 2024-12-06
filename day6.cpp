#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <array>

using namespace std;

int n = 4;
char dir[] = {'^', '>', 'v', '<'};
int incrementerX[] = {-1, 0, 1, 0};
int incrementerY[] = {0, 1, 0, -1};

// -1: no boundary, -2: grid().size() - 1
int exitBoundaryX[] = {0, -1, -2, -1};
int exitBoundaryY[] = {-1, -2, -1, 0};

vector<vector<char>> processInput() {
    vector<vector<char>> grid;
    string line;
    while (getline(cin, line)) {
        grid.push_back(vector<char>(line.begin(), line.end()));
    }
    return grid;
}

pair<pair<int, int>, int> findGaurd(vector<vector<char>>& grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            for (int k = 0; k < n; k++) {
                if (grid[i][j] == dir[k])
                    return {{i, j}, k};
            }
        }
    }
    return {{-1, -1}, -1};
}

bool checkLoop(vector<vector<char>> grid, pair<int, int> newObstacle, pair<pair<int, int>, int> gaurd) {
    vector<vector<array<bool, 4>>> dirVisited(grid.size(), vector<array<bool, 4>>(grid[0].size(), array<bool, 4>{0, 0, 0, 0}));
    pair<int, int> pos = gaurd.first;
    int dir = gaurd.second;

    grid[newObstacle.first][newObstacle.second] = '#';

    while(true) {
        if (dirVisited[pos.first][pos.second][dir])
            return 1;
        
        dirVisited[pos.first][pos.second][dir] = 1;
        
        if ((pos.first == exitBoundaryX[dir]) || (pos.second == exitBoundaryY[dir]))
            break;

        if (grid[pos.first + incrementerX[dir]][pos.second + incrementerY[dir]] == '#') {
            dir = (dir + 1) % n;
            continue;
        } else {
            pos.first += incrementerX[dir];
            pos.second += incrementerY[dir];
        }
    }

    return 0;
}

void part1(vector<vector<char>> grid, pair<pair<int, int>, int> gaurd) {
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    pair<int, int> pos = gaurd.first;
    int dir = gaurd.second;
    
    while(true) {
        visited[pos.first][pos.second] = true;
        
        if ((pos.first == exitBoundaryX[dir]) || (pos.second == exitBoundaryY[dir]))
            break;
        else if (grid[pos.first + incrementerX[dir]][pos.second + incrementerY[dir]] == '#') {
            dir = (dir + 1) % n;
            continue;
        } else {
            pos.first += incrementerX[dir];
            pos.second += incrementerY[dir];
        }
    }

    int ans = 0;

    for (int i = 0; i < visited.size(); i++) {
        for (int j = 0; j < visited[0].size(); j++) {
            if (visited[i][j])
                ans++;
        }
    }

    cout << ans << endl;
}

void part2(vector<vector<char>> grid, pair<pair<int, int>, int> gaurd) {
    int ans = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (i != gaurd.first.first || j != gaurd.first.second) {
                if (checkLoop(grid, {i, j}, gaurd)) {
                    ans++;
                }
            }
        }
    }

    cout << ans << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    vector<vector<char>> grid = processInput();
    exitBoundaryX[2] = grid.size() - 1;
    exitBoundaryY[1] = grid[0].size() - 1;
    pair<pair<int, int>, int> gaurd = findGaurd(grid);
    part1(grid, gaurd);
    part2(grid, gaurd);
}