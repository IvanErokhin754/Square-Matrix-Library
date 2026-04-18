#ifndef IMMUTABLE_LIST_SEQUENCE_HPP
#define IMMUTABLE_LIST_SEQUENCE_HPP

#include "ListSequence.hpp"

template<typename T>
class ImmutableListSequence : public ListSequence<T> {
protected:
    ListSequence<T>* CreateFromList(const LinkedList<T>& other) const override {
        return new ImmutableListSequence<T>(other);
    }

public:
    ImmutableListSequence() : ListSequence<T>() {}
    ImmutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}
    ImmutableListSequence(const LinkedList<T>& other) : ListSequence<T>(other) {}
    ImmutableListSequence(const ImmutableListSequence<T>& other) : ListSequence<T>(other) {}

    const T& operator[](size_t index) const {
        return this->Get(index);
    }

    ImmutableListSequence<T>* Append(const T& value) const {
        auto* copy = new ImmutableListSequence<T>(*this);
        copy->AppendInternal(value);
        return copy;
    }

    ImmutableListSequence<T>* Prepend(const T& value) const {
        auto* copy = new ImmutableListSequence<T>(*this);
        copy->PrependInternal(value);
        return copy;
    }

    ImmutableListSequence<T>* InsertAt(size_t index, const T& value) const {
        auto* copy = new ImmutableListSequence<T>(*this);
        copy->InsertAtInternal(index, value);
        return copy;
    }

    ImmutableListSequence<T>* Remove(size_t index) const {
        auto* copy = new ImmutableListSequence<T>(*this);
        copy->RemoveAtInternal(index);
        return copy;
    }

    Sequence<T>* Clone() const override {
        return new ImmutableListSequence<T>(*this);
    }

};
#endif /* IMMUTABLE_LIST_SEQUENCE_HPP */
