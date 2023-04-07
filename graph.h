#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
#include <string>
#include <list>
#include <map>

using namespace std;

template<class D, class K>
class Vertex 
{
public:
    K               key;
    D               data; 
    bool            color;
    double          distance; 
    int             discovery_time; 
    int             end_time; 
    vector<K>*      adj_list;
    Vertex<D,K>*    parent;

    Vertex<D,K>(D d, K k){
        data = d; 
        key = k; 
        color = false; //undiscovered
        distance = numeric_limits<double>::infinity();
        discovery_time = 0; 
        end_time = 0; 
        this->parent = nullptr;}

    Vertex<D,K>(){
        data = D(); 
        key = K(); 
        color = false; 
        distance = numeric_limits<double>::infinity();
        discovery_time = 0; 
        end_time = 0; 
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
bool            reachable( K u, K v ) ;
void            bfs( K start_key );
void            dfs() ; //not void 
void            dfs_visit(Vertex<D,K>* u);
void            print_path( K start_key, K end_key ); //not void
string          edge_class( K u, K v ); //need dfs 
void            bfs_tree( K s );

private:
map<K, Vertex<D,K>*> vertices; //key -> vertex
int     time;
};

#endif