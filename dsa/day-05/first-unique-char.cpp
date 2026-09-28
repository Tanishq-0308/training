#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// First Unique Character (#387).
// Return the INDEX of the first non-repeating char, or -1 if none.
// Pattern: frequency count (Pass 1), then scan in order (Pass 2).
int firstUniqChar(string s) {
    unordered_map<char, int> count;

    // PASS 1: count how many times each char appears
    //   (loop the string, count[s[i]]++)
    for (int i=0;i<s.size();i++){
        count[s[i]]++;
    }



    // PASS 2: walk the string in order; return the index of the
    //         first char whose count == 1
    for(int i=0;i<s.size();i++){
        if(count[s[i]] == 1) return i;
    }

    return -1;   // no unique character found
}

int main() {
    cout << firstUniqChar("leetcode") << endl;      // expect 0  ('l')
    cout << firstUniqChar("loveleetcode") << endl;  // expect 2  ('v')
    cout << firstUniqChar("aabb") << endl;          // expect -1
    return 0;
}
