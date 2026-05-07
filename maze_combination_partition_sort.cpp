#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/* ============================
   Rat in a Maze (Backtracking)
   ============================ */
void helpermaze(vector<vector<int>>& mat, int row, int col, string path, vector<string>& ans) {
    int n = mat.size();
    // Boundary and visited check
    if (row < 0 || row >= n || col < 0 || col >= n || mat[row][col] == -1) {
        return;
    }
    // Destination reached
    if (row == n - 1 && col == n - 1) {
        ans.push_back(path);
        return;
    }
    // Mark current cell as visited
    mat[row][col] = -1;

    // Explore all four directions
    helpermaze(mat, row + 1, col, path + 'D', ans); // Down
    helpermaze(mat, row - 1, col, path + 'U', ans); // Up
    helpermaze(mat, row, col - 1, path + 'L', ans); // Left
    helpermaze(mat, row, col + 1, path + 'R', ans); // Right

    // Backtrack (unmark cell)
    mat[row][col] = 1;
}

vector<string> maze(vector<vector<int>>& mat) {
    string path = "";
    vector<string> ans;
    helpermaze(mat, 0, 0, path, ans);
    return ans;
}

/* ============================
   Combination Sum (Recursion)
   ============================ */
void combinationhelper(vector<int>& arr, int idx, int tar, vector<int>& comb, vector<vector<int>>& ans) {
    // Base cases
    if (tar < 0 || idx == arr.size()) return;
    if (tar == 0) {
        ans.push_back(comb);
        return;
    }

    // Include current element
    comb.push_back(arr[idx]);
    combinationhelper(arr, idx + 1, tar - arr[idx], comb, ans); // Move forward
    combinationhelper(arr, idx, tar - arr[idx], comb, ans);     // Allow reuse
    comb.pop_back();

    // Exclude current element
    combinationhelper(arr, idx + 1, tar, comb, ans);
}

vector<vector<int>> combination(vector<int>& arr, int tar) {
    vector<vector<int>> ans;
    vector<int> comb;
    combinationhelper(arr, 0, tar, comb, ans);
    return ans;
}

/* ============================
   Palindrome Partitioning
   ============================ */
bool ispalin(string &s) {
    string s2 = s;
    reverse(s2.begin(), s2.end());
    return s2 == s;
}

void helperpartition(string s, vector<string>& current, vector<vector<string>>& ans) {
    if (s.size() == 0) {
        ans.push_back(current);
        return;
    }
    for (int i = 1; i <= s.size(); i++) {
        string part = s.substr(0, i);
        if (ispalin(part)) {
            current.push_back(part);
            helperpartition(s.substr(i), current, ans);
            current.pop_back();
        }
    }
}

vector<vector<string>> partition(string &s) {
    vector<vector<string>> ans;
    vector<string> current;
    helperpartition(s, current, ans);
    return ans;
}

/* ============================
   Merge Sort (Divide & Conquer)
   ============================ */
void mergehelper(vector<int>& arr2, int st, int mid, int end) {
    vector<int> ans;
    int i = st, j = mid + 1;

    // Merge two sorted halves
    while (i <= mid && j <= end) {
        if (arr2[i] <= arr2[j]) ans.push_back(arr2[i++]);
        else ans.push_back(arr2[j++]);
    }
    while (i <= mid) ans.push_back(arr2[i++]);
    while (j <= end) ans.push_back(arr2[j++]);

    // Copy back to original array
    for (int idx = 0; idx < ans.size(); idx++) {
        arr2[st + idx] = ans[idx];
    }
}

void mergesort(vector<int>& arr2, int st, int end) {
    if (st < end) {
        int mid = st + (end - st) / 2;
        mergesort(arr2, st, mid);
        mergesort(arr2, mid + 1, end);
        mergehelper(arr2, st, mid, end);
    }
}

/* ============================
   Quick Sort (Divide & Conquer)
   ============================ */
int partitionQS(vector<int>& arr1, int st, int end) {
    int pivot = arr1[end];
    int idx = st - 1;
    for (int j = st; j < end; j++) {
        if (arr1[j] <= pivot) {
            idx++;
            swap(arr1[j], arr1[idx]);
        }
    }
    swap(arr1[idx + 1], arr1[end]);
    return idx + 1;
}

void quicksort(vector<int>& arr1, int st, int end) {
    if (st < end) {
        int pividx = partitionQS(arr1, st, end);
        quicksort(arr1, st, pividx - 1);
        quicksort(arr1, pividx + 1, end);
    }
}

/* ============================
   Main Function
   ============================ */
int main() {
    // Input Maze
    int o;
    cout << "Enter the order of matrix: ";
    cin >> o;
    vector<vector<int>> mat(o, vector<int>(o));
    for (int i = 0; i < o; i++) {
        for (int j = 0; j < o; j++) {
            cout << "Enter element [" << i << "][" << j << "]: ";
            cin >> mat[i][j];
        }
    }

    // Rat in a Maze
    auto a = maze(mat);
    cout << "\n.......Paths in Maze.......\n";
    for (auto val : a) cout << val << " ";
    cout << endl;

    // Input Array for Combination Sum
    vector<int> arr;
    int n;
    cout << "\nEnter the size of array: ";
    cin >> n;
    int ele;
    for (int i = 0; i < n; i++) {
        cout << "Enter element " << i + 1 << ": ";
        cin >> ele;
        arr.push_back(ele);
    }
    int k;
    cout << "Enter the target sum: ";
    cin >> k;

    // Combination Sum
    cout << "\n.......Combinations.......\n";
    auto b = combination(arr, k);
    for (auto comb : b) {
        for (auto val : comb) cout << val << " ";
        cout << "\n";
    }

    // Palindrome Partitioning
    string s;
    cout << "\nEnter the string: ";
    cin >> s;
    auto c = partition(s);
    cout << "\n.......Palindrome Partitions.......\n";
    for (auto vec : c) {
        for (auto val : vec) cout << val << " ";
        cout << "\n";
    }

    // Merge Sort
    mergesort(arr, 0, arr.size() - 1);
    cout << "\n.......Array after Merge Sort.......\n";
    for (auto val : arr) cout << val << " ";
    cout << endl;

    // Quick Sort
    quicksort(arr, 0, arr.size() - 1);
    cout << "\n.......Array after Quick Sort.......\n";
    for (auto val : arr) cout << val << " ";
    cout << endl;

    return 0;
}
