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
// Pre-condition: Initialize the map vertices and time.
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

//===================================================================================
// destructor for element of datatype K and D
// Pre-condition: Initialize the map vertices and time.
// Post-condition: All things delete from our graph.
// Params: none
//===================================================================================
template <class D, class K>
        Graph<D,K>::~Graph(){
    time = 0;
    for (auto& pair : vertices) {
        Vertex<D,K>* v = pair.second;
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
    for (int i = 0; i < keys.size(); i++) {
        Vertex<D,K>* v = new Vertex<D,K>(data[i], keys[i]);
        v->adj_list = new vector<K>(edges[i]);
        vertices.insert(make_pair(keys[i], v));
    }
}

//===================================================================================
// get vector<D,K> we store in the unordered_map vertices
// Pre-condition: The Graph object has been initialized and contains vertices, amd a
// valid key k of type K is passed as input to the function.
// Post-condition: If a vertex with key k exists in the graph, a pointer to the 
// corresponding Vertex<D,K> object is returned. If no vertex with key k exists 
// in the graph, a nullptr is returned. The state of the Graph object is not 
// modified by this function.
// Params: K keys: key with datatype k 
//===================================================================================
template <class D, class K>
Vertex<D,K>*    Graph<D,K>::get(K k) {
    if (vertices.count(k) <= 0)
    {
        return nullptr;
    }
    return vertices.at(k);
}

//===================================================================================
// Check the datatype K u and datatype K v is reach each or not
// Pre-condition: The Graph object has been initialized and contains vertices.
// Two valid keys u and v of type K are passed as input to the function.
// Post-condition: If both vertices with keys u and v exist in the graph and there 
// is a path from vertex u to vertex v, or from vertex v to vertex u, the function 
// returns true. Else return false.
// Params: K u: u with datatype k  K v: v with datatype k
//===================================================================================
template <class D, class K>
bool        Graph<D,K>::reachable( K u, K v ){
    if (get(u) == nullptr || get(v) == nullptr)
    {
        return false;
    };

    Vertex<D,K>* u_vertex = get(u);   
    for(int i = 0; i < u_vertex->adj_list->size(); i++)
    {
        if (u_vertex->adj_list->at(i) == v)
        {
            cout << v << " is reachable from " << u << endl;
            return true;
        }
    }
    
    Vertex<D,K>* v_vertex = get(v); 
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

//===================================================================================
// The breadth first search for the graph we build
// Pre-condition: The Graph object has been initialized and contains vertices. 
// A valid key start_key of type K is passed as input to the function.
// Post-condition: The color of each vertex is set to false. The distance of each 
// vertex is set to positive infinity. The parent of each vertex is set to nullptr 
// Params: K start_key : the key for bfs start for search
//===================================================================================
template <class D, class K>
void    Graph<D,K>::bfs( K start_key ){ 
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



//===================================================================================
// The depth first search for the graph we build
// Pre-condition: The graph object has been initialized, and all vertices in the 
// graph have been defined with data and keys, and there is no infinite loop in the
// graph.
// Post-condition: The depth-first search has been performed on the graph, and all 
// vertices have been visited, The parent of each vertex has been set to the 
// vertex that discovered it. The time variable has been updated to indicate 
// the time that each vertex was discovered and finished. 
// Params: None
//===================================================================================
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

//===================================================================================
// The dfs visit help the depth first search to be visit all vertices
// Pre-condition: An instance of Graph class has been created. The graph contains 
// at least one vertex.The input vertex u is a valid vertex in the graph.
// Post-condition: The depth-first search traversal of the graph is performed 
// starting from the vertex u. All vertices reachable from u have been visited, 
// and Each vertex has been assigned a discovery time and an end time
// Params: Vertex<D,K>* u : a verctex store D data and K key
//===================================================================================
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
}

//===================================================================================
// Print the sequence of path from s to v
// Pre-condition: The graph must have been initialized and constructed properly. Both 
// the start vertex key s and the destination vertex key v must be valid and exist 
// in the graph.h.
// Post-condition: If a path exists between the start vertex s and the destination 
// vertex v, the function will print the path from s to v. If there is no path from
//  s to v, the function will cout error
// Params: K u: u with datatype k  K v: v with datatype k
//===================================================================================
template <class D, class K>
void Graph<D,K>::print_path(K s, K v) {
    if (get(s) != nullptr && get(v) != nullptr) 
    {
        if (v == s) {
            cout << s;
        } 
        else if (vertices.at(v)->parent == nullptr) {
            cout << "no path from " << s << " to " << v << " exists.";
        } 
        else {
            print_path(s, vertices.at(v)->parent->key);
            cout << " -> " << v;
        }

    } 
    else {
        cout << "One or more vertices not found in graph" << endl;
    }
   
}

//===================================================================================
// find the u and v is what edge pattern
// Pre-condition: The graph must be initialized with vertices and edges. The keys 
// "u" and "v" passed as arguments must be valid keys of existing vertices in the graph.
// Post-condition: The DFS algorithm is called to visit all the vertices in the 
// graph. The discovery time and end time of each vertex are calculated during 
// the DFS algorithm. The function returns a string indicating the type of edge 
// between vertices "u" and "v
// Params: K u: u with datatype k  K v: v with datatype k
//===================================================================================
template <class D, class K>
string Graph<D,K>::edge_class(K u, K v)
{
    string result = "no edge";

    if(vertices.empty())
    {
        return result;
    }
    if (get(u) != nullptr && get(v) != nullptr) { 
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
    else
    {
        return "One or more vertices not found in graph\n";

    }
}

//===================================================================================
// print the sequence of bfs by their distance
// Pre-condition: The graph should be initialized with vertices and edges. The 
// start_key parameter should be a valid key of a vertex in the graph
// Post-condition: The BFS algorithm is executed starting from the vertex 
// with the key equal to start_key, and the vertices are printed in BFS order. The edges
//  in the BFS tree are identified as the tree edges, and they are printed as a sequence 
// of vertices in the tree order.
// Params: K u: u with datatype k  K v: v with datatype k
//===================================================================================
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
