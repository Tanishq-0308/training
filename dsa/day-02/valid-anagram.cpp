#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

bool isAnagram(string s, string t) {
    unordered_map<char, int> count;
    // STEP 1: early exit — if lengths differ, return false
    //   hint: s.size() and t.size()  (or s.length())
    if (s.size() != t.size()) return false;


    // STEP 2: count each char of s  →  count[s[i]]++
    //   loop over s with an index, increment the map for each char
    for(int i=0;i<s.size();i++){
        count[s[i]]++;
    }

    // STEP 3: subtract each char of t  →  count[t[i]]--
    //   loop over t, decrement the map for each char
    for(int i=0;i<t.size();i++){
        count[t[i]]--;
        if(count[t[i]] < 0 ) return false;
    }


    // STEP 4: check the map — if any value != 0, return false; otherwise true
    //   loop:  for (auto p : count) { if (p.second != 0) return false; }
    for(auto p: count) {
        if(p.second != 0) return false;
    }

    return true;
}

int main() {
    cout << isAnagram("anagram", "nagaram") << endl; // expect 1 (true)
    cout << isAnagram("rat", "car") << endl;         // expect 0 (false)
    cout << isAnagram("a", "ab") << endl;            // expect 0 (false)
    return 0;
}
