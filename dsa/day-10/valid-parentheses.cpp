// Valid Parentheses (#20)
// Return true if every opening bracket ( { [ is closed by the same type, in order.
//
// Write the #includes and the isValid(string) function yourself.

// ... your includes + isValid here ...
#include<iostream>
#include<string>
#include<stack>

using namespace std;

bool isValid(string s) {
    stack<int> st;

    for (int i=0; i<s.size();i++) {
        char c = s[i];
        // if () return false;
        if ( c == '[' || c == '(' || c=='{'){
            st.push(c);
        }
        if (c == ')' || c == ']' || c == '}') {
            if (st.empty()) return false;
            
        if(c == ']' && st.top() == '['){
            st.pop();
        }else if(c == '}' && st.top() == '{'){
            st.pop();
        }else if(c == ')' && st.top() == '('){
            st.pop();
        }else {
            return false;
        }
        }
    }

    return st.empty();
}


int main() {
    cout << isValid("()") << endl;        // 1
    cout << isValid("()[]{}") << endl;    // 1
    cout << isValid("(]") << endl;        // 0
    cout << isValid("([)]") << endl;      // 0
    cout << isValid("{[]}") << endl;      // 1
    cout << isValid(")") << endl;         // 0
    return 0;
}
