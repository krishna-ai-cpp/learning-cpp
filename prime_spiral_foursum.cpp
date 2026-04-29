#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isprime(int &z){
    int n = z;
    for(int i = 2 ; i < n ; i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}

vector<bool> sieve(int &e){
    int n = e;
    vector<bool> isprime(n+1 , true);
    isprime[0] = isprime[1] = false; 
    for(int i = 2; i <= n ; i++){
        if(isprime[i]){
            for(int j = i*2; j <= n ; j+=i){
                isprime[j] = false;
            }
        }
    }
    return isprime;   // ✅ fixed return
}

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
                sum = vec[i] + vec[j] + vec[p] + vec[q];  // ✅ fixed

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

int main() {
    int num;
    cout << "enter an integer n (size of matrix): ";
    cin >> num;
    int k;
    cout << "enter the number k: ";
    cin >> k;

    vector<bool> a = sieve(num);
    cout << " *******PRIME NUMBERS**********\n";
    for (int i = 2 ; i <= num ; i++) {
        if(a[i]) cout << i << " ";   // ✅ print primes
    }
    cout << endl;

    cout << " *******MATRIX**********\n";
    vector<vector<int>> mat(num, vector<int>(num, 0));
    for(int i = 0; i < num ; i++){
        for(int j = 0; j < num; j++){
            mat[i][j] = i+j;   // dummy fill
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    cout << " *******SPIRAL MATRIX**********\n";
    vector<int> c = spiral(mat);
    for (int val : c){
        cout << val << " ";
    }
    cout << endl;

    cout << " *******FOUR SUM **********\n";
    int d = foursum(c);
    cout << d << endl;

    return 0;
}
