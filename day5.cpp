#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

unordered_map<int, set<int>> processRules() {
    unordered_map<int, set<int>> rules;
    string line;
    while (getline(cin, line)) {
        if (line.find('|') == string::npos)
            break;

        size_t pos = line.find('|');
        int num1 = stoi(line.substr(0, pos));
        int num2 = stoi(line.substr(pos + 1));

        rules[num1].insert(num2);
    }
    return rules;
}

vector<int> processUpdate(string line) {
    replace(line.begin(), line.end(), ',', ' ');
    istringstream iss(line);
    vector<int> nums;
    int num;
    while (iss >> num)
        nums.push_back(num);

    return nums;
}

int main() {
    freopen("input.txt", "r", stdin);
    unordered_map<int, set<int>> rules = processRules();
    auto sorter = [&](int a, int b) { return rules[a].count(b) > 0; };

    int ans1 = 0, ans2 = 0;
    string line;
    while(getline(cin, line)) {
        vector<int> nums = processUpdate(line);
        if (nums.size() % 2 == 0)
            continue;

        if (is_sorted(nums.begin(), nums.end(), sorter)) {
            ans1 += nums[nums.size() / 2];
        } else {
            sort(nums.begin(), nums.end(), sorter);
            ans2 += nums[nums.size() / 2];
        }
    }

    cout << ans1 << endl << ans2 << endl;
}