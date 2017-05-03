/* This code implements a non-recursive solution to convert a binary
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
 */
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <string>
#include <vector>

using namespace std;

void Print(const std::vector<int> &v) {
    for (auto &i : v) printf("%d ", i);
    printf("\n");
}

struct TreeNode {
    int       val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {
    }
};

TreeNode *helper(TreeNode *curr, TreeNode *&prev, bool &foundHead) {
    if (!curr) {
        return NULL;
    }

    TreeNode *head = helper(curr->left, prev, foundHead);
    if (!foundHead && curr->left == NULL) {
        head      = curr;
        foundHead = true;
    }

    printf("prev:%d curr:%d\n", prev ? prev->val : -1, curr->val);
    curr->left            = prev;
    if (prev) prev->right = curr;
    prev                  = curr;

    helper(curr->right, prev, foundHead);

    return head;
}

TreeNode *TreeToList1(TreeNode *root) {
    bool      foundHead = false;
    TreeNode *prev      = NULL;
    return helper(root, prev, foundHead);
}

TreeNode *TreeToList(TreeNode *root) {
    stack<TreeNode *> stk;
    TreeNode *        curr = root;
    TreeNode *        prev = NULL;

    bool      foundHead = false;
    TreeNode *head      = NULL;

    while (!stk.empty() || curr != NULL) {
        if (curr) {
            stk.push(curr);
            curr = curr->left;
        } else {
            curr = stk.top();
            stk.pop();
            printf("%d\n", curr->val);

            curr->left            = prev;
            if (prev) prev->right = curr;

            if (!foundHead) {
                foundHead = true;
                head      = curr;
            }

            prev = curr;
            curr = curr->right;
        }
    }
    return head;
}

TreeNode** TreeToListRecursive(TreeNode *root) {
    TreeNode **ret = (TreeNode*)malloc(2*sizeof(TreeNode));
    ret[0] = ret[1] = NULL;

    if (root->left) {
        TreeNode** left = TreeToListRecursive(root->left);

    }

    if (root->right) {
        TreeNode** right = TreeToListRecursive(root->right);
    }
}

int main(int argc, char **argv) {
    TreeNode *root = new TreeNode(1);
    TreeNode *n2   = new TreeNode(2);
    TreeNode *n3   = new TreeNode(3);
    TreeNode *n4   = new TreeNode(4);
    TreeNode *n5   = new TreeNode(5);
    TreeNode *n6   = new TreeNode(6);
    TreeNode *n7   = new TreeNode(7);
    TreeNode *n8   = new TreeNode(8);
    TreeNode *n9   = new TreeNode(9);

    root->left  = n2;
    root->right = n9;
    n2->left    = n3;
    n2->right   = n6;
    n3->left = n4;
    n3->right = n5;
    n6->left=n7;
    n6->right=n8;

    TreeNode *head = TreeToList1(root);
    // forward
    printf("forward: ");
    TreeNode *tail = head;
    while (head) {
        printf("%d ", head->val);
        tail = head;
        head = head->right;
    }
    printf("\n");

    // backward
    printf("backward: ");
    while (tail) {
        printf("%d ", tail->val);
        tail = tail->left;
    }
    printf("\n");

    return 0;
}
