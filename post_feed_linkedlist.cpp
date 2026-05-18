#include <iostream>
#include <string>
using namespace std;

// -------------------- Base Class --------------------
class Post {
protected:
    int id;
    string content;
    string timestamp;
public:
    Post(int id, string content, string timestamp)
        : id(id), content(content), timestamp(timestamp) {}

    virtual void display() {
        cout << "ID: " << id << "\nContent: " << content
             << "\nTimestamp: " << timestamp << endl;
    }

    int getId() const { return id; }
    virtual ~Post() {}
};

// -------------------- Derived Classes --------------------
class TextPost : public Post {
    string fontStyle;
public:
    TextPost(int id, string content, string timestamp, string fontStyle)
        : Post(id, content, timestamp), fontStyle(fontStyle) {}
    void display() override {
        Post::display();
        cout << "Font Style: " << fontStyle << endl;
    }
};

class ImagePost : public Post {
    string resolution;
public:
    ImagePost(int id, string content, string timestamp, string resolution)
        : Post(id, content, timestamp), resolution(resolution) {}
    void display() override {
        Post::display();
        cout << "Resolution: " << resolution << endl;
    }
};

class VideoPost : public Post {
    string duration;
public:
    VideoPost(int id, string content, string timestamp, string duration)
        : Post(id, content, timestamp), duration(duration) {}
    void display() override {
        Post::display();
        cout << "Duration: " << duration << endl;
    }
};

// -------------------- Node --------------------
struct Node {
    Post* post;
    Node* next;
    Node* prev;
    Node(Post* p) : post(p), next(nullptr), prev(nullptr) {}
};

// -------------------- Linked List --------------------
class LinkedList {
    Node* head;
    Node* tail;
public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    void insert(Post* p) {
        Node* newNode = new Node(p);
        if(!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void traverseForward() {
        Node* temp = head;
        while(temp) {
            temp->post->display();
            cout << "------------------\n";
            temp = temp->next;
        }
    }

    void traverseBackward() {
        Node* temp = tail;
        while(temp) {
            temp->post->display();
            cout << "------------------\n";
            temp = temp->prev;
        }
    }

    Node* reverseList(){
        Node* curr = head;
        Node* next = NULL;
        Node* prev = NULL;
        while(curr != NULL){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev; // new head
    }

    void print(){
        Node* temp = head;
        while(temp != NULL){
            temp->post->display();
            cout << "------------------\n";
            temp = temp->next;
        } 
    }

    Node* getHead() { return head; } // ✅ Added getter
};

// -------------------- Free Function --------------------
int countvid(Node* node){
    if(node == NULL){
        return 0;
    }
    return (dynamic_cast<VideoPost*>(node->post) ? 1 : 0) + countvid(node->next);
}

// -------------------- Main --------------------
int main() {
    LinkedList feed;

    // Insert posts
    feed.insert(new TextPost(1, "Hello World", "2026-05-18", "Bold"));
    feed.insert(new ImagePost(2, "Sunset Pic", "2026-05-18", "1080p"));
    feed.insert(new VideoPost(3, "Tutorial", "2026-05-18", "15min"));
    feed.insert(new VideoPost(4, "Lecture", "2026-05-18", "30min"));

    cout << "--- Traverse Forward ---\n";
    feed.traverseForward();

    cout << "\n--- Traverse Backward ---\n";
    feed.traverseBackward();

    // Count video posts recursively
    cout << "\nNumber of VideoPosts: " << countvid(feed.getHead()) << endl;

    // Reverse the list
    Node* newHead = feed.reverseList();
    cout << "\n--- After Reversal ---\n";
    Node* temp = newHead;
    while(temp) {
        temp->post->display();
        cout << "------------------\n";
        temp = temp->next;
    }

    // Cleanup (delete all nodes and posts)
    temp = newHead;
    while(temp) {
        Node* next = temp->next;
        delete temp->post;  // delete the Post object
        delete temp;        // delete the Node
        temp = next;
    }

    return 0;
}
