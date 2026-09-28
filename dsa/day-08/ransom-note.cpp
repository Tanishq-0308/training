#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// Ransom Note (#383): can ransomNote be built from magazine's letters (each used once)?
// Pattern: frequency counting. Need magazine to have ENOUGH of each letter (>=), not equal.
//
// Approach:
//   1. Count every letter in magazine:   count[c]++
//   2. For each letter in ransomNote:     count[c]--  ; if it goes < 0 -> return false
//   3. return true
bool canConstruct(string ransomNote, string magazine) {
    unordered_map<char, int> count;

    // STEP 1: count magazine's letters (loop over magazine, count[magazine[i]]++)
    for(int i=0; i<magazine.size(); i++) {
        count[magazine[i]]++;
    }


    // STEP 2: for each letter in ransomNote, subtract; if below 0, return false
    for(int i=0; i < ransomNote.size(); i++) {
        count[ransomNote[i]]--;
        if ( count[ransomNote[i]] < 0) {
            return false;
        }
    }

    return true;
}

int main() {
    cout << canConstruct("aa", "aab") << endl;   // expect 1 (true)
    cout << canConstruct("aa", "ab") << endl;    // expect 0 (false)
    cout << canConstruct("a", "b") << endl;      // expect 0 (false)
    return 0;
}
