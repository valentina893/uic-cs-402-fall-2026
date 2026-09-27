#include <climits>
#include <functional>
#include <string>
#include <vector>
#include <limits>
#include <random>
#include <iostream>
#include <algorithm>
#include "sha256.c"

// be sure to change FIRSTNAME and LASTNAME with your own first and last name
#include "Valentina_Ramirez-Susarret_project2.h"

using namespace std;

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
            res.push_back(seen[hash_value]);
            res.push_back(integer);
            return res;
        }

        seen[hash_value] = integer;
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

    // reset tort
    tort = 0;
    i = 0;

    while (hash_function(tort) != hash_function(hare)) {
        // both take 1 step
        tort = hash_function(tort);
        hare = hash_function(hare);
        i++;
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
 *          - ASSUMPTION: i < list.size() is always true!
 *  Output:
 *      - vector<pair<string,string>> proof: a proof certifying that list[i] is consistent
 *          with the given commitment root. proof[0] is required to be the value pair("L", list[i])
 *          if list[i] is a left leaf node, or pair("R", list[i]) if it is a right leaf node.
 *  Algorithm:
 *      - Merkle trees are awesome because they allow us to certify that a list[i] is consistent
 *          with a computed Merkle root "hash", for any position i, without giving away the
 *          entire list!
 *      - Do do this, the "proof" we provide consists of the minimum amount of 
 *          node labels (i.e., hash values) needed to compute the root hash.
 *      - Intuitively, you can construct the proof as follows
 *          - In the complete binary tree representing the merkle root computation, 
 *              draw a leaf-to-root path the leaf list[i] to the root.
 *          - Determine if leaf list[i] is a left or right leaf node.
 *          - Append ("L", list[i]) to the proof if it is a left leaf node, 
 *              or ("R", list[i]) if it is a right leaf node.
 *          - For every node on the root-to-leaf path that is not a leaf node:
 *              - add the the tuple (left_or_right, label) (i.e., hash) to the proof, where
 *                  - label is the hash of its child that is NOT on the root to leaf path; and
 *                  - left_or_right = "L" or "R" depending on if it is a left or right child.
 *      - One algorithm for obtaining this proof is given below recursively
 *          - if the list is of size 1, add ("L", list[0]) to proof and return.
 *          - otherwise, divide the list into two halves: list_left, list_right.
 *              - if index i is in list_left:
 *                  - recurse on list_left
 *                  - merkle hash list_right, obtaining root_right
 *                  - add ("R", root_right) to the proof
 *              - otherwise, index i is in list_right:
 *                  - recurse on list_right
 *                  - merkle hash list_left, obtaining root_left
 *                  - add ("L", root_left) to the proof
 *      - Note: there are other algorithms to compute the proof.
 *      - IMPORTANT: the order of the proof matters. The value
 *          proof[i] must come from level i of the complete binary tree.
 *          An example is given below.
 *          - Suppose you are asked to prove the value list[2] = C is consistent
 *              with the Merkle root root_hash.
 *          - Below is the complete binary tree of labels, where the label of a node is the
 *              hash of both its child nodes, concatenated in order left to right.
 *
 *              root_hash
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

 *      - To prove that C is consistent with Merkle root root_hash, you must add all information
 *          to the proof string `proof` which is needed to recover the hash value root_hash.
 *      - To do this, must add all hash values needed to compute root_hash from node C. To figure out
 *          which hashes you need, consider the leaf-to-root path from root_hash to C, which is
 *          C -- h2 -- h9 -- h12 -- R.
 *      - Starting from the bottom, to compute hash h2, all you need is the value C. We also
 *          want to include if this node is a left or right node to help the verifier. In the
 *          above picture, C is a left node, so we'll use "L" to mark this. Now, we add the
 *          pair ("L", C) to the proof, giving proof = [ ("L", C) ]
 *      - To compute hash value h9, you need h2 and h3. You can compute h2 from C (in the proof), 
 *          so all you need is h3. The proof becomes proof = [ ("L",C), ("R",h3) ].
 *      - Now, you need to compute h12. To do so, you need h8 and h9. In the proof so far, you have
 *          C and h3, which allows you to compute h9. So you must now add h8 to the proof, giving
 *          proof = [ ("L",C), ("R",h3), ("L",h8) ].
 *      - Finally, to compute root_hash, you need h12 and h13. From the current proof, you can compute h12
 *          since you are given h8 and can compute h9 from the remainder of the proof. So we must
 *          add h13 to the proof, giving proof = [ ("L",C), ("R",h3), ("L",h8), ("R",h13) ].
 *      - The final proof is [("L",C), ("R",h3), ("L",h8), ("R",h13)], since this gives you all information 
 *      needed to compute the root root_hash.
 *
 *
 *  EXTRA CREDIT:
 *      - 5 points of extra credit will be awarded if you use at most O(log(n)) additional
 *          space, where n = list.size().
 *      - 2.5 points of extra credit will be awarded if your algorithm can handle inputs of
 *          size n, where n is NOT a power of 2.
 */

vector<pair<string,string>> merkle_open_position(
    const vector<string>& list, 
    function<string(string)> hash_function, 
    const unsigned int i
) {
    vector<pair<string,string>> proof;

    if (i >= list.size()) {
        return proof;
    }

    if (i < list.size() / 2) {
        proof.push_back(pair<string, string>("L", list.at(i)));
    } else {
        proof.push_back(pair<string, string>("R", list.at(i)));
    }
    
    // create leaf hashes to preserve original indices of a0, b1, c2, ..., h7
    vector<string> leaf_hashes;
    for (int i = 0; i < list.size(); i++) {
        leaf_hashes.push_back(hash_function(list.at(i) + to_string(i)));
    }

    // call recursive helper function
    make_proof(leaf_hashes, i, proof, hash_function);
    return proof;
}

string merkle_commit2(const vector<string>& list, function<string(string)> hash_function) {
    if (list.size() >= 1) {
        vector<string> curr_level;
        for (int i = 0; i < list.size(); i++) {
            string to_hash = list.at(i);
            curr_level.push_back(to_hash);
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

void make_proof(vector<string> list, unsigned int i, 
    vector<pair<string,string>>& proof, 
    function<string(string)> hash_function
) {
    // check if we are done recursing
    if (list.size() == 1) return;
    // divide list into two halves
    auto middle = list.begin() + list.size() / 2;
    vector<string> list_left(list.begin(), middle);
    vector<string> list_right(middle, list.end());
    if (i < list_left.size()) { // i is in left sublist
        make_proof(list_left, i, proof, hash_function);
        string root_right = merkle_commit2(list_right, hash_function);
        proof.push_back(pair<string,string>("R", root_right));
    } else { // i is in right sublist
        make_proof(list_right, i - list_left.size(), proof, hash_function);
        string root_left = merkle_commit2(list_left, hash_function);
        proof.push_back(pair<string,string>("L", root_left));
    }
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
 *          - compute h = hash_function(proof[0].second+"i")
 *          - for pair p in proof[1:] (i.e., to the end of the proof)
 *              - determine whether p is the left or right input to the hash function,
 *                  given by p.first
 *              - compute h = hash_function(p.second || h) or hash_function(h || p.second) 
 *              based on the above decision
 *          - check if h == root and return an appropriate value
 *      - IMPORTANT
 *          - Remember that the Merkle tree is built in a position dependent way, which
 *              means that the label of a node is the hash of the concatenation of its
 *              left and right child labels. This means you need to figure out in the
 *              returned proof if the label you are given is a left or right child.
 *          - Example from merkle_open_position: the proof you are given is
 *              proof = [ ("L",C), ("R",h3), ("L",h8), ("R",h13) ]. 
 *              - h2 = hash_function(C), and is a left child, while h3 is a right child.
 *                  So to compute h9, you must compute hash_function(h2||h3).
 *              - h8 is a left child and h9 is a right child, so to compute h12, you must
 *                  compute hash_function(h8||h9).
 *              - h12 is a left child and h13 is a right child, so you must compute
 *                  h = hash_function(h12||h13), then compare h to root.
 *
 *
 *  EXTRA CREDIT:
 *      - 2.5 points of extra credit will be awarded if your algorithm can handle inputs of
 *          size n, where n is NOT a power of 2.
 */

int merkle_verify_position(
    const string root, 
    const vector<pair<string,string>>& proof, 
    function<string(string)> hash_function, 
    const unsigned int i
) {
}


 /* 4. The Full Verify Algorithm (5 points)
 *  Inputs:
 *      - string root: the Merkle root
 *      - vector<string> list: the list claimed to be Merkle hashed as root
 *      - function<string(string)> hash_function: a hash function from strings to string
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

int merkle_verify_full(const string root, const vector<std::string>& list, function<string(string)> hash_function) {
}

int test_bday1() {

    const std::vector<unsigned int> primes = {
        2003, 2011, 2017, 2027, 2029, 2039, 2053, 2063, 2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129, 2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213, 2221, 2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287, 2293, 2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357, 2371, 2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423, 2437, 2441, 2447, 2459, 2467, 2473, 2477, 2503, 2521, 2531, 2539, 2543, 2549, 2551, 2557, 2579, 2591, 2593, 2609, 2617, 2621, 2633, 2647, 2657, 2659, 2663, 2671, 2677, 2683, 2687, 2689, 2693, 2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741, 2749, 2753, 2767, 2777, 2789, 2791, 2797, 2801, 2803, 2819, 2833, 2837, 2843, 2851, 2857, 2861, 2879, 2887, 2897, 2903, 2909, 2917, 2927, 2939, 2953, 2957, 2963, 2969, 2971, 2999, 3001, 15013, 15017, 15031, 15053, 15061, 15073, 15077, 15083, 15091, 15101, 15107, 15121, 15131, 15137, 15139, 15149, 15161, 15173, 15187, 15193, 15199, 15217, 15227, 15233, 15241, 15259, 15263, 15269, 15271, 15277, 15287, 15289, 15299, 15307, 15313, 15319, 15329, 15331, 15349, 15359, 15361, 15373, 15377, 15383, 15391, 15401, 15413, 15427, 15439, 15443, 15451, 15461, 15467, 15473, 15493, 15497, 15511, 15527, 15541, 15551, 15559, 15569, 15581, 15583, 15601, 15607, 15619, 15629, 15641, 15643, 15647, 15649, 15661, 15667, 15671, 15679, 15683, 15727, 15731, 15733, 15737, 15739, 15749, 15761, 15767, 15773, 15787, 15791, 15797, 15803, 15809, 15817, 15823, 15859, 15877, 15881, 15887, 15889, 15901, 15907, 15913, 15919, 15923, 15937, 15959, 15971, 15973, 15991, 16001,
    };

    double total_score = 20.0;
    double score = 0.0;

    unsigned int n = primes.size();

    int runs = 0;
    int runs_upper = 5;

    for(int i = 0; i < 20;) {
        unsigned int a = sample_int() % n;
        unsigned int b = sample_int() % n;
        while(a == b) {
            b = sample_int() % n;
        }

        a = primes[a];
        b = primes[b];

        std::function<unsigned short(unsigned int)> hash = 
        [&a, &b](unsigned int x) -> unsigned short 
        {return static_cast<unsigned short>(a*(x<<2)+b);};

        std::vector<unsigned int> result = birthday_attack_1(hash);
        if(result.size() != 2) {
            if(runs == runs_upper) {
                ++i;
                runs = 0;
            }
            else ++runs;
            continue;
        }
        if(hash(result[0]) == hash(result[1]) && result[0] != result[1]) {
            ++score;
            ++i;
        }
    }

    return (100*(score / total_score));
}

int test_bday2() {

    const std::vector<unsigned int> primes = {
        2003, 2011, 2017, 2027, 2029, 2039, 2053, 2063, 2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129, 2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213, 2221, 2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287, 2293, 2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357, 2371, 2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423, 2437, 2441, 2447, 2459, 2467, 2473, 2477, 2503, 2521, 2531, 2539, 2543, 2549, 2551, 2557, 2579, 2591, 2593, 2609, 2617, 2621, 2633, 2647, 2657, 2659, 2663, 2671, 2677, 2683, 2687, 2689, 2693, 2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741, 2749, 2753, 2767, 2777, 2789, 2791, 2797, 2801, 2803, 2819, 2833, 2837, 2843, 2851, 2857, 2861, 2879, 2887, 2897, 2903, 2909, 2917, 2927, 2939, 2953, 2957, 2963, 2969, 2971, 2999, 3001, 15013, 15017, 15031, 15053, 15061, 15073, 15077, 15083, 15091, 15101, 15107, 15121, 15131, 15137, 15139, 15149, 15161, 15173, 15187, 15193, 15199, 15217, 15227, 15233, 15241, 15259, 15263, 15269, 15271, 15277, 15287, 15289, 15299, 15307, 15313, 15319, 15329, 15331, 15349, 15359, 15361, 15373, 15377, 15383, 15391, 15401, 15413, 15427, 15439, 15443, 15451, 15461, 15467, 15473, 15493, 15497, 15511, 15527, 15541, 15551, 15559, 15569, 15581, 15583, 15601, 15607, 15619, 15629, 15641, 15643, 15647, 15649, 15661, 15667, 15671, 15679, 15683, 15727, 15731, 15733, 15737, 15739, 15749, 15761, 15767, 15773, 15787, 15791, 15797, 15803, 15809, 15817, 15823, 15859, 15877, 15881, 15887, 15889, 15901, 15907, 15913, 15919, 15923, 15937, 15959, 15971, 15973, 15991, 16001,
    };

    double total_score = 10.0;
    double score = 0.0;

    unsigned int n = primes.size();

    int runs = 0;
    int runs_upper = 5;

    int zero_collisions = 0;

    for(int i = 0; i < 10;) {
        if(zero_collisions == 10) {
            return -1;
        }
        unsigned int a = sample_int() % n;
        unsigned int b = sample_int() % n;
        while(a == b) {
            b = sample_int() % n;
        }

        a = primes[a];
        b = primes[b];

        std::function<unsigned short(unsigned int)> hash = [&a, &b](unsigned int x) -> unsigned short {return static_cast<unsigned short>(a*(x<<2)+b);};

        std::vector<unsigned int> result = birthday_attack_2(hash);
        if(result.size() != 2) {
            if(runs == runs_upper) {
                ++i;
                runs = 0;
            }
            else ++runs;
            continue;
        }
        if(result[0] == result[1] && result[0] == 0) {
            ++zero_collisions;
            continue;
        }
        if(hash(result[0]) == hash(result[1]) && result[0] != result[1]) {
            ++score;
            ++i;
            zero_collisions = 0;
        }
    }

    return (100*(score / total_score));
}

// Here are some tests to check if you are correctly computing the
// Merkle root and proofs with respect to the below test_vec's.
// All tests are with respect to the hash function 
// SHA256::hashString(const std::string& str) defined in sha256.h.
const vector<string> test_vec1 {"a", "b", "c", "d", "e", "f", "g", "h" };
const string test_vec1_merkle_root = "03d17ec0ddabb9af008dce3964169c576491f112481ef00d1e1ed93f8ff36673";

// Merkle proof for test_vec1[2] = "c"
const vector<pair<string,string>> test_vec1_proof_of_2 = {
    {"L",test_vec1[2]},
    {"R","f451a61749c611ba0fa0e16c61831db44f38c611dff25879cf271a24c81a88b6"}, // SHA256::hashString("d3")
    {"L","09fc26616cb10a1249d12c2ce0837e194f90a0f737d474ae827e50be5fbcafe8"}, // SHA256::hashString( SHA256::hashString("a0") + SHA256::hashString("b1") )
    {"R","3b73ae5b262f6e0c074cb04d9487ecd34ca2058722deb80cae9576d8365218a5"}, // SHA256::hashString( SHA256::hashString(SHA256::hashString("e4") + SHA256::hashString("f5")) + SHA256::hashString(SHA256::hashString("g6") + SHA256::hashString("h7"))  )
};

// above was generated using the following link and sha256 to get the complete hashes for each proof
// https://www.cipherdecipher.com/tools/merkle-tree-calculator?input=a0%0Ab1%0Ac2%0Ad3%0Ae4%0Af5%0Ag6%0Ah7&proof=1&idx=2

const vector<string> test_vec2 = {"hello", "world!"};
const string test_vec2_merkle_root = "45bc2c583b1d8ebb501fcc2f29d0330f316649bbf23d76feee22b64e6b67972b";
// Merkle proof for test_vec2[1] = "world!"
const vector<pair<string,string>> test_vec2_proof_of_1 = {
    {"R", test_vec2[1]},
    {"L", "5a936ee19a0cf3c70d8cb0006111b7a52f45ec01703e0af8cdc8c6d81ac5850c"}
};
// see https://www.cipherdecipher.com/tools/merkle-tree-calculator?input=hello0%0Aworld%211&proof=1&idx=1

const vector<string> test_vec3 = {"Merkle", "trees", "are", "cool!"};
const string test_vec3_merkle_root = "4683d51abcd4e5b01faec86dd4efaca78e669176d10a3f047c90790bab793cc2";
// Merkle proof for test_vec3[3]
const vector<pair<string,string>> test_vec3_proof_of_3 = {
    {"R", test_vec3[3]},
    {"L", "07b83ebd03651aa06a3e788f04cf1875a063005f2bece50e46cd8d3736bfa23d"},
    {"L", "d60697595896c2a90bcffa77d76dd7cd25b46034d7c7f2310b692c9d97d53624"}
};
// see https://www.cipherdecipher.com/tools/merkle-tree-calculator?input=Merkle0%0Atrees1%0Aare2%0Acool%213&proof=1&idx=3



// the following link can be used to help verify other tests you may have with respect
// to SHA256
// https://www.cipherdecipher.com/tools/merkle-proof-verifier

int main() {

    cout << "birthday attack 1 test:\n";
    cout << test_bday1() << endl;

    cout << "birthday attack 2 test:\n";
    cout << test_bday2() << endl;

    return 0;
}