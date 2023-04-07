//==================================================
// graph.cpp
// graph projecty
//
// Created by Ava Batsel, Rachel Zeng, 
//
//==================================================

#include "graph.h"

//===================================================================================
// Empty Constructor for element of datatype K and D
// Pre-condition: Initialize the unordered_map vertices and time.
// Post-condition: The time variable is initialized to 0, and the vertices method 
// of the Graph class is called, which initializes the data structures that will 
// store the graph's vertices.
// Params: none
//===================================================================================
template <class D, class K>
        Graph<D,K>::Graph(){
    time = 0;
    vertices();
}

// Destructor
template <class D, class K>
        Graph<D,K>::~Graph(){
    time = 0;
    for (auto& pair : vertices) {
        Vertex<D,K>* v = pair.second;
        delete v->adj_list;
        delete v;
    }
}

//===================================================================================
// Constructor for element of datatype K and D
// Pre-condition: provided three input vectors keys, data, and edges.
// Post-condition: The vertices of the graph are initialized using the input vectors.
// A new Vertex object is created, initialized with the corresponding data and key.
// The adjacency list for the vertex is set to the corresponding element of the edges 
// vector. The vertex is added to the graph's vertices map, with its key as the key 
// in the map and the Vertex object as the value.
// Params: vector<K> keys: vectors store k keys and vector<D> store d datas, and 
// vector<vector<k>> edges: store the vectors of edges vector
//===================================================================================
template <class D, class K>
        Graph<D,K>::Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges){
    // Add vertices to the graph
    for (int i = 0; i < keys.size(); i++) {
        Vertex<D,K>* v = new Vertex<D,K>(data[i], keys[i]);
        v->adj_list = new vector<K>(edges[i]);
        vertices.insert(make_pair(keys[i], v));
    }
}

//===================================================================================
//  get vector<D,K> we store in the unordered_map vertices
// Pre-condition: The Graph object has been initialized and contains vertices, amd a
// valid key k of type K is passed as input to the function.
// Post-condition: 
// Params: K keys: 
//===================================================================================
template <class D, class K>
Vertex<D,K>*    Graph<D,K>::get(K k) {
    if (vertices.count(k) <= 0)
    {
        return nullptr;
    }
    return vertices.at(k); //&（ G.at(k))
}


template <class D, class K>
bool        Graph<D,K>::reachable( const K u, const K v ) const{
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
void    Graph<D,K>::bfs( K start_key ) const{ 
    for(auto it = vertices.begin(); it != vertices.end();it++)
    {
        Vertex<D,K>* define_vertex = it->second;
        define_vertex->color = false;
        define_vertex->distance = numeric_limits<double>::infinity();
        define_vertex->parent = nullptr;
    }
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
void Graph<D,K>::dfs() {
    for(auto it = vertices.begin(); it != vertices.end();it++)
    {
        Vertex<D,K>* define_vertex = it->second;
        define_vertex->color = false;
        define_vertex->parent = nullptr;
    }
    time = 0;
    for(auto it = vertices.begin(); it != vertices.end();it++)
    {
        Vertex<D,K>* temp_v = it->second;
        if(temp_v->color == false) //not discovered
        {
            dfs_visit(temp_v);
        }
    }
}

template <class D, class K>
void Graph<D,K>::dfs_visit(Vertex<D,K>* u) {
    time = time + 1;
    u->discovery_time = time;
    u->color = true; // discovered
    for (int i = 0; i < u->adj_list->size(); i++) {
        Vertex<D,K>* v = vertices.at(u->adj_list->at(i));
        if (v->color == false) { // not discovered
            v->parent = u;
            dfs_visit(v);
        }
    }
    time = time + 1;
    u->end_time = time;
    u->color == true;
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
string Graph<D,K>::edge_class(K u, K v)
{
    string result = "no edge";
    if(vertices.empty())
    {
        return result;
    } 
    
    dfs();
    Vertex<D,K>* u_vertex = vertices.at(u);
    Vertex<D,K>* v_vertex = vertices.at(v);
    if((u_vertex != nullptr ) && (v_vertex != nullptr)){
       
        if (v_vertex->parent == u_vertex) {
            result =  "tree edge";
        } 
        else if ((v_vertex->discovery_time <= u_vertex->discovery_time) && (u_vertex->end_time <= v_vertex->end_time)) {
            result = "back edge";
            } 
        else if ((v_vertex->discovery_time > u_vertex -> discovery_time) && (u_vertex->end_time > v_vertex->end_time)) {
            result = "forward edge";
        } 
        else if ((u_vertex->discovery_time > v_vertex->discovery_time) && (u_vertex->end_time > v_vertex->end_time)){
            result = "cross edge";
        } 
        else {
            result = "no edge";
        }
    }
    return result;
}

template<class D, class K>
void    Graph<D,K>::bfs_tree(K start_key)
{
    bfs(start_key);
    
    Vertex<D,K>* start_vertex = vertices.at(start_key);
    queue<Vertex<D,K>*> q;
    q.push(start_vertex);
    int level = 0;
    
    while (!q.empty()) {
        Vertex<D,K>* u = q.front();
        q.pop();
        if ( u->distance > level) {
            cout << "\n";
            level++;
        }
        if ( (!q.empty() && (q.front())->distance > u->distance) || (u->key == start_key) )
        {
            cout << u->key;
        }
        else if ( q.empty() )
        {
           cout << u->key; 
        }
        else
        {
            cout << u->key << " ";
        }

        for (int i = 0; i < u->adj_list->size(); i++) {
            Vertex<D,K>* v = vertices.at(u->adj_list->at(i));
            if (v->parent == u) {
                q.push(v);
            }
        }
    }
    if (!q.empty())
    {
        cout << "\n";
    }
    
}
