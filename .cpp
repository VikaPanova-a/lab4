#include <iostream>
template <class T>
class Tree {
public:
    struct Node {
        Node* Left;
        Node* Right;
        Node* Parent;
        T Value;
        Node(const T& val) : Left(nullptr), Right(nullptr), Parent(nullptr), Value(val) {}
    };
    Node* Root;
    Tree() : Root(nullptr) {}
    ~Tree() {
        Clear(Root);
    }
    void PreOrderWalk(Node* node) {
        if (node != nullptr) {
            std::cout << node->Value << " ";
            PreOrderWalk(node->Left);
            PreOrderWalk(node->Right);
        }
    }
    void Add(const T& val) {
        Node* newNode = new Node(val);
        Node* y = nullptr;
        Node* x = Root;
        while (x != nullptr) {
            y = x;
            if (val < x->Value) {
                x = x->Left;
            }
            else {
                x = x->Right;
            }
        }
        newNode->Parent = y;
        if (y == nullptr) {
            Root = newNode;
        }
        else if (val < y->Value) {
            y->Left = newNode;
        }
        else {
            y->Right = newNode;
        }
    }
    Node* Find(const T& val) {
        return TreeSearch(Root, val);
    }
    Node* FindMin(Node* node) {
        while (node && node->Left != nullptr) {
            node = node->Left;
        }
        return node;
    }
    Node* FindMax(Node* node) {
        while (node && node->Right != nullptr) {
            node = node->Right;
        }
        return node;
    }
    Node* Successor(Node* node) {
        if (node->Right != nullptr) {
            return FindMin(node->Right);
        }
        Node* y = node->Parent;
        while (y != nullptr && node == y->Right) {
            node = y;
            y = y->Parent;
        }
        return y;
    }
    Node* Predecessor(Node* node) {
        if (node->Left != nullptr) {
            return FindMax(node->Left);
        }
        Node* y = node->Parent;
        while (y != nullptr && node == y->Left) {
            node = y;
            y = y->Parent;
        }
        return y;
    }
    void Remove(Node* node) {
        if (node == nullptr) return;

        if (node->Left == nullptr) {
            Transplant(node, node->Right);
        }
        else if (node->Right == nullptr) {
            Transplant(node, node->Left);
        }
        else {
            Node* y = FindMin(node->Right);
            if (y->Parent != node) {
                Transplant(y, y->Right);
                y->Right = node->Right;
                if (y->Right) y->Right->Parent = y;
            }
            Transplant(node, y);
            y->Left = node->Left;
            if (y->Left) y->Left->Parent = y;
        }
        delete node;
    }
    T Median() {
        int total = CountNodes(Root);
        if (total % 2 == 0) {
            throw std::runtime_error("Число узлов должно быть нечетным");
        }
        int target = total / 2;
        int count = 0;
        Node* result = nullptr;
        FindMedian(Root, count, target, result);
        if (result) return result->Value;
        throw std::runtime_error("Медиана не найдена");
    }
private:
    int CountNodes(Node* node) {
        if (node == nullptr) return 0;
        return 1 + CountNodes(node->Left) + CountNodes(node->Right);
    }
    void FindMedian(Node* node, int& count, int target, Node*& result) {
        if (node == nullptr || result != nullptr) return;
        FindMedian(node->Left, count, target, result);
        if (count == target) {
            result = node;
            return;
        }
        count++;
        FindMedian(node->Right, count, target, result);
    }
    void Transplant(Node* u, Node* v) {
        if (u->Parent == nullptr) {
            Root = v;
        }
        else if (u == u->Parent->Left) {
            u->Parent->Left = v;
        }
        else {
            u->Parent->Right = v;
        }
        if (v != nullptr) {
            v->Parent = u->Parent;
        }
    }
    void Clear(Node* node) {
        if (node != nullptr) {
            Clear(node->Left);
            Clear(node->Right);
            delete node;
        }
    }
    Node* TreeSearch(Node* node, const T& val) {
        if (node == nullptr || val == node->Value) {
            return node;
        }
        if (val < node->Value) {
            return TreeSearch(node->Left, val);
        }
        else {
            return TreeSearch(node->Right, val);
        }
    }
};