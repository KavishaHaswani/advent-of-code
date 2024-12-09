#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;

vector<int> processInput() {
    string line;
    char c;
    vector<int> nums;
    cin >> line;
    istringstream iss(line);
    while (iss >> c)
        nums.push_back(c - '0');
    return nums;
}

void part1(vector<int> files)
{
    long long sum = 0;
    int index = 0, lastId_elementsLeft = 0, id = 0, id_back = (files.size() + 1) / 2;


    for (int i = 0; i < files.size(); i += 2)
    {
        for (int j = 0; j < files[i]; j++)
        {
            sum += (id * index++);
        }
        id++;

        if (i + 1 != files.size())
            for (int j = 0; j < files[i + 1]; j++)
            {
                if (lastId_elementsLeft == 0) {
                    lastId_elementsLeft = files[files.size() - 1];
                    id_back--;
                    files.pop_back();
                    files.pop_back();
                }

                sum += (id_back * index++);
                lastId_elementsLeft--;
            }
    }

    while (lastId_elementsLeft > 0)
    {
        sum += (id_back * index++);
        lastId_elementsLeft--;
    }

    cout << endl << sum << endl;
}

void part2(vector<int> files) {
    vector<int> ids((files.size() + 1) / 2);
    for (int i = 0; i < ids.size(); ++i) {
        ids[i] = i;
    }

    int temp = 0;

    for (int i = (files.size() / 2) * 2; i > 0; i -= 2) {
        for (int j = 1; (j < files.size()) && j < i; j += 2) {
            if ((i / 2 + 1 < ids.size()) && (ids[i / 2] > ids[i / 2 + 1]))
                break;
            if (files[j] >= files[i]) {
                int temp_i = files[i];
                files[j] = files[j] - files[i];
                if (i + 1 < files.size())
                    files[i] = files[i - 1] + files[i] + files[i + 1];
                else
                    files[i] = files[i - 1] + files[i];
                files.erase(files.begin() + i - 1);
                if (i < files.size())
                    files.erase(files.begin() + i);
                files.insert(files.begin() + j, temp_i);
                files.insert(files.begin() + j, 0);
                ids.insert(ids.begin() + (j + 1) / 2, ids[i / 2]);
                ids.erase(ids.begin() + i / 2 + 1);
                i += 2;
                break;
            }
        }
    }

    long long sum = 0;
    int index = 0;
    for (size_t i = 0; i < files.size(); i += 2)
    {
        for (int j = 0; j < files[i]; j++)
        {
            sum += (ids[i / 2] * index++);
        }

        if (i + 1 < files.size()) {
            index += files[i + 1];
        }
    }

    cout << sum << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    vector<int> files = processInput();

    part1(files);
    part2(files);
}