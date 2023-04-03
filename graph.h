#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
#include <string>
using namespace std;

template<typename D, typename K>
class Graph {
public:                      
                Graph();
                Graph(vector<D> data, vector<K> key, vector<vector<K>> edges);
                ~Graph();
unordered_map<K, Vertex>*         get(K key);
bool            reachable(const K& u, const K& v) const;
void            print_path(const K& start_key, const K& end_key);
std::string     edge_class(K u, K v);
void            bfs_tree(K s);
void            bfs(K start_key);

struct Vertex{ //node in graph 
    K           key;
    D           data; 
    string      color;
    int         distance;
    list <D, K> adj_list;
    };
private:
unordered_map<K, Vertex> vertices; //key -> vertex

};

#endif