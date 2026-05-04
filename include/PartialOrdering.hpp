#ifndef PARTIAL_ORDERING_HPP
#define PARTIAL_ORDERING_HPP

#include <stdexcept>
#include <cstddef>
#include "MutableArraySequence.hpp"
#include "SquareMatrix.hpp"

template<typename T>
class PartialOrdering {
private:
    MutableArraySequence<T> elements;
    SquareMatrix<int> relation;

    int FindIndex(const T& value) const {
        for (size_t i = 0; i < elements.GetLength(); i++) {
            if (elements[i] == value)
                return static_cast<int>(i);
        }
        return -1;
    }

    bool ContainsElement(const T& value) const {
        return FindIndex(value) != -1;
    }

    void BuildReflexiveClosure() {
        for (size_t i = 0; i < elements.GetLength(); i++) {
            relation(i, i) = 1;
        }
    } 

public:
    PartialOrdering() : elements(), relation() {}

    explicit PartialOrdering(const MutableArraySequence<T>& input_elements) : elements(input_elements), relation(input_elements.GetLength(), 0) {
        BuildReflexiveClosure();
    }

    size_t GetSize() const {
        return elements.GetLength();
    }

    void AddElement(const T& value) {
        if (ContainsElement(value))
            return;
        
        size_t old_size = elements.GetLength();
        elements.Append(value);

        SquareMatrix<int> new_relation(old_size + 1, 0);

        for (size_t i = 0; i < old_size; i++) {
            for (size_t j = 0; j < old_size; j++) {
                new_relation(i, j) = relation(i, j);
            }
        }

        relation = new_relation;
        relation(old_size, old_size) = 1;
    }

    void AddPair(const T& first, const T& second) {
        if (!ContainsElement(first))
            AddElement(first);

        if (!ContainsElement(second))
            AddElement(second);
        
        int i = FindIndex(first);
        int j = FindIndex(second);

        relation(i, j) = 1;
    }

    bool IsLessOrEqual(const T& first, const T& second) const {
        int i = FindIndex(first);
        int j = FindIndex(second);

        if (i == -1 || j == -1)
            throw std::invalid_argument("Element not found");
        
        return relation(i, j) != 0;
    }

    void BuildTransitiveClosure() {
        size_t n = elements.GetLength();

        BuildReflexiveClosure();
        
        for (size_t k = 0; k < n; k++) {
            for (size_t i = 0; i < n; i++) {
                for (size_t j = 0; j < n; j++) {
                    if (relation(i, k) && relation(k, j)) {
                        relation(i, j) = 1;
                    }
                }
            }
        }
    }

    SquareMatrix<int> GetRelationMatrix() const {
        return relation;
    }

    const T& GetElement(size_t index) const {
        if (index >= elements.GetLength())
            throw std::out_of_range("Index out of range");
        
        return elements[index];
    }
};

#endif /* PARTIAL_ORDERING_HPP */
