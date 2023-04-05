#include "graph.h"

// Empty Constructor
template <class D, class K>
        Graph<D,K>::Graph()
{
    vertices();
}

// Destructor
template <class D, class K>
        Graph<D,K>::~Graph()
{
    for (auto& pair : vertices) {
        Vertex<D,K>* v = pair.second;
        delete v->adj_list;
        delete v;
    }
}
// Constructor
template <class D, class K>
        Graph<D,K>::Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges)
{
    // Add vertices to the graph
    for (int i = 0; i < keys.size(); i++) {
        Vertex<D,K>* v = new Vertex<D,K>(data[i], keys[i]);
        v->adj_list = new vector<K>(edges[i]);
        vertices.insert(make_pair(keys[i], v));
    }

    for (auto& pair : vertices) {
        K key = pair.first;
        Vertex<D,K>* v = pair.second;
        for (K adj_key : *(v->adj_list)) {
            Vertex<D,K>* adj_v = vertices[adj_key];
            adj_v->parent = v;
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
    return vertices.at(k); //&（ G.at(k))
}

template <class D, class K>
bool        Graph<D,K>::reachable( const K u, const K v ) const
{
    if (vertices.count(u) == 0 || vertices.count(v) == 0)
    {
        return false;
    }

    Vertex<D,K>* u_vertex = vertices.at(u);
    if(count(u_vertex->adj_list->begin(), u_vertex->adj_list->end(), v) != 0)
    {
        cout << v << " is reachable from " << u << endl;
        return true;
    }

    Vertex<D,K>* v_vertex = vertices.at(v);
     if(count(v_vertex->adj_list->begin(), v_vertex->adj_list->end(), u) != 0)
    {
        cout << u << " is reachable from " << v << endl;
        return true;
    }
    return false;

}

template <class D, class K>
void    Graph<D,K>::bfs( K start_key ) const
{
    
}