#include "graph.h"

// Constructor
template <typename K, typename D>
            Graph<K,D>::Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges)
{
        for (int i = 0; i < keys.size(); i++) {
            Vertex<D,K> vertex = new Vertex();
            vertex->key = keys[i];
            vertex->data = data[i];
            vertex->color = "white";
            vertex->distance = 0;
            vertex->adj_list = edges[i];
            vertices[keys[i]] = {vertex};
        }
}

template <typename K, typename D>
Vertex*     Graph<K,D>::get(K k) 
{
    return &vertices[k]; //&（G.at(k))
}



