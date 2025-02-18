// DON’T CHANGE THE EXISTING FUNCTION SIGNATURES
// IF YOU NEED, YOU CAN ADD NEW FUNCTIONS TO SpecialBinaryTree CLASS
#ifndef SPECIAL_BINARY_TREE_H
#define SPECIAL_BINARY_TREE_H
class BinaryTreeNode; // This is called a "forward decleration"
class SpecialBinaryTree
{
private:
    BinaryTreeNode *root;

public:
    SpecialBinaryTree();
    ~SpecialBinaryTree();
    bool add_node(int new_value, int parent_value, bool is_left_child, bool is_right_child, bool is_root);
    bool update_value(int previous_value, int new_value);
    bool remove_node(int value);
    int is_leaf_node(int value);
    bool does_exist_in_subtree(int subtree_root_value, int value_to_search);
    int find_depth(int value);
    int find_height(int value);
    void preorder_traversal();
    void postorder_traversal();
    void inorder_traversal();
    int find_sum_of_values_in_subtree(int subtree_root_val);
    int find_minimum_value_in_subtree(int subtree_root_val);
    int find_maximum_value_in_subtree(int subtree_root_val);
    BinaryTreeNode* find_node(BinaryTreeNode *root, int value);
    BinaryTreeNode* recursive_removal(BinaryTreeNode* node, int value);
    void recursive_preorder_traversal(BinaryTreeNode* node);
    void recursive_postorder_traversal(BinaryTreeNode* node);
    void recursive_inorder_traversal(BinaryTreeNode* node);
    int recursive_find_depth(BinaryTreeNode* node, int value, int depth);
    int recursive_find_height(BinaryTreeNode* node);
    int recursive_find_sum_of_values_in_subtree(BinaryTreeNode* node);
    int recursive_find_minimum_value_in_subtree(BinaryTreeNode* node);
    int recursive_find_maximum_value_in_subtree(BinaryTreeNode* node);
};
#endif
