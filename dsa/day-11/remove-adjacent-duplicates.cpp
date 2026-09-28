// #1047 Remove All Adjacent Duplicates In String  (Easy)
//
// Repeatedly remove two ADJACENT and EQUAL letters. Keep going until none are left.
//   "abbaca" -> remove "bb" -> "aaca" -> remove "aa" -> "ca"
//
// Write the #includes and removeDuplicates(string) yourself.

// ... your includes + removeDuplicates here ...


int main() {
    cout << removeDuplicates("abbaca") << endl;    // ca
    cout << removeDuplicates("azxxzy") << endl;    // ay
    cout << removeDuplicates("aaaaa") << endl;     // a
    cout << removeDuplicates("abcd") << endl;      // abcd
    cout << "[" << removeDuplicates("aa") << "]" << endl;   // []
    return 0;
}
