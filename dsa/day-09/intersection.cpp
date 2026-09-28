#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Intersection of Two Arrays (#349): return UNIQUE elements present in BOTH arrays.
// Pattern: Set existence. Toolkit: unordered_set<int> s;  s.count(x);  s.insert(x);  s.erase(x);
//
// Approach:
//   1. Put all of nums1 into a set `s`.
//   2. Loop nums2: if s.count(num) -> it's in both. Add to result, then s.erase(num)
//      (erase so we never add the same value twice → result stays unique).
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> s;
    vector<int> result;

    // STEP 1: insert every element of nums1 into s
    for (int i=0; i<nums1.size(); i++ ) {
        s.insert(nums1[i]);
    };


    // STEP 2: loop nums2 — if present in s, push to result and erase from s
    for (int i=0; i<nums2.size(); i++) {
        if(s.count(nums2[i])){
            result.push_back(nums2[i]);
            s.erase(nums2[i]);
        }
    }

    return result;
}

int main() {
    vector<int> a1 = {1,2,2,1}, a2 = {2,2};
    vector<int> r1 = intersection(a1, a2);
    for (int x : r1) cout << x << " ";       // expect: 2
    cout << endl;

    vector<int> b1 = {4,9,5}, b2 = {9,4,9,8,4};
    vector<int> r2 = intersection(b1, b2);
    for (int x : r2) cout << x << " ";       // expect: 9 4 (any order)
    cout << endl;

    return 0;
}
