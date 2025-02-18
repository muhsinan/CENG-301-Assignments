#include "SpecialBinaryTree.h"
#include "BinaryTreeNode.h"
#include <climits>
#include <iostream>

using namespace std;

SpecialBinaryTree::SpecialBinaryTree() : root(nullptr) {}

SpecialBinaryTree::~SpecialBinaryTree()
{
}

bool SpecialBinaryTree::add_node(int new_value, int parent_value, bool is_left_child, bool is_right_child, bool is_root)
{
    if (find_node(root, new_value) != nullptr)
    {
        return false;
    }

    BinaryTreeNode *parent_node = find_node(root, parent_value);
    if (parent_node == nullptr && !is_root)
    {
        return false;
    }

    if (is_left_child && parent_node && parent_node->get_left() != nullptr)
    {
        return false;
    }
    if (is_right_child && parent_node && parent_node->get_right() != nullptr)
    {
        return false;
    }

    if (is_root && root != nullptr)
    {
        return false;
    }

    BinaryTreeNode *new_node = new BinaryTreeNode();
    new_node->set_value(new_value);

    if (is_root)
    {
        root = new_node;
    }
    else if (is_left_child)
    {
        parent_node->set_left(new_node);
    }
    else
    {
        parent_node->set_right(new_node);
    }

    return true;
}

bool SpecialBinaryTree::update_value(int previous_value, int new_value)
{
    BinaryTreeNode *node_to_change = find_node(root, previous_value);

    if (node_to_change == nullptr)
    {
        return false;
    }

    if (find_node(root, new_value) != nullptr)
    {
        return false;
    }

    node_to_change->set_value(new_value);

    return true;
}

bool SpecialBinaryTree::remove_node(int value)
{
    BinaryTreeNode *node = find_node(root, value);
    if (node == nullptr)
    {
        return false;
    }
    root = recursive_removal(root, value);
    return true;
}

BinaryTreeNode *SpecialBinaryTree::recursive_removal(BinaryTreeNode *node, int value)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node->get_value() == value)
    {
        if (node->get_left() == nullptr && node->get_right() == nullptr)
        {
            delete node;
            return nullptr;
        }
        if (node->get_left() != nullptr)
        {
            node->set_value(node->get_left()->get_value());
            node->set_left(recursive_removal(node->get_left(), node->get_value()));
        }
        else
        {
            node->set_value(node->get_right()->get_value());
            node->set_right(recursive_removal(node->get_right(), node->get_value()));
        }
    }
    else
    {
        node->set_left(recursive_removal(node->get_left(), value));
        node->set_right(recursive_removal(node->get_right(), value));
    }
    return node;
}

int SpecialBinaryTree::is_leaf_node(int value)
{
    BinaryTreeNode *node = find_node(root, value);

    if (node == nullptr)
    {
        return -1;
    }

    if (node->get_left() == nullptr && node->get_right() == nullptr)
    {
        return 1;
    }

    return 0;
}

bool SpecialBinaryTree::does_exist_in_subtree(int subtree_root_value, int value_to_search)
{
    BinaryTreeNode *subtree_root = find_node(root, subtree_root_value);

    if (subtree_root == nullptr)
    {
        return false;
    }

    if (subtree_root->get_value() == value_to_search)
    {
        return true;
    }

    bool left = false;
    if (subtree_root->get_left() != nullptr)
    {
        left = does_exist_in_subtree(subtree_root->get_left()->get_value(), value_to_search);
    }

    if (left)
    {
        return true;
    }

    bool right = false;
    if (subtree_root->get_right() != nullptr)
    {
        right = does_exist_in_subtree(subtree_root->get_right()->get_value(), value_to_search);
    }

    if (right)
    {
        return true;
    }

    return false;
}

int SpecialBinaryTree::find_depth(int value)
{
    return recursive_find_depth(root, value, 0);
}

int SpecialBinaryTree::recursive_find_depth(BinaryTreeNode *node, int value, int depth)
{
    if (node == nullptr)
    {
        return -1;
    }

    if (node->get_value() == value)
    {
        return depth;
    }

    int left = recursive_find_depth(node->get_left(), value, depth + 1);
    int right = recursive_find_depth(node->get_right(), value, depth + 1);

    if (left == -1 && right == -1)
    {
        return -1;
    }

    if (left == -1)
    {
        return right;
    }

    return left;
}

int SpecialBinaryTree::find_height(int value)
{
    BinaryTreeNode *node = find_node(root, value);
    return recursive_find_height(node);
}

int SpecialBinaryTree::recursive_find_height(BinaryTreeNode *node)
{
    if (node == nullptr)
    {
        return -1;
    }

    int left = recursive_find_height(node->get_left());
    int right = recursive_find_height(node->get_right());

    if (left > right)
    {
        return left + 1;
    }
    else
    {
        return right + 1;
    }
}

