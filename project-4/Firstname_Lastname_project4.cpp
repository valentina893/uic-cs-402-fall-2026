
// be sure to change FIRSTNAME and LASTNAME with your own first and last name
#include "Firstname_Lastname_project4.h"
#include <string>
#include <deque>
#include <iostream>

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
 * - Implement the appropriate algorithms as described below.
 *   You must follow the specifications as written below.
 *
 * - Certain function signatures may not be modified (as it will affect auto
 *   grading). These functions will be specified.
 *
 * - You are allowed to add helper functions. Be sure to add the appropriate
 *   function prototypes in "Fistname_Lastname_project4.h."
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



/*** PROJECT 4: Graphs ***/

/* Topological Sorting
 *
 * 10 Points
 *
 * In this problem, you are tasked with reading the description of a
 * directed graph as input, then outputting a valid topological
 * sort of the graph, if one exists.
 *
 * Input
 *  - int n: number of nodes/vertices in the graph, labeled from 0 to n-1
 *  - vector<Edge> edges: a list of directed edges in the graph
 *
 * Output
 *  - vector<int>: a valid topological sorting of the graph. If
 *    no topological sorting exists, output an empty list.
 *    If multiple topological sortings exist, you only need to
 *    output a single one.
 *
 * Note: Edge is a struct defined in Firstname_Lastname_project2.h.
 *
 */


