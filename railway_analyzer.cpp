#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

class passenger{
    public:
    vector<string>name;
    vector<int>id;
    vector<string>bookTrain;
    vector<int>Tprice;
    passenger(vector<string>name,vector<int>id,vector<string>bookTrain, vector<int>Tprice){
        this->name = name;
        this->id = id;
        this->bookTrain = bookTrain;
        this->Tprice = Tprice;
    }
    virtual void bookTicket(string trainName, int price){
        bookTrain.push_back(trainName);
        Tprice.push_back(price);
    }
    virtual void display(){
        string n;
        cout << "enter the passenger name: ";
        cin >> n;
        name.push_back(n);
        int i;
        cout << "enetr the passenger ID: ";
        cin >> i;
        id.push_back(i);
        cout << endl;
        string t;
        int p;
        cout << "enetr the train name and price: ";
        cin >> t >> p;
        bookTicket(t,p);
    }
};
class normalPass : public passenger {
public:
    vector<int> travelHrs;
    vector<int> seatNo;
    normalPass(vector<string> name, vector<int> id,
               vector<string> bookTrain, vector<int> Tprice,
               vector<int> travelHrs, vector<int> seatNo,
               vector<string> travelHis)
        : passenger(name, id, bookTrain, Tprice) {
        this->travelHrs = travelHrs;
        this->seatNo = seatNo;
    }

    void analyzeTravelPattern(int hrs) {
        travelHrs.push_back(hrs);

        if (travelHrs.size() == 1 || travelHrs.size() == 0  ) {
            cout << "Only one travel record, no jump to analyze." << endl;
            return;
        }

        int maxjump = 0;
        int sum = 0;

        for (size_t i = 1; i < travelHrs.size(); i++) {
            int jump = abs(travelHrs[i] - travelHrs[i - 1]);
            maxjump = max(jump, maxjump);
        }

        for (size_t i = 0; i < travelHrs.size(); i++) {
            sum += travelHrs[i];
        }

        double avg = static_cast<double>(sum) / travelHrs.size();

        cout << "MAX JUMP IN TRAVEL HOURS: " << maxjump << endl;
        cout << "AVERAGE TRAVEL HOURS: " << avg << endl;
    }
    pair<string,int> findBestJourney(const vector<pair<string,int>>& journeys) {
    if (journeys.empty()) {
        return {"", -1}; // no journeys
    }

    pair<string,int> best = journeys[0]; // start with first journey

    for (size_t i = 1; i < journeys.size(); i++) {
        // Compare by price first
        if (journeys[i].second > best.second) {
            best = journeys[i];
        }
        // If price is equal, compare lexicographically
        else if (journeys[i].second == best.second &&
                 journeys[i].first < best.first) {
            best = journeys[i];
        }
    }

    return best;
}


    void book() {
    string trainName;
    int price;
    cout << "Enter train name: ";
    cin >> trainName;
    cout << "Enter ticket price: ";
    cin >> price;
    bookTicket(trainName, price);

    cout << endl;
    vector<pair<string,int>> journeys;
    int j;
    cout << "Enter the number of journeys you have: ";
    cin >> j;

    for (int i = 0; i < j; i++) {
        string val;
        int pr;
        cout << "Enter train " << i+1 << " name and price: ";
        cin >> val >> pr;
        journeys.push_back({val, pr});
    }

    cout << "_______BEST JOURNEY ANALYSED__________" << endl;
    auto best = findBestJourney(journeys);
    cout << "Best Journey: " << best.first << " with price " << best.second << endl;
}


    void show() {
        display();
        int h;
        cout << "Enter the travel hours: ";
        cin >> h;
        cout << "_______TRAVELING PATTERN ANALYSED__________" << endl;
        analyzeTravelPattern(h);
    }
};
int main() {
    vector<string> names = {"Krishna"};
    vector<int> ids = {101};
    vector<string> trains = {"Rajdhani"};
    vector<int> prices = {1500};
    vector<int> hrs = {80};
    vector<int> seats = {12};
    vector<string> history = {"Bhubaneswar to Delhi"};

    normalPass p1(names, ids, trains, prices, hrs, seats, history);

    p1.show();  // will ask for passenger details and analyze travel hours
    p1.book();  // will ask for journeys and find best journey
    return 0;
}
