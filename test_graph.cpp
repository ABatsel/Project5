//
//  test_graph_example.cpp
//  CS 271 Graph Project: Example Test File
//
//  Created by Rachel Zeng, Ava Batsel, 
//

#include <fstream>
#include <sstream>
#include "graph.cpp"

Graph<string, string>* generate_graph(string fname){
    string line;
    ifstream infile(fname);
    vector<string> keys = {};
    vector<string> data = {};
    vector<vector<string>> adjs = {};
    if(infile.is_open()){
        while(getline(infile, line)){
            unsigned long delim = line.find(":");
            string key = line.substr(0, delim);
            string adj = line.substr(delim+1);
            
            keys.push_back(key);
            data.push_back(key + " data");
            delim = adj.find(",");
            vector<string> adj_lst = {};
            while(delim != string::npos){
                adj_lst.push_back(adj.substr(0, delim));
                adj = adj.substr(delim+1);
                delim = adj.find(",");
            }
            adj_lst.push_back(adj);
            adjs.push_back(adj_lst);
        }
    }
    Graph<string,string>* G = new Graph<string, string>(keys, data, adjs);
    return G;
}

void test_get(Graph<string,string>* G) {
    try {
        if(G->get("S")==nullptr || G->get("S")->data != "S data") {
            cout << "Incorrect result getting vertex \"s\"" << endl; 
        }
        if(G->get("T")==nullptr || G->get("T")->data != "T data") {
            cout << "Incorrect result getting vertex \"s\"" << endl; 
        }
        if(G->get("W")==nullptr || G->get("W")->data != "W data") {
            cout << "Incorrect result getting vertex \"s\"" << endl; 
        }
        if(G->get("a") != nullptr) {
            cout << "Incorrect result getting non-existant vertex \"a\"" << endl;
        }
        if(G->get("D") != nullptr) {
            cout << "Incorrect result getting non-existant vertex \"D\"" << endl;
        }
        if(G->get("") != nullptr) {
            cout << "Incorrect result getting non-existant vertex \"\"" << endl;
        }
    } catch(exception& e) {
        cerr << "Error getting vertex from graph : " << e.what() << endl;
    }
    try {
        vector<int> keys = {1,2,3,4,5};
        vector<int> data = {5,4,3,2,1};
        vector<vector<int>> adjs = {{2,3},{4},{3},{5},{1}};
        Graph<int,int>* int_G = new Graph<int, int>(keys, data, adjs);
        if(int_G->get(1)==nullptr || int_G->get(1)->data != 5) {
            cout << "Incorrect result getting vertex \"1\"" << endl; 
        }
        if(int_G->get(2)==nullptr || int_G->get(2)->data != 4) {
            cout << "Incorrect result getting vertex \"2\"" << endl; 
        }
        if(int_G->get(10) != nullptr) {
            cout << "Incorrect result getting non-existant vertex \"10\"" << endl;
        }
    } catch(exception& e) {
        cerr << "Error getting vertex from int graph : " << e.what() << endl;
    }

    try {
        vector<double> keys = {1.34,2.25,3.87,4.26,5.34};
        vector<double> data = {5.33,4.22,3.11,2.55,1.44};
        vector<vector<double>> adjs = {{2.25,3.87},{4.26},{3.87},{5.34},{1.34}};
        Graph<double,double>* double_G = new Graph<double, double>(keys, data, adjs);
        if(double_G->get(1.34)==nullptr || double_G->get(1.34)->data != 5.33) {
            cout << "Incorrect result getting vertex \"1.34\"" << endl; 
        }
        if(double_G->get(2.25)==nullptr || double_G->get(2.25)->data != 4.22) {
            cout << "Incorrect result getting vertex \"2.25\"" << endl; 
        }
        if(double_G->get(10.23) != nullptr) {
            cout << "Incorrect result getting non-existant vertex \"10.23\"" << endl;
        }
    } catch(exception& e) {
        cerr << "Error getting vertex from double graph : " << e.what() << endl;
    }

    try {
        vector<char> keys = {'a', 'b', 'c','d','e'};
        vector<char> data = {'e', 'd', 'c','b','a'};
        vector < vector<char> > adjs = {{'b','d'},{'a'},{'c'},{'a'},{'d'}};
        Graph<char,char>* char_G = new Graph<char, char>(keys, data, adjs);
        if(char_G->get('a')==nullptr || char_G->get('a')->data != 'e') {
            cout << "Incorrect result getting vertex \"a\"" << endl; 
        }
        if(char_G->get('b')==nullptr || char_G->get('b')->data != 'd') {
            cout << "Incorrect result getting vertex \"b\"" << endl; 
        }
        if(char_G->get('H') != nullptr) {
            cout << "Incorrect result getting non-existant vertex \"H\"" << endl;
        }
    } catch(exception& e) {
        cerr << "Error getting vertex from double graph : " << e.what() << endl;
    }
}

