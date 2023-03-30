#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <queue>

template <typename K, typename D>
class Graph {
public:
    // Constructor
    Graph(const std::vector<K>& keys, const std::vector<D>& data, const std::vector<std::vector<K>>& edges);

    // Method to get a pointer to a vertex given a key
    // Returns nullptr if the vertex does not exist in the graph
    const D* get(const K& key) const;

    // Method to check if there is a path from vertex u to vertex v
    bool reachable(const K& u, const K& v) const;

    // Method to print a shortest path from vertex u to vertex v
    void print_path(const K& u, const K& v) const;

    // Method to get the classification of the edge from vertex u to vertex v
    std::string edge_class(const K& u, const K& v) const;

    // Method to print the BFS tree starting from vertex s
    void bfs_tree(const K& s) const;

private:
    // Define a vertex struct to hold information about each vertex
    struct Vertex {
        D data; // vertex data
        std::unordered_map<K, int> neighbors; // maps adjacent vertex keys to edge weights
        bool visited; // flag to mark if the vertex has been visited
        // add any other information you want to store about a vertex here
    };

    std::unordered_map<K, Vertex> vertices; // maps vertex keys to vertex structs

    // Add any helper methods you need here
};

#endif