vector<int> topological_sort(int n, vector<Edge> edges) {
    // Khan's algorithm:
    // build an adj_list and calculate each node's in-degrees
    // queue all nodes with in-degree == 0
    // while queue isn't empty
    //   pop node
    //   for each neighbor of node
    //     decrement neighbor's in-degree
    //     if neighbor's in-degree == 0
    //       push to queue
    // if length of top_order != n, return empty array?
    // return top_order

    vector<int> top_order;
    if (n > 0 && edges.size() > 0) {
        unordered_map<int, vector<int>> adj_list;
        vector<int> in_degrees(n);
        for (int i = 0; i < edges.size(); i++) {
            if (adj_list.count(i) == 0) {
                adj_list[edges.at(i).from].push_back(edges.at(i).to);
            } else {
                adj_list.at(edges.at(i).from).push_back(edges.at(i).to);
            }
            in_degrees.at(edges.at(i).to) += 1;
        }

        deque<int> q;

        for (int i = 0; i < in_degrees.size(); i++) {
            if (in_degrees.at(i) == 0) {
                q.push_back(i);
            }
        }

        while (q.size() > 0) {
            int curr = q.front();
            q.pop_front();

            top_order.push_back(curr);

            for (int i = 0; i < adj_list.at(curr).size(); i++) {
                in_degrees.at(i)--;
                if (in_degrees.at(i) == 0) {
                    q.push_back(in_degrees.at(i));
                }
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            top_order.push_back(i);
        }
    }
    if (top_order.size() != n) return vector<int>{};
    return top_order;
}


/* Single Source Shortest Paths on DAGs
 *
 * 15 points
 *
 * In this problem, you will be given a directed acyclic graph with 
 * arbitrary integer edge weights (i.e., they can be negative!), as
 * well as a single source node. Your goal will be to output the
 * shortest distance from the source to every other vertex in the
 * graph.
 *
 * Input
 *  - int n: number of nodes in the graph, labeled from 0 to n-1
 *  - vector<Edge> edges: list of weighted directed edges in the graph
 *  - int source: ID of the source node
 *
 * Output
 *  - vector<int>: vector of size n such that entry i is the distance
 *    from source to i in the given graph. Use the value "INT_MAX" to
 *    indicate that there is no path from source to i.
 *
 * Algorithm
 *  - Topological Sorting + BFS is enough to solve this problem.
 *
 * Assumptions
 *  - The graph given as input will always be a DAG
 *
 */
vector<int> dag_single_source(int n, vector<Edge> edges, int source) {
    return vector<int>{};
}


/* Dijkstra's Algorithm
 *
 * 25 Points
 *
 * In this problem, you are simply tasked to implement Dijkstra's Algorithm.
 *
 * Input
 *  - int n: number of nodes in the graph, labeled from 0 to n-1
 *  - vector<Edge> edges: list of weighted directed edges in the graph
 *  - int source: ID of the source node
 *
 * Output
 *  - vector<Node>: a list of size n such that entry i contains a Node node
 *    with the following properties:
 *      - node.id = i
 *      - node.path_cost = cost of the shortest path from source to i
 *      - node.pred = id of the predecessor of i on the shortest path from
 *        source to i
 *
 * Assumptions
 *  - You are guaranteed that the graph contains only non-negative edges
 *    (i.e., weight at least 0). For simplicity, all weights will be
 *    integers.
 * 
 * Note: Node is a struct defined in Firstname_Lastname_project2.h.
 */


vector<Node> dijkstras_algorithm(int n, vector<Edge> edges, int source) {
    // Your code here!
    // Note: see the LeetCode from in-class for the problem "Cheapest Flights
    // K stops" to see how you can create a priority_queue with the Node struct.
    return vector<Node>{};
}


/* A-star Algorithm
 *
 * 25 Points
 *
 * In this problem, you are asked to implement a modified version of Dijkstras,
 * known as A* (A-star). The A* algorithm is very similar to Dijkstras, with
 * two notable differences:
 *  (a) A* uses some heuristic function h to estimate the distance between any
 *      two nodes; and
 *  (b) A* only finds a path from a specified source node and a target node.
 *
 * Recall in Dijkstras, the algorithm finds the shortest path from a single
 * source to all other nodes in the graph.
 *
 * Given a source s and a target t, A* is guaranteed to output a shortest path
 * from s to t as long as the heuristic h underestimates the distance between 
 * any two nodes u,v in the graph. If d(u,v) represents the actual distance
 * between u and v, then h(u,v) <= d(u,v) for all u,v is enough to guarantee
 * that A* outputs a shortest path from s to t.
 *
 * For this specific version of A*, you will be given two points on a grid (a
 * start point and an end point). The grid will be specified by a graph, with
 * nodes being a GridNode (each with their own x and y value on the grid), and
 * edges being a GridEdge. Each GridEdge has a weight that is of a double type.
 * A GridEdge will only connect adjacent or diagonal nodes. Formally, for a
 * GridNode at point (x,y), all of the following edges are possible:
 *
 *  - (x+1, y) (cost = 1.0)
 *  - (x-1, y) (cost = 1.0)
 *  - (x, y+1) (cost = 1.0)
 *  - (x, y-1) (cost = 1.0)
 *  - (x+1, y+1) (cost = 1.5)
 *  - (x-1, y+1) (cost = 1.5)
 *  - (x+1, y-1) (cost = 1.5)
 *  - (x-1, y-1) (cost = 1.5)
 * 
 * Here, edges all have an implicit movement cost, described above. Moving along
 * a diagonal edge has a cost of 1.5, while moving along a cardinally adjacent  
 * edge (north, south, east, west) has a cost of 1.
 *
 * Note that GridEdge and GridNode are structs defined in Firstname_Lastname_project2.h.
 *
 * Input:
 *  - int m: number of columns (x-axis)
 *  - int n: number of rows in the grid (y-axis)
 *  - vector<GridEdge> edges: list of edges in the graph
 *  - GridNode source: source node of the algorithm
 *  - GridNode target: target node of the algorithm
 *  - function<double(GridNode, GridNode)> h: h is a function which takes as input
 *      two GridNodes and outputs a double. This represents the heruistic_cost
 *      function for A*.
 *
 * Output:
 *  - vector<GridNode>: a list of nodes containing the path from source to target.
 *                      Note that if variable "output" is your output vector, then
 *                      it must satisfy the following properties:
 *                          - if a path from source to target exists, then
 *                              - output[0] = source
 *                              - output[output.size()-1] = target
 *                              - Moreover, output[output.size()-1].path_cost is the cost
 *                                of the path from source to target.
 *                          - if no path from source to target exists, then
 *                              - output = {} (the empty list)
 *
 * Algorithm:
 *  The algorithm is nearly identical to Dijkstra's Algorithm, with the following changes.
 *      - Suppose in Dijkstra's you are currently considering node u and expanding the 
 *        frontier along the neighbors of u.
 *      - Let v be a neighbor of u.
 *      - In Dijkstra's, you check if u.cost + weight(u,v) < v.cost, where weight(u,v) 
 *        is the weight of the edge from u to v. If this is true, you update v.cost as
 *        v.cost = u.cost + weight(u,v), update it in / add it to the priority queue,
 *        and continue.
 *      - In A*, this is modified as: v.cost = u.cost + weight(u,v) + heuristic_cost(v, target),
 *        where heuristic_cost(v, target) is a heuristic distance from node v to the target node
 *        target.
 *          - Note you also change the dijkstra's check to u.cost+weight(u,v)+heuristic_cost(v,target) < v.cost
 *  
 *  As part of your implementation of A*, you are required to implement the function
 *  heuristic_cost(GridNode start, GridNode dest) defined below. Your heuristic should never
 *  over estimate the distance between any two nodes start and dest. Remember, in theory you
 *  can move north, south, east, west, or along any diagonal (so long as there is an edge).
 *  Use this information to write a heuristic function that never over estimates the distance.
 *
 *
 * Additional Resources:
 *  - Wikipedia: https://en.wikipedia.org/wiki/A*_search_algorithm
 *  - GeeksForGeeks: https://www.geeksforgeeks.org/dsa/a-search-algorithm/
 *  - Stanford: https://theory.stanford.edu/~amitp/GameProgramming/AStarComparison.html
 *
 */



// You must implement this function.
double heuristic_cost(GridNode start, GridNode dest) {
    // Your code here!
    return 0.0f;
}

// To test your algorithm with the function "heruistic_cost" above,
// simply pass "heuristic_cost" as a parameter to the function.
vector<GridNode> a_star_algorithm(
    int m, 
    int n, 
    vector<GridEdge> edges, 
    GridNode source, 
    GridNode target,
    function<double(GridNode,GridNode)> h
) 
{
    // Your code here!
    // Be sure to use "h" from the inputs in your implementation; do not
    // directly use "heruistic_cost" above!
    return vector<GridNode>{};
}

int main() {
    test_top_order();
    return 0;
}

bool is_valid_topo(int n, std::vector<Edge> edges, std::vector<int> order) {
    if(order.empty()) {
        std::vector<int> my_order = topological_sort(n, edges);
        return my_order.empty();
    }
    std::vector<std::vector<int>> graph(n);
    std::vector<int> indeg(n,0);
    for(const Edge& e: edges) {
        graph[e.from].push_back(e.to);
        ++indeg[e.to];
    }
    for(int i = 0; i < n; ++i) {
        int curr = order[i];
        if(indeg[curr] != 0) return false;
        for(int& child: graph[curr]) {
            --indeg[child];
        }
    }
    return true;
}

bool test_top_order() {

    int score = 0;
    // empty test
    std::vector<Edge> empty_test = {};
    std::vector<int> empty_res = topological_sort(0, empty_test);
    if(empty_res.empty()) ++score;

    cout << "empty\n";

    // single node test
    std::vector<int> single_res = topological_sort(1, empty_test);
    if(is_valid_topo(1, empty_test, single_res)) ++score;

    cout << "single\n";

    // easy small tests
    std::vector<Edge> test1 = {Edge(0,1,1), Edge(1,2,1), Edge(2,3,1), Edge(3,4,1)};
    std::vector<Edge> test2 = {Edge(0,1,1), Edge(2,1,1), Edge(0,3,1), Edge(2,3,1)};
    std::vector<Edge> test3 = {Edge(0,1,1), Edge(1,2,1), Edge(2,3,1), Edge(3,0,1)}; // has a cycle


    std::vector<int> res1 = topological_sort(5, test1);
    if(is_valid_topo(5, test1, res1)) ++score;

    std::vector<int> res2 = topological_sort(4, test2);
    if(is_valid_topo(4, test2, res2)) ++score;

    std::vector<int> res3 = topological_sort(4, test3);
    if(is_valid_topo(4, test3, res3)) ++score;

    return true;
}
