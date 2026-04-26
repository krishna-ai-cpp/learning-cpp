#include <iostream>
#include <vector>
using namespace std;

int binary(int a) {
    int ans = 0;
    int pow = 1;

    while(a > 0) {
        int rem = a % 2;
        a = a / 2;
        ans += (rem * pow);
        pow = pow * 10;   // FIXED
    }

    return ans;   // IMPORTANT
}

int main() {
    vector<int> v;
    int num;
    int value;

    cout << "enter the size of binary vector you want: ";
    cin >> num;

    for(int i = 0; i < num; i++) {
        cout << "enter the " << i + 1 << " element: ";
        cin >> value;

        int b = binary(value);
        v.push_back(b);
    }

    cout << "binary vector: ";
    for(int val : v) {
        cout << val << " ";
    }

    cout << endl;

    return 0;
}
