
#include <vector>
#include <string>
#include <iostream>

// other modules
#include <stack>

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
    vector<int> res;
    stack<int> s;
    if (root != NULL) {
        res.push_back(root->id);
        TreeNode* curr = root->first_child;
        // begin traversing levels
        while (curr != NULL) {
            // get all children on odd level
            TreeNode* odd = curr;
            while (odd != NULL) {
                s.push(odd->id);
                odd = odd->next_sibling;
            }
            // access even level
            curr = curr->first_child;
            // get all children on even level
            TreeNode* even = curr;
            while (even != NULL) {
                res.push_back(even->id);
                even = even->next_sibling;
            }
            // access odd level if possible
            if (curr != NULL) curr = curr->first_child;
        }
        while (s.empty() == false) {
            //cout << "collecting odd node: " << s.top() << endl;
            res.push_back(s.top());
            s.pop();
        }
    }
    return res;
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
    return NULL;
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
    string postfix = infix_to_postfix(expr);
    // convert to parse tree
    return build_tree_from_postfix(postfix);
}

ParseTreeNode* build_tree_from_postfix(const string& postfix) {
    stack<ParseTreeNode*> s;
    ParseTreeNode* right_child = NULL;
    ParseTreeNode* left_child = NULL;
    for (int i = 0; i < postfix.size(); i++) {
        char c = postfix.at(i);
        switch (c) {
            case '^': // and
            case '|': // or
                //ParseTreeNode* right_child = s.top();
                right_child = s.top();
                s.pop();
                //ParseTreeNode* left_child = s.top();
                left_child = s.top();
                s.pop();
                s.push(new ParseTreeNode(c, left_child, right_child));
                break;
            case '~': // not
                //ParseTreeNode* left_child = s.top();
                left_child = s.top();
                s.pop();
                s.push(new ParseTreeNode(c, left_child, NULL));
                break;
            default: // operand
                s.push(new ParseTreeNode(c, NULL, NULL));
                break;
        }
    }
    return s.top();
}

string infix_to_postfix(const string& infix) {
    // convert the infix expression to a postfix expression
    stack<char> s;
    string postfix;
    for (int i = 0; i < infix.size(); i++) {
        char c = infix.at(i);
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
                find_left_parentheses(s, postfix);
                break;
            case ' ': // white space
                break;
            default: // operand
                postfix += c;
                break;
        }
    }
    // pop all remaining operators from stack
    while (s.size() > 0) {
        postfix += s.top();
        s.pop();
    }
    return postfix;
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

void find_left_parentheses(stack<char>& s, string& postfix) {
    while (s.size() > 0 && s.top() != '(') {
        postfix += s.top();
        s.pop();
    }
    // finally pop left parentheses from stack
    s.pop();
}

