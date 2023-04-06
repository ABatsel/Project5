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
    Vertex<D,K>* start_vertex = vertices.at(start_key);
    queue<Vertex<D,K>*> q;
    start_vertex-> color = true; //discovered = true
    start_vertex-> distance = 0;
    start_vertex-> parent = nullptr; 
    q.push(start_vertex); //enqueue
    while ( !q.empty() )
    {

        Vertex<D,K>* u = q.front();
        q.pop();
        for( int i = 0; i < u->adj_list->size(); i++ )
        {
            Vertex<D,K>* temp_vertex = vertices.at(u->adj_list->at(i));
            if(temp_vertex->color == false) //not discovered
            {
                temp_vertex->color = true; //true = gray = discovered
                temp_vertex->distance = u->distance + 1; // distance = distance + 1
                temp_vertex->parent = u; //pi = u
                q.push(temp_vertex);
            }
        }
        u->color = true; //discovered
    }
}




template <class D, class K>
void Graph<D,K>::dfs(K start_key) const {
    Vertex<D,K>* start_vertex = vertices.at(start_key);
    dfs_visit(start_vertex);
}

template <class D, class K>
void Graph<D,K>::dfs_visit(Vertex<D,K>* u) const {
    u->color = true; // discovered
    cout << u->key << endl;
    for (int i = 0; i < u->adj_list->size(); i++) {
        Vertex<D,K>* v = vertices.at(u->adj_list->at(i));
        if (v->color == false) { // not discovered
            v->parent = u;
            dfs_visit(v);
        }
    }
}


template <class D, class K>
void Graph<D,K>::print_path(K s, K v) {
    if (v == s) {
        cout << s;
    } else if (vertices.at(v)->parent == nullptr) {
        cout << "no path from " << s << " to " << v << " exists." << endl;
    } else {
        print_path(s, vertices.at(v)->parent->key);
        cout << " -> " << v;
    }
}



template <class D, class K>
void    Graph<D,K>::bfs_tree( K start_key )
{ 
    Vertex<D,K>* start_vertex = vertices.at(start_key);
    queue<Vertex<D,K>*> q;
    start_vertex-> color = true; //discovered = true
    start_vertex-> distance = 0;
    start_vertex-> parent = nullptr; 
    q.push(start_vertex); //enqueue
    cout << start_key << endl; // print starting key
    cout << "1" << endl;
    while ( !q.empty() )
    {
        cout << "2" << endl;

        Vertex<D,K>* u = q.front();
        q.pop();
        for( int i = 0; i < u->adj_list->size(); i++ )
        {
            cout << "3" << endl;
            Vertex<D,K>* temp_vertex = vertices.at(u->adj_list->at(i));
            //Vertex<D,K>* temp_vertex = vertices.at(i);
            cout << temp_vertex->color << "HHHHHHHH" << endl; 
            //if(temp_vertex->color == false) //not discovered //never enters for loop
            if ( !(vertices.at(u->adj_list->at(i))) )
            {
                cout << "4" << endl;

                temp_vertex->color = true; //true = gray = discovered
                temp_vertex->distance = u->distance + 1; // distance = distance + 1
                temp_vertex->parent = u; //pi = u
                //cout << u->adj_list->at(i)->key; //want to print the key, why does u->adj_list not work
                cout << temp_vertex->key;
                q.push(temp_vertex);
            }
        }
        u->color = true; //discovered
        if ( !q.empty() && q.front()->distance == (u->distance)+1)        
            cout << endl;     //start a new row 
    }
}

