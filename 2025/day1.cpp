#include <iostream>

using namespace std;

void solution()
{
    string s;
    char c;
    int n, ans1 = 0, ans2 = 0, pos = 50, temp;
    while (cin >> s)
    {
        c = s[0];
        s.erase(s.begin(), s.begin() + 1);
        n = stoi(s);

        if (c == 'L')
        {
            temp = pos - n;
            if (temp < 0)
            {
                ans2 += abs(temp) / 100 + (pos ? 1 : 0) - (abs(temp) % 100 ? 0 : 1);
            }
            pos = (temp % 100 + 100) % 100;
        }
        else
        {
            temp = pos + n;
            if (temp > 100)
            {
                ans2 += temp / 100 - (temp % 100 ? 0 : 1);
            }
            pos = temp % 100;
        }

        if (pos == 0)
        {
            ans1++;
        }
    }
    cout << ans1 << endl
         << ans1 + ans2 << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    solution();
}