#pragma once

#include <ostream>
#include <string>

class ListNode {
private:
    std::string value;
    ListNode *next;
public:
    ListNode(const std::string& value);
    std::string getValue() const;
    ListNode* getNext() const;
    
    friend class LinkedList;
};

class LinkedList {
private:
    ListNode *head;
    ListNode *last;
public:
    LinkedList();
    ~LinkedList();

    bool isEmpty() const;
    void insertAtFront(const std::string & elem);
    void insertAtBack(const std::string & elem);
    bool removeFromFront(std::string & output);
    bool removeFromBack(std::string & output);
    
    friend std::ostream & operator<<(std::ostream & stream, const LinkedList & list );

    ListNode *search(const std::string &value);
    void remove(const std::string &value);
};