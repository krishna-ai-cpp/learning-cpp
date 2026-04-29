#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

bool alpnum(char ch){
    if(ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9') {
        return true;
    }
    return false;
}

bool Ispalindrome(string &s1) {
    int st = 0;
    int n = s1.size();
    int end = n - 1;

    while (st < end) {
        if (!alpnum(s1[st])) {
            st++;
            continue;
        }
        if (!alpnum(s1[end])) {
            end--;
            continue;
        }
        if (tolower(s1[st]) != tolower(s1[end])) {
            return false;
        }
        st++;
        end--;
    }
    return true;
}

string compress(string &s1) {
    int idx = 0;
    string result = "";

    for (int i = 0; i < s1.size(); i++) {
        char ch = s1[i];
        int count = 0;

        while (i < s1.size() && s1[i] == ch) {
            count++;
            i++;
        }

        if (count == 1) {
            result.push_back(ch);
        } else {
            result.push_back(ch);
            string str = to_string(count);
            result += str;
        }
    }
    return result;
}

bool ispermutation(string &s1 , string &s2) {
    int f1[26] = {0};
    int n = s1.size();
    for(int i = 0 ; i < n ; i++){
        f1[s1[i]-'a']++;
    }
    int windfreq[26] = {0};
    int windidx = 0;
    int idx = 0;
    int windsize = s1.size();
    while(idx < s2.size() && windidx < windsize){
        windfreq[s2[idx] - 'a']++;
        idx++;
        windidx++;
    }
    for(int i = 0; i < 26; i++){   // ✅ fixed array comparison
        if(f1[i] != windfreq[i]){
            return false;
        }
    }
    return true;
}

vector<int> threesum(vector<int>& arr) {
    int num = arr.size();
    int sum = 0;

    for (int i = 0; i < num; i++) {
        int p = i + 1;
        int q = p + 1;

        while (p < q && q < num) {
            sum = arr[i] + arr[p] + arr[q];

            if (sum > 0) {
                q--;
            } else if (sum < 0) {
                p++;
            } else {
                cout << arr[i] << " " << arr[p] << " " << arr[q] << endl;
                p++;
                q--;
            }
        }
    }
    return arr;   // ✅ fixed return type
}

int main() {
    string s1;
    int n1;
    char v1;
    cout << "Enter the size of s1: ";
    cin >> n1;
    for (int i = 0; i < n1; i++) {
        cout << "Enter the " << i + 1 << " element: ";
        cin >> v1;
        s1.push_back(v1);
    }
    cout << endl;

    string s2;
    int n2;
    char v2;
    cout << "Enter the size of s2: ";
    cin >> n2;
    for (int i = 0; i < n2; i++) {
        cout << "Enter the " << i + 1 << " element: ";
        cin >> v2;
        s2.push_back(v2);
    }
    

    set<string> s;
    if (ispermutation(s1, s2)) {
        cout << "Vault unlocked\n";
        string b = compress(s1);
        s.insert(b);
        cout << "******** Your vault number **********" << endl;
        for (string val : s) {
            cout << val << " ";
        }
        cout << endl;
    } else {
        cout << "Vault locked\n";
    }

    if (Ispalindrome(s1)) {
        cout << "🔓 Vault opened! Palindrome confirmed.\n";
    } else {
        cout << "Vault number rejected.\n";
    }

    int num;
    cout << "Enter the size of array: ";
    cin >> num;
    vector<int> arr;
    int dig;
    for (int i = 0; i < num; i++) {
        cout << "Enter the " << i + 1 << " element: ";
        cin >> dig;
        arr.push_back(dig);
    }
    threesum(arr);
    return 0;
}
