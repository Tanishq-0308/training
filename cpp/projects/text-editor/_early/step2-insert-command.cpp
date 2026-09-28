// Project 1, Step 2 — InsertCommand
//
// A "command" is a NOTE about something the user did, which knows how to reverse itself.
//
// InsertCommand remembers the text that was inserted. That's how undo knows
// how many characters to remove — text.size().
//
// Write the InsertCommand class yourself. Buffer is already here (your Step 1 code).
// main() is already written.
//
// InsertCommand needs:
//   - a private member: the text that was inserted
//   - a CONSTRUCTOR taking the text            InsertCommand(const string& s)
//   - void execute(Buffer& b)   → insert the text into b
//   - void undo(Buffer& b)      → remove that many characters from b
//
// Note the parameter is `Buffer& b` — not const, because the command MODIFIES the buffer.

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


// ... your InsertCommand class here ...
class InsertCommand {
    string text;

public:
    InsertCommand(const string& s) {
        text = s;
    }

    void execute(Buffer& b) {
        b.insert(text);
    }

    void undo(Buffer& b) {
        b.remove(text.size());
    }
    const string& getText() {
        return text;
    }
};

class DeleteCommand {
    int count;
    string deletedText;

public:
    DeleteCommand(int deleteCount) {
        count = deleteCount;
    }

    void execute(Buffer& b) {
        if(count > (int)b.getText().size()) count = b.getText().size();
        deletedText = b.getText().substr(b.getText().size() -  count);
        b.remove(count);
    }

    void undo(Buffer& b) {
        b.insert(deletedText);
    }
};

int main() {
    Buffer b;

    InsertCommand c1("Hi");
    c1.execute(b);
    cout << "[" << b.getText() << "]" << endl;     // [Hi]
    cout << "c1" << c1.getText() << endl;
    
    InsertCommand c2("Goodbye");
    c2.execute(b);
    cout << "c1" << c1.getText() << endl;
    cout << "[" << b.getText() << "]" << endl;     // [HiGoodbye]

    // undo the most recent one first — this is why order matters
    c2.undo(b);
    cout << "[" << b.getText() << "]" << endl;     // [Hi]

    c1.undo(b);
    cout << "[" << b.getText() << "]" << endl;     // []

    // a command can be re-executed (this is what REDO will use later)
    c1.execute(b);
    cout << "[" << b.getText() << "]" << endl;     // [Hi]

    return 0;
}
