#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void helperknightour(vector<vector<int>>& mat, int r, int c, int n, int path, vector<int>& ans) {
    if (r < 0 || r >= n || c < 0 || c >= n || mat[r][c] != 0) {
        return;
    }
    mat[r][c] = -1;          // mark visited
    ans.push_back(path);     // record step

    if (path == (n * n) - 1) {
        return;              // base case
    }

    // explore all 8 moves
    helperknightour(mat, r - 2, c + 1, n, path + 1, ans);
    helperknightour(mat, r - 1, c + 2, n, path + 1, ans);
    helperknightour(mat, r + 1, c + 2, n, path + 1, ans);
    helperknightour(mat, r + 2, c + 1, n, path + 1, ans);
    helperknightour(mat, r + 2, c - 1, n, path + 1, ans);
    helperknightour(mat, r + 1, c - 2, n, path + 1, ans);
    helperknightour(mat, r - 1, c - 2, n, path + 1, ans);
    helperknightour(mat, r - 2, c - 1, n, path + 1, ans);

    mat[r][c] = 0;           // unmark for backtracking
    ans.pop_back();          // remove last step
}

vector<int> knighttour(vector<vector<int>>& mat) {
    int path = 0;
    vector<int> ans;
    helperknightour(mat, 0, 0, mat.size(), path, ans);
    return ans;
}

// --- Stub functions to allow compilation ---
int mergesort(vector<int>& a, int s, int mid, int e) {
    int i = s;
    int j = mid+1;
    int count = 0;
    vector <int>ans;
    if(i <= mid && j <= e){
        if(a[i] <= a[j]){
            ans.push_back(a[i]);
            i++;
        }
        else{
            ans.push_back(a[j]);
            j++;
            count += mid - i + 1;
        }
        while(i <= mid){
            ans.push_back(a[i]);
            i++;
        }
        while(j <= e){
            ans.push_back(a[j]);
            j++;
        }
        for(int idx = 0 ; idx < ans.size() ; idx++){
            a[idx + s] = ans[idx];
        }
    }
    return count;
}
int countinv(vector<int>& a, int s, int e) {
    if(s < e){
        int mid = s + ( e - s ) / 2;
        int lcountinv = countinv(a, s , mid);
        int rcountinv = countinv(a,mid+1 , e);
        int final = mergesort(a , s , mid , e);
        return lcountinv + rcountinv + final;
    }
    return 0; // ✅ added
}
int partion(vector <int>&a, int s , int e){
    int piv = a[e];
    int idx = s-1;
    int end = e - 1;
    for(int j = 0; j < end ; j++){
        if(a[j] < piv){
            idx++;
            swap(a[j],a[idx]);
        }
    }
    idx++;
    swap(a[e], a[idx]); // ✅ fixed
    return idx;
}
void quick(vector<int>& a, int s, int e) {
    if(s < e){
        int pividx = partion(a,s,e);
        quick(a,s,pividx-1);
        quick(a,pividx+1,e);
    }
}
void quicksort(vector <int>&a){
    quick(a,0,a.size()-1);
}
bool ispalin(string &part){
    string s2 = part;
    reverse(s2.begin(),s2.end());
    return s2 == part;
}
bool Partionhelper(string s, int idx) {
    int n = s.size();
    if(idx == n){
        return true;
    }
    for(int i = 0 ; i < n ; i++){
        string part = s.substr(0,i-idx+1);
        if(ispalin(part)){
            Partionhelper(s.substr(i+1),idx);
            return true;
        }
    }
    return false;
}
bool canPartion(string &s){
    return Partionhelper(s,0); // ✅ added return
}
void rotate90(vector<vector<int>> &m) {
    int n = m.size();
    for(int i=0;i<n;i++){
     for(int j=i;j<n;j++){
        swap(m[i][j],m[j][i]);   // transpose
    }
   }
   for(int i=0;i<n;i++){
    reverse(m[i].begin(),m[i].end()); // reverse each row
   }

}

int main() {
    int o;
    cout << "enter the order of matrix: ";
    cin >> o;
    vector<vector<int>> mat(o, vector<int>(o, 0));
    for (int i = 0; i < o; i++) {
        for (int j = 0; j < o; j++) {
            cout << "mat[" << i << "][" << j << "] = ";
            cin >> mat[i][j];
        }
    }

    vector<int> a = knighttour(mat);
    for (int val : a) cout << val << " ";
    cout << endl;

    int b = countinv(a, 0, a.size() - 1);
    cout << "total number of inversion: " << b << endl;

    quicksort(a);
    for (int val : a) cout << val << " ";
    cout << endl;
    string s;
    cout << "enter a knight move: ";
    cin >> s;
    if (canPartion(s)) cout << "string encoded";

    vector<int> c = a;
    vector<vector<int>> m2(o, c);  // o rows, each a copy of c

    rotate90(m2);
    for (int i = 0; i < o; i++) {
        for (int j = 0; j < o; j++) cout << m2[i][j] << " ";
    }
    cout << endl;

    rotate90(m2);
    for (int i = 0; i < o; i++) {
        for (int j = 0; j < o; j++) cout << m2[i][j] << " ";
    }
    cout << endl;

    rotate90(m2);
    for (int i = 0; i < o; i++) {
        for (int j = 0; j < o; j++) cout << m2[i][j] << " ";
    }
    cout << endl;

    return 0;
}

