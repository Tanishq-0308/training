#include<iostream>
#include<string>
#include<stack>
using namespace std;
bool isValid(string s){stack<int> st;for(int i=0;i<s.size();i++){char c=s[i];if(c=='['||c=='('||c=='{'){st.push(c);}if(c==')'||c==']'||c=='}'){if(st.empty())return false;if(c==']'&&st.top()=='['){st.pop();}else if(c=='}'&&st.top()=='{'){st.pop();}else if(c==')'&&st.top()=='('){st.pop();}else{return false;}}}return st.empty();}
int main(){cout<<"(]) -> "<<isValid("(])")<<" (want 0)\n";cout<<")   -> "<<isValid(")")<<" (want 0)\n";}
