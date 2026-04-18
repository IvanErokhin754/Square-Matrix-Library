#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>


template<typename T>

class LinkedList{
private:
    struct Node {
        T data;
        Node *next;
        Node (const T &value) : data(value), next(nullptr) {}
    };

    void Clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    Node *head;
    Node *tail;
    size_t size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    LinkedList(const LinkedList &other) : head(nullptr), tail(nullptr), size(0) {
        Node *ptr = other.head;
        while (ptr != nullptr) {
            Append(ptr->data);
            ptr = ptr->next;
        }
    }
    ~LinkedList() {
        Clear();
    }
    
   
    class Iterator {
        private:
            Node* current;
        public:
            Iterator(Node* node) : current(node) {}

            T& operator*() const {
                return current->data;
            }

            Iterator& operator++() {
                if (current != nullptr)
                    current = current->next;
                return *this;
            }
            
            bool operator!=(const Iterator& other) const {
                return current != other.current;
            }

            bool operator==(const Iterator& other) const {
                return current == other.current;
            }

    };

    class ConstIterator {
        private:
            const Node* current;
        public:
            ConstIterator(const Node* node) : current(node) {}

            const T& operator*() const {
                return current->data;
            }

            ConstIterator& operator++() {
                if (current != nullptr)
                    current = current->next;
                return *this;
            }

            bool operator==(const ConstIterator& other) const {
                return current == other.current;
            }
            
            bool operator!=(const ConstIterator& other) const {
                return current != other.current;
            }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    ConstIterator begin() const {
        return ConstIterator(head);
    }

    ConstIterator end() const {
        return ConstIterator(nullptr);
    }

    LinkedList &operator=(const LinkedList &other) {
        if (this == &other)
            return *this;
        
        Clear();

        Node *ptr_other = other.head;
        while (ptr_other != nullptr) {
            Append(ptr_other->data);
            ptr_other = ptr_other->next;
        }
        
        return *this;
    }
    
    size_t GetSize() const {
        return size;
    }

    const T& GetFirst() const {
        if (size == 0)
            throw std::out_of_range("List is empty");
        return head->data;
    }

    const T& GetLast() const {
        if (size == 0)
            throw std::out_of_range("List is empty");
        return tail->data;
    }

    void Append(const T &value) {
        Node *new_node = new Node(value);
        if (!head)
            head = tail = new_node;
        else {
            tail->next = new_node;
            tail = new_node;
        }
        size++;
    }

    void Prepend(const T &value) {
        Node *new_node = new Node(value);

        new_node->next = head;
        head = new_node;
        
        if (size == 0)
            tail = new_node;
        size++;
    }

    T& GetElement(size_t index) {
        if (index >= size) 
            throw std::out_of_range("Index larger than size");
        
        Node *ptr = head;

        for (size_t i = 0; i < index; i++) {
            ptr = ptr->next;
        }   

        return ptr->data;
    }

    const T& GetElement(size_t index) const {
        if (index >= size) 
            throw std::out_of_range("Index larger than size");
        
        const Node *ptr = head;

        for (size_t i = 0; i < index; i++){
            ptr = ptr->next;
        }
        
        return ptr->data;
    }

    void SetElement(size_t index, const T &value) {
        if (index >= size)
            throw std::out_of_range("Index larger than size");
        
        Node *ptr = head;

        for (size_t i = 0; i < index; i++){
            ptr = ptr->next;
        }

        ptr->data = value;
    } 

    void InsertAt(size_t index, const T &value) {
        if (index > size)
            throw std::out_of_range("Index larger than size");
        
        if (index == size) {
            Append(value);
            return;
        }

        if (index == 0){
            Prepend(value);
            return;
        }   

        Node *ptr = head;
        for (size_t i = 0; i < index - 1; i++){
            ptr = ptr->next;
        }

        Node *insert_element = new Node(value);
        insert_element->next = ptr->next;
        ptr->next = insert_element;

        size++;
    }

    void RemoveAt(size_t index) {
        if (index >= size)
            throw std::out_of_range("Index larger than size");

        if (index == 0) {
            Node *ptr = head;
            head = head->next;
            delete ptr;
            size--;

            if (size == 0)
                tail = nullptr;

            return;
        }

        Node *prev = head;
        for (size_t i = 0; i < index - 1; i++) {
            prev = prev->next;
        }

        Node *delete_me = prev->next;
        prev->next = delete_me->next;

        if (delete_me == tail)
            tail = prev;

        delete delete_me;
        size--;
    }

};

#endif /* LINKED_LIST_HPP */
