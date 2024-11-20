//https://contest.yandex.ru/contest/25070/run-report/125751584/
/*
-- WORKING PRINCIPLE --

First, I check whether I already have an edge with the same vertices, if so, 
I rewrite it in a vector of maps if it has more weight.
I put all existing vertices into a set of not-added vertices.

Second, I remove any existing vertex from the not_added and put all adjacent edges 
into priority_queue by weight in the decreasing order.

After that, I will top&pop the first element off the priority_queue until 
not_added and the queue are empty putting the adjacent edges with not added vertex into the priority_queue
Finally, during the putting, I calculate the weights of added edges 
to return it out of the function as a result.

-- PROOF OF CORRECTNESS --

1. We need to keep an eye on whether connected vertices and edges are taken into account
   for calculating the summary weight.

    This condition is satisfied because I compute all not visited edges 
    until not added vertices become empty.
    
2. We need to define accurately when our graph is not connected.

    This condition is satisfied as well because I check whether there are not added vertices left
    after the processing of the priority_queue. It means that there are no any edges to these vertices.

3. We need to ensure that we calculate only the biggest weights.

    This condition is satisfied as well because I use priority_queue with the biggest edge on the top
    for the weights, it also means that we traverse only across the biggest edges with not added vertices.
    This ensures that the summary maximal weight is calculated correctly.
             

-- TIME COMPLEXITY --

Time complexity in the worst case:
    O(∣M∣⋅log∣N∣), 
    where N is the number of vertices,
          M is the number of edges.
That's because I need to put and find the vertices in the set for each edge.

-- SPACE COMPLEXITY --

Space complexity in the worst case:
    O(N + M), 
where N is the number of vertices,
      M is the number of edges.
That's because I use space to store the edges and the vertices.
*/

#include <iostream>
#include <string>
#include <ranges>
#include <map>
#include <vector>
#include <type_traits>
#include <set>
#include <queue>
#include <algorithm>
//#include <numeric>

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
    Graph(int N) : vertices(N), vedges(N + 1) {}
    //default constructor
    Graph() = default;
    //Not oriented
    void vaddEdgeNO(int u, int v, int w) {
        //avoid multiply edges
        if (auto it1 = vedges[u].find(v); it1 != vedges[u].end()) {
            it1->second = std::max(it1->second, w);
            vedges[v][u] = std::max(it1->second, w);
        } else {
            if (auto it2 = vedges[v].find(u); it2 != vedges[v].end()){
                it2->second = std::max(it2->second, w);
                vedges[u][v] = std::max(it2->second, w);
            } else {
                vedges[u][v] = w;
                vedges[v][u] = w;
            }
        }
    }

    void v1addEdgeNO(int u, int v, int w) {
        vedges[u][v] = w;
    }

    int vertices;

    std::vector<std::map<int, int>> vedges;

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
};

struct GraphDetails {
    GraphDetails(Graph &graph) : graph_(graph)
                        { add_vertices(graph.vertices); };
    Graph &graph_;
    void add_vertices (int v)
    {
        for (int i = 1; i <= v; ++i){
            not_added.insert(i);
        }
    }
    std::set <int> not_added;
    //std::set <int> added;

    std::priority_queue<std::pair<int, std::pair<int,int>>> adj;
    void add_v(int u) {
        not_added.erase(u);
        //added.insert(u);
        for (auto &edge : graph_.vedges[u]){
            int w = edge.second;
            int v = edge.first;
            if (not_added.contains(v)){
                adj.push({w, {u, v}});
            }
        }
    }
};

int findMaxST(int s, Graph &graph ) {
    GraphDetails gd(graph);
    Graph MaxST(graph.vertices);
    int total_weight = 0;
    
    gd.add_v(s);

    while (!gd.not_added.empty() && !gd.adj.empty()) {
        auto edge = gd.adj.top();
        gd.adj.pop();

        if (gd.not_added.contains(edge.second.second)) {
            gd.add_v(edge.second.second);
            total_weight += edge.first;
            //MaxST.v1addEdgeNO(edge.second.first, edge.second.second, edge.first);
        }
    }

    if (!gd.not_added.empty())
        return 0;

    //return MaxST.count_all_weights();
    return total_weight;
}



int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N, M; //N - vertices, M - edges
	std::cin >> N >> M;
    std::cin.ignore();
    Graph gr(N);

	for (int i = 0; i < M; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        gr.vaddEdgeNO(v, u, w);
        std::cin.ignore();
    }
    
    if (std::cin.fail()) {
        print("Invalid input");
        return 1;
    }

    if (N == 1){
        print(0);
        return 0;
    }

    if (N == 0 || M == 0){
        print("Oops! I did it again");
        return 0;
    }

    if (int w = findMaxST(1, gr); w != 0)
        print(w);
    else
        print("Oops! I did it again");

    return 0;
}

