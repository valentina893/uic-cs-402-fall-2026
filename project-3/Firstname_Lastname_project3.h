
#ifndef FIRSTNAME_LASTNAME_PROJECT3
#define FIRSTNAME_LASTNAME_PROJECT3

#include <vector>
#include <stack>
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

// converts infix expression to postfix expression
string infix_to_postfix(const string& infix);

// returns the precedence of a token
int prec(const char& c);

/*
pops operators from stack and pushes to postfix until
the stack until empty, left parentheses is found, 
or token with precedence < than c is found.
*/
void handle_operator(stack<char>& s, string& postfix, char& c);

/*
pops operators from stack and pushes to postfix until
a left parentheses character is found.
*/
void find_left_parentheses(stack<char>& s, string& postfix);

#endif


