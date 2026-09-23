#include <climits>
#include <functional>
#include <string>
#include <vector>
#include <limits>
#include <random>
#include <iostream>
#include <algorithm>
#include "sha256.c"

#include <unordered_map>

// be sure to change FIRSTNAME and LASTNAME with your own first and last name
#include "Firstname_Lastname_project2.h"

using namespace std;

bool verbose = false;

SHA256 sha265 = SHA256();

const string who_am_i() {
    return "Valentina_Ramirez-Susarret";
}

/****************
 * INSTRUCTIONS *
 ****************
 *
 * - Replace all instances of "Firstname_Lastname" with your firstname and
 *   your last name. This include the .h and .cpp files, along with the
 *   header guards at the top of the .h file.
 *
 * - Implement the appropriate algorithms as described below.
 *   You must follow the specifications as written below.
 *
 * - Certain function signatures may not be modified (as it will affect auto
 *   grading). These functions will be specified.
 *
 * - You are allowed to add helper functions. Be sure to add the appropriate
 *   function prototypes in "Fistname_Lastname_project2.h."
 *
 * - The file "testing.cpp" has various functions you can utilize to test
 *   your code. You can also add your own tests!
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



/*** Project 2: Hashing ***/

/* Birthday Attack 1
 *
 * 10 Points
 *
 * In this problem, you will implement a birthday attack on a simple hash function that is provided
 * in the header file. The goal will be to find a collision in the hash function using the Birthday 
 * Attack (with at least a 50% chance of success).
 *
 * Assumptions
 * - The hash function will have a 16 bit output (2 bytes). We will use the `unsigned short` type
 *   as the output type to make things simple.
 * - The hash function will take `unsigned integers` as input, again to make things simple.
 * - Your function will output:
 *     (a) two inputs a and b such that h(a) = h(b) (a collision), as a list [a, b], or 
 *     (b) {} if no collision is found.
 *   The output type of the function will be `vector<unsigned int>`.
 *
 * Algorithm Description
 * - Do the following a small constant number of times (at least 2):
 *     - Randomly generate 350 unsigned integers. Feel free to use the provided helper function
 *       `sample_int()`.
 *     - For each of the generated integers:
 *         - Hash the integer
 *         - Check if you find a collision. If yes, you can stop and output the two colliding inputs.
 * - If no collision is found, output {} (an empty list).
 *
 * Hash Function Signature
 *   unsigned short test_hash(unsigned int input);
 *
 */

unsigned int sample_int() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<unsigned int> dist(0);
    return dist(mt);
}

unsigned short test_hash(unsigned int input) {
    const unsigned int b = 3177205741;
    const unsigned int a = 2371597069;
    return a*(input << 2) + b;
}

// Do not modify this function signature. 
vector<unsigned int> birthday_attack_1(function<unsigned short(unsigned int)> hash_function) {
    // Here, hash_function is an actual function. To test this function with
    // the provided `test_hash`, you can call your function in main as:
    //     vector<long> out = birthday_attack_1(test_hash);
    // Note you can implement your own test hash functions so long as their 
    // signatures match the `test_hash` function signature.
    
    // Your code here!
    vector<unsigned int> res;

    unordered_map<unsigned short, unsigned int> seen; // <hash value, integer>
    size_t num_attempts = 0;

    while (num_attempts < 350) {
        num_attempts++;
        unsigned int integer = sample_int();
        unsigned short hash_value = hash_function(integer);

        // check if hash_value was already generated
        if (seen.find(hash_value) != seen.end()) {
            if (verbose) {
                cout << "birthday attack 1 results:\n";
                cout << "  collision found after " << num_attempts << " attempts\n";
                cout << "  prev integer: " << seen[hash_value] << endl;
                cout << "  curr integer: " << integer << endl;
            }
            res.push_back(seen[hash_value]);
            res.push_back(integer);
            return res;
        }

        seen[hash_value] = integer;
    }
    if (verbose) {
        cout << "birthday attack 1 produced no collisions after " << num_attempts << " attempts.\n";
    }
    return res;
}



