#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class user {

private:
    int user_id;

public:

    string name;
    vector<int> solvedProb;

    user(string name,
         int user_id,
         vector<int>& solvedProb) {

        this->name = name;
        this->user_id = user_id;
        this->solvedProb = solvedProb;
    }

    virtual void login(int prob) {

        solvedProb.push_back(prob);
    }

    int getid() {
        return user_id;
    }

    virtual void displayProfile() {

        cout << "NAME: "
             << name
             << endl;

        cout << "USER ID: "
             << getid()
             << endl;

        cout << "PROBLEMS SOLVED: "
             << solvedProb.size()
             << endl;
    }
};

// ================= STUDENT =================

class student : public user {

public:

    int curRating;
    int streak;

    vector<int> weeklyRatings;
    vector<int> streaks;
    vector<int> submission;

    student(string name,
            int user_id,
            vector<int>& solvedProb,
            int curRating,
            int streak,
            vector<int>& submission)

        : user(name, user_id, solvedProb) {

        this->curRating = curRating;
        this->streak = streak;
        this->submission = submission;
    }

    void login(int sol) override {

        submission.push_back(sol);
    }

    void displayProfile() override {

        user::displayProfile();

        cout << "CURRENT RATING: "
             << curRating
             << endl;

        cout << "STREAK: "
             << streak
             << endl;

        cout << "SUBMISSIONS: "
             << submission.size()
             << endl;
    }

    void addRatings(int curRatings) {
        weeklyRatings.push_back(curRatings);
    }

    void addStreaks(int streakValue) {
        streaks.push_back(streakValue);
    }

    void highImpr_and_streak() {

        int maximp = 0;

        for(int val : weeklyRatings) {
            maximp = max(maximp, val);
        }

        cout << "Highest Rating: "
             << maximp
             << endl;

        int longestStreak = 0;

        for(int val : streaks) {
            longestStreak =
            max(longestStreak, val);
        }

        cout << "Highest Streak: "
             << longestStreak
             << endl;

        int sum = 0;

        for(int val : weeklyRatings) {
            sum += val;
        }

        double avg =
        (double)sum / weeklyRatings.size();

        cout << "Average Rating: "
             << avg
             << endl;
    }
};

// ================= MENTOR =================

class mentor : public user {

public:

    vector<int> handled;
    vector<string> feedback;

    mentor(string name,
           int user_id,
           vector<int>& solvedProb,
           vector<int> handled,
           vector<string> feedback)

        : user(name, user_id, solvedProb) {

        this->handled = handled;
        this->feedback = feedback;
    }

    void login(int han) override {

        handled.push_back(han);
    }

    void displayProfile() override {

        user::displayProfile();

        cout << "STUDENTS HANDLED: "
             << handled.size()
             << endl;

        cout << "FEEDBACK COUNT: "
             << feedback.size()
             << endl;
    }
};

// ================= CONTEST ADMIN =================

class contestAdmin : public user {

public:

    contestAdmin(string name,
                 int user_id,
                 vector<int>& solvedProb)

        : user(name, user_id, solvedProb) {}

    vector<string> challenge =
    {"Array", "Recursion", "Strings"};

    void comb(vector<string>& challenge,
              int idx,
              vector<string>& ans,
              vector<vector<string>>& combination) {

        if(idx == challenge.size()) {

            combination.push_back(ans);
            return;
        }

        ans.push_back(challenge[idx]);

        comb(challenge,
             idx + 1,
             ans,
             combination);

        ans.pop_back();

        comb(challenge,
             idx + 1,
             ans,
             combination);
    }

    vector<vector<string>> getcomb(vector<string> challenge) {

        vector<string> ans;
        vector<vector<string>> combination;

        comb(challenge,
             0,
             ans,
             combination);

        return combination;
    }

    bool ispalin(const string& parts) {

        string s = parts;

        reverse(s.begin(), s.end());

        return s == parts;
    }

    bool checkpalin(const vector<string>& feedback,
                    int idx) {

        if(idx == feedback.size()) {
            return true;
        }

        if(!ispalin(feedback[idx])) {
            return false;
        }

        return checkpalin(feedback,
                           idx + 1);
    }
};

// ================= MAIN =================

int main() {

    vector<int> solved = {1,2,3};

    vector<int> sub = {10,20};

    vector<int> handled = {5,6};

    vector<string> feedback =
    {"madam", "level"};

    student s1("krishna",
               101,
               solved,
               1450,
               12,
               sub);

    mentor m1("Guru",
              100,
              solved,
              handled,
              feedback);

    contestAdmin c1("Admin",
                    3,
                    solved);

    s1.displayProfile();

    cout << endl;

    m1.displayProfile();

    cout << endl;

    s1.addRatings(1200);
    s1.addRatings(1300);
    s1.addRatings(1450);

    s1.addStreaks(5);
    s1.addStreaks(10);

    s1.highImpr_and_streak();

    cout << "\nContest combinations:\n";

    auto combs =
    c1.getcomb(c1.challenge);

    for(auto& comb : combs) {

        for(auto& str : comb) {
            cout << str << " ";
        }

        cout << endl;
    }

    cout << "\nPalindrome Feedback Check: ";

    if(c1.checkpalin(feedback, 0))
        cout << "All Palindrome\n";
    else
        cout << "Not All Palindrome\n";
}
