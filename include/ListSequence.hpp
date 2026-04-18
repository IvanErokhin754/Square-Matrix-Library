#ifndef LIST_SEQUENCE_HPP
#define LIST_SEQUENCE_HPP

#include "Sequence.hpp"
#include "LinkedList.hpp"
#include <stdexcept>

template<typename T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T> list;

    virtual ListSequence<T>* CreateFromList(const LinkedList<T>& other) const = 0;

    void AppendInternal(const T& value) {
        list.Append(value);
    }
    void PrependInternal(const T& value) {
        list.Prepend(value);
    }
    void InsertAtInternal(size_t index, const T& value) {
        if (index > list.GetSize())
            throw std::out_of_range("Index out of range");
        list.InsertAt(index, value);
    }
    void RemoveAtInternal(size_t index) {
        if (index >= list.GetSize())
            throw std::out_of_range("Index out of range");
        list.RemoveAt(index);
    }

public:
    ListSequence() : list() {}
    ListSequence(T* items, int count) : list() {
        for (int i = 0; i < count; i++) {
            AppendInternal(items[i]);
        }
    }
    ListSequence(const LinkedList<T>& other) : list(other) {}
    ListSequence(const ListSequence<T>& other) : list(other.list) {}

    typename LinkedList<T>::Iterator begin() {
        return list.begin();
    }

    typename LinkedList<T>::Iterator end() {
        return list.end();
    }

    typename LinkedList<T>::ConstIterator begin() const {
        return list.begin();
    }

    typename LinkedList<T>::ConstIterator end() const {
        return list.end();
    }

    const T& Get(size_t index) const override {
        return list.GetElement(index);
    } 

    void Set(size_t index, const T& value) override {
        list.SetElement(index, value);
    }

    const T& GetFirst() const override {
        return list.GetFirst(); 
    }

    const T& GetLast() const override {
        return list.GetLast();
    }

    size_t GetLength() const override {
        return list.GetSize();
    } 

    Sequence<T>* GetSubsequence(size_t start_index, size_t end_index) const override {
        if (start_index > end_index || end_index >= list.GetSize()) 
            throw std::out_of_range("Index out of range");
        
        LinkedList<T> temp;
        for (size_t i = start_index; i <= end_index; i++) {
            temp.Append(list.GetElement(i));
        }

        return CreateFromList(temp);
    }

    Sequence<T>* Concat(const Sequence<T>& other) const override {
        LinkedList<T> temp(list);

        for (size_t i = 0; i < other.GetLength(); i++) {
            temp.Append(other.Get(i));
        }

        return CreateFromList(temp);
    }

    Sequence<T>* Map(T (*func)(const T&)) const {
        LinkedList<T> temp;

        for (auto it = this->begin(); it != this->end(); ++it) {
            temp.Append(func(*it));
        }

        return CreateFromList(temp);
    }

    Sequence<T>* Where(bool (*pred)(const T&)) const {
        LinkedList<T> temp;

        for (auto it = this->begin(); it != this->end(); ++it) {
            if (pred(*it))
                temp.Append(*it);
        }

        return CreateFromList(temp);
    }

};



#endif /* LIST_SEQUENCE_HPP */