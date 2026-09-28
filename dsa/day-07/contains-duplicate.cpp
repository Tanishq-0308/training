#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Contains Duplicate (#217): return true if any value appears at least twice.
// Pattern: HashSet existence. Toolkit: seen.count(x) [0/1], seen.insert(x).
//
// Algorithm:
//   for each num in nums:
//     if seen.count(num)  -> return true   (already seen = duplicate)
//     else seen.insert(num)
//   return false
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> seen;

    // write the loop here
    for (int i=0;i< nums.size(); i++) {
        if (seen.count(nums[i])) 
        {
            return true;
        }else {
            seen.insert(nums[i]);
        }
    }


    return false;
}

int main() {
    vector<int> a = {1, 2, 3, 1};
    cout << containsDuplicate(a) << endl;   // expect 1 (true)

    vector<int> b = {1, 2, 3, 4};
    cout << containsDuplicate(b) << endl;   // expect 0 (false)

    return 0;
}
