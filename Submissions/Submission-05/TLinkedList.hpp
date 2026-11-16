#pragma once

struct SearchSummary {
    long long comparisons = 0;
    double timeSpentMs = 0;
};

template <typename T> struct TNode {
    T *data = nullptr;
    TNode *next = nullptr;
};

template <typename T> class TLinkedList {
    using Node = TNode<T>;
    using FCompare = bool (*)(T *context, void *key);

  public:
    /// Constructor determines if the list owns the underlying data it holds
    TLinkedList(bool isDataOwner) : m_head(new Node), m_isOwner(isDataOwner) {}
    ~TLinkedList() {
        Node *currentNode{m_head};
        while (currentNode != nullptr) {
            Node *nextNode = currentNode->next;
            if (m_isOwner)
                delete currentNode->data;
            delete currentNode;
            currentNode = nextNode;
        }
    }

    void Append(T *node) {
        Node *currentNode = m_head;
        while (true) {
            if (currentNode->next == nullptr) {
                currentNode->next = new Node(node);
                return;
            }
            currentNode = currentNode->next;
        }
    }
    void Prepend(T *node) {
        Node *newNode = new Node(node);
        newNode->next = m_head->next;
        m_head->next = newNode;
    }

    Node *GetAtIndex(unsigned int index) {
        Node *currentNode = m_head;
        for (unsigned int i = 0; i < index + 1; i++) {
            if (currentNode->next == nullptr)
                return nullptr;
            currentNode = currentNode->next;
        }
        return currentNode;
    }
    void Remove(unsigned int index) {
        Node *previousNode{}, *currentNode = m_head;
        for (unsigned int i = 0; i < index + 1; i++) {
            if (currentNode->next != nullptr) {
                previousNode = currentNode;
                currentNode = currentNode->next;
            }
        }
        if (previousNode != nullptr && currentNode != nullptr) {
            previousNode->next = currentNode->next;
            if (m_isOwner)
                delete currentNode->data;
            delete currentNode;
        }
    }
    void Reverse() {
        Node *previousNode{nullptr}, *nextNode{nullptr};

        for (T *currentNode = m_head->next; currentNode != nullptr;
             currentNode = nextNode) {
            nextNode = currentNode->next;
            currentNode->next = previousNode;
            previousNode = currentNode;
        }
        m_head->next = previousNode;
    }

    T *Find(FCompare compareFn, void *searchKey, SearchSummary &summary) {
        for (Node *node = m_head->next; node != nullptr; node = node->next) {
            summary.comparisons++;
            if (compareFn(node->data, searchKey)) {
                return node->data;
            }
        }
        return nullptr;
    }

    TLinkedList<T> *Every(FCompare compareFn, void *searchKey,
                          SearchSummary &summary) {
        // Construct a non-owning list to hold the reslts of the search.
        // The caller is responsible for deleting the returned list.
        TLinkedList<T> *subList = new TLinkedList<T>(false);
        for (Node *node = m_head->next; node != nullptr; node = node->next) {
            summary.comparisons++;
            if (compareFn(node->data, searchKey)) {
                subList->Append(node->data);
            }
        }
        return subList;
    }

  private:
    Node *m_head;
    bool m_isOwner;
};
