#ifndef MUTABLE_LIST_SEQUENCE_HPP
#define MUTABLE_LIST_SEQUENCE_HPP

#include "ListSequence.hpp"

template<typename T>
class MutableListSequence : public ListSequence<T> {
protected:
    ListSequence<T>* CreateFromList(const LinkedList<T>& other) const override {
        return new MutableListSequence<T>(other);
    }

public:
    MutableListSequence() : ListSequence<T>() {}
    MutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}
    MutableListSequence(const LinkedList<T>& other) : ListSequence<T>(other) {}
    MutableListSequence(const MutableListSequence<T>& other) : ListSequence<T>(other) {}
    
    T& operator[](size_t index) {
        return this->list.GetElement(index);
    }

    const T& operator[](size_t index) const {
        return this->Get(index);
    }

    MutableListSequence<T>* Append(const T& value) {
        this->AppendInternal(value);
        return this;
    }

    MutableListSequence<T>* Prepend(const T& value) {
        this->PrependInternal(value);
        return this;
    }

    MutableListSequence<T>* InsertAt(size_t index, const T& value) {
        this->InsertAtInternal(index, value);
        return this;
    }

    MutableListSequence<T>* Remove(size_t index) {
        this->RemoveAtInternal(index);
        return this;
    }

    Sequence<T>* Clone() const override {
        return new MutableListSequence<T>(*this);
    }

};

#endif /* MUTABLE_LIST_SEQUENCE_HPP */
