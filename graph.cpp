#include <graph.h>

// Constructor
template <typename K, typename D>
Graph<K,D>::Graph(std::vector<K> keys, std::vector<D> data, std::vector<std::vector<K>> edges) {
    // Create Vertex objects for each key/data pair and add them to the vertices map
    for (int i = 0; i < keys.size(); i++) {
        Vertex<K, D>* vertex = new Vertex<K, D>(keys[i], data[i]);
        vertices[keys[i]] = vertex;
    }

    // Add edges to the adjacency lists of the corresponding vertices
    for (int i = 0; i < edges.size(); i++) {
        K key = keys[i];
        Vertex<K, D>* vertex = vertices[key]; // Get the Vertex object for the current key
        for (int j = 0; j < edges[i].size(); j++) {
           // Get the key of the adjacent vertex
            K adj_key = edges[i][j]; 
            // Get the Vertex object for the adjacent vertex
            Vertex<K, D>* adj_vertex = vertices[adj_key]; 
            // Add the adjacent vertex to the current vertex's adjacency list
            vertex->adj_list.push_back(adj_vertex); 
        }
    }
}


//get method
template <typename K, typename D>
Vertex<K,D>* Graph<K,D>::get(K key) {
    // Check if the key is in the vertices map
    if (vertices.count(key) > 0) { 
       // Return the corresponding Vertex objec
       return vertices[key]; t
    } else {
        // Key not found, return null pointer
        return nullptr; 
    }
}

//Reachable method
template <typename K, typename D>
bool Graph<K, D>::reachable(K u, K v) {
    // Get the starting vertex for the search
    Vertex<K, D>* start = vertices[u];
    // Initialize all vertices as unvisited
    for (auto& pair : vertices) {
        pair.second->visited = false;
    }
    // Perform a depth-first search from the starting vertex
    return dfs(start, v);
}



//BFS method 
template<typename K, typename D>
void Graph<K,D>::bfs(K start_key) {
    // Initialize all vertices as unvisited and with infinite distance from the start vertex
    for (auto it = vertices.begin(); it != vertices.end(); it++) {
        it->second->visited = false;
        it->second->distance = INT_MAX;
    }

    // Get the start vertex
    Vertex<K, D>* start_vertex = vertices[start_key];

    // Initialize the distance of the start vertex to be 0
    start_vertex->distance = 0;

    // Initialize the queue with the start vertex
    std::queue<Vertex<K, D>*> q;
    q.push(start_vertex);

    // Perform BFS
    while (!q.empty()) {
        // Get the next vertex from the queue
        Vertex<K, D>* current_vertex = q.front();
        q.pop();

        // Mark the current vertex as visited
        current_vertex->visited = true;

        // Update the distance of adjacent vertices and add them to the queue
        for (auto it = current_vertex->adj_list.begin(); it != current_vertex->adj_list.end(); it++) {
            Vertex<K, D>* adj_vertex = *it;
            if (!adj_vertex->visited) {
                adj_vertex->distance = current_vertex->distance + 1;
                q.push(adj_vertex);
            }
        }
    }
}




//print_path method

template <typename K, typename D>
void Graph<K,D>::print_path(const K& start_key, const K& end_key) {
    // Perform breadth-first search to find shortest path
    bfs(start_key);
    
    // Check if there exists a path from start vertex to end vertex
    if (vertices[end_key]->parent == nullptr) {
        std::cout << "No path exists from " << start_key << " to " << end_key << std::endl;
        return;
    }
    
    // Traverse the parent pointers to construct the path
    std::vector<K> path;
    Vertex<K,D>* curr_vertex = vertices[end_key];
    while (curr_vertex != nullptr) {
        path.push_back(curr_vertex->key);
        curr_vertex = curr_vertex->parent;
    }
    
    // Print the path in reverse order
    for (int i = path.size() - 1; i > 0; i--) {
        std::cout << path[i] << " -> ";
    }
    std::cout << path[0] << std::endl;
}



/*  Precondition: The Graph object has been constructed and 
    contains at least two vertices with the given keys u and v.

    Postcondition: The edge classification of the edge from 
    vertex u to v has been determined and returned as a string.*/ 


// Method to get the classification of the edge from vertex u to vertex v
template<typename K, typename D>
std::string Graph<K,D>::edge_class(K u, K v) {
    Vertex<K, D>* source = vertices[u];
    Vertex<K, D>* dest = vertices[v];

    if (source->parent == dest) {
        return "tree edge";
    } else if (dest->visited && source->visited && source->start_time < dest->start_time && source->finish_time > dest->finish_time) {
        return "back edge";
    } else if (dest->visited && source->visited && source->start_time > dest->start_time) {
        return "cross edge";
    } else if (dest->visited && !source->visited) {
        return "forward edge";
    } else {
        return "no edge";
    }
}

// BFS tree method 
// Method to print the BFS tree starting from vertex s
template<typename K, typename D>
void Graph<K, D>::bfs_tree(K s) {
    // Mark all vertices as not visited
    std::unordered_map<K, bool> visited;
    for (auto const& pair : vertices) {
        visited[pair.first] = false;
    }

    // Create a queue for BFS
    std::queue<Vertex<K, D>*> queue;

    // Mark the source vertex as visited and enqueue it
    visited[s] = true;
    queue.push(vertices[s]);

    // Initialize depth counter and last node at current depth
    int depth = 0;
    Vertex<K, D>* last = vertices[s];

    while (!queue.empty()) {
        // Dequeue a vertex from queue and print it
        Vertex<K, D>* vertex = queue.front();
        queue.pop();

        // If the depth changes, print a new line
        if (vertex == last->next) {
            std::cout << std::endl;
            depth++;
            last = vertex;
        }

        // Print the key of the vertex
        std::cout << vertex->key << " ";

        // Enqueue all adjacent vertices of the dequeued vertex that are not visited yet
        for (Vertex<K, D>* adj_vertex : vertex->adj_list) {
            if (!visited[adj_vertex->key]) {
                visited[adj_vertex->key] = true;
                adj_vertex->next = vertex->next;
                queue.push(adj_vertex);
            }
        }
    }
}


// Add any additional helper methods you need here

// Explicitly instantiate the template class for any types you plan to use
template class Graph<int, int>;
template class Graph<std::string, std::string>;
// Add more instantiations as needed
