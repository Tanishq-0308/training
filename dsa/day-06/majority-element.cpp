#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Majority Element (#169). Returns the element appearing MORE than n/2 times (guaranteed to exist).
//
// Approach 1: HashMap frequency count.  Time O(n), Space O(n).
// Your job: count each element; return the one whose count > n/2.
int majorityElement(vector<int>& nums) {
    int n = nums.size();
    unordered_map<int, int> count;

    // loop over nums:
    //   - increment count[nums[i]]
    //   - if count[nums[i]] > n/2  → return nums[i]
    for (int i=0;i<nums.size();i++){
            // cout << count.count(nums[i]) << endl;
            count[nums[i]]++;
            if(count[nums[i]] > n/2) {
                return nums[i];
            }
        // cout << "out the if "<<  count.count(nums[i]) << endl;
    }


    return -1;  // (won't reach here — majority guaranteed)
}

int main() {
    vector<int> a = {3, 2, 3};
    cout << majorityElement(a) << endl;                 // expect 3

    vector<int> b = {2, 2, 1, 1, 1, 2, 2};
    cout << majorityElement(b) << endl;                 // expect 2

    return 0;
}