void SpecialBinaryTree::preorder_traversal()
{
    if (root == nullptr)
    {
        cout << "There is no node in the tree." << endl;
    }
    else
    {
        recursive_preorder_traversal(root);
        cout << endl;
    }
}

void SpecialBinaryTree::recursive_preorder_traversal(BinaryTreeNode *node)
{
    if (node != nullptr)
    {
        cout << node->get_value() << " ";
        recursive_preorder_traversal(node->get_left());
        recursive_preorder_traversal(node->get_right());
    }
}

void SpecialBinaryTree::postorder_traversal()
{
    if (root == nullptr)
    {
        cout << "There is no node in the tree." << endl;
    }
    else
    {
        recursive_postorder_traversal(root);
        cout << endl;
    }
}

void SpecialBinaryTree::recursive_postorder_traversal(BinaryTreeNode *node)
{
    if (node != nullptr)
    {
        recursive_postorder_traversal(node->get_left());
        recursive_postorder_traversal(node->get_right());
        cout << node->get_value() << " ";
    }
}

void SpecialBinaryTree::inorder_traversal()
{
    if (root == nullptr)
    {
        cout << "There is no node in the tree." << endl;
    }
    else
    {
        recursive_inorder_traversal(root);
        cout << endl;
    }
}

void SpecialBinaryTree::recursive_inorder_traversal(BinaryTreeNode *node)
{
    if (node != nullptr)
    {
        recursive_inorder_traversal(node->get_left());
        cout << node->get_value() << " ";
        recursive_inorder_traversal(node->get_right());
    }
}

int SpecialBinaryTree::find_sum_of_values_in_subtree(int subtree_root_val)
{
    BinaryTreeNode *node = find_node(root, subtree_root_val);
    if (node == nullptr)
    {
        return -1;
    }

    return recursive_find_sum_of_values_in_subtree(node);
}

int SpecialBinaryTree::recursive_find_sum_of_values_in_subtree(BinaryTreeNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }

    int left = recursive_find_sum_of_values_in_subtree(node->get_left());
    int right = recursive_find_sum_of_values_in_subtree(node->get_right());

    return node->get_value() + left + right;
}

int SpecialBinaryTree::find_minimum_value_in_subtree(int subtree_root_val)
{
    BinaryTreeNode *node = find_node(root, subtree_root_val);
    if (node == nullptr)
    {
        return -1;
    }

    return recursive_find_minimum_value_in_subtree(node);
}

int SpecialBinaryTree::recursive_find_minimum_value_in_subtree(BinaryTreeNode *node)
{
    if (node == nullptr)
    {
        return INT_MAX;
    }

    int left = recursive_find_minimum_value_in_subtree(node->get_left());
    int right = recursive_find_minimum_value_in_subtree(node->get_right());

    if (left < right && left < node->get_value())
    {
        return left;
    }
    else if (right < left && right < node->get_value())
    {
        return right;
    }
    else
    {
        return node->get_value();
    }
}

int SpecialBinaryTree::find_maximum_value_in_subtree(int subtree_root_val)
{
    BinaryTreeNode *node = find_node(root, subtree_root_val);
    if (node == nullptr)
    {
        return -1;
    }

    return recursive_find_maximum_value_in_subtree(node);
}

int SpecialBinaryTree::recursive_find_maximum_value_in_subtree(BinaryTreeNode *node)
{
    if (node == nullptr)
    {
        return INT_MIN;
    }

    int left = recursive_find_maximum_value_in_subtree(node->get_left());
    int right = recursive_find_maximum_value_in_subtree(node->get_right());

    if (left > right && left > node->get_value())
    {
        return left;
    }
    else if (right > left && right > node->get_value())
    {
        return right;
    }
    else
    {
        return node->get_value();
    }
}

BinaryTreeNode *SpecialBinaryTree::find_node(BinaryTreeNode *root, int value)
{
    BinaryTreeNode *tmp = root;
    if (tmp == nullptr)
    {
        return nullptr;
    }

    if (tmp->get_value() == value)
    {
        return tmp;
    }

    BinaryTreeNode *left = nullptr;
    if (tmp->get_left() != nullptr)
    {
        left = find_node(tmp->get_left(), value);
    }

    if (left != nullptr)
    {
        return left;
    }

    BinaryTreeNode *right = nullptr;
    if (tmp->get_right() != nullptr)
    {
        right = find_node(tmp->get_right(), value);
    }

    if (right != nullptr)
    {
        return right;
    }

    return nullptr;
}

/*
    IF YOU ADDED NEW FUNCTIONS TO SpecialBinaryTree.h IMPLEMENT THEM HERE.
    NOTE THAT, ADDING GLOBAL VARIABLES OR FUNCTIONS IS FORBIDDEN.
*/
