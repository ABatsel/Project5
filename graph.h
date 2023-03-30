#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
#include <string>

template<typename K, typename D>
struct Vertex {
    K key;
    D data;
    bool visited;
    int start_time;
    int finish_time;
    int distance;
    Vertex<K, D>* parent;
    Vertex<K, D>* next;
    std::vector<Vertex<K, D>*> adj_list;
    Vertex(K key, D data)
        : key(key), data(data), visited(false), start_time(0), finish_time(0), distance(INT_MAX), parent(nullptr), next(nullptr) {}
};

template<typename K, typename D>
class Graph {
public:
    Graph() {}
    Graph(const std::vector<K>& keys, const std::vector<D>& data, const std::vector<std::vector<K>>& edges);
    ~Graph() {
        for (auto& pair : vertices) {
            delete pair.second;
        }
    }
    Vertex<K,D>* get(K key);
    bool reachable(const K& u, const K& v) const;
    void print_path(const K& start_key, const K& end_key);
    std::string edge_class(K u, K v);
    void bfs_tree(K s);

private:
    std::unordered_map<K, Vertex<K, D>*> vertices;
    bool dfs(Vertex<K, D>* start, K end);
    void dfs_helper(Vertex<K, D>* start, int& time);
    void bfs(K start_key);
};

#include "graph.cpp"
#endif /* GRAPH_H */
