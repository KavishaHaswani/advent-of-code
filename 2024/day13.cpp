#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<int>> processInput() {
    string line;
    vector<vector<int>> input;
    vector<int> row;
    int n = 0;

    while(getline(cin, line)) {
        if (line.empty()) {
            input.push_back(row);
            row.clear();
        } else {
            int temp;
            while (((temp = line.find('+')) != string::npos) || 
                ((temp = line.find('=')) != string::npos)) {
                line = line.substr(temp + 1);
                istringstream iss(line);
                iss >> temp;
                row.push_back(temp);
                n++;
            }
        }
    }

    input.push_back(row);
    return input;
}

void solution(const vector<vector<int>>& input, bool isPart1) {
    uint64_t ans = 0;
    for (auto i: input) {
        int64_t xA = i[0], yA = i[1], xB = i[2], yB = i[3], x = i[4], y = i[5];
        if (!isPart1) {
            x += 10000000000000;
            y += 10000000000000;
        }
        int64_t nA = (x * yB - y * xB) / (xA * yB - yA * xB);
        int64_t nB = (x - xA * nA) / xB;

        if (nA > -1 && nB > -1 && nA * xA + nB * xB == x && nA * yA + nB * yB == y) {
            if (nA < 101 && nB < 101) {
                ans += (nA * 3 + nB);
            } else if (!isPart1) {
                ans += (nA * 3 + nB);
            }
        }
    }
    cout << ans << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    vector<vector<int>> input = processInput();

    solution(input, 1);
    solution(input, 0);
}