void test_reachable(Graph<string,string>* G) {
    try {
        if(!G->reachable("R", "V")) {
            cout << "Incorrectly identified adjacent vertex \"V\" as unreachable from \"R\"" << endl;
        }
        if(!G->reachable("X", "W")) {
            cout << "Incorrectly identified \"W\" as unreachable from \"X\"" << endl;
        }
        if(G->reachable("S", "A")) {
            cout << "Incorrectly identified non-existant vetex \"A\" as reachable from \"S\"" << endl;
        }
        if(G->reachable("", "")) {
            cout << "Incorrectly identified non-existant vetex \"\" as reachable from \"\"" << endl;
        }       
        if(G->reachable("X", "")) {
            cout << "Incorrectly identified non-existant vetex \"X\" as reachable from \"\"" << endl;
        } 
        if(G->reachable("", "W")) {
            cout << "Incorrectly identified non-existant vetex \"\" as reachable from \"W\"" << endl;
        } 
    } catch(exception& e) {
        cerr << "Error testing reachable : " << e.what() << endl;
    }
    try {
        vector<char> keys = {'a', 'b', 'c','d','e'};
        vector<char> data = {'e', 'd', 'c','b','a'};
        vector < vector<char> > adjs = {{'b','d'},{'a'},{'c'},{'a'},{'d'}};
        Graph<char,char>* char_G = new Graph<char, char>(keys, data, adjs);
        if(!char_G->reachable('a','d')) {
            cout << "Incorrectly identified adjacent vertex \"a\" as unreachable from \"b\"" << endl;
        }
        if(!char_G->reachable('b','a')) {
            cout << "Incorrectly identified \"b\" as unreachable from \"a\"" << endl;
        }
        if(char_G->reachable('a','s')) {
            cout << "Incorrectly identified non-existant vetex \"a\" as reachable from \"s\"" << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing char graph reachable : " << e.what() << endl;
    }
    try {
        vector<int> keys = {1,2,3,4,5};
        vector<int> data = {5,4,3,2,1};
        vector<vector<int>> adjs = {{2,3},{4},{3},{5},{1}};
        Graph<int,int>* int_G = new Graph<int, int>(keys, data, adjs);
        if(!int_G->reachable(1,2)) {
            cout << "Incorrectly identified adjacent vertex \"1\" as unreachable from \"2\"" << endl;
        }
        if(!int_G->reachable(5,4)) {
            cout << "Incorrectly identified \"5\" as unreachable from \"4\"" << endl;
        }
        if(int_G->reachable(10,5)) {
            cout << "Incorrectly identified non-existant vetex \"10\" as reachable from \"5\"" << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing int graph reachable : " << e.what() << endl;
    }
}

void test_bfs(Graph<string,string>* G) {
    try {
        G->bfs("T");
        string vertices[8] = {"V", "R", "S", "W", "T", "X", "U", "Y"};
        int distances[8] = {3,2,1,1,0,2,1,2};
        for(int i = 0; i < 8; i++){
            if(G->get(vertices[i])==nullptr || G->get(vertices[i])->distance!=distances[i]) {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"1\"" << endl;
                cout<< G->get(vertices[i])->distance << endl; 
            }
        }
    } catch(exception& e) {
        cerr << "Error testing bfs : " << e.what() << endl;
    } 
    try {
        vector<char> keys = {'a', 'b', 'c','d','e'};
        vector<char> data = {'e', 'd', 'c','b','a'};
        vector < vector<char> > adjs = {{'b','c'},{'d'},{'c'},{'e'},{'a'}};
        Graph<char,char>* char_G = new Graph<char, char>(keys, data, adjs);
        char_G->bfs('a');
        char vertices[5] = {'a', 'b', 'c','d','e'};
        int distances[5] = {0,1,1,2,3};
        for(int i = 0; i < 5; i++){
            if(char_G->get(vertices[i])==nullptr || char_G->get(vertices[i])->distance!=distances[i]) {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"a\"" << endl;
                cout<< char_G->get(vertices[i])->distance << endl; 
            }
        }
    } catch(exception& e) {
        cerr << "Error testing char bfs : " << e.what() << endl;
    }

    try {
        vector<int> keys = {1,2,3,4,5};
        vector<int> data = {5,4,3,2,1};
        vector<vector<int>> adjs = {{2,3},{4},{3},{5},{1}};
        Graph<int,int>* int_G = new Graph<int, int>(keys, data, adjs);
        int_G->bfs(1);
        int vertices[5] = {1,2,3,4,5};
        int distances[5] = {0,1,1,2,3};
        for(int i = 0; i < 5; i++){
            if(int_G->get(vertices[i])==nullptr || int_G->get(vertices[i])->distance!=distances[i]) {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"1\"" << endl;
                cout<< int_G->get(vertices[i])->distance << endl; 
            }
        }
    } catch(exception& e) {
        cerr << "Error testing int bfs : " << e.what() << endl;
    } 
}

void test_print_path(Graph<string,string>* G) {
    try {

        //test 1 regular path 
        stringstream buffer1;
        streambuf* prevbuf1 = cout.rdbuf(buffer1.rdbuf());
        G->print_path("T", "V");
        cout.rdbuf(prevbuf1);
        if(buffer1.str()!="T -> S -> R -> V") {
            cout << "Incorrect path from vertex \"T\" to vertex \"V\". Expected: T -> S -> R -> V but got : " << buffer1.str() << endl;
        }  
        //test 2 no path check
        stringstream buffer2;
        streambuf* prevbuf2 = cout.rdbuf(buffer2.rdbuf());
        G->print_path("W", "T");
        cout.rdbuf(prevbuf2);
        if(buffer2.str()!= "no path from W to T exists.") {
            cout << "Incorrect path from vertex \"W\" to vertex \"T\". Expected: no path from W to T exists. but got : " << buffer2.str() << endl;
        }  
        //test 3 check same value to same value 
        stringstream buffer3;
        streambuf* prevbuf3 = cout.rdbuf(buffer3.rdbuf());
        G->print_path("W", "W");
        cout.rdbuf(prevbuf3);
        if(buffer3.str()!= "W") {
            cout << "Incorrect path from vertex \"W\" to vertex \"W\". Expected: W. but got : " << buffer3.str() << endl;
        } 
        //test 4 check value vs. empty string 
        stringstream buffer4;
        streambuf* prevbuf4 = cout.rdbuf(buffer4.rdbuf());
        G->print_path("W", "");
        cout.rdbuf(prevbuf4);
        if(buffer4.str() != "One or more vertices not found in graph\n") {
            cout << "Incorrect path from vertex \"W\" to vertex \" \". Expected:  One or more vertices not found in graph but got : " << buffer4.str() << endl;
        }  
        //test 5 check value vs. value which does not exist in graph 
        stringstream buffer5;
        streambuf* prevbuf5 = cout.rdbuf(buffer5.rdbuf());
        G->print_path("W", "L");
        cout.rdbuf(prevbuf5);
        if(buffer5.str() != "One or more vertices not found in graph\n") {
            cout << "Incorrect path from vertex \"W\" to vertex \"L\". Expected:  One or more vertices not found in graph but got : " << buffer4.str() << endl;
        }  
        //test 6 check value vs. value which does not exist in graph 
        stringstream buffer6;
        streambuf* prevbuf6 = cout.rdbuf(buffer6.rdbuf());
        G->print_path("9", "2");
        cout.rdbuf(prevbuf6);
        if(buffer6.str() != "One or more vertices not found in graph\n") {
            cout << "input does not exist in graph Expected:  One or more vertices not found in graph but got : " << buffer4.str() << endl;
        }  


    } catch(exception& e) {
        cerr << "Error testing print path : " << e.what() << endl;
    }
    try {
        vector<int> keys = {1,2,3,4,5};
        vector<int> data = {5,4,3,2,1};
        vector<vector<int>> adjs = {{2,3,4},{4},{1},{5},{1}};
        Graph<int,int>* int_G_2 = new Graph<int, int>(keys, data, adjs);
        int_G_2->bfs(1);
        //test 7 no path exists
        stringstream buffer7;
        streambuf* prevbuf7 = cout.rdbuf(buffer7.rdbuf());
        int_G_2->print_path(1,4);
        cout.rdbuf(prevbuf7);
        if(buffer7.str()!="1 -> 4") {
            cout << "Expected: 1 -> 4, but got: " << buffer7.str() << endl; 
        }
        //test 8 no path exists
        int_G_2->bfs(1);
        stringstream buffer8;
        streambuf* prevbuf8 = cout.rdbuf(buffer8.rdbuf());
        int_G_2->print_path(2,1);
        cout.rdbuf(prevbuf8);
        if(buffer8.str()!="no path from 2 to 1 exists.") {
            cout << "Expected: but got: " << buffer8.str() << endl; 
        }
    } catch(exception& e) {
        cerr << "Error getting vertex from int graph : " << e.what() << endl;
    }

}

void test_edge_class(Graph<string,string>* G) {
    try {
        // tree edge 
        string e_class =  G->edge_class("R", "V"); 
        if(e_class != "tree edge") {
            cout << "Misidentified tree edge (\"R\", \"V\") as : " << e_class << endl;
        }
        // back edge
        e_class = G->edge_class("X", "U"); 
        if(e_class != "back edge") {
            cout << "Misidentified back edge (\"X\", \"U\") as : " << e_class << endl;
        }
        // no edge
        e_class =  G->edge_class("R", "U");
        if(e_class != "no edge") {
            cout << "Misidentified non-existant edge (\"R\", \"U\") as : " << e_class << endl;
        }
        // forward edge
        e_class = G->edge_class("T", "W"); 
        if(e_class != "forward edge") {
            cout << "Misidentified forward edge (\"T\", \"W\") as : " << e_class << endl;
        }
        // cross edge
        e_class = G->edge_class("T", "S"); 
        if(e_class != "cross edge") {
            cout << "Misidentified forward edge (\"T\", \"S\") as : " << e_class << endl;
        }
        
        // 1 empty value 
        e_class = G->edge_class("T", ""); 
        if(e_class != "One or more vertices not found in graph\n") {
            cout << "One or more vertices not found in graph  as : " << e_class << endl;
        }
        
        // 2 empty value 
        e_class = G->edge_class("", ""); 
        if(e_class != "One or more vertices not found in graph\n") {
            cout << "One or more vertices not found in graph as : " << e_class << endl;
        }
        
        // 1 value which does not exist in graph 
        e_class = G->edge_class("T", "A"); 
        if(e_class != "One or more vertices not found in graph\n") {
            cout << "One or more vertices not found in graph as : " << e_class << endl;
        }
        
        // 2 value do not exist in graph 
        e_class = G->edge_class("2", "8"); 
        if(e_class != "One or more vertices not found in graph\n") {
            cout << "Misidentified forward edge (\"T\", \"S\") as : " << e_class << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
}

void test_bfs_tree(Graph<string,string>* G) {
    try {
        stringstream buffer;
        streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree("T");
        cout.rdbuf(prevbuf);
        if(buffer.str() != "T\nS U W\nR Y X\nV") {
            cout << "Incorrect bfs tree. Expected : \nT\nS U W\nR Y X\nV \nbut got :\n" << buffer.str() << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
    try {
        vector<int> keys = {1,2,3,4,5};
        vector<int> data = {5,4,3,2,1};
        vector<vector<int>> adjs = {{2,3,4},{4},{1},{5},{1}};
        Graph<int,int>* int_G_2 = new Graph<int, int>(keys, data, adjs);
        int_G_2->bfs(1);
        //test 7 no path exists
        stringstream buffer2;
        streambuf* prevbuf2 = cout.rdbuf(buffer2.rdbuf());
        int_G_2->bfs_tree(2);
        cout.rdbuf(prevbuf2);
        if(buffer2.str()!="2\n4\n5\n1\n3") {
            cout << "Expected: 2\n4\n5\n1\n3 but got: " << buffer2.str() << endl; 
        }
    } catch(exception& e) {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
    
}

int main() {

    Graph<string,string>* G = generate_graph("graph_description.txt");
    test_get(G); 
    test_reachable(G);
    test_bfs(G); 
    test_print_path(G); 
    test_edge_class(G); 
    test_bfs_tree(G);

    cout << "Testing completed" << endl;

    delete G;

    return 0;
}