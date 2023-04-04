#include "graph.h"

// Constructor
template <class D, class K>
            Graph<D,K>::Graph(vector<D> data, vector<K> key, vector<vector<K>> edges)
{
        for (int i = 0; i < key.size(); i++) {
            Vertex<D,K> vertex = new Vertex<D,K>(data[i], key[i]);
            for (int j = 0; j < edges[i].size; j++){
                vertex->adj_list.push_back(edges[i][j]);
            }
            vertices[key[i]] = {key[i], make_pair{vertex}}
            //vertices[key[i]] = {makepair{vertex}};
        }
}

template <class D, class K>
Vertex<D,K>*    Graph<D,K>::get(K k) 
{
    return &(vertices.at(k)); //&（G.at(k))
}



