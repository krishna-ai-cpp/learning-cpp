#include <iostream>
#include <vector>
using namespace std;

// Program: Take input in vector and perform basic operations
// Time Complexity: O(n)

int main() {
    vector<int> v;
    int n, value;

    cout << "Enter number of elements: ";
    cin >> n;

    // Taking input
    for(int i = 0; i < n; i++) {
        cout << "Enter element " << i + 1 << ": ";
        cin >> value;
        v.push_back(value);
    }

    // Display vector
    cout << "\nVector elements: ";
    for(int val : v) {
        cout << val << " ";
    }

    // Insert element at position
    int pos, newVal;
    cout << "\nEnter position to insert (0-based index): ";
    cin >> pos;
    cout << "Enter value to insert: ";
    cin >> newVal;

    if(pos >= 0 && pos <= v.size()) {
        v.insert(v.begin() + pos, newVal);
    }

    // Delete element
    cout << "Enter position to delete: ";
    cin >> pos;

    if(pos >= 0 && pos < v.size()) {
        v.erase(v.begin() + pos);
    }

    // Final vector
    cout << "\nUpdated vector: ";
    for(int val : v) {
        cout << val << " ";
    }

    cout << endl;

    return 0;
}
