#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);

    int ans1 = 0, ans2 = 0;
    bool flag = 1;
    string text;
    while (getline(cin, text)) {
        smatch combinations;
        smatch disabler;
        regex pattern("mul\\((\\d+)\\,(\\d+)\\)");
        regex pattern2("don\\'t\\(\\)");
        regex pattern3("do\\(\\)");

        while (regex_search(text, combinations, pattern)) {
            int num1 = stoi(combinations[1].str());
            int num2 = stoi(combinations[2].str());
            ans1 += (num1 * num2);

            string prefix_str = combinations.prefix(), suffix_disabler = combinations.prefix();
            if (regex_search(prefix_str, disabler, pattern2)) {
                flag = 0;
                suffix_disabler = disabler.suffix();
            }
            if (regex_search(suffix_disabler, disabler, pattern3))
                flag = 1;

            if (flag)
                ans2 += (num1 * num2);

            text = combinations.suffix();
        }
    }

    cout << ans1 << endl << ans2 << endl;
}
