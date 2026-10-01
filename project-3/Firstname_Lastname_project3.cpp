
#include <vector>
#include <string>
#include <iostream>

// be sure to change FIRSTNAME and LASTNAME with your own first and last name
#include "Firstname_Lastname_project3.h"

using namespace std;

const string who_am_i() {
    return "Firstname_Lastname";
}


/****************
 * INSTRUCTIONS *
 ****************
 *
 * - Replace all instances of "Firstname_Lastname" with your firstname and
 *   your last name. This include the .h and .cpp files, along with the
 *   header guards at the top of the .h file.
 *
 * - Implement solutions to the problems described below.
 *   You must follow the specifications as written below.
 *
 * - Certain function signatures may not be modified (as it will affect auto
 *   grading). These functions will be specified.
 *
 * - You are allowed to add helper functions. Be sure to add the appropriate
 *   function prototypes in "Fistname_Lastname_project3.h."
 *
 * - If you are working in a group, please modify the comments directly below.
 *   
 * - IMPORTANT: If you are working in a group, every member is expected to submit their
 *   source code individually.
 *
 */


/*** GROUP PROJECT ***/
// Please list ALL of your other group members as comments below.
//   Member 1
//   Member 2


/* Problem 1: "Weird" Tree Traversal 
 *
 * 25 Points
 *
 * In this problem, you are asked to implement what I am calling "weird"
 * traversal on a tree.
 *
 * Definition: A weird traversal on an arbitrary rooted tree (i.e., a node can have
 * any number of children) proceeds as follows.
 *
 *   - First, the traversal visits all even layers in level-order, where we
 *     define the root to be layer 0, its children as layer 1, etc. "Level-
 *     order" here means visiting the nodes in layer i from left to right, 
 *     followed by nodes in layer i+2 from left to right (for even i). In
 *     other words, this traversal, starting from the root, visits all even
 *     layers in level-order (top to bottom, left to right).
 *
 *   - Once all even layers have been visited, all of the odd layers are then
 *     visited, bottom to top and right to left. In other words, this traversal
 *     visits the deepest odd layer first, from right most node to left most node,
 *     then proceeds back up, with the children of the root visited last.
 * 
 * Problem 
 *  - Given a pointer to the root of a Tree (specified as a TreeNode in
 *    the header file), output a vector of integers which represents the 
 *    weird-traversal of the tree.
 *
 * Grading
 *  - This problem is easily solvable using 2 traversals. This will only give
 *    you 15 points. To get full marks, you must solve this problem doing
 *    a single traversal of the tree.
 *      - Note this also means you cannot copy this tree into a different
 *        representation, as this would be at least 2 traversals to solve
 *        the problem (one to put the tree into a different format, then
 *        another traversal to perform weird-traversal).
 * 
 * Assumptions
 *  - Each node in the tree has a unique integer id. However, you cannot
 *    assume that the root is id 0, its first child has id 1, etc. The
 *    ids in the tree are only guaranteed to be unique.
 *  - The tree is in the first-child, next-sibling representation. That is,
 *    a node in a tree only has 2 pointers: one to its first (i.e., left-
 *    most) child, and one to its first (i.e., right) sibling.
 *
 * Examples
 *  - Tree in first-child, next-sibling representation. Consider the following
 *    tree:
 *       0
 *     / | \
 *    1  2  3
 *      /    \
 *     4      5
 *   / | \   /||\
 *  6  7 8  9 ab c
 *
 *    The first-child, next-sibling representation turns this tree into an equivalent
 *    binary tree, where a left branch is the first child in the above tree, and a
 *    right branch is the next sibling in the above tree:
 *               0
 *             /
 *           1
 *             \
 *             [  2  ]
 *            /      \
 *           4       3
 *          /       /
 *         6       5
 *          \     /
 *           7   9
 *            \   \
 *             8   a
 *                  \
 *                   b
 *                    \
 *                     c
 *
 * - Weird-traversal of above tree, given pointer to root labeled "a":
 *   [0, 4, 5, c, b, a, 9, 8, 7, 6, 3, 2, 1]
 *
 * - Other weird-traversal examples
 *    (a)    1   -> [1, 3, 2]
 *         /  \
 *        2    3
 *
 *    (b) -1    -> [-1, 3, 6, -9, 7, 2]
 *        / \
 *      2    7
 *       \  / \
 *       3 6  -9
 */

// Do not modify this function signature.
vector<int> weird_traversal(TreeNode* root) {
    // Your code here!
}



