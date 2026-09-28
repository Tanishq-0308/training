#include <iostream>
#include <vector>
using namespace std;

// Two Sum II — array is SORTED. Use TWO POINTERS (O(n) time, O(1) space — no map!).
// Return the two indices whose values add up to target.
vector<int> twoSumSorted(vector<int>& nums, int target) {
    int L = 0;
    int R = nums.size() - 1;

    // Loop while the pointers haven't crossed:  while (L < R) { ... }
    //   - compute sum = nums[L] + nums[R]
    //   - if sum == target  → return {L, R}
    //   - else if sum < target (too small) → L++
    //   - else (too big)                   → R--

    while(L < R){
        int sum = nums[L] + nums[R];
        if(sum > target){
            R--;
        }else if(sum < target) {
            L++;
        }else if (sum == target){
            return {L,R};
        }
    }

    return {};  // no pair found
}

int main() {
    vector<int> a = {1, 3, 4, 5, 7, 11};
    vector<int> r1 = twoSumSorted(a, 9);
    cout << r1[0] << " " << r1[1] << endl;   // expect: 2 3

    vector<int> b = {2, 7, 11, 15};
    vector<int> r2 = twoSumSorted(b, 9);
    cout << r2[0] << " " << r2[1] << endl;   // expect: 0 1

    vector<int> c = {1, 2, 3, 4, 4, 9, 56, 90};
    vector<int> r3 = twoSumSorted(c, 8);
    cout << r3[0] << " " << r3[1] << endl;   // expect: 3 4  (4 + 4)

    return 0;
}
