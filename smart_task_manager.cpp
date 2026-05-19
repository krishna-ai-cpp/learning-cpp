#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

class task {
public:
    int id;
    string title;
    int priority;
    int deadline;
    string status;
    string difficulty;
    string time;
    string impLevel;
    string catagory;
    bool completeT;
    int productivity;
    int completed;

    task(int id, string title, int priority, int deadline, string status, string difficulty,
         string time, string impLevel, string catagory, bool completeT, int productivity, int completed) {
        this->id = id;
        this->title = title;
        this->priority = 0;          
        this->deadline = deadline;
        this->status = status;
        this->difficulty = difficulty;
        this->time = time;
        this->impLevel = impLevel;
        this->catagory = catagory;   
        this->completeT = false;     
        this->productivity = 0;
        this->completed = 0;
    }

    virtual void createTask() {
        cout << "enter the task: ";
        cin >> title;
        cout << "enter the days of deadline: ";
        cin >> deadline;
        cout << "enter difficulty: ";
        cin >> difficulty;
        cout << "enter the estimated time: ";
        cin >> time;
        cout << "enter catagory: ";
        cin >> catagory;
        cout << "Tell the importance: ";
        cin >> impLevel;
        cout << "Enter the time: ";
        cin >> time;
    }

    virtual void display() {
        cout << "TASK: " << title << endl;
        cout << "DEADLINE: " << deadline << endl;
        cout << "ESTIMATED TIME: " << time << endl;
        cout << "CATAGORY: " << catagory << endl;
        cout << "IMPORTANCE: " << impLevel << endl;
        cout << "DIFFICULTY: " << difficulty << endl;
    }

    virtual void completedTask() { 
        string y;
        cout << "Have you completed the work (yes / no): ";
        cin >> y;
        if (y == "yes") {            
            completeT = true;        
            productivity += 1;
            completed += 1;
            cout << "Time: " << time << endl;
        } else {
            cout << "Complete your work.....";
        }
        cout << "productivity: " << productivity << endl;  
        cout << "completed: " << completed << endl;
    }

    virtual void upPriority() {
        if (deadline <= 1) {
            priority += 2;
            if (priority > 8) {
                cout << "you have a high priority\nkeep it up......" << endl;
            }
        } else if (difficulty == "high") {   
            priority += 2;
            if (priority > 8) {
                cout << "you have a high priority\nkeep it up......" << endl;
            }
        } else {
            cout << "Improve yourself" << endl;
            cout << "No priority score" << endl;
        }
    }
};
class taskManager : public task {
public:
    vector<task> tasks;

    taskManager(int id, string title, int priority, int deadline, string status, string difficulty,
                string time, string impLevel, string catagory, bool completeT, int productivity, int completed)
        : task(id, title, priority, deadline, status, difficulty, time, impLevel, catagory, completeT, productivity, completed) {}

    void add_task() {
    int newId;
    cout << "create a unique task ID: ";
    cin >> newId;

    // Check for duplicate ID
    for (auto &t : tasks) {
        if (t.id == newId) {
            cout << "duplicate id cannot be entered....." << endl;
            return;   // stop function instead of break
        }
    }

    string newTitle;
    cout << "enter a new task: ";
    cin >> newTitle;

    // Fill other fields with defaults
    int deadline = 0, priority = 0, productivity = 0, completed = 0;
    string status = "pending", difficulty = "medium", time = "0h", impLevel = "low", catagory = "general";
    bool completeT = false;

    // Push new task into vector
    tasks.push_back(task(newId, newTitle, priority, deadline, status, difficulty, time, impLevel, catagory, completeT, productivity, completed));
    cout << "Task added successfully!\n";
   }


