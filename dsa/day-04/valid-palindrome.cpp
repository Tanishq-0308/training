#include <iostream>
#include <string>
#include <cctype>     // for isalnum() and tolower()
using namespace std;

// Valid Palindrome (#125). Two pointers from both ends.
// Ignore non-alphanumeric chars; compare case-insensitively.
//
// Tools available: isalnum(c) → true if letter/digit.  tolower(c) → lowercase version.
//
// Your job — write the body of the while loop:
//   1. Skip any non-alphanumeric char on the LEFT  (advance L)
//   2. Skip any non-alphanumeric char on the RIGHT (retreat R)
//   3. Compare the two chars case-insensitively; if they differ, it's NOT a palindrome
//   4. Move both pointers inward and continue
bool isPalindrome(string s) {
    int L = 0;
    int R = s.size() - 1;

    while (L < R) {
        // write steps 1–4 here
        while(L < R && !isalnum(s[L])) L++;

        while(L < R && !isalnum(s[R])) R--;

        if(tolower(s[L]) != tolower(s[R])) return false;

        L++;
        R--;
    }

    return true;
}

int main() {
    cout << isPalindrome("A man, a plan, a canal: Panama") << endl; // expect 1 (true)
    cout << isPalindrome("race a car") << endl;                     // expect 0 (false)
    cout << isPalindrome(" ") << endl;                              // expect 1 (empty after skipping)
    cout << isPalindrome("0P") << endl;                             // expect 0 ('0' vs 'p')
    return 0;
}
