struct Node {
    int key, val, h;
    Node *left, *right;

    Node(int k, int v) {
        key = k;
        val = v;
        h = 1;
        left = NULL;
        right = NULL;
    }
};

struct AVL {
    Node *bst = NULL;

    int getHeight(Node *root) {
        return root ? root->h : 0;
    }

    int getBalance(Node *root) {
        if (!root) return 0;
        return getHeight(root->left) - getHeight(root->right);
    }

    void updateHeight(Node *root) {
        root->h = 1 + max(getHeight(root->left), getHeight(root->right));
    }

    Node* leftRotate(Node *root) {
        Node *new_root = root->right;
        root->right = new_root->left;
        new_root->left = root;
        updateHeight(root);
        updateHeight(new_root);
        return new_root;
    }

    Node* rightRotate(Node *root) {
        Node *new_root = root->left;
        root->left = new_root->right;
        new_root->right = root;
        updateHeight(root);
        updateHeight(new_root);
        return new_root;
    }

    Node* balance(Node *root){
        if (abs(getBalance(root)) > 1) {
            if (getBalance(root) < 0) { // node went to right subtree

                if (getBalance(root->right) < 0) { // R-R
                    root = leftRotate(root);
                } else {                          // R-L
                    root->right = rightRotate(root->right);
                    root = leftRotate(root);
                }

            } else { // node went to left subtree

                if (getBalance(root->left) < 0) { // L-R
                    root->left = leftRotate(root->left);
                    root = rightRotate(root);
                } else {                          // L-L
                    root = rightRotate(root);
                }

            }
        }

        return root;
    }

    Node* insert(Node *root, int k, int v) {
        if (!root) {
            return new Node(k, v);
        }

        if (root->key == k) {
            root->val = v;
        } else if (root->key > k){
            root->left = insert(root->left, k, v);
        } else {
            root->right = insert(root->right, k, v);
        }
        // need to balance after insertion
        root = balance(root);
        updateHeight(root);

        return root;
    }

    // returns pointer to the target node
    Node* search(Node *root, int k) {
        if (!root) return 0;

        if (root->key == k) return root;
        else if (root->key < k) return search(root->right, k);
        else return search(root->left, k);
        
    }

    void insert(int k, int v) {
        bst = insert(bst, k, v);
    }

    int search(int k) {
        return search(bst, k)->val;
    }
};