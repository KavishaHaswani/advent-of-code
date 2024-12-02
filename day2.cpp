#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<int> processLine(string line) {
    vector<int> report;
    int num;
    istringstream iss(line);
    while(iss >> num) {
        report.push_back(num);
    }

    return report;
}

int isSafe(vector<int> report) {
    bool inc_or_dec = (report[0] < report[1]);
    for (int i = 1; i < report.size(); i++) {
        if ((abs(report[i - 1] - report[i]) > 3) || (abs(report[i - 1] - report[i]) < 1) || ((report[i - 1] < report[i]) != inc_or_dec)) {
            return i;
        }
    }
    return 0;
}

bool isSafeWithRemoval(vector<int> report, int try_removing_index) {
    // isSafe function only returns one number for violation but either of the numbers in that pair can be the cause of the violation. Thus temp vector is needed. if violation occurs at i = 2, it could also have been caused by i = 0 due to need for change in inc_or_dec variables value.
    vector<int> temp = {0, 1};
    if (try_removing_index == 2)
        temp.push_back(2);
    for (int i: temp) {
        vector<int> report_new = report;
        report_new.erase(report_new.begin() + try_removing_index - i);
        if (isSafe(report_new) == 0)
            return true;
    }
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);
    string line;

    int count1 = 0, count2 = 0;
    while (getline(cin, line)) {
        vector<int> report = processLine(line);
        int try_removing_index;
        
        if ((try_removing_index = isSafe(report)) == 0) {
            count1++;
            count2++;
        } else if (isSafeWithRemoval(report, try_removing_index)) {
            count2++;
        }
    }

    cout << count1 << endl << count2 << endl;
}