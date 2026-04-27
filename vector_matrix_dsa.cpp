/*
===========================================================
 Title: vector_matrix_dsa.cpp
 Author: Krishna
 Goal: Practice suite of DSA problems in C++ using Arrays, STL, and Matrices
===========================================================

📌 Problems Covered:
1. totalsubarray()  → Count subarrays with given sum
2. foursum()        → Find quadruplets with sum = 0
3. spiral()         → Spiral traversal of a matrix
4. remdup()         → Detect duplicates in a matrix

-----------------------------------------------------------
⏱️ Time & Space Complexity (Big-O Analysis):

1. totalsubarray():
   - Time: O(n) for prefix sum + O(n) for map lookup → O(n)
   - Space: O(n) for prefix sum + O(n) for hashmap → O(n)

2. foursum():
   - Time: O(n^2 * log n) approx (nested loops + two pointers)
   - Space: O(n) for storing quadruplets

3. spiral():
   - Time: O(m * n) → visits each element once
   - Space: O(m * n) for result vector

4. remdup():
   - Time: O(n^2) → scans all matrix elements
   - Space: O(n^2) for set + result vector

-----------------------------------------------------------
📌 Notes:
- Code is practice‑oriented, not optimized for production.
- Focus is on syntax clarity, STL usage, and problem framing.
- Each function demonstrates a different DSA concept.

===========================================================
*/

#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Function 1: Count subarrays with target sum
int totalsubarray(vector<int>& vec, int tar) {
    int n = vec.size();
    int count = 0;
    vector<int> prefixsum(n, 0);

    prefixsum[0] = vec[0];
    for (int i = 1; i < n; i++) {
        prefixsum[i] = prefixsum[i - 1] + vec[i];
    }

    unordered_map<int, int> m;

    for (int j = 0; j < n; j++) {
        if (prefixsum[j] == tar) {
            m[prefixsum[j]]++;
        }
        int val = prefixsum[j] - tar;
        if (m.find(val) != m.end()) {
            m[prefixsum[j]] = 0;
        }
        m[prefixsum[j]]++;
    }
    return count;
}

// Function 2: Four-sum problem
int foursum(vector<int>& vec) {
    int n = vec.size();
    int sum = 0;
    vector<int> ans;

    for (int i = 0; i < n; i++) {
        if (i > 0 && vec[i] == vec[i - 1]) continue;

        for (int j = i + 1; j < n; j++) {
            if (j > 0 && vec[j] == vec[j - 1]) continue;

            int p = j + 1;
            int q = n - 1;

            while (p < q) {
                sum += vec[i] + vec[j] + vec[p] + vec[q];

                if (sum > 0) {
                    p++;
                } else if (sum < 0) {
                    q--;
                } else {
                    ans.push_back(vec[i]);
                    ans.push_back(vec[j]);
                    ans.push_back(vec[p]);
                    ans.push_back(vec[q]);
                    p++;
                    q--;
                }
            }
        }
    }
    return sum;
}

// Function 3: Spiral traversal of matrix
vector<int> spiral(vector<vector<int>> &mat) {
    int n = mat[0].size() - 1;
    int m = mat.size() - 1;
    int srow = 0;
    int scol = 0;
    int endr = m - 1;
    int endc = n - 1;
    vector<int> ans;

    while (srow <= endr && scol <= endc) {
        for (int j = scol; j <= endc; j++) {
            ans.push_back(mat[srow][j]);
        }
        for (int i = srow + 1; i <= endr; i++) {
            ans.push_back(mat[i][endc]);
        }
        for (int j = endc - 1; j >= scol; j--) {
            ans.push_back(mat[srow][j]);
        }
        for (int i = endr - 1; i >= srow + 1; i--) {
            ans.push_back(mat[i][scol]);
        }
        srow++;
        endr--;
        endc--;
        scol++;
    }

    return ans;
}

// Function 4: Remove duplicates in matrix
vector<int> remdup(vector<vector<int>> &mat) {
    vector<int> ans;
    unordered_set<int> s;
    int a;
    int b;
    int expsum = 0;
    int actsum = 0;
    int n = mat.size();

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            actsum += mat[row][col];
            if (s.find(mat[row][col]) != s.end()) {
                a = mat[row][col];
                ans.push_back(a);
            }
            s.insert(mat[row][col]);
        }
    }

    expsum += n * n * (n * n + 1) / 2;
    b = expsum + a - actsum;
    ans.push_back(b);

    return ans;
}

// Main driver
int main() {
    vector<int> vec;
    string choice;
    int ele;
    int num;

    cout << "Enter the size of vector: ";
    cin >> num;

    for (int i = 0; i < num; i++) {
        cout << "Enter element " << vec.size() + 1 << ": ";
        cin >> ele;
        vec.push_back(ele);
    }

    cout << "*********** THE VECTOR FORMED ***********\n";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;

    cout << "Do you want to clean the vector (yes/no): ";
    cin >> choice;

    if (choice == "yes") {
        cout << "*********** SORTED VECTOR ***********\n";
        sort(vec.begin(), vec.end());
        for (int val : vec) {
            cout << val << " ";
        }
        cout << endl;

        int tar;
        cout << "Enter the target: ";
        cin >> tar;
        cout << "There are " << totalsubarray(vec, tar) << " in the original vector\n";
        cout << "THE 4 ELEMENTS THAT EQUALS 0: " << foursum(vec) << endl;
    }

    vector<vector<int>> mat;
    mat.push_back(vec);
    sort(mat.begin(), mat.end());

    cout << "*********** SORTED MATRIX ************\n";
    int row = mat.size();
    int col = mat[0].size();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << mat[i][j] << " ";
        }
    }
    cout << endl;

    cout << "*********** MATRIX WITHOUT DUPLICATE ************\n";
    remdup(mat);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << mat[i][j] << " ";
        }
    }
    cout << endl;

    cout << "*********** SPIRAL MATRIX ************\n";
    spiral(mat);

    return 0;
}
