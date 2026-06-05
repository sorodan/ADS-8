// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <vector>
#include <utility>

template<typename T>
class BST {
 private:
    struct Node {
        T data;
        int count;
        Node* left;
        Node* right;
    };
    Node* root;

    Node* addNode(Node* root, T data) {
        if (root == nullptr) {
            root = new Node; root->data = data;
            root->left = nullptr;
            root->right = nullptr;
            root->count = 1;
        } else if (root->data > data) {
            root->left = addNode(root->left, data);
        } else if (root->data < data) {
            root->right = addNode(root->right, data);
        } else {
            root->count++;
        }
        return root;
    }

    Node* delNode(Node* root, T data) {
        if (root == nullptr) {
            return root;
        } else if (data < root->data) {
            root->left = delNode(root->left, data);
        } else if (data > root->data) {
            root->right = delNode(root->right, data);
        } else {
            Node* p = root;
            if (root->right == nullptr) {
                root = root->left;
            } else if (root->left == nullptr) {
                root = root->right;
            } else {
                Node* v = root->left;
                if (v->right != nullptr) {
                    while (v->right->right != nullptr)
                        v = v->right;
                    root->data = v->right->data;
                    root->count = v->right->count;
                    p = v->right;
                    v->right = v->right->left;
                } else {
                    root->data = v->data;
                    root->count = v->count;
                    p = v;
                    root->left = root->left->left;
                }
            }
            delete p;
        }
        return root;
    }

    void delTree(Node* root) {
        if (root == nullptr)
            return;
        delTree(root->right);
        delTree(root->left);
        delete root;
    }

    int countNodesTree(Node* root) {
        if (root == nullptr)
            return 0;
        else
            return countNodes(root->left) + countNodes(root->right) + 1;
    }

    int depthTree(Node* root) {
        if (root == nullptr)
            return -1;
        int right = depthTree(root->right);
        int left = depthTree(root->left);
        if (right >= left)
            return right + 1;
        else
            return left + 1;
    }

    int searchTree(Node* root, T data) {
        if (root == nullptr)
            return 0;
        else if (data > root->data)
            return searchTree(root->right, data);
        else if (data < root->data)
            return searchTree(root->left, data);
        else
            return root->count;
    }

    void getDataNodes(Node* root, std::vector<std::pair<int, T>>& array) const {
        if (root) {
            getDataNodes(root->left, array);
            array.push_back(std::make_pair(root->count, root->data));
            getDataNodes(root->right, array);
        }
    }

 public:
    BST() : root(nullptr) {}
    ~BST() {
        delTree(root);
    }

    void del(const T& data) {
        root = delNode(root, data);
    }

    void add(const T& data) {
        root = addNode(root, data);
    }

    int depth() {
        return depthTree(root);
    }

    int search(T data) {
        return searchTree(root, data);
    }

    int countNodes() {
        return countNodesTree(root);
    }

    std::vector<std::pair<int, T>> getData() const {
        std::vector<std::pair<int, T>> result;
        getDataNodes(root, result);
        return result;
    }
};
#endif  // INCLUDE_BST_H_
