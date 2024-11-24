//https://contest.yandex.ru/contest/25070/run-report/126655400/
/*
-- WORKING PRINCIPLE --

First, I note any existing vertex from the not_added and put all adjacent edges 
into priority_queue by weight in the decreasing order.

Second, I will top&pop the first element off the priority_queue until 
added is full of "trues" and the queue are empty putting the adjacent edges with not added vertex 
into the priority_queue.

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
    O(∣E∣⋅log∣V∣), 
    where V is the number of vertices,
          E is the number of edges.
That's because I need to push and top the edges in the priority_queue(log V) 
    each time doing checking for all edges (E).

-- SPACE COMPLEXITY --

Space complexity in the worst case:
    O(V + E), 
where V is the number of vertices,
      E is the number of edges.
That's because I use space to store the edges and the vertices.
*/

#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <type_traits>
#include <queue>
#include <algorithm>


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
    Graph(int V) : vertices(V), edges(V + 1) {}
    //default constructor
    Graph() = default;
    //Not oriented
    void addEdge(int u, int v, int w) {
        edges[u].push_back({v, w});
        edges[v].push_back({u, w});
    }

    int vertices;

    std::vector<std::vector<std::pair <int, int>>> edges;

    //print edges
    void print (){
        for (int i = 1; i <= vertices; i++) {
            std::cout << i << ": ";
            for (auto &e : edges[i]) {
                std::cout << "(" << e.first << ", " << e.second << ") ";
            }
            std::cout << std::endl;
        }
    }
};

struct GraphDetails {
    GraphDetails(Graph &graph) 
                        : graph_(graph)
                        , added(graph.vertices + 1, false)
                        {};
    Graph &graph_;

    std::vector <bool> added;
    int nTrueInAdded = 0;

    std::priority_queue<std::pair<int, std::pair<int,int>>> adj;
    void add_v(int u) {
        added[u] = true;
        nTrueInAdded++;
        for (const auto &[v , w] : graph_.edges[u]){
            if (added[v] == false){
                adj.push({w, {u, v}});
            }
        }
    }

    bool isEverythingAdded(){
        return graph_.vertices <= nTrueInAdded;
    }
};

int findMaxST(int s, Graph &graph ) {
    GraphDetails gd(graph);

    int total_weight = 0;
    
    gd.add_v(s);

    while (!gd.isEverythingAdded() && !gd.adj.empty()) {
        const auto edge = gd.adj.top();
        gd.adj.pop();

        if (gd.added[edge.second.second] == false) {
            gd.add_v(edge.second.second);
            total_weight += edge.first;
        }
    }

    if (!gd.isEverythingAdded())
        return 0;

    return total_weight;
}



int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int V, E; //N - vertices, M - edges
	std::cin >> V >> E;
    Graph gr(V);

	for (int i = 0; i < E; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        gr.addEdge(v, u, w);
    }
    
    if (std::cin.fail()) {
        print("Invalid input");
        return 1;
    }

    if (V == 1){
        print(0);
        return 0;
    }

    if (V == 0 || E == 0){
        print("Oops! I did it again");
        return 0;
    }

    if (int w = findMaxST(1, gr); w != 0)
        print(w);
    else
        print("Oops! I did it again");

    return 0;
}