    void del_task() {
        int i;
        cout << "enter the task ID to delete: ";
        cin >> i;   // ✅ semicolon added

        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            if (it->id == i) {
                tasks.erase(it);   // ✅ erase with iterator
                cout << "Task deleted successfully!\n";
                return;
            }
        }
        cout << "invalid ID...\n";
    }
    void searchT() {
    int searchId;
    cout << "enter the Task ID to search: ";
    cin >> searchId;

    bool found = false;
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == searchId) {
            cout << "Task found: " << it->title << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Not found....." << endl;
    }
   }
   void show(){
    display();
   }
   void sortByPriority() {
    vector<int> priorities;

    // Collect priorities
    for (auto &t : tasks) {
        priorities.push_back(t.priority);
    }

    // Sort priorities
    sort(priorities.begin(), priorities.end());

    cout << "Priorities sorted:\n";
    for (int p : priorities) {
        cout << p << " ";
    }
    cout << endl;
   }
   void gen_report() {
    cout << "____________GENERATED REPORT_____________" << endl;

    // Show all tasks
    display();

    // Call sort function (it prints internally)
    cout << "\nSorted by Priority:\n";
    sortByPriority();
   }
};
class node {
public:
    int data;
    node* next;
    node(int v) {
        data = v;
        next = NULL;   // initialize next pointer
    }
};

class slist {
private:
    node* head;
    node* tail;
public:
    slist() {
        head = NULL;
        tail = NULL;
    }

    void push_back(node* t) {
        if (head == NULL) {
            head = tail = t;   // first node
            return;
        }
        tail->next = t;
        tail = t;
    }

    void push_front(node* t) {
        if (head == NULL) {
            head = tail = t;   // first node
            return;
        }
        t->next = head;
        head = t;
    }

    void deleteById(int id) {
    if (head == NULL) {
        cout << "List is empty, nothing to delete.\n";
        return;
    }

    // Case 1: delete head
    if (head->data == id) {
        node* temp = head;
        head = head->next;
        delete temp;
        if (head == NULL) tail = NULL;
        cout << "Deleted node with value " << id << endl;
        return;
    }

    // Case 2: delete middle or tail
    node* prev = head;
    node* curr = head->next;
    while (curr != NULL) {
        if (curr->data == id) {
            prev->next = curr->next;
            if (curr == tail) tail = prev;
            delete curr;
            cout << "Deleted node with value " << id << endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    cout << "Node with value " << id << " not found.\n";
}


    void display() {
        node* temp = head;
        while (temp != NULL) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
    node* reverse(node* n){
        node* prev = NULL;
        node* curr = head;
        node* last = NULL;
        while(curr != NULL){
            last = curr->next;
            curr->next = prev;
            prev = curr;
            curr = last;
        }
        return prev;
    }
    node* cycle(node* n) {
    node* slow = head;
    node* fast = head;
    bool isCycle = false;

    // Detect cycle
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;          // advance slow by 1
        fast = fast->next->next;    // advance fast by 2
        if (slow == fast) {
            isCycle = true;
            break;
        }
    }

    if (!isCycle) {
        return NULL;
    }

    // Find start of cycle
    slow = head;
    node* prev = NULL;
    while (fast != slow) {
        slow = slow->next;
        prev = fast;
        fast = fast->next;
    }

    // Break the cycle
    prev->next = NULL;
    return slow;   // return start of cycle
   }
};
int main() {

    taskManager tm(
        0, "", 0, 0, "", "",
        "", "", "", false, 0, 0
    );

    int choice;

    do {

        cout << "\n========== TASK MANAGER ==========\n";

        cout << "1. Add Task\n";
        cout << "2. Delete Task\n";
        cout << "3. Search Task\n";
        cout << "4. Show Task Details\n";
        cout << "5. Update Priority\n";
        cout << "6. Complete Task\n";
        cout << "7. Generate Report\n";
        cout << "8. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {

        case 1:
            tm.add_task();
            break;

        case 2:
            tm.del_task();
            break;

        case 3:
            tm.searchT();
            break;

        case 4:
            tm.show();
            break;

        case 5:
            tm.upPriority();
            break;

        case 6:
            tm.completedTask();
            break;

        case 7:
            tm.gen_report();
            break;

        case 8:
            cout << "Exiting Task Manager...\n";
            break;

        default:
            cout << "Invalid Choice...\n";
        }

    } while(choice != 8);

    return 0;
}
