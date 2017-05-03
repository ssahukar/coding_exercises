/* This code implements a recursive solution to convert a binary
 * tree into a "circular (optional) doubly linked list" with the nodes
 * in the list appearing as per the "inorder" traversal of the tree.
 * Example:
 *   input tree:
 *          A
 *        /   \
 *       B     C
 *      / \   / \
 *     D   E F   G
 *
 *  output list:
 *  head-> D <-> B <-> E <-> A <-> F <-> C <-> G
 *
 *
 */
#include <stdio.h>
#include <assert.h>

typedef struct node {
    int v;
    struct node *left;
    struct node *right;
}Node ;

Node** convert_tree_to_list(Node *root) {
    Node **p = (Node**) malloc(2*sizeof(Node*));
    Node **lret;
    Node **rret;

    if (root->left == NULL)
        p[0] = root;
    else {
        lret = convert_tree_to_list(root->left);
        root->left = lret[1];
        lret[1]->right = root;
        p[0] = lret[0];
        free(lret);
    }

    if (root->right == NULL)
        p[1] = root;
    else {
        rret = convert_tree_to_list(root->right);
        root->right = rret[0];
        rret[0]->left = root;
        p[1] = rret[1];
        free(rret);
    }

    return p;
}

Node* tree_to_list(Node *root) {
    if (root == NULL)
        return NULL;

    Node **ret = convert_tree_to_list(root);
    //For a circular linked list, change this
    //to 
    //ret[0]->left = ret[1];
    //ret[1]->right = ret[0];

    ret[0]->left = NULL;
    ret[1]->right = NULL;
    return ret[0];
}

Node *getNode(int val, Node *l, Node *r) {
    Node *n = (Node*)malloc(sizeof(Node));
    assert(n!=NULL);
    n->left = l;
    n->right = r;
    n->v = val;
    return n;
}

Node *createTree() {
    Node *l5 = getNode(5, NULL, NULL);
    Node *l6 = getNode(6, NULL, NULL);
    Node *l7 = getNode(7, NULL, NULL);
    Node *l8 = getNode(8, NULL, NULL);
    Node *l3 = getNode(3, l5, l6);
    Node *l4 = getNode(4, l7, l8);
    Node *l2 = getNode(2, l3, l4);
    Node *l1 = getNode(1, l2, NULL);
    return l1;
}

Node *print_forward(Node *head) {
    Node *tail = head;
    while (head != NULL) {
        printf("%d ", head->v);
        tail = head;
        head=head->right;
    }
    printf("\n");
    return tail;
}

Node *print_reverse(Node *tail) {
    Node *head = tail;
    while (tail != NULL) {
        printf("%d ", tail->v);
        head = tail;
        tail=tail->left;
    }
    printf("\n");
    return head;
}

void inorder(Node *root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->v);
    inorder(root->right);
}

int main() {
    Node *root = createTree();
    inorder(root);
    printf("\n");

    Node *head = tree_to_list(root);

    Node *tail = print_forward(head);
    print_reverse(tail);
}
