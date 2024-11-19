#include <iostream>
#include <string>
#include <ranges>
#include <map>
#include <vector>
#include <type_traits>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>

template<typename T>
concept BasicString = std::is_same_v<T, std::basic_string<typename T::value_type>>;

template<typename T>
concept StringLike = BasicString<T> || std::is_convertible_v<T, std::string>;

template<typename T>
concept range = std::is_class_v<T> && !StringLike<T>;

template <range C>
void print(const C& s) {
    for (const auto& e : s)
        std::cout << e << " ";
    std::cout << std::endl;
}


template <typename C> 
void print(const C& s) {
    std::cout << s << "";
    std::cout << std::endl;
}


struct Graph {
    Graph(int N) : vertices(N), vedges(N + 1), adj(N + 1) {}
    //default constructor
    Graph() = default;
    //Not oriented
    void addEdgeNO(int u, int v, int w) {
        edges[u].push_back({v, w});
        edges[v].push_back({u, w});
    }
    void vaddEdgeNO(int u, int v, int w) {
        //avoid multiply edges
        
        if (auto it1 = vedges.at(u).find(v); it1 != vedges.at(u).end()) {
            it1->second = std::max(it1->second, w);
            vedges[v][u] = std::max(it1->second, w);
        } else {
            if (auto it2 = vedges.at(v).find(u); it2 != vedges.at(v).end()){
                it2->second = std::max(it2->second, w);
                vedges[u][v] = std::max(it2->second, w);
            } else {
                vedges[u][v] = w;
                vedges[v][u] = w;
            }
        }
        //vedges[u][v] = w;
        //vedges[v][u] = w;
        //adj[u].push({w, v});
        //adj[v].push({w, u});
    }
    void addAdj () {
        //add from vedges to adj
        for (int u = 1; u <= vertices; u++) {
            for (auto &e : vedges[u]) {
                adj[u].push({e.second, e.first});
            }
        }

    }

    void v1addEdgeNO(int u, int v, int w) {
        vedges.at(u)[v] = w;
        adj.at(u).push({w, v});
    }
    std::vector<std::pair<int, int>> outgoingEdges(int v) {
        auto it = edges.find(v);
        if (it != edges.end())
            return it->second;
        return std::vector<std::pair<int, int>> {};
    }

    int vertices;
    std::map<int, std::vector<std::pair<int, int>>> edges;

    std::vector<std::map<int, int>> vedges;
    std::vector <std::priority_queue<std::pair<int, int>>> adj;

    //print vedges
    void print (){
        for (int i = 1; i <= vertices; i++) {
            std::cout << i << ": ";
            for (auto &e : vedges[i]) {
                std::cout << "(" << e.first << ", " << e.second << ") ";
            }
            std::cout << std::endl;
        }
    }
    //vedges count
    int count_all_weights()
    {
        int total_weight = 0;
        for (auto &e : vedges) {
            for (auto &w : e) {
                total_weight += w.second;
            }
        }
        return total_weight;
    }
    /*
    int count_all_weights()
    {
        int total_weight = 0;
        for (auto &e : adj) {
            while (!e.empty())  {
                total_weight += e.top().first;
                e.pop();
            }
        }
        return total_weight;
    }
    */
};

struct GraphDetails {
    GraphDetails(int v, Graph &graph)
                       : graph_(graph)
                       , cur_vertex(v)
                        { add_vertices(graph.vertices); };
    Graph &graph_;
    void add_vertices (int v)
    {
        for (int i = 1; i <= v; ++i){
            not_added.insert(i);
        }
    }
    std::set <int> not_added;
    std::set <int> added;
    int cur_vertex;
    void add_v_and_adj (Graph &dest)
    {
        int v = cur_vertex;
        //print("*");print(v);
        //# Добавляем все рёбра, которые инцидентны v, но их конец ещё не в остове.
        //if ( auto it = not_added.find(v); it != not_added.end() ){
            //not_added.erase(it);
            //added.insert(v);
            if (graph_.adj.at(v).empty()){
                cur_vertex = 0;
                return;
            }

            auto e = graph_.adj.at(v).top();
            
                if (auto it2 = not_added.find(e.second); it2 != not_added.end() ){
                    dest.v1addEdgeNO(v, e.second, e.first);
                    graph_.adj.at(v).pop();
                    not_added.erase(it2);
                    added.insert(e.second);
                    //not_added.erase(v);
                    //added.insert(v);
                    cur_vertex = e.second;
                    print(v);print(cur_vertex);
                    //print(not_added.size());
                    //std::cout << std::flush;
                } else
                    cur_vertex = 0;
            /*
            for (auto &e : graph_.vedges.at(v)) {
                if (auto it2 = added.find(e.first); it2 == added.end() ){
                    dest.vaddEdgeNO(v, e.first, e.second);
                    not_added.erase(it2);
                    added.insert(e.first);
                }
            }
            */
        //} else 
        //cur_vertex = 0;
    }
    void extract_max_edge (int v, Graph &dest)
    {
        //# Добавляем все рёбра, которые инцидентны v, но их конец ещё не в остове.
        auto it = not_added.find(v);
        if ( it != not_added.end() ){
            not_added.erase(it);
            added.insert(v);
            for (auto &e : graph_.edges.at(v)) {
                if (auto it2 = added.find(e.first); it2 != added.end() ){
                    dest.vaddEdgeNO(v, e.first, e.second);
                    not_added.erase(e.first);
                    added.insert(e.first);
                }

            }
        }
    }
};

int findMaxST(int s, Graph &graph ) {
    GraphDetails gd(s, graph);

    Graph MaxST(graph.vertices);

    while (gd.not_added.size() > 0 && gd.cur_vertex > 0) {
        gd.add_v_and_adj(MaxST);
    }
    MaxST.print();
    MaxST.addAdj();
    return MaxST.count_all_weights();
}



int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N, M; //N - vertices
	std::cin >> N >> M;
    std::cin.ignore();
    Graph gr(N);

	for (int i = 0; i < M; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        //gr.addEdgeNO(u, v, w);
        gr.vaddEdgeNO(v, u, w);
        std::cin.ignore();
    }
    //gr.print();
    
    gr.addAdj();
    if (N == 0 || N == 1 || M == 0){
        print("Oops! I did it again");
        return 0;
    }

    if (int w = findMaxST(1, gr); w != 0)
        print(w);
    else
        print("Oops! I did it again");

    return 0;
}

