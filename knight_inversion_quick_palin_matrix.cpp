#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/* ============================
   Knight's Tour (Backtracking)
   ============================ */
bool knightstourhelper(vector<vector<int>>& mat, int row, int col, int n, int expval) {
    if (row < 0 || col < 0 || row >= n || col >= n || mat[row][col] != expval) {
        return false;
    }
    if (mat[row][col] == expval) {
        return true;
    }
    // Recursive calls for all 8 knight moves
    bool ans1 = knightstourhelper(mat, row - 2, col + 1, n, expval + 1);
    bool ans2 = knightstourhelper(mat, row - 1, col + 2, n, expval + 1);
    bool ans3 = knightstourhelper(mat, row + 1, col + 2, n, expval + 1);
    bool ans4 = knightstourhelper(mat, row + 2, col + 1, n, expval + 1);
    bool ans5 = knightstourhelper(mat, row + 2, col - 1, n, expval + 1);
    bool ans6 = knightstourhelper(mat, row + 1, col - 2, n, expval + 1);
    bool ans7 = knightstourhelper(mat, row - 1, col - 2, n, expval + 1);
    bool ans8 = knightstourhelper(mat, row - 2, col - 1, n, expval + 1);
    return (ans1 || ans2 || ans3 || ans4 || ans5 || ans6 || ans7 || ans8);
}

bool knightstour(vector<vector<int>> mat) {
    return knightstourhelper(mat, 0, 0, mat.size(), 0);
}

/* ============================
   Merge Sort (Inversion Count)
   ============================ */
int mergesort(vector<int>& arr, int st, int mid, int end) {
    vector<int> ans;
    int i = st, j = mid + 1;
    int icount = 0;

    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            ans.push_back(arr[i++]);
        } else {
            ans.push_back(arr[j++]);
            icount += mid - i + 1;
        }
    }
    while (i <= mid) ans.push_back(arr[i++]);
    while (j <= end) ans.push_back(arr[j++]);

    for (int idx = 0; idx < ans.size(); idx++) {
        arr[st + idx] = ans[idx];
    }
    return icount;
}

int countinv(vector<int>& arr, int st, int end) {
    if (st >= end) return 0;
    int mid = st + (end - st) / 2;
    int leftinv = countinv(arr, st, mid);
    int rightinv = countinv(arr, mid + 1, end);
    int final = mergesort(arr, st, mid, end);
    return leftinv + rightinv + final;
}

/* ============================
   Quick Sort
   ============================ */
int partitionQS(vector<int>& a, int st, int end) {
    int piv = a[end];
    int idx = st - 1;
    for (int i = st; i < end; i++) {
        if (a[i] < piv) {
            idx++;
            swap(a[i], a[idx]);
        }
    }
    swap(a[idx + 1], a[end]);
    return idx + 1;
}

void quicksort(vector<int>& a, int st, int end) {
    if (st < end) {
        int pividx = partitionQS(a, st, end);
        quicksort(a, st, pividx - 1);
        quicksort(a, pividx + 1, end);
    }
}

/* ============================
   Palindrome Partitioning
   ============================ */
bool ispalin(string s) {
    string p = s;
    reverse(p.begin(), p.end());
    return s == p;
}

void palinpartition(string s, vector<string>& ans, vector<vector<string>>& partion) {
    if (s.size() == 0) {
        partion.push_back(ans);
        return;
    }
    for (int i = 1; i <= s.size(); i++) {
        string part = s.substr(0, i);
        if (ispalin(part)) {
            ans.push_back(part);
            palinpartition(s.substr(i), ans, partion);
            ans.pop_back();
        }
    }
}
/* ============================
   Matrix Rotation (90° Clockwise)
   ============================ */
void rotateMatrix(vector<vector<int>>& mat) {
    int n = mat.size();
    // Transpose
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            swap(mat[i][j], mat[j][i]);
        }
    }
    // Reverse each row
    for (int i = 0; i < n; i++) {
        reverse(mat[i].begin(), mat[i].end());
    }
}


/* ============================
   Main Function
   ============================ */
int main() {
    // Knight's Tour input
    int o;
    cout << "Enter the order of matrix: ";
    cin >> o;
    vector<vector<int>> mat(o, vector<int>(o, 0));
    for (int i = 0; i < o; i++) {
        for (int j = 0; j < o; j++) {
            cout << "Enter element [" << i << "][" << j << "]: ";
            cin >> mat[i][j];
        }
    }
    bool a = knightstour(mat);
    cout << "\nKnight's Tour result: " << (a ? "Valid" : "Invalid") << endl;

    // Inversion Count input
    int n;
    cout << "\nEnter the size of array: ";
    cin >> n;
    vector<int> arr;
    int val;
    for (int i = 0; i < n; i++) {
        cout << "Enter element " << i + 1 << ": ";
        cin >> val;
        arr.push_back(val);
    }
    int b = countinv(arr, 0, arr.size() - 1);
    cout << "\nInversion Count: " << b << endl;

    // Quick Sort
    quicksort(arr, 0, arr.size() - 1);
    cout << "\nArray after Quick Sort: ";
    for (auto val : arr) cout << val << " ";
    cout << endl;

    // Palindrome Partitioning
    string s;
    cout << "\nEnter the string: ";
    cin >> s;
    vector<string> ans;
    vector<vector<string>> partion;
    palinpartition(s, ans, partion);
    cout << "\nPalindrome Partitions:\n";
    for (auto vec : partion) {
        for (auto val : vec) cout << val << " ";
        cout << "\n";
    }
        // Matrix Rotation
    int m;
    cout << "\nEnter order of matrix to rotate: ";
    cin >> m;
    vector<vector<int>> mat2(m, vector<int>(m));
    cout << "Enter matrix elements:\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat2[i][j];
        }
    }
    rotateMatrix(mat2);
    cout << "\nMatrix after 90-degree rotation:\n";
    for (auto row : mat2) {
        for (auto val : row) cout << val << " ";
        cout << "\n";
    }

    return 0;
}
