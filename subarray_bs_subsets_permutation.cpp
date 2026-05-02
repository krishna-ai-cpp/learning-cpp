#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Function: Check if any subarray sum equals k using prefix sums + hashmap
// Time Complexity: O(n)  (single pass + hashmap lookups)
// Space Complexity: O(n) (prefix sum array + hashmap)
bool subarray(vector<int> &arr, int k) {
    int n = arr.size();
    vector<int> pf(n, 0);
    pf[0] = arr[0];

    for (int i = 1; i < n; i++) {  
        pf[i] = pf[i - 1] + arr[i];
    }

    unordered_map<int, int> m;
    for (int j = 0; j < n; j++) {
        if (pf[j] == k) {           
            return true;
        }
        int val = pf[j] - k;
        if (m.find(val) != m.end()) {   
            return true;
        }
        if (m.find(pf[j]) == m.end()) { 
            m[pf[j]] = 0;
        }
        m[pf[j]]++;
    }
    return false;  
}

// Function: Recursive binary search
// Time Complexity: O(log n)
// Space Complexity: O(log n) due to recursion stack
bool bs(vector<int> &arr, int k, int st, int end) {
    if (st > end) {
        return false;
    }
    int mid = st + (end - st) / 2;

    if (arr[mid] == k) {
        return true;
    }
    else if (arr[mid] < k) {
        return bs(arr, k, mid + 1, end);
    }
    else {
        return bs(arr, k, st, mid - 1);
    }
}

// Helper for generating subsets recursively
// Time Complexity: O(2^n) (each element has two choices: include/exclude)
// Space Complexity: O(n) for recursion stack + storage for subsets
void helper(vector<int> &arr, vector<int> &ans, int i, vector<vector<int>> &allsubsets) {
    if (i == arr.size()) {
        allsubsets.push_back(ans);
        return;
    }
    ans.push_back(arr[i]);
    helper(arr, ans, i + 1, allsubsets);
    ans.pop_back();
    helper(arr, ans, i + 1, allsubsets);
}

vector<vector<int>> subsets(vector<int> &arr) {
    vector<int> ans;
    vector<vector<int>> allsubsets;
    helper(arr, ans, 0, allsubsets);
    return allsubsets;
}

// Helper for generating permutations recursively
// Time Complexity: O(n * n!) (n! permutations, each takes O(n) to build)
// Space Complexity: O(n) recursion stack + storage for permutations
void helper2(vector<int> &l2, int idx, vector<vector<int>> &ans, vector<int> &temp) {
    if (idx == l2.size()) {
        ans.push_back(temp);
        return;
    }
    for (int i = idx; i < l2.size(); i++) {
        swap(l2[idx], l2[i]);
        temp.push_back(l2[idx]);
        helper2(l2, idx + 1, ans, temp);
        temp.pop_back();
        swap(l2[idx], l2[i]);
    }
}

vector<vector<int>> permutation(vector<int> &l2) {
    vector<vector<int>> ans;
    vector<int> temp;
    helper2(l2, 0, ans, temp);
    return ans;
}

int main() {
    vector<int> arr;
    int n;
    cout << "enter the size of array: ";
    cin >> n;
    int e;
    for (int i = 0; i < n; i++) {
        cout << "enter the " << i + 1 << " element: ";
        cin >> e;
        arr.push_back(e);
    }

    cout << "_________THE ARRAY FORMED_________\n";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;

    int tar;
    cout << "enter the target: ";
    cin >> tar;

    // Step 1: Subarray sum check
    bool a = subarray(arr, tar);
    if (a) {
        cout << "______LIST FORMED _________\n";
        list<int> l;
        l.push_back(tar);
        l.sort();
        for (int val : l) {
            cout << val << " ";
        }
        cout << endl;
    } else {
        cout << "no subarray found.....";
    }

    // Step 2: Binary search check
    if (bs(arr, tar, 0, n - 1)) {
        auto b = subsets(arr);
        cout << "_______SUBSETS IN THE LIST_________\n";
        for (auto &subset : b) {
            for (int val : subset) {
                cout << val << " ";
            }
            cout << endl;
        }
    } else {
        cout << "no subsets found.....";
    }

    // Step 3: Permutations
    auto c = permutation(arr);
    cout << "_______PERMUTATIONS_________\n";
    for (auto &perm : c) {
        for (int val : perm) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
