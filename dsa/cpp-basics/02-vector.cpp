#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Given vector:
    vector<int> nums = {10, 20, 30};

    // TASK 1: print the size of nums  (should be 3)
    //   hint: cout << nums.size() << endl;
    cout << nums.size() << endl;
    
    
    // TASK 2: loop through nums and print each element on its own line
    //   hint: a for loop from i=0 to i < nums.size(), print nums[i]
    for(int i=0;i< nums.size();i++){
        cout << nums[i] << endl;
    }
    
    // TASK 3: add the number 40 to the end of nums
    //   hint: nums.push_back(...)
    nums.push_back(40);
    
    // TASK 4: print the size again  (should now be 4)
    cout << nums.size() << endl;
    

    return 0;
}
