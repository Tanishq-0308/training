#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Two Sum (UNSORTED array) using a HashMap.
// Same algorithm you wrote in JS on Day 1 — now in C++.
// Return the indices of the two numbers that add up to target.
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;   // number -> its index   (JS: new Map())

    for (int i = 0; i < nums.size(); i++) {
        int need = target - nums[i];

        // STEP 1: have we already SEEN `need`?  (use .count, NOT [] — avoid the trap!)
        //   if yes → return { seen[need], i }
        if (seen.count(need)) return { seen[need], i};

        // STEP 2: otherwise, store the current number -> its index
        //   seen[ nums[i] ] = i;
        seen[nums[i]] = i;

    }

    return {};  // no pair found
}

int main() {
    vector<int> a = {2, 7, 11, 15};
    vector<int> r1 = twoSum(a, 9);
    cout << r1[0] << " " << r1[1] << endl;   // expect: 0 1

    vector<int> b = {3, 2, 4};
    vector<int> r2 = twoSum(b, 6);
    cout << r2[0] << " " << r2[1] << endl;   // expect: 1 2

    return 0;
}
