#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// ================= BASE CLASS =================

class Account {

private:
    int account_id;

protected:
    string name;

public:

    vector<string> borrowedBooks;

    Account(string name,
            int account_id,
            vector<string> borrowedBooks) {

        this->name = name;
        this->account_id = account_id;
        this->borrowedBooks = borrowedBooks;
    }

    void borrowBook(string book) {
        borrowedBooks.push_back(book);
    }

    int getID() {
        return account_id;
    }

    virtual void displayAccount() {

        cout << "\n===== ACCOUNT DETAILS =====\n";

        cout << "Name: "
             << name
             << endl;

        cout << "Account ID: "
             << account_id
             << endl;

        cout << "Borrowed Books: ";

        for(string b : borrowedBooks) {
            cout << b << " ";
        }

        cout << endl;
    }
};

// ================= STUDENT ACCOUNT =================

class Student : public Account {

public:

    vector<string> favGenre;
    vector<int> readingHours;
    vector<int> ratingsGiven;

    Student(string name,
            int account_id,
            vector<string> borrowedBooks,
            vector<string> favGenre,
            vector<int> readingHours,
            vector<int> ratingsGiven)

        : Account(name,
                  account_id,
                  borrowedBooks) {

        this->favGenre = favGenre;
        this->readingHours = readingHours;
        this->ratingsGiven = ratingsGiven;
    }

    void addGenre(string genre) {
        favGenre.push_back(genre);
    }

    void addReadingHours(int hrs) {
        readingHours.push_back(hrs);
    }

    void addRating(int r) {
        ratingsGiven.push_back(r);
    }

    // ================= RECOMMENDATION =================

    void recommendBooks() {

        cout << "\n===== RECOMMENDATIONS =====\n";

        for(string genre : favGenre) {

            if(genre == "Programming") {
                cout << "Recommend: Clean Code\n";
            }

            else if(genre == "AI") {
                cout << "Recommend: AI Superpowers\n";
            }

            else if(genre == "Fantasy") {
                cout << "Recommend: Harry Potter\n";
            }

            else {
                cout << "Recommend: General Knowledge Book\n";
            }
        }
    }

    // ================= READING ANALYTICS =================

    void analyzeReadingPattern() {

        if(readingHours.empty()) {
            cout << "No reading data.\n";
            return;
        }

        cout << "\n===== READING ANALYTICS =====\n";

        // Longest productive streak
        int streak = 1;
        int bestStreak = 1;

        for(int i = 1; i < readingHours.size(); i++) {

            if(readingHours[i]
               > readingHours[i-1]) {

                streak++;
            }

            else {
                bestStreak =
                max(bestStreak, streak);

                streak = 1;
            }
        }

        bestStreak = max(bestStreak, streak);

        cout << "Longest Productive Streak: "
             << bestStreak
             << endl;

        // Maximum jump
        int maxJump = 0;

        for(int i = 1; i < readingHours.size(); i++) {

            maxJump = max(maxJump,
                          abs(readingHours[i]
                          - readingHours[i-1]));
        }

        cout << "Maximum Reading Jump: "
             << maxJump
             << endl;

        // Average consistency
        double sum = 0;

        for(int hrs : readingHours) {
            sum += hrs;
        }

        double avg = sum / readingHours.size();

        cout << "Average Reading Hours: "
             << avg
             << endl;
    }

    // ================= STRING ANALYSIS =================

    void analyzeBookTags(string tag) {

        cout << "\n===== TAG ANALYSIS =====\n";

        cout << "Tag: "
             << tag
             << endl;

        // Frequency
        map<char,int> freq;

        for(char ch : tag) {
            freq[ch]++;
        }

        cout << "\nCharacter Frequency:\n";

        for(auto x : freq) {

            cout << x.first
                 << " -> "
                 << x.second
                 << endl;
        }

        // Longest repeated sequence
        int best = 1;
        int curr = 1;

        for(int i = 1; i < tag.size(); i++) {

            if(tag[i] == tag[i-1]) {
                curr++;
            }

            else {
                best = max(best, curr);
                curr = 1;
            }
        }

        best = max(best, curr);

        cout << "Longest Repeated Sequence: "
             << best
             << endl;

        // Palindrome check
        string rev = tag;

        reverse(rev.begin(), rev.end());

        if(rev == tag)
            cout << "Palindrome Tag\n";
        else
            cout << "Not Palindrome\n";
    }
};

// ================= PREMIUM ACCOUNT =================

class PremiumAccount : public Account {

public:

    vector<string> wishlist;
    vector<int> audioBookHours;

    PremiumAccount(string name,
                   int account_id,
                   vector<string> borrowedBooks,
                   vector<string> wishlist,
                   vector<int> audioBookHours)

        : Account(name,
                  account_id,
                  borrowedBooks) {

        this->wishlist = wishlist;
        this->audioBookHours = audioBookHours;
    }

    void addWishlist(string book) {

        wishlist.push_back(book);

        sort(wishlist.begin(),
             wishlist.end());
    }

    void addAudioHours(int hrs) {
        audioBookHours.push_back(hrs);
    }

    void premiumRecommendations() {

        cout << "\n===== PREMIUM ANALYTICS =====\n";

        for(int hrs : audioBookHours) {

            if(hrs > 120) {
                cout << "Heavy listener\n";
            }

            else if(hrs >= 60) {
                cout << "Good listener\n";
            }

            else {
                cout << "Casual listener\n";
            }
        }
    }

    // ================= RECURSION =================

    void generateBundles(vector<string>& books,
                         int idx,
                         int k,
                         vector<string>& curr,
                         vector<vector<string>>& ans) {

        // constraint
        if(curr.size() > k) {
            return;
        }

        // base case
        if(idx == books.size()) {

            ans.push_back(curr);
            return;
        }

        // include
        curr.push_back(books[idx]);

        generateBundles(books,
                        idx + 1,
                        k,
                        curr,
                        ans);

        // backtrack
        curr.pop_back();

        // exclude
        generateBundles(books,
                        idx + 1,
                        k,
                        curr,
                        ans);
    }

    vector<vector<string>> getBundles(int k) {

        vector<string> curr;
        vector<vector<string>> ans;

        generateBundles(wishlist,
                        0,
                        k,
                        curr,
                        ans);

        return ans;
    }
};

// ================= MAIN =================

int main() {

    // ================= STUDENT =================

    vector<string> books =
    {"TreasureTrove", "HarryPotter"};

    vector<string> genres =
    {"Programming", "Fantasy"};

    vector<int> reading =
    {2,5,3,8,10};

    vector<int> ratings =
    {5,4,5};

    Student s1("Krishna",
               101,
               books,
               genres,
               reading,
               ratings);

    s1.displayAccount();

    s1.recommendBooks();

    s1.analyzeReadingPattern();

    s1.analyzeBookTags("fantasyyy");

    // ================= PREMIUM =================

    vector<string> wishlist =
    {"AIBook", "DSA", "Math", "Physics"};

    vector<int> audio =
    {45,90,150};

    PremiumAccount p1("Ayush",
                      201,
                      books,
                      wishlist,
                      audio);

    p1.displayAccount();

    p1.premiumRecommendations();

    // ================= RECURSIVE BUNDLES =================

    auto bundles = p1.getBundles(2);

    cout << "\n===== BOOK BUNDLES =====\n";

    for(auto &vec : bundles) {

        cout << "{ ";

        for(string s : vec) {
            cout << s << " ";
        }

        cout << "}\n";
    }

    return 0;
}
