#include "LinkedString.h"

LinkedString::LinkedString() {
    head = nullptr;
    // add the 2nd pointer -> tail
    tail = nullptr;
}

LinkedString::LinkedString(const string& str) {
    head = nullptr;
    tail = nullptr;
    strToLink(str, head, tail);
}

// Task 2: O(N^2) -> O(N)   *** return 2 data ***
// head & tail were cited from up
void LinkedString::strToLink(const string& str, Node*& head, Node*& tail) {
    for (const char ch : str) {
        if (head == nullptr) {
            head = new Node{ch, nullptr};
            tail = head;
        } else {
            tail->next = new Node{ch, nullptr};
            tail = tail->next;
        }
    }
}

LinkedString::~LinkedString(){
    clear();
}

void LinkedString::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;  // important
        delete temp;
    }
}

string LinkedString::toString() {
    Node* temp = head;
    string result;
    while (temp != nullptr) {
        result += temp->ch;
        temp = temp->next;
    }
    return result;
}
