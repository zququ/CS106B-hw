#include "LinkedString.h"

LinkedString::LinkedString() {
    // Task 1: O(N^2)
    head = nullptr;
    // Task 2: O(N^2) -> O(N)
    tail = nullptr;
}

LinkedString::LinkedString(const string& str) {
    // Task 1: O(N^2)
    // head = strToLink(str);
    // Task 2: O(N^2) -> O(N)
    head = nullptr;
    tail = nullptr;
    strToLink(str, head, tail);
}

// Task 1: O(N^2)
Node* LinkedString::strToLink(const string& str) {
    Node* link = nullptr;
    for (const char ch : str) {
        if (link == nullptr) {
            link = new Node{ch, nullptr};
        } else {
            Node* copy = link;
            while (copy->next != nullptr) { // O(N)
                copy = copy->next;
            }
            copy->next = new Node{ch, nullptr};
        }
    }
    return link;
}

// Task 2: O(N^2) -> O(N)   *** return 2 data ***
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

LinkedString::~LinkedString() {
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
