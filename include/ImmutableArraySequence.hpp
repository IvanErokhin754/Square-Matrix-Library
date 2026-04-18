#ifndef IMMUTABLE_ARRAY_SEQUENCE_HPP
#define IMMUTABLE_ARRAY_SEQUENCE_HPP

#include "ArraySequence.hpp"

template<typename T>
class ImmutableArraySequence : public ArraySequence<T> {
protected:
    ArraySequence<T>* CreateFromArray(const DynamicArray<T>& other) const override {
        return new ImmutableArraySequence<T>(other);
    }

public:
    ImmutableArraySequence() : ArraySequence<T>() {}
    ImmutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    ImmutableArraySequence(const DynamicArray<T>& other) : ArraySequence<T>(other) {}
    ImmutableArraySequence(const ImmutableArraySequence<T>& other) : ArraySequence<T>(other) {}

    const T& operator[](size_t index) const {
        return this->Get(index);
    }
    
    ImmutableArraySequence<T>* Append(const T& value) const {
        auto* copy = new ImmutableArraySequence<T>(*this);
        copy->AppendInternal(value);
        return copy;
    }

    ImmutableArraySequence<T>* Prepend(const T& value) const {
        auto* copy = new ImmutableArraySequence<T>(*this);
        copy->PrependInternal(value);
        return copy;
    }

    ImmutableArraySequence<T>* InsertAt(size_t index, const T& value) const {
        auto* copy = new ImmutableArraySequence<T>(*this);
        copy->InsertAtInternal(index, value);
        return copy;
    }

    ImmutableArraySequence<T>* Remove(size_t index) const {
        auto* copy = new ImmutableArraySequence<T>(*this);
        copy->RemoveAtInternal(index);
        return copy;
    }

    Sequence<T>* Clone() const override {
        return new ImmutableArraySequence<T>(*this);
    }
};


#endif /* IMMUTABLE_ARRAY_SEQUENCE_HPP */