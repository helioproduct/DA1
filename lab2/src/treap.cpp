#include <iostream>
#include <cstring>
#include <cstdint>

const int MAX_KEY_LEN = 257;

struct node {
    char *key;
    int priority;
    uint64_t value;
    node *left, *right;
};

node* newNode(char *key, uint64_t value) {
    node* temp = new node;
    temp->key = new char[MAX_KEY_LEN];
    memcpy(temp->key, key, MAX_KEY_LEN);
    temp->value = value;
    temp->priority = rand();
    temp->left = temp->right = nullptr;
    return temp;
}

void destroy(node *node) {
    if (node != nullptr) {
        delete[] node->key;
        destroy(node->left);
        destroy(node->right);
    }
}


void split(node* root, node*& left, node*& right, char *key) {
    if (root == nullptr) {
        left = right = nullptr;
        return;
    }
    if (strcmp(root->key, key) <= 0) {
        left = root;
        split(root->right, left->right, right, key);
    } else {
        right = root;
        split(root->left, left, right->left, key);
    }
}

node* merge(node* left, node* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

void insert(node*& root, node* item) {
    if (root == nullptr) {
        root = item;
        return;
    }
    if (item->priority > root->priority) {
        split(root, item->left, item->right, item->key);
        root = item;
    } else {
        if (strcmp(item->key, root->key) < 0)
            insert(root->left, item);
        else
            insert(root->right, item);
    }
}

void remove(node*& root, char *key) {
    if (root == nullptr)
        return;

    if (strcmp(root->key,key)==0) {
        node* temp = merge(root->left, root->right);
        delete (root);
        root = temp;
        return;
    }

    if (strcmp(root->key,key)>0)
        remove(root->left,key);
    else
        remove(root->right,key);
}

node *search(node *root, char *key) {
    if (root == nullptr) {
        return nullptr;
    }
    else if (strcmp(root->key, key) == 0) {
        return root;
    }
    else if (strcmp(root->key, key) > 0) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

void toLower(char *str) {
    // Loop through each character in the string
    for (int i = 0; i < strlen(str); i++) {
        // Use the tolower standard function to convert the character to lowercase
        str[i] = tolower(str[i]);
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    srand(time(nullptr));
    node* root = nullptr;

    char *command = new char[MAX_KEY_LEN];
    char *key = new char[MAX_KEY_LEN];
    uint64_t value;

    while (std::cin >> command) {

        if (strcmp(command, "+") == 0) {
            std::cin >> key >> value;
            toLower(key);
            if (search(root, key)) {
                std::cout << "Exist" << "\n";
            } else {
                insert(root, newNode(key, value));
                std::cout << "OK" << "\n";
            }
        }
        else if (strcmp(command, "-") == 0) {
            std::cin >> key;
            toLower(key);
            if (search(root, key)) {
                remove(root, key);
                std::cout << "OK" << "\n";
            } else {
                std::cout << "NoSuchWord" << "\n";
            }
        }
        else {
            toLower(command);
            node *found_node = search(root, command);
            if (found_node) {
                std::cout << "OK: " << found_node->value << "\n";
            } else {
                std::cout << "NoSuchWord" << "\n";
            }
        }
    }
    destroy(root);
    delete[] command;
    delete[] key;
}