bool test_weird_traversal() {

    string error;
    bool passed = true;

    // test empty tree
    vector<int> res0 = weird_traversal(NULL);
    if (res0.size() != 0) {
        passed = false;
        error += "\nfailed on empty tree\n";
    }

    // test tree with just root
    TreeNode* root = new TreeNode(0, NULL, NULL);

    vector<int> res1 = weird_traversal(root);
    if (res1.size() != 1) {
        passed = false;
        error += "\nfailed on tree with single node\n";
    } else if (res1.at(0) != root->id) {
        passed = false;
        error += "\nincorrect id collected from tree with single node\n";
    }

    // test full tree

    // first odd layer
    TreeNode* odd0 = new TreeNode(1, NULL, NULL);
    root->first_child = odd0;

    // first even layer
    TreeNode* even0 = new TreeNode(2, NULL, NULL);
    TreeNode* even1 = new TreeNode(4, NULL, NULL);
    TreeNode* even2 = new TreeNode(6, NULL, NULL);
    TreeNode* even3 = new TreeNode(8, NULL, NULL);
    odd0->first_child = even0;
    even0->next_sibling = even1;
    even1->next_sibling = even2;
    even2->next_sibling = even3;

    // second odd layer
    TreeNode* odd0_2 = new TreeNode(9, NULL, NULL);
    TreeNode* odd1_2 = new TreeNode(11, NULL, NULL);
    TreeNode* odd2_2 = new TreeNode(13, NULL, NULL);
    even0->first_child = odd0_2;
    odd0_2->next_sibling = odd1_2;
    odd1_2->next_sibling = odd2_2;

    // second even layer
    TreeNode* even0_2 = new TreeNode(10, NULL, NULL);
    TreeNode* even1_2 = new TreeNode(12, NULL, NULL);
    odd0_2->first_child = even0_2;
    even0_2->next_sibling = even1_2;

    // expected output of weird traversal for this tree
    vector<int> exp = {0, 2, 4, 6, 8, 10, 12, 13, 11, 9, 1};

    vector<int> res = weird_traversal(root);

    if (res.size() != exp.size()) {
        passed = false;
        error += "\nincorrect size\n";
        error += "expected: " + to_string(exp.size()) + "\n";
        error += "result: " + to_string(res.size()) + "\n";
        for (int i = 0; i < res.size(); i++) {
            error += to_string(res.at(i)) + " ";
        }
        error += "\n";
    }

    if (res.size() == exp.size()) {
        for (int i = 0; i < res.size(); i++) {
            if (res.at(i) != exp.at(i)) {
                passed = false;
                error += "\nincorrect element at position " + to_string(i) + "\n";
                error += "expected: " + to_string(exp.at(i)) + "\n";
                error += "result: " + to_string(res.at(i)) + "\n"; 
            }
        }
    }

    // copied code from prof. block's test case for weird_traversal()

    TreeNode* test = new TreeNode(
      0, 
      new TreeNode(1, nullptr, new TreeNode(2, new TreeNode(4, new TreeNode(6, nullptr,
        new TreeNode(7, nullptr, new TreeNode(8))
            ),
            nullptr
          ),
          new TreeNode(3,
            new TreeNode(5, new TreeNode(9, nullptr, new TreeNode(10, nullptr,
                  new TreeNode(11, nullptr, new TreeNode(12)))), nullptr), nullptr)
        )
      ),
      nullptr
    );

    std::vector<int> wd_trav = weird_traversal(test);

    const std::vector<int> wd_ans = {0, 4, 5, 12, 11, 10, 9, 8, 7, 6, 3, 2, 1};

    if(wd_trav == wd_ans) passed = false;

    if (!passed) {
        cout << "weird traversal errors:\n";
        cout << error;
    }

    return passed;

}

bool check_equal(TreeNode* t1, TreeNode* t2) {
    if(t1 == nullptr && t2 == nullptr) {
        return true;
    }
    if(t1 != nullptr && t2 == nullptr) {
        return false;
    }
    if(t1 == nullptr && t2 != nullptr) {
        return false;
    }
    if(t1->id != t2->id) { 
        return false;
    }
    return check_equal(t1->first_child, t2->first_child)
            && check_equal(t1->next_sibling, t2->next_sibling);
}

bool test_bits_to_tree() {
    string error;
    bool passed = true;

    // prof block's unit test
    const std::vector<bool> test1 = {1, 0};
    const std::vector<bool> test2 = {1, 0, 1, 0, 1, 1, 0, 1, 0, 0};

    TreeNode* ans1 = bits_to_tree(test1);
    TreeNode* ans2 = bits_to_tree(test2);

    TreeNode* sol1 = new TreeNode(0, new TreeNode(1), nullptr);
    TreeNode* sol2 = new TreeNode(0, 
        new TreeNode(1, nullptr,
            new TreeNode(2, nullptr,
                new TreeNode(3,
                    new TreeNode(4, nullptr, new TreeNode(5)), nullptr
          )
        )
      )
    , nullptr);

    double total_score = 2.0;
    double score = 0.0;

    if(check_equal(ans1, sol1)) ++score;
    if(check_equal(ans2, sol2)) ++score;

    int res = 100*(score / total_score);

    if (res != 100) {
        passed = false;
    }

    if (!passed) {
        cout << "test_bits_to_tree errors\n";
        cout << error;

    }

    return passed;
}

