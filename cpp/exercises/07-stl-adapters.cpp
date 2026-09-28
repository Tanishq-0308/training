#include <iostream>
#include <stack>
#include <queue>
using namespace std;

int main() {
    // TASK A (stack, LIFO): push 1,2,3. Then pop all and print each top as you go.
    //   Use a while(!s.empty()) loop: print s.top(), then s.pop().
    //   Expect: 3 2 1
    stack<int> s;

    s.push(1);
    s.push(2);
    s.push(3);

    while (!s.empty())
    {
        cout << s.top() << " ";  s.pop();
        /* code */
    }
    


    // TASK B (queue, FIFO): push 1,2,3. Then drain and print each front.
    //   while(!q.empty()) { print q.front(); q.pop(); }
    //   Expect: 1 2 3
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    while(!q.empty()) { 
        cout <<  q.front() << " "; q.pop(); 
    }

    

    // TASK C (priority_queue, max-heap): push 4,1,7,3. Drain and print each top.
    //   Expect: 7 4 3 1   (always max first)
    priority_queue<int> pq;
    pq.push(4);
    pq.push(1);
    pq.push(7);
    pq.push(3);

    while (!pq.empty())
    {
        cout << pq.top() << " "; pq.pop();
        /* code */
    }
    

    return 0;
}

