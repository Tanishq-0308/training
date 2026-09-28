// Project 1, Step 1 — the Buffer class
//
// The Buffer is JUST the text. It knows nothing about undo, commands, or stacks.
// Think of it as the white page in Word: it holds characters, and you can add to
// the end or chop off the end.
//
// Write the `Buffer` class yourself. main() is already written and will test it.
//
// It needs:
//   - a private member holding the text
//   - void insert(const string& s)   → glue s onto the end
//   - void remove(int n)             → chop n characters off the end (CLAMP if n is too big)
//   - const string& getText() const  → hand back the text (no copy, read-only, const method)
//   - int size() const               → how many characters (also a const method)
//
// Reminders from your notes:
//   - members go under `private:`, methods under `public:`
//   - a const member function promises not to modify the object
#include<iostream>
#include<string>

using namespace std;

class Buffer {
    string text;

    public:
        void insert(const string& s) {
            text += s;
        }

        void remove(int n) {
            if (n <= 0) return;
            if (n > (int)text.size()) n = text.size();
            text.erase(text.size() - n);
        }

        const string& getText() const {
            return text;
        }

        int size() const {
            return text.size();
        }
};


int main() {
    Buffer b;

    b.insert("Hello");
    cout << "[" << b.getText() << "]" << endl;        // [Hello]

    b.insert(" world");
    cout << "[" << b.getText() << "]" << endl;        // [Hello world]
    cout << "size: " << b.size() << endl;             // size: 11

    b.remove(6);
    cout << "[" << b.getText() << "]" << endl;        // [Hello]

    // the clamp test — asking to remove more than exists
    b.remove(100);
    cout << "[" << b.getText() << "]" << endl;        // []   (empty, NOT a crash)
    cout << "size: " << b.size() << endl;             // size: 0

    // removing from an already-empty buffer must also be safe
    b.remove(5);
    cout << "[" << b.getText() << "]" << endl;        // []

    return 0;
}