/* Birthday Attack 2
 *
 * 10 Points
 *
 * In this problem, you will implement a slightly different birthday attack on a simple 
 * hash function that is provided in the header file. The birthday attack described in 
 * part 1 above has the drawback of potentially needing too much space to implement
 * (proportional to sqrt(hash_output_domain_size)). You will address this in this
 * problem.
 *
 * The birthday-type attack you will implement in this problem is known as "Floyd's
 * tortoise and hare algorithm" (which is actually just a cycle finding algorithm).
 * We'll use it to implement a small-space birthday attack.
 *
 * Assumptions
 * - The hash function will have a 16 bit output (2 bytes). We will use the `unsigned short` type
 *   as the output type to make things simple.
 * - The hash function will take `unsigned integers` as input, again to make things simple.
 * - Your function will output two inputs a and b such that h(a) = h(b) (a collision), as a list [a, b].
 *
 * Algorithm Description
 * - Maintain two values, `tort` and `hare`, initialized as 
 *   tort = hash(0) and hare = hash(hash(0)).
 * - While tort != hare, take "one-step" with tort and "two-steps" with hare.
 *   This means updating tort by hashing the previous value of tort once, and hare
 *   by computing the double hash of the previous value of hare (see the initialization
 *   as an example).
 * - Once tort == hare, reset tort = 0.
 * - Now, while hash(tort) != hash(hare) take "one-step" with
 *   both tort and hare, until hash(tort) == hash(hare).
 * - Output [tort, hare]
 *
 * Additional Resources
 * - The following lecture notes explain both birthday attack algorithms:
 *      https://people.cs.uchicago.edu/~davidcash/284-autumn-21/12-hash.pdf
 *
 * Hash Function Signature
 *   unsigned short test_hash(unsigned int input);
 */

// Do not modify this function signature. 
vector<unsigned int> birthday_attack_2(function<unsigned short(unsigned int)> hash_function) {
    // Here, hash_function is an actual function. To test this function with
    // the provided `test_hash`, you can call your function in main as:
    //     vector<unsigned int> out = birthday_attack_1(test_hash);
    // Note you can implement your own test hash functions so long as their 
    // signatures match the `test_hash` function signature.
    
    // Your code here!
    vector<unsigned int> res;

    unsigned short tort = hash_function(0);
    unsigned short hare = hash_function(hash_function(0));
    size_t i = 0;

    while (tort != hare) {
        // tort takes 1 step, hare takes two steps
        tort = hash_function(tort);
        hare = hash_function(hash_function(hare));
        i++;
    }

    if (verbose) {
        cout << "\nbirthday attack 2 results:\n";
        cout << "  1-2 step found collision after " << i << " attempts\n";
        cout << "  tort: " << tort << endl;
        cout << "  hare: " << hare << endl;
    }

    // reset tort
    tort = 0;
    i = 0;

    while (hash_function(tort) != hash_function(hare)) {
        // both take 1 step
        tort = hash_function(tort);
        hare = hash_function(hare);
        i++;
    }

    if (verbose) {
        cout << "  found another collision after " << i << " attempts hashing 1 step each\n";
        cout << "  tort: " << tort << endl;
        cout << "  hare: " << hare << endl;
    }

    res.push_back(tort);
    res.push_back(hare);

    return res;
}


/* Merkle Trees
 *
 * 55 Points
 *
 * In this problem, you will implement a cryptographic commitment scheme, known as a Merkle Tree,
 * named after Ralph Merkle, who introduced the concept in 1987; see (https://link.springer.com/chapter/10.1007/3-540-48184-2_32).
 *
 * Generally speaking, a Merkle tree is a cryptographic commitment for vectors, which allow you
 * to (1) commit to a vector (i.e., write a vector down into a sealed envelope that you cannot
 * change), and (2) prove that position i of the commited vector is a particular value v.
 *
 * For this problem, there are 4 algorithms you will impelment as part of the Merkle tree, each described below.
 */