bool test_infix_to_postfix() {
    string test1 = "c | (a ^ b)";
    string test2 = "a | b ^ c";
    string test3 = "~(A ^ b) ^ (c | ~z)";
    string test4 = "~(A ^ (c | ~(d ^ e) ^ F) | ~z)";
    string test5 = "";

    string error;
    bool passed = true;

    string res1 = infix_to_postfix(test1);
    string exp1 = "cab^|";
    if (res1 != exp1) {
        passed = false;
        error += "test1 failed:\n";
        error += "input: " + test1 + "\n";
        error += "expected: " + exp1 + "\n";
        error += "result: " + res1 + "\n";
    }

    string res2 = infix_to_postfix(test2);
    string exp2 = "ab|c^";
    if (res2 != exp2) {
        passed = false;
        error += "test2 failed:\n";
        error += "input: " + test2 + "\n";
        error += "expected: " + exp2 + "\n";
        error += "result: " + res2 + "\n";
    }

    string res3 = infix_to_postfix(test3);
    string exp3 = "Ab^~cz~|^";
    if (res3 != exp3) {
        passed = false;
        error += "test3 failed:\n";
        error += "input: " + test3 + "\n";
        error += "expected: " + exp3 + "\n";
        error += "result: " + res3 + "\n";
    }

    string res4 = infix_to_postfix(test4);
    string exp4 = "Acde^F^~|z~|^~";
    if (res4 != exp4) {
        passed = false;
        error += "test4 failed:\n";
        error += "input: " + test4 + "\n";
        error += "expected: " + exp4 + "\n";
        error += "result: " + res4 + "\n";
    }

    string res5 = infix_to_postfix(test5);
    string exp5 = "";
    if (res5 != exp5) {
        passed = false;
        error += "test5 failed:\n";
        error += "input: " + test5 + "\n";
        error += "expected: " + exp5 + "\n";
        error += "result: " + res5 + "\n";
    }

    if (!passed) cout << "infix_to_postfix errors:\n";
    cout << error;
    return passed;
}

bool test_build_parse_tree() {
    string test1 = "c | (a ^ b)";
    string test2 = "a | b ^ c";
    string test3 = "~(A ^ b) ^ (c | ~z)";

    string error;
    bool passed = true;

    ParseTreeNode* tree1 = build_parse_tree(test1);
    string res1;
    preorder(tree1, res1);
    string exp1 = "|c^ab";
    if (res1 != exp1) {
        passed = false;
        error += "test1 failed:\n";
        error += "input: " + test1 + "\n";
        error += "expected: " + exp1 + "\n";
        error += "result: " + res1 + "\n";
    }

    ParseTreeNode* tree2 = build_parse_tree(test2);
    string res2;
    preorder(tree2, res2);
    string exp2 = "^|abc";
    if (res2 != exp2) {
        passed = false;
        error += "test2 failed:\n";
        error += "input: " + test2 + "\n";
        error += "expected: " + exp2 + "\n";
        error += "result: " + res2 + "\n";
    }

    ParseTreeNode* tree3 = build_parse_tree(test3);
    string res3;
    preorder(tree3, res3);
    string exp3 = "^~^Ab|c~z";
    if (res3 != exp3) {
        passed = false;
        error += "test3 failed:\n";
        error += "input: " + test3 + "\n";
        error += "expected: " + exp3 + "\n";
        error += "result: " + res3 + "\n";
    }

    if (!passed) cout << "build_parse_tree errors:\n";
    cout << error;
    return passed;
}

int main() {

    test_weird_traversal();
    test_bits_to_tree();
    test_build_parse_tree();

    return 0;
}
