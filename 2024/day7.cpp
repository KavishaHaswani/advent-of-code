#include <iostream>
#include <vector>
#include <tuple>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

vector<pair<long long, vector<long long>>> processInput() {
    vector<pair<long long, vector<long long>>> equations;
    string line;
    long long target;
    vector<long long> numbers;
    while (cin >> line) {
        if (line.find(':') != string::npos) {
            if (!numbers.empty()) {
                equations.push_back({target, numbers});
                numbers.clear();
            }
            target = stoll(line.substr(0, line.size() - 1));
        }
        else numbers.push_back(stoi(line));
    }
    equations.push_back({target, numbers});

    return equations;
}

long long powerOf10(int num) {
    long long ans = 1;
    while (ans <= num)
        ans *= 10;
    return ans;
}

bool solution(long long target, vector<long long> numbers, bool isPart1) {
    if (numbers.size() == 1) {
        return target == numbers[0];
    }

    int num = numbers.back();
    numbers.pop_back();
    long long target_concat =  (target - num) / powerOf10(num);
    bool target_concat_possible = target % powerOf10(num) == num;

    return solution(target - num, numbers, isPart1) || 
            ((target % num == 0) && solution(target / num, numbers, isPart1)) ||
            (!isPart1 && target_concat_possible && solution(target_concat, numbers, isPart1));
}

void looper(vector<pair<long long, vector<long long>>> equations, bool isPart1) {
    long long ans = 0;
    for (auto& i : equations) {
        if (solution(i.first, i.second, isPart1)) {
            ans += i.first;
        }
    }

    cout << ans << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    vector<pair<long long, vector<long long>>> equations = processInput();

    looper(equations, true);
    looper(equations, false);
}