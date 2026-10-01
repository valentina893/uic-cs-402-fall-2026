
#ifndef FIRSTNAME_LASTNAME_PROJECT3
#define FIRSTNAME_LASTNAME_PROJECT3

#include <vector>
#include <string>

using namespace std;

// Struct for tree in first-child, next-sibling representation
struct TreeNode {
    int id;
    TreeNode* first_child;
    TreeNode* next_sibling;
};

const static char AND = '^';
const static char OR = '|';
const static char NOT = '~';


struct ParseTreeNode {
    char val; // AND, OR, NOT, or some other char not in this set
    ParseTreeNode* left_child;
    ParseTreeNode* right_child;
};


// function delcarations
vector<int> weird_traversal(TreeNode* root);
TreeNode* bits_to_tree(const vector<bool>& bits);

// helpers

// returns the precedence of a token
int prec(const char& c);

#endif