/* 1. The Commitment Algorithm (15 points)
 *  Inputs: 
 *      - vector<string> list: a vector of strings. For this problem, the length of list will always be
 *          a power of 2.
 *      - function<string(string)> hash_function: a hash function which maps strings to strings.
 *  Output:
 *      - string root: the Merkle root (which is a hash value)
 *  Algorithm:
 *      - A Merkle tree is a complete binary tree with 2^n leaves, 
 *          where each node in the tree is labeled as follows.
 *          - Order each leaf, from left to right, as 0, 1, ..., 2^n - 1.
 *              Leaf i is labeled with hash_function(list[i] + "i").
 *              Note that list[i] is a string, and "i" is the string representation of index i.
 *          - For each non-leaf node w with child nodes u, v and labels
 *              hash_u, hash_v, the label of w is hash_w = hash_function(hash_u || hash_v),
 *              where hash_u || hash_v denotes string concatenation.
 *      - The commitment algorithm computes the hash labels of every node in
 *          the complete binary tree, and outputs the label of the root as
 *          the commitment.
 *  EXTRA CREDIT:
 *      - 5 points of extra credit will be awarded if you use at most O(log(n)) additional
 *          space, where n = list.size().
 *      - 2.5 points of extra credit will be awarded if your algorithm can handle inputs of
 *          size n, where n is NOT a power of 2.
 */


string merkle_commit(const vector<string>& list, function<string(string)> hash_function) {
    if (list.size() >= 1) {
        vector<string> curr_level;
        for (int i = 0; i < list.size(); i++) {
            string to_hash = list.at(i) + to_string(i);
            curr_level.push_back(hash_function(to_hash));
        }
        while (curr_level.size() > 1) {
            vector<string> next_level;
            if (curr_level.size() % 2 != 0) {
                curr_level.push_back(curr_level.at(curr_level.size()-1));
            }
            for (int i = 0; i < curr_level.size(); i += 2) {
                string combined = curr_level.at(i) + curr_level.at(i+1);
                next_level.push_back(hash_function(combined));
            }
            curr_level = next_level;
        }
        return curr_level.at(0);
    }
    return "";
}

 /* 2. The Positional Open Algorithm (20 points)
 *  Inputs:
 *      - vector<string> list: a vector of strings, assumed to be a power of 2.
 *      - function<string(string)> hash_function: a hash function from strings to strings
 *      - unsigned int i: the position list[i] to be opened.
 *  Output:
 *      - vector<string> proof: a proof certifying that list[i] is consistent
 *          with the given commitment root. proof[0] is required to be the value list[i].
 *  Algorithm:
 *      - Merkle trees are awesome because they allow us to certify that a list[i] is consistent
 *          with a computed Merkle root "hash", for any position i, without giving away the
 *          entire list!
 *      - Do do this, the "proof" we provide consists of the minimum amount of 
 *          node labels (i.e., hash values) needed to compute the root hash.
 *      - Intuitively, you can construct the proof as follows
 *          - In the complete binary tree representing the merkle root computation, 
 *              draw a leaf-to-root path the leaf list[i] to the root.
 *          - Append [list[i], "i"] to the proof.
 *          - For every node on the root-to-leaf path that is not a leaf node:
 *              - add the label (i.e., hash) of its child that is NOT on the 
 *                  root to leaf path to the proof.
 *      - One algorithm for obtaining this proof is given below recursively
 *          - if the list is of size 1, add list[i] to proof and return.
 *          - otherwise, divide the list into two halves: list_left, list_right.
 *              - if index i is in list_left:
 *                  - recurse on list_left
 *                  - merkle hash list_right, obtaining root_right
 *                  - add root_right to the proof
 *              - otherwise, index i is in list_right:
 *                  - recurse on list_right
 *                  - merkle hash list_left, obtaining root_left
 *                  - add root_left to the proof
 *      - Note: there are other algorithms to compute the proof.
 *      - IMPORTANT: the order of the proof matters. The value
 *          proof[i] must come from level i of the complete binary tree.
 *          An example is given below.
 *          - Suppose you are asked to prove the value list[2] = C is consistent
 *              with the Merkle root R.
 *          - Below is the complete binary tree of labels, where the label of a node is the
 *              hash of both its child nodes, concatenated in order left to right.
 *
 *                 R
                  / \
                 /   \
                /     \
               /       \
              /         \
             /           \
           h12           h13
           / \           / \
          /   \         /   \
         /     \       /     \
        h8     h9    h10     h11
        / \    / \   / \     / \
       h0 h1  h2 h3 h4 h5   h6 h7
       |  |   |  |  |  |    |  |
list=[ A, B,  C, D, E, F,   G, H ]

 *      - To prove that C is consistent with Merkle root R, you must add all information
 *          to the proof string `proof` which is needed to recover the hash value R.
 *      - To do this, must add all hash values needed to compute R from node C. To figure out
 *          which hashes you need, consider the leaf-to-root path from R to C, which is
 *          C -- h2 -- h9 -- h12 -- R.
 *      - Starting from the bottom, to compute hash h2, all you need is the value C. So you add
 *          C to the proof, giving proof = [ C ]
 *      - To compute hash value h9, you need h2 and h3. You can compute h2 from C (in the proof), 
 *          so all you need is h3. The proof becomes proof = [ C, h3 ].
 *      - Now, you need to compute h12. To do so, you need h8 and h9. In the proof so far, you have
 *          C and h3, which allows you to compute h9. So you must now add h8 to the proof, giving
 *          proof = [ C, h3, h8 ].
 *      - Finally, to compute R, you need h12 and h13. From the current proof, you can compute h12
 *          since you are given h8 and can compute h9 from the remainder of the proof. So we must
 *          add h13 to the proof, giving proof = [ C, h3, h8, h13 ].
 *      - The final proof is [C, h3, h8, h13], since this gives you all information needed to compute
 *          the root R.
 *
 *
 *  EXTRA CREDIT:
 *      - 5 points of extra credit will be awarded if you use at most O(log(n)) additional
 *          space, where n = list.size().
 *      - 2.5 points of extra credit will be awarded if your algorithm can handle inputs of
 *          size n, where n is NOT a power of 2.
 */
