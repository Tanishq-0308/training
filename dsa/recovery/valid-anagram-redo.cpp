#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

// RECOVERY RE-SOLVE — from memory, no peeking at your old solution or notes.
// Valid Anagram: return true if t is an anagram of s (same chars, same counts).
//
// Write the whole function yourself. If you get stuck, that's useful data —
// tell me where, and we refresh just that piece.
bool isAnagram(string s, string t) {
    // your code here
    unordered_map<char,int> map;

    if (s.size() != t.size()) return false;

    for (int i=0;i<s.size();i++){
        map[s[i]]++;
    }

    for(int i=0;i<t.size();i++){
        map[t[i]]--;
    }

    for(auto p: map) {
        if (p.second != 0) {
            return false;
        }
    }

    return true;
}

int main() {
    cout << isAnagram("anagram", "nagaram") << endl; // expect 1
    cout << isAnagram("rat", "car") << endl;         // expect 0
    cout << isAnagram("a", "ab") << endl;            // expect 0
    return 0;
}
