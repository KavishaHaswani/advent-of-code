#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

vector<vector<char>> processInput() {
    vector<vector<char>> grid;
    string line;
    while (getline(cin, line)) {
        grid.push_back(vector<char>(line.begin(), line.end()));
    }
    return grid;
}

void markAntinodes(vector<vector<char>>& map, vector<vector<bool>>& antinodes, char c, pair<int, int> startingPos, bool isPart1) {
    
    for (int i = startingPos.first; i < map.size(); i++) {
        for (int j = (i == startingPos.first ? startingPos.second + 1 : 0); j < map[i].size(); j++) {
            if (map[i][j] == c) {
                markAntinodes(map, antinodes, c, {i, j}, isPart1);

                int diffX = i - startingPos.first;
                int diffY = j - startingPos.second;

                if (!isPart1) {
                    antinodes[startingPos.first][startingPos.second] = 1;
                    antinodes[i][j] = 1;
                }

                int antiNodeX1 = startingPos.first;
                int antiNodeY1 = startingPos.second;
                do {
                    antiNodeX1 -=  diffX;
                    antiNodeY1 -=  diffY;

                    if (antiNodeX1 >= 0 && antiNodeX1 < antinodes.size() && antiNodeY1 >= 0 && antiNodeY1 < antinodes[0].size()) {
                        antinodes[antiNodeX1][antiNodeY1] = 1;
                    } else {
                        break;
                    }
                } while (!isPart1);

                int antiNodeX2 = i;
                int antiNodeY2 = j;
                do {
                    antiNodeX2 += diffX;
                    antiNodeY2 += diffY;

                    if (antiNodeX2 >= 0 && antiNodeX2 < antinodes.size() && antiNodeY2 >= 0 && antiNodeY2 < antinodes[0].size()) {
                        antinodes[antiNodeX2][antiNodeY2] = 1;
                    } else {
                        break;
                    }
                } while (!isPart1);
            }
        }
    }
}

int looper(vector<vector<char>>& map, bool isPart1) {
    vector<vector<bool>> antinodes(map.size(), vector<bool>(map[0].size(), 0));
    set<char> c = {'.'};

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.size(); j++)  {
            if (c.find(map[i][j]) == c.end()) {
                c.insert(map[i][j]);
                markAntinodes(map, antinodes, map[i][j], {i, j}, isPart1);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < antinodes.size(); i++) {
        for (int j = 0; j < antinodes[i].size(); j++) {
            if (antinodes[i][j] == 1) {
                ans++;
            }
        }
    }

    cout << ans << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    vector<vector<char>> map = processInput();
    
    looper(map, 1);
    looper(map, 0);
}