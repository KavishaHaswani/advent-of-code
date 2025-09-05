#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<char, pair<int, int>> dz = {{'>', {0, 1}}, {'<', {0, -1}}, {'^', {-1, 0}}, {'v', {1, 0}}};

pair<int, int> find(vector<vector<char>> &grid, char c) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == c) {return {i, j};}
        }
    }
}

bool move(vector<vector<char>> &grid, char &i, pair<int, int> pos) {
    if (grid[pos.first][pos.second] == '.') {return true;}
    if (grid[pos.first][pos.second] == '#') {return false;}
    pair<int, int> nextPos = make_pair(pos.first + dz[i].first, pos.second + dz[i].second);
    if (move(grid, i, nextPos)) {
        grid[nextPos.first][nextPos.second] = grid[pos.first][pos.second];
        if (i == '^' || i == 'v') {
            if (grid[pos.first][pos.second] == '[' && grid[pos.first][pos.second + 1] == ']') {
                grid[pos.first][pos.second] = '.';
                move(grid, i, {pos.first, pos.second + 1});
            }
            if (grid[pos.first][pos.second] == ']' && grid[pos.first][pos.second - 1] == '[') {
                grid[pos.first][pos.second] = '.';
                move(grid, i, {pos.first, pos.second - 1});
            }
        }
        grid[pos.first][pos.second] = '.';
        return true;
    }
    return false;
}

bool movePossible(vector<vector<char>> &grid, char &c, pair<int, int> pos) {
    if (grid[pos.first][pos.second] == '.') {return true;}
    if (grid[pos.first][pos.second] == '#') {return false;}

    pair<int, int> newPos = {pos.first + dz[c].first, pos.second + dz[c].second};
    if (grid[newPos.first][newPos.second] == ']' && c != '>') {
        newPos.second -= 1;
    }
    bool ans = movePossible(grid, c, newPos);
    if (grid[pos.first][pos.second] == '[' && (c == '^' || c == 'v')) {
        newPos = {pos.first + dz[c].first, pos.second + 1};
        if (grid[newPos.first][newPos.second] == ']') {
            return ans;
        }
        ans = ans && movePossible(grid, c, newPos);
    }
    return ans;
}

int finalVal(vector<vector<char>> &grid) {
    int ans = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            char c = grid[i][j];
            if (c == 'O' || c == '[') {ans += (i * 100 + j);}
        }
    }
    return ans;
}

int main() {
    int part = 0;
    do {
        cout << "Enter 1 or 2 for selecting part" << endl;
        cin >> part;
    } while (part != 1 && part != 2);
    bool isPart1 = part == 1? true: false;
    string filename = "input15a.txt";
    freopen(filename.c_str(), "r", stdin);
    vector<vector<char>> grid;
    string line;
    while (getline(cin, line) && line != "") {
        vector<char> l;
        for (char i: line) {
            if (isPart1) {
                l.push_back(i);
            } else {
                if (i == '@') {l.push_back('@'); l.push_back('.');}
                else if (i == 'O') {l.push_back('['); l.push_back(']');}
                else {l.push_back(i); l.push_back(i);}
            }
        }
        grid.push_back(l);
    }
    pair<int, int> pos = find(grid, '@');
    while (cin >> line) {
        for (char i: line) {
            if ((isPart1 || movePossible(grid, i, pos)) && move(grid, i, pos)) {
                pos.first = pos.first + dz[i].first;
                pos.second = pos.second + dz[i].second;
            }
        }
    }
    cout << finalVal(grid) << endl;
}