/*
 *      - One algorithm for obtaining this proof is given below recursively
 *          - if the list is of size 1, add list[i] to proof and return.
 *          - otherwise, divide the list into two halves: list_left, list_right.
 *              - if index i is in list_left:
 *                  - recurse on list_left
 *                  - merkle hash list_right, obtaining root_right -- What does it mean to merkle hash list_right?
 *                  - add root_right to the proof
 *              - otherwise, index i is in list_right:
 *                  - recurse on list_right
 *                  - merkle hash list_left, obtaining root_left   -- Same question, merkle hash list_left meaning?
 *                  - add root_left to the proof
*/
vector<string> merkle_open_position(
    const vector<string>& list, 
    function<string(string)> hash_function, 
    const unsigned int i
) {
    vector<string> proof;
    if (list.size() != 1) {
        auto middle = list.begin() + list.size() / 2;
        vector<string> list_left(list.begin(), middle);
        vector<string> list_right(middle, list.end());
        if (i < list_left.size()) {
            proof = merkle_open_position(list_left, hash_function, i / 2);
            string root_right = hash_function(list_right.at(0));
            proof.push_back(root_right);
        } else {
            proof = merkle_open_position(list_right, hash_function, i / 2);
            string root_left = hash_function(list_left.at(0));
            proof.push_back(root_left);
        }
    } else {
        proof.push_back(list.at(i));
    }
    return proof;
}



 /* 3. The Positional Verify Algorithm (15 points)
 *  Inputs:
 *      - string root: the Merkle root
 *      - vector<string> proof: a positional opening proof
 *      - function<string(string)> hash_function: a hash function from strings to strings
 *      - unsigned int i: the position list[i] to be opened.
 *  Output:
 *      - int decision: the verifier decition to accept or reject
 *          output 0 if accept, and any other integer if reject
 *  Algorithm:
 *      - Given the string proof, you must now verify that it is consistent with the root.
 *      - Assuming the proof is in the correct order, verification proceeds as follows:
 *          - compute h = hash_function(proof[0]+proof[1])
 *          - for p in proof[2:] (i.e., to the end of the proof)
 *              - determine whether p is the left or right input to the hash function
 *              - compute h = hash_function(p || h) or hash_function(h || p) based on
 *                  the above decision
 *          - check if h == R and return an appropriate value
 *      - IMPORTANT
 *          - Remember that the Merkle tree is built in a position dependent way, which
 *              means that the label of a node is the hash of the concatenation of its
 *              left and right child labels. This means you need to figure out in the
 *              returned proof if the label you are given is a left or right child.
 *          - Example from merkle_open_position: the proof you are given is
 *              proof = [ C, h3, h8, h13 ]. 
 *              - h2 = hash_function(C), and is a left child, while h3 is a right child.
 *                  So to compute h9, you must compute hash_function(h2||h3).
 *              - h8 is a left child and h9 is a right child, so to compute h12, you must
 *                  compute hash_function(h8||h9).
 *              - h12 is a left child and h13 is a right child, so you must compute
 *                  h = hash_function(h12||h13), then compare h to R.
 *
 *
 *  EXTRA CREDIT:
 *      - 2.5 points of extra credit will be awarded if your algorithm can handle inputs of
 *          size n, where n is NOT a power of 2.
 */

