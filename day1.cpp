#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    // input
    freopen("input.txt", "r", stdin);
    long long n1 = 0, n2 = 0;
    pair<vector<int>, vector<int>> input;
    while (cin >> n1 >> n2) {
        input.first.push_back(n1);
        input.second.push_back(n2);
    }

    // part 1
    sort(input.first.begin(), input.first.end());
    sort(input.second.begin(), input.second.end());
    long long sum = 0;
    for (int i = 0; i < input.first.size(); i++) {
        sum += abs(input.first[i] - input.second[i]);
    }
    cout << sum << endl;

    // part 2
    map<int, int> number_of_ocurrences_in_right;
    for (auto i : input.second) {
        number_of_ocurrences_in_right[i]++;
    }
    sum = 0;
    for (auto i: input.first) {
        sum += (i * number_of_ocurrences_in_right[i]);
    }
    cout << sum << endl;
}