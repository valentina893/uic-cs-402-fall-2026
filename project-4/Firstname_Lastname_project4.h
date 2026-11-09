#ifndef FIRSTNAME_LASTNAME_PROJECT4
#define FIRSTNAME_LASTNAME_PROJECT4

#include <vector>
#include <functional>
#include <unordered_map>

// Struct Declarations

// Struct to capture (weighted) edges in a graph; used in Dijkstra's algorithm
// as well.
struct Edge {
    int from;
    int to;
    int weight; // default = 2 if unweighted graph

    Edge(int f, int t, int w = 2) {
        from = f;
        to = t;
        weight = w;
    }
};


// struct to capture nodes in the graph such that you can recover the path
// length from source to node id, as well as the actual path from the
// source to each node.
struct Node {
    int id;
    int path_cost;
    int pred;
    bool operator> (const Node&) const;
    bool operator>=(const Node&) const;
    bool operator==(const Node&) const;
    bool operator< (const Node&) const;
    bool operator<=(const Node&) const;
    bool operator!=(const Node&) const;

};

inline bool Node::operator>=(const Node& node) const {return path_cost >= node.path_cost; }
inline bool Node::operator> (const Node& node) const {return path_cost > node.path_cost; }
inline bool Node::operator==(const Node& node) const {return path_cost == node.path_cost; }
inline bool Node::operator< (const Node& node) const {return path_cost < node.path_cost; }
inline bool Node::operator<=(const Node& node) const {return path_cost <= node.path_cost; }
inline bool Node::operator!=(const Node& node) const {return path_cost != node.path_cost; }


struct GridNode {
    int x;
    int y;
    double path_cost;
    int pred_x;
    int pred_y;
    bool operator> (const GridNode&) const;
    bool operator>=(const GridNode&) const;
    bool operator==(const GridNode&) const;
    bool operator< (const GridNode&) const;
    bool operator<=(const GridNode&) const;
    bool operator!=(const GridNode&) const;
};

inline bool GridNode::operator> (const GridNode& node) const { return path_cost > node.path_cost; }
inline bool GridNode::operator>=(const GridNode& node) const { return path_cost >= node.path_cost; }
inline bool GridNode::operator==(const GridNode& node) const { return path_cost == node.path_cost; }
inline bool GridNode::operator< (const GridNode& node) const { return path_cost < node.path_cost; }
inline bool GridNode::operator<=(const GridNode& node) const { return path_cost <= node.path_cost; }
inline bool GridNode::operator!=(const GridNode& node) const { return path_cost != node.path_cost; }

struct GridEdge {
    int from_x;
    int from_y;
    int to_x;
    int to_y;
};

std::vector<int> topological_sort(int n, std::vector<Edge> edges);
std::vector<int> dag_single_source(int n, std::vector<Edge> edges, int source);
std::vector<Node> dijkstras_algorithm(int n, std::vector<Edge> edges, int source);
double heuristic_cost(GridNode start, GridNode dest);

std::vector<GridNode> a_star_algorithm(
    int m, 
    int n, 
    std::vector<GridEdge> edges, 
    GridNode source, 
    GridNode target,
    std::function<double(GridNode,GridNode)> h
);

// testing methods

bool is_valid_topo(int n, std::vector<Edge> edges, std::vector<int> order);
bool test_top_order(); 

#endif
