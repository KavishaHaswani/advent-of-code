#include <iostream>
#include <vector>
#include <string>

using namespace std;


vector<vector<char>> getInput() {
    string text;
    vector<vector<char>> grid;

    while (getline(cin, text)) {
        vector<char> row;
        for (int i = 0; i < text.size(); i++) {
            row.push_back(text[i]);
        }
        grid.push_back(row);
    }

    return grid;
}

int countOccurence_xmas(vector<vector<char>> grid) {
    int ans = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'X') {
                if (j > 2) {
                    if (grid[i][j - 1] == 'M' && grid[i][j - 2] == 'A' && grid[i][j - 3] == 'S') {
                        ans++;
                    }
                    if (i > 2) {
                        if (grid[i - 1][j - 1] == 'M' && grid[i - 2][j - 2] == 'A' && grid[i - 3][j - 3] == 'S') {
                            ans++;
                        }
                    }
                }
                if (j + 3 < grid.size()) {
                    if (grid[i][j + 1] == 'M' && grid[i][j + 2] == 'A' && grid[i][j + 3] == 'S') {
                        ans++;
                    }
                    if (i + 3 < grid.size()) {
                        if (grid[i + 1][j + 1] == 'M' && grid[i + 2][j + 2] == 'A' && grid[i + 3][j + 3] == 'S') {
                            ans++;
                        }
                    }
                }
                if (i > 2) {
                    if (grid[i - 1][j] == 'M' && grid[i - 2][j] == 'A' && grid[i - 3][j] == 'S') {
                        ans++;
                    }
                    if (j + 3 < grid.size()) {
                        if (grid[i - 1][j + 1] == 'M' && grid[i - 2][j + 2] == 'A' && grid[i - 3][j + 3] == 'S') {
                            ans++;
                        }
                    }
                }
                if (i + 3 < grid.size()) {
                    if (grid[i + 1][j] == 'M' && grid[i + 2][j] == 'A' && grid[i + 3][j] == 'S') {
                        ans++;
                    }
                    if (j > 2) {
                        if (grid[i + 1][j - 1] == 'M' && grid[i + 2][j - 2] == 'A' && grid[i + 3][j - 3] == 'S') {
                            ans++;
                        }
                    }
                }
            }
        }
    }
    return ans;
}

int countOccurence_x_mas(vector<vector<char>> grid) {
    int ans = 0;
    for (int i = 1; i < grid.size() - 1; i++) {
        for (int j = 1; j < grid[i].size() - 1; j++) {
            if (grid[i][j] == 'A') {
                bool lu_m = grid[i - 1][j - 1] == 'M'; // left up - M
                bool lu_s = grid[i - 1][j - 1] == 'S';
                bool rd_m = grid[i + 1][j + 1] == 'M'; // right down - M
                bool rd_s = grid[i + 1][j + 1] == 'S';

                if ((lu_m && rd_s) || (lu_s && rd_m)) {
                    bool ru_m = grid[i - 1][j + 1] == 'M';
                    bool ru_s = grid[i - 1][j + 1] == 'S';
                    bool ld_m = grid[i + 1][j - 1] == 'M';
                    bool ld_s = grid[i + 1][j - 1] == 'S';

                    if ((ru_m && ld_s) || (ru_s && ld_m))
                        ans++;
                }
            }
        }
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    vector<vector<char>> grid = getInput();
    
    int ans1 = countOccurence_xmas(grid);
    int ans2 = countOccurence_x_mas(grid);

    cout << ans1 << endl << ans2 << endl;
}