#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void subsethelper(vector<int>& arr, int i, vector<int>& ans, vector<vector<int>>& sets) {
    if (i == arr.size()) {
        sets.push_back(ans);
        return;
    }
    ans.push_back(arr[i]);
    subsethelper(arr, i + 1, ans, sets);
    ans.pop_back();
    int idx = 0;
    int n = arr.size();
    while (i < n && idx > 0 && arr[idx] == arr[idx - 1]) {
        idx++;
    }
    subsethelper(arr, i + 1, ans, sets);
}

vector<vector<int>> subset(vector<int>& arr) {
    vector<int> ans;
    vector<vector<int>> sets;
    subsethelper(arr, 0, ans, sets);
    return sets;
}

void permutationhelper(vector<int>& arr, int idx, vector<vector<int>>& ans) {
    if (idx == arr.size()) {
        ans.push_back(arr);
        return;
    }
    for (int i = idx; i < arr.size(); i++) {
        swap(arr[idx], arr[i]);
        permutationhelper(arr, idx + 1, ans);
        swap(arr[idx], arr[i]);
    }
}

vector<vector<int>> permutation(vector<int>& arr) {
    vector<vector<int>> ans;
    permutationhelper(arr, 0, ans);
    return ans;
}

bool issafe(vector<vector<char>>& mat, int row, int col, int n) {
    for (int j = 0; j < n; j++) {
        if (mat[row][j] == 'Q') return false;
    }
    for (int i = 0; i < n; i++) {
        if (mat[i][col] == 'Q') return false;
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (mat[i][j] == 'Q') return false;
    }
    for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
        if (mat[i][j] == 'Q') return false;
    }
    return true;
}

void nqueenshelper(vector<vector<char>>& mat, int row, int n, vector<vector<string>>& ans) {
    if (row == n) {
        vector<string> board;
        for (int i = 0; i < n; i++) {
            string s;
            for (int j = 0; j < n; j++) s.push_back(mat[i][j]);
            board.push_back(s);
        }
        ans.push_back(board);
        return;
    }
    for (int col = 0; col < n; col++) {
        if (issafe(mat, row, col, n)) {
            mat[row][col] = 'Q';
            nqueenshelper(mat, row + 1, n, ans);
            mat[row][col] = '.';
        }
    }
}

vector<vector<string>> nqueens(int n) {
    vector<vector<char>> mat(n, vector<char>(n, '.'));
    vector<vector<string>> ans;
    nqueenshelper(mat, 0, n, ans);
    return ans;
}

// Sudoku part
bool issafe2(vector<vector<int>>& mat, int row, int col, int dig) {
    for (int i = 0; i < 9; i++) {
        if (mat[i][col] == dig) return false;
        if (mat[row][i] == dig) return false;
    }
    int srow = (row / 3) * 3;
    int scol = (col / 3) * 3;
    for (int i = srow; i < srow + 3; i++) {
        for (int j = scol; j < scol + 3; j++) {
            if (mat[i][j] == dig) return false;
        }
    }
    return true;
}

bool sudokuhelper(vector<vector<int>>& mat, int row, int col) {
    if (row == 9) return true;
    int nextrow = row, nextcol = col + 1;
    if (nextcol == 9) {
        nextrow = row + 1;
        nextcol = 0;
    }
    if (mat[row][col] != 0) {
        return sudokuhelper(mat, nextrow, nextcol);
    }
    for (int dig = 1; dig <= 9; dig++) {
        if (issafe2(mat, row, col, dig)) {
            mat[row][col] = dig;
            if (sudokuhelper(mat, nextrow, nextcol)) return true;
            mat[row][col] = 0;
        }
    }
    return false;
}

vector<vector<int>> sudoku(vector<vector<int>>& mat) {
    sudokuhelper(mat, 0, 0);
    return mat;
}

int main() {
    vector<int> arr;
    int n;
    cout << "enter the array size: ";
    cin >> n;
    int val;
    for (int i = 0; i < n; i++) {
        cout << "enter the " << i + 1 << " element: ";
        cin >> val;
        arr.push_back(val);
    }

    auto a = subset(arr);
    cout << "weapon choice for the next battle\n";
    for (auto& v : a) {
        for (int x : v) cout << x << " ";
        cout << "\n";
    }

    auto b = permutation(arr);
    cout << "battle sequence\n";
    for (auto& v : b) {
        for (int x : v) cout << x << " ";
        cout << "\n";
    }

    auto c = nqueens(n);
    cout << "shield arrangement\n";
    for (auto& board : c) {
        for (auto& row : board) cout << row << "\n";
        cout << "----\n";
    }

    vector<vector<int>> mat(9, vector<int>(9, 0));
    auto d = sudoku(mat);
    cout << "cipher scroll\n";
    for (auto& row : d) {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }

    return 0;
}
