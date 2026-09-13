#include "Header_workWithList.h"

List* createListAuto(int len) {

    List* head = nullptr;
    List* tail = nullptr;
    
    for (int i = 0; i < len; ++i) {
        List* newNode = new List;
        newNode->value = rand() % 100 + 1;
        newNode->head = tail;
        newNode->tail = nullptr;
        if (!head) {
            head = newNode;
        }
        if (tail) {
            tail->tail = newNode;
        }
        tail = newNode;
    }
    return head;
    
}

bool hasCycle(List* p) {
    
    List* slow = p;
    List* fast = p;

    do {
        if ((fast->tail == nullptr) || (fast->tail->tail == nullptr)) {
            return false;
        }

        slow = slow->tail;
        fast = fast->tail->tail;
    } while (slow != fast);

    return true;
}


List* createListHand(int* arr, int size) {

    List* head = nullptr;
    List* tail = nullptr;

    for (int i = 0; i < size; i++) {
        List* newNode = new List;
        newNode->value = arr[i];
        newNode->head = tail;
        newNode->tail = nullptr;

        if (!head) {
            head = newNode;
        }
        if (tail) {
            tail->tail = newNode;
        }
        tail = newNode;
    }

    return head;
}


List* insertElementList(List* head, int pos, int value) {

    List* newNode = new List{ value, nullptr, nullptr };

    if (!head || pos <= 1) {
        newNode->tail = head;
        if (head) head->head = newNode;
        head = newNode;
    }
    else {
        List* curr = head;
        int index = 1;
        while (curr->tail && index < pos - 1) {
            curr = curr->tail;
            index++;
        }
        newNode->tail = curr->tail;
        newNode->head = curr;
        if (curr->tail) curr->tail->head = newNode;
        curr->tail = newNode;
    }

    return head;
}


void readList(List* p) {
    if (p != nullptr) {
        cout << GREEN << "Лист в памяти: ";
        List* curr = p;
        while (curr) {
            cout << curr->value << ' ';
            curr = curr->tail;
        }
        cout << RESET;
        pause();
    }
    else {
        cout << RED << "Создайте лист!" << RESET << endl;
        pause();
    }
}


void readListWithoutPause(List* p) {
    if (p != nullptr) {
        cout << GREEN << "Лист в памяти: ";
        List* curr = p;
        while (curr) {
            cout << curr->value << ' ';
            curr = curr->tail;
        }
        cout << RESET;
    }
    else {
        cout << RED << "Создайте лист!" << RESET << endl;
    }
}


List* getElementByIndexMain(List* head, int pos) {

    List* curr = head;
    int index = 1;
    while (curr && index < pos) {
        curr = curr->tail;
        index++;
    }
    return curr; // nullptr, если нет такого индекса
}


List* getElementByIndex(List* head, int pos) {

    List* curr = head;
    int index = 1;
    while (curr && index < pos) {
        curr = curr->tail;
        index++;
    }
    return curr; // nullptr, если нет такого индекса
}


List* getElementByValueMain(List* head, int value) {

    List* curr = head;
    while (curr) {
        if (curr->value == value)
            return curr;
        curr = curr->tail;
    }
    return nullptr;
}

List* getElementByValue(List* head, int value) {
    
    List* curr = head;
    while (curr) {
        if (curr->value == value)
            return curr;
        curr = curr->tail;
    }
    return nullptr;
}

List* deleteElementByIndex(List* head, int pos) {

    List* toDelete = getElementByIndex(head, pos);
    if (!toDelete) return head;

    if (toDelete->head)
        toDelete->head->tail = toDelete->tail;
    else
        head = toDelete->tail; 

    if (toDelete->tail)
        toDelete->tail->head = toDelete->head;

    delete toDelete;
    return head;
}


List* deleteElementByValue(List* head, int value) {
    
    List* toDelete = getElementByValue(head, value);
    if (!toDelete) return head;

    if (toDelete->head)
        toDelete->head->tail = toDelete->tail;
    else
        head = toDelete->tail; // удаляем голову

    if (toDelete->tail)
        toDelete->tail->head = toDelete->head;

    delete toDelete;
    return head;
}


List* swapNodesByIndex(List* head, int pos1, int pos2) {
    
    if (pos1 == pos2 || !head) {
        return head;
    }
    List* node1 = head;
    List* node2 = head;
    int i = 1;
    while (node1 && i < pos1) { node1 = node1->tail; i++; }
    i = 1;
    while (node2 && i < pos2) { node2 = node2->tail; i++; }

    if (!node1 || !node2) {
        return head;
    }
        

    if (node1->tail == node2) swap(node1, node2);

    List* prev1 = node1->head;
    List* next1 = node1->tail;
    List* prev2 = node2->head;
    List* next2 = node2->tail;

    if (prev1) prev1->tail = node2;
    if (next1) next1->head = node2;
    if (prev2) prev2->tail = node1;
    if (next2) next2->head = node1;

    swap(node1->head, node2->head);
    swap(node1->tail, node2->tail);

    if (head == node1) {
        return node2;
    }
    if (head == node2) {
        return node1;
    }
    return head;
}


void deleteList(List*& head) {
    List* current = head;

    while (current != nullptr) {
        List* temp = current;
        current = current->tail;
        delete temp;
    }

    head = nullptr;
}

void deleteAllLists(List* NewList) {
    deleteList(NewList);
    delete[] logs;
    logs = nullptr;
    logCount = 0;
}