#ifndef PG_GAME_VECTOR_H
#define PG_GAME_VECTOR_H
#pragma once
#include "./SDL2-2.0.10/include/SDL.h"

// klasa vektor bedzie dzialac analogicznie do vektora z c++
template <class T>
class Vector {
public:
    Vector();
    // funkcja dodaje element vektora na koniec
    void push_back(T elementToAdd);
    // funckja wyczyszcza vektor
    void clear();
    // obsluga wyrazenia "[]" w sposob analogiczny do tego z c++
    T& operator [] (uint64_t idx);
    uint64_t size();
    void deleteAt(int index);
    T* getRawArray() {
        return this->rawArray;
    }
    ~Vector();
private:
    T* rawArray;
    uint64_t arraySize;
};

template<class T>
Vector<T>::Vector() {
    this->rawArray = new T[0]();
    this->arraySize = 0;
}

template<class T>
void Vector<T>::push_back(T elementToAdd) {
    T* newArray = new T[this->arraySize+1]();
    for (int i = 0; i < this->arraySize; i++){
        newArray[i] = this->rawArray[i];
    }
    newArray[this->arraySize] = elementToAdd;
    delete[] this->rawArray;
    this->rawArray = newArray;
    this->arraySize++;
}

template<class T>
void Vector<T>::clear() {
    this->arraySize = 0;
    delete[] this->rawArray;
    this->rawArray = new T[0]();
}

template<class T>
Vector<T>::~Vector() {
    delete[] this->rawArray;
}

template<class T>
T &Vector<T>::operator[](uint64_t idx) {
    return this->rawArray[idx];
}

template<class T>
uint64_t Vector<T>::size() {
    return this->arraySize;
}

template<class T>
void Vector<T>::deleteAt(int index) {
    T* newArray = new T[this->arraySize-1]();
    for(int i = 0; i < this->arraySize; i++) {
        if(i == index) continue;
        newArray[i < index ? i : i-1] = this->rawArray[i];
    }
    this->arraySize--;
    delete[](this->rawArray);
    this->rawArray = newArray;
}

#endif //PG_GAME_VECTOR_H
