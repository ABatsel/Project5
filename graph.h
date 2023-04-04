#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
#include <string>
#include <list>

using namespace std;

template<class D, class K>
class Vertex 
{
public:
    K               key;
    D               data; 
    bool            color;
    int             distance;
    vector<K>       adj_list;
    Vertex<D,K>*    parent;

    Vertex<D,K>(D d, K k){
        data = d; 
        key = k; 
        color = false; 
        distance = 0; 
        this->parent = nullptr;}
private:
};

template<class D, class K>
class Graph 
{
public:     
                Graph();
                Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges);
                ~Graph();
Vertex<D,K>*    get(K key);
bool            reachable( K u, K v );
void            print_path( K start_key, K end_key );
std::string     edge_class( K u, K v );
void            bfs_tree( K s );
void            bfs( K start_key );

private:
unordered_map<K, Vertex<D,K>> vertices; //key -> vertex
};

#endif