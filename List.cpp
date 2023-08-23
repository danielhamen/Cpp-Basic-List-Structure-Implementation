#include <iostream>

template <typename T>
struct List {
    struct Node {
        T value;
        Node* next;
        Node(const T& val) : value(val), next(nullptr) {}
    };

    Node* head;

    List() : head(nullptr) {}

    void append(const T& x) {
        Node* newNode = new Node(x);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    template <typename Iterable>
    void extend(const Iterable& iterable) {
        for (const T& item : iterable) {
            append(item);
        }
    }

    void insert(size_t i, const T& x) {
        if (i == 0) {
            Node* newNode = new Node(x);
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            size_t pos = 0;
            while (current && pos < i - 1) {
                current = current->next;
                ++pos;
            }
            if (current) {
                Node* newNode = new Node(x);
                newNode->next = current->next;
                current->next = newNode;
            }
        }
    }

    void remove(const T& x) {
        if (!head) {
            return;
        }
        if (head->value == x) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* current = head;
        while (current->next && current->next->value != x) {
            current = current->next;
        }
        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    T pop(int i = -1) {
        if (!head) {
            // Return a default value if the list is empty (customize as needed)
            return T();
        }
        if (i == 0 || i == -1) {
            Node* temp = head;
            T value = temp->value;
            head = head->next;
            delete temp;
            return value;
        }
        Node* current = head;
        size_t pos = 0;
        while (current && pos < i - 1) {
            current = current->next;
            ++pos;
        }
        if (current && current->next) {
            Node* temp = current->next;
            T value = temp->value;
            current->next = current->next->next;
            delete temp;
            return value;
        }
        // Return a default value if the index is out of bounds (customize as needed)
        return T();
    }

    size_t index(const T& x) const {
        Node* current = head;
        size_t pos = 0;
        while (current) {
            if (current->value == x) {
                return pos;
            }
            current = current->next;
            ++pos;
        }
        // Return a value indicating not found (customize as needed)
        return static_cast<size_t>(-1);
    }

    size_t count(const T& x) const {
        size_t count = 0;
        Node* current = head;
        while (current) {
            if (current->value == x) {
                ++count;
            }
            current = current->next;
        }
        return count;
    }

    void sort() {
        if (!head) {
            return;
        }
        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            while (current->next) {
                if (current->value > current->next->value) {
                    T temp = current->value;
                    current->value = current->next->value;
                    current->next->value = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

    void reverse() {
        if (!head || !head->next) {
            return;
        }
        Node* prev = nullptr;
        Node* current = head;
        Node* nextNode = nullptr;
        while (current) {
            nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        head = prev;
    }

    List<T> copy() const {
        List<T> copyList;
        Node* current = head;
        while (current) {
            copyList.append(current->value);
            current = current->next;
        }
        return copyList;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    ~List() {
        clear();
    }
};
