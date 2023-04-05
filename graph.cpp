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
    };

    Vertex<D,K>* u_vertex = vertices.at(u);   
    for(int i = 0; i < u_vertex->adj_list->size(); i++)
    {
        if (u_vertex->adj_list->at(i) == v)
        {
            cout << v << " is reachable from " << u << endl;
            return true;
        }
    }
    
    Vertex<D,K>* v_vertex = vertices.at(v); 
    for(int i = 0; i < v_vertex->adj_list->size(); i++)
    {
        if (v_vertex->adj_list->at(i) == u)
        {
            cout << u << " is reachable from " << v << endl;
            return true;
        }
    }
    return false;
}

template <class D, class K>
void    Graph<D,K>::bfs( K start_key ) const
{
    Vertex<D,K>* start_vertex = vertices.begin();
    queue<Vertex<D,K>*> q;
    q.push(start_vertex);
    while ( !q.empty() )
    {
        Vertex<D,K>* u = q.front();
        for( int i = 0; i < u->adj_list->size(); i++ )
        {
            Vertex<D,K>* temp_vertex = vertices.at(i);
            if(temp_vertex->color == false)
            {
                temp_vertex->color = true;
                temp_vertex->distance += 1;
                temp_vertex->parent = u;
                q.push(temp_vertex);
            }
        }
        u->color = true;
    }
}