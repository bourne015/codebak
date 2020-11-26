/*
 *Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

Note: A leaf is a node with no children.

Example:

Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
return its depth = 3.
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <stdio.h>
#include "../create.h"

int maxDepth(struct TreeNode* root) {
    static int sum = 0, max = 0;

    if (root) {
        sum += root->val;
        if (!root->left && !root->right) {
            printf("sum: %d\n", sum);
            if (sum > max)
                max = sum;
        }
        if (root->left)
            maxDepth(root->left);
        if (root->right)
            maxDepth(root->right);
        if (max == 0)
            max = sum;
        sum -= root->val;
    }
    return max;
}

int main(void)
{
    int a[] = {1,2,3,4,5,6,7,8,9};
    //int a[] = {3,-1,20};
    struct TreeNode *root;

    root = create_tree(a, sizeof(a)/sizeof(int));
    level_tree(root);

    printf("max route: %d\n", maxDepth(root));
}
