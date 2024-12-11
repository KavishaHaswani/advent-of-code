#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

// custom hash function for pair
struct pair_hash {
    template <class T1, class T2>
    size_t operator() (const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

unordered_map<pair<uint64_t, uint64_t>, uint64_t, pair_hash> cache;

vector<uint64_t> processInput() {
    vector<uint64_t> stones;
    uint64_t num;
    
    while (cin >> num) {
        stones.push_back(num);
    }
    return stones;
}  

uint64_t solution(vector<uint64_t> stones, uint64_t iter) {
    if (iter == 0) {
        return stones.size();
    }

    uint64_t ans = 0;

    while (stones.size() != 0) {
        uint64_t stone = stones[0];
        stones.erase(stones.begin() + 0);
        uint64_t temp;

        if (cache[{stone, iter}] != 0) {
            temp = cache[{stone, iter}];
        }

        else {
            vector<uint64_t> stones_temp;

            if (stone == 0) {
                stones_temp.push_back(1);
            } else if (to_string(stone).length() % 2 == 0) {
                uint64_t midLength = to_string(stone).length() / 2;
                stones_temp.push_back(stoll(to_string(stone).substr(0, midLength)));
                stones_temp.push_back(stoll(to_string(stone).substr(midLength)));
            } else {
                stones_temp.push_back(stone * 2024);
            }
            temp = solution(stones_temp, iter - 1);
        }
        cache[{stone, iter}] = temp;
        ans += temp;
    }

    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    vector<uint64_t> stones = processInput();

    cout << solution(stones, 25) << endl;
    cout << solution(stones, 75) << endl;
}