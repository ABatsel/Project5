#include "graph.h"

// Constructor
template <class D, class K>
            Graph<D,K>::Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges)
{
    // Add vertices to the graph
    for (int i = 0; i < keys.size(); i++) {
        Vertex<D,K> v(data[i], keys[i]);
        vertices.insert({keys[i], v});
    }

    // Add edges to the graph
    for (int i = 0; i < edges.size(); i++) {
        Vertex<D,K>& temp_vertex = vertices.at(keys[i]);
        for (int j = 0; j < edges[i].size(); j++) {
            temp_vertex.adj_list.push_back(edges[i][j]);
        }
    }
}

template <class D, class K>
Vertex<D,K>*    Graph<D,K>::get(K k) 
{
    if (vertices.count(k) <= 0)
    {
        return nullptr;
    }
    return &(vertices.at(k)); //&（ G.at(k))
}

template <class D, class K>
bool        Graph<D,K>::reachable( K u, K v )
{
    if (vertices.count(u) == 0)
    {
        return false;
    }

    Vertex<D,K>& u_vertex = vertices.at(u);
    if(count(u_vertex.adj_list.begin(), u_vertex.adj_list.end(), v) == 0)
    {
        return false;
    }

    Vertex<D,K>& v_vertex = vertices.at(v);
     if(count(u_vertex.adj_list.begin(), u_vertex.adj_list.end(), v) == 0)
    {
        return false;
    }
   
    cout << v << " is reachable from " << u << endl;
    return true;

}