#include "LinkedString.h"

LinkedString::LinkedString() {
    head = nullptr;
}

LinkedString::LinkedString(const string& str) {
    head = nullptr;
    strToLink(str);
}

// 创建链表
Node* LinkedString::strToLink(const string& str) {
    // TODO: 尾端插入
    (void)str;
    Node* link = nullptr;

    return link;
}

LinkedString::~LinkedString() {
    clear();
}

// 删除链表
void LinkedString::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// 遍历链表
string LinkedString::toString() {
    Node* temp = head;
    string result;
    while (temp != nullptr) {
        result += temp->ch;
        temp = temp->next;
    }
    return result;
}