/* Problem 2: Bits-to-Tree 
 *
 * 25 Points
 *
 * In this problem, you are given a vector of bits which represents 
 * a DFS traversal of a tree with the following properties:
 *  1. Non-empty: the tree always has at least 1 node (the root).
 *  2. Unlabeled: the nodes in the tree are not labeled.
 *  3. Ordered: the children of each noded are ordered from left to right.
 *
 * Your goal is to reconstruct the tree given the vector of bits, using
 * the TreeNode struct. The bits in the vector correspond to a DFS
 * traversal in the following way:
 *  - A '1' represents a "down" traversal; and
 *  - A '0' represents a "up" traversal.
 * Moreover, this DFS traversal visits each child in left-to-right order.
 *
 * Helpful Properties of this Problem
 *  - For a tree with n nodes, the input "bits" is valid if and only if
 *      - bits has exactly n-1 1's and n-1 0's;
 *      - bits has even length (i.e., = 2(n-1)); and
 *      - For any prefix of bits (i.e., bits[0,..,i]), #0s <= #1s
 *
 * Other Considerations
 *  - The tree is guaranteed to be non-empty. What type of input would lead
 *    to a tree that is a single root node?
 *  - Defining a helper function for this problem could be useful.
 *
 * Grading
 *  - The returned pointer must be the root of the tree you have reconstructed,
 *    or the nullptr if 'bits' is not a valid encoding.
 *  - Additionally, label each node from 0 to n-1, where the ID of the node
 *    corresponds to its ordering during the pre-order DFS traversal.
 *  - Using your own TreeNode type which represents a tree in a format other
 *    than specified to construct your solution will only yield 15 points. For
 *    full marks, directly construct your tree using the TreeNode struct.
 * 
 * Examples
 *  - [1, 0] ->  0
 *              /
 *             1
 *
 *  - [1, 0, 1, 0, 1, 1, 0, 1, 0, 0]
 *      -> (in a format where each node has a vector of children)
 *                0
 *              / | \
 *             1  2   3
 *                   | \
 *                   4  5
 *      -> (in the required first-child, next sibling format)
 *               0
 *              /
 *             1
 *             \
 *              2
 *               \
 *                3
 *               /
 *              4
 *               \
 *                5
 */

// Do not modify this fuction signature
TreeNode* bits_to_tree(const vector<bool>& bits) {
}


/* Problem 3: Build a Parse Tree
*
* 25 Points
*
* In this problem, you are asked to build a parse tree
* which represents a Boolean expression you are given 
* as input as a string.
*
* Your goal is that given a string that represents a
* Boolean expression, build a tree that represents 
* evaluating this expression.
*
* Input:
*   - A string expr which represents the Boolean expression
*     you must parse. There are 5 special characters that
*     can appear in these strings:
*       - '^', which represents && (Boolean and),
*       - '|', which represents || (Boolean or),
*       - '~', which represents Boolean not,
*       - '(' and ')', which open and close parentheses
*    In the header file, for the first 3 characters, I have
*    specified 3 const static char variables you can use to help.
*    Other than these 5 characters, the string may contain a-z and
*    A-Z. No other characters will appear in the strings given
*    as input.
* 
* Output:
*   - A pointer to a ParseTreeNode which represents the parse tree
*     of the given string.
*
* More Details:
*   You are expected to build the tree so that a preorder
*     traversal of the tree results in the correct evaluation
*     of the given Boolean expression. This means that the following
*     rules must be followed:
*     1. Expressions are evaluated from left to right
*     1. Anything in parentheses gets evaluated first, before operators
*       outside of the parenthesis
*     2. any NOT gets evaluated next
*     3. any AND or OR gets evaluated next (they have the same precidence)
*   In the case of multiple of the same operater in a row, it gets
*     processed from left to right. 
*   Note that the ParseTreeNode struct always has two children; in the
*     case of a NOT node, you must always leave the right child null.
*
*   Some examples are given below.
*   - Example 1: c | (a ^ b) 
*     Following the rules of Boolean logic, you would evaluate
*     (a ^ b) first, followed by the result of this with v c.
*     This gives the following parse tree:
*
*                    |
*                 /    \
*                c     ^
*                    /  \  
*                   a    b
*
*  - Example 2: a | b ^ c
*    Since all of these operators have the same precidence, we would 
*    evaluate in order from left to right. This gives the following tree
*
*
*                    ^
*                 /    \
*                |      c
*              /  \  
*             a    b
*
*  - Example 3: ~(A ^ b) ^ (c | ~z)
*
*               ^
*           /       \
*          ~         |
*         /        /  \
*        ^        c    ~
*      /  \           /
*     A    b         z
*
* - Example 4: ~(A ^ (c | ~(d ^ e) ^ F) | ~z)
*
*                ~
*               /
*              |
*           /     \
*          ^       ~
*       /   \     /
*      A     ^   z
*           / \
*          |  F
*        /  \
*       c    ~
*           /
*          ^
*         / \
*        d  e
*
*
* Note that in the given strings, there will be no spaces (the whitespace
*   above is to help you see the expressions clearly)
*
*/

// Do not modify this function signature
ParseTreeNode* build_parse_tree(const string& expr) {
    // convert the infix expression to a postfix expression
    stack<char> s;
    string postfix;
    for (int i = 0; i < expr.size(); i++) {
        char c = expr.at(i);
        switch (c) {
            case '^': // and
            case '|': // or
            case '~': // not
                handle_operator(s, postfix, c);
                break;
            case '(': // left parentheses
                s.push(c);
                break;
            case ')': // right parentheses
                break;
            default: // operand
                postfix += c;
                break;
        }
    }
    return NULL;
}

int prec(const char& c) {
    switch (c) {
        case '^':
        case '|': return 1;
        case '~': return 2;
        case '(':
        case ')': return 3;
        default: return 0;
    }
}

void handle_operator(stack<char>& s, string& postfix, char& c) {
    // pop operators from the stack until empty, left parentheses is found, 
    // or token with precedence < than c is found.
    while (s.size() > 0 && s.top() != '(' &&
        prec(s.top()) >= prec(c) 
    ) {
        postfix += s.top();
        s.pop();
    }
    // push c to stack
    s.push(c);
}

int main() {

    return 0;
}
