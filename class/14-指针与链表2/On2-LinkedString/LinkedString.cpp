#include "LinkedString.h"

LinkedString::LinkedString() {
    head = nullptr;
}

LinkedString::LinkedString(const string& str) {
     head = strToLink(str);
}

Node* LinkedString::strToLink(const string& str) {
    Node* link = nullptr;
    for (const char ch : str) {  // O(N)
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
    return link; // O(N^2)
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