int merkle_verify_position(
    const string root, 
    const vector<string>& proof, 
    function<string(string)> hash_function, 
    const unsigned int i
) {
    return 0;
}


 /* 4. The Full Verify Algorithm (5 points)
 *  Inputs:
 *      - string root: the Merkle root
 *      - vector<string> list: the list claimed to be Merkle hashed as root
 *      - function<string(string)> hash_function: a hash function from strings to strings
 *      - unsigned int i: the position list[i] to be opened.
 *  Output:
 *      - int decision: the verifier decition to accept or reject
 *          output 0 if accept, and any other integer if reject
 *  Algorithm:
 *      - The verification is given the full list and must now check if the Merkle
 *          hash of the given list is equal to the root given as input.
 *      - Must return 0 if they match and any other integer otherwise.
 *  EXTRA CREDIT:
 *      - 5 points of extra credit will be awarded if you use at most O(log(n)) additional
 *          space, where n = list.size().
 *      - 2.5 points of extra credit will be awarded if your algorithm can handle inputs of
 *          size n, where n is NOT a power of 2.
 */

int merkle_verify_full(const string root, const vector<std::string> list) {
    return 0;
}



int main(int argc, char** argv) {

    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-v") {
            verbose = true;
        }
    }

    SHA256 s;

    vector<unsigned int> bday1 = birthday_attack_1(test_hash);
    vector<unsigned int> bday2 = birthday_attack_2(test_hash);

    vector<string> merkle_tree = {"a", "b", "c", "d"};

    if (verbose) {
    cout << "\ntesting merkle methods with merkle tree:\n";
    for (int i = 0; i < merkle_tree.size(); i++) {
        cout << merkle_tree.at(i) << " ";
    }
    cout << endl;
    }

    string commit = merkle_commit(merkle_tree, s.hashString);

    if (verbose) cout << "merkle commit: " << commit << endl;

    vector<string> merkle_open_pos = merkle_open_position(merkle_tree, s.hashString, 3);

    if (verbose) {
    cout << "\nmerkle open position results:\n";
    for (int i = 0; i < merkle_open_pos.size(); i++) {
        cout << merkle_open_pos.at(i) << " ";
    }
    cout << endl;
    }

    return 0;
}
