#ifndef BULLET_HELL_3_LIST_H
#define BULLET_HELL_3_LIST_H
#pragma once

// node to element listy, ktory przechowuje pointer do poprzedniego elementu, swoja wartość i pointer do nastepnego
template<class T>
struct node {
    node* next = nullptr;
    node* prev = nullptr;
    T value;
};

// lista elementow
template<class T>
class List {
public:
    // head przechowuje pointer do pierwszego noda listy, tail do ostatniego
    node<T>* head = nullptr;
    node<T>* tail = nullptr;


    // funkcja dodaje nastepny node do listy
    void addAfter(T element) {
        // jezeli nie istnieje pierwszy node, zostaje on stworzony
        if(head == nullptr) {
            head = new node<T>();
            head->value = element;
            tail = head;
        }

        // jezeli istnieje juz pierwszy node listy: ostatni node listy otrzymuje pointer do "nowego noda", "nowy node" otrzymuje pointer do wczesniejszego
        else {
            tail->next = new node<T>();
            tail->next->value = element;
            tail->next->prev = tail;
            tail = tail->next;
        }
    }


    // funkcja usuwa node
    void remove(node<T>* node) {
        // jezeli usuwany node jest pierwszym nodem listy: podmianka pierwszego noda listy
        if(node == head) {
           head = node->next;
           // jezeli lista nie ma noda (elementu), to tail i head nie przechowuja wartości; jezeli ma, to head nie powinien wskazywac na element wczesniejszy
           if(head == nullptr) tail = head;
           else
               head->prev = nullptr;
        }

        // jezeli usuwany node nie jest pierwszym nodem listy
        else {
            // niech wcześniejszy node nie przechowuje pointera do usuwanego noda
            node->prev->next = node->next;
            // jezeli node jest ostatnim nodem listy, zmien tail na nowy ostatni node; jezeli nie, niech pozniejszy node nie przechowuje pointera do usuwanego noda
            if (node == tail) tail = node->prev;
            else
                node->next->prev = node->prev;
        }
        // usun node
        delete node->value;
        delete node;
    }


    // funkcja przekazuje pointer do następnego noda listy
    // jezeli nie pobrano zadnego noda, zwraca pierwszy
    node<T>* getNext(node<T>* currentNode) {
        if (currentNode == nullptr) return this->head;
        return currentNode->next;
    }

    // usuwa wszytskie nody
    void deleteAll() {
        if (this->head != nullptr) {
            while (true) {
                // wyjdz z petli jezeli nie ma nastepnego noda
                if (this->head != nullptr && this->head->next == nullptr) break;
                remove(this->head);
            }
            remove(this->head);
        }
    }
};

#endif //BULLET_HELL_3_LIST_H
