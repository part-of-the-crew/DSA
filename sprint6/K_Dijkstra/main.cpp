#include <iostream>
#include <string>
#include <ranges>
#include <map>
#include <vector>
#include <type_traits>
#include <stack>
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
    Graph(int N) : vertices(N), matrix(N, std::vector<int>(N, 0)) {}
    int vertices;
    //int edge;
    std::vector<std::pair<int, int>> outgoingEdges(int v) {
        auto it = edges.find(v);
        if (it != edges.end())
            return it->second;
        return std::vector<std::pair<int, int>> {};
    }
    //private:
    std::map<int, std::vector<std::pair<int, int>>> edges;
    std::vector<std::vector<int>> matrix;
    //std::vector<std::vector<int>> matrix(N, std::vector<int>(N, 0));
};

struct GraphDetails {
    GraphDetails(const Graph &graph) :
                        dist(graph.vertices + 1, std::numeric_limits<int>::max()),
                        previous(graph.vertices + 1, -1),
                        visited(graph.vertices + 1, false) {};
    std::vector<int> dist;
    std::vector<int> previous;          // SPT.
    std::vector<bool> visited;
};

int weight(Graph &graph, int u, int v)
{
    auto vec = graph.edges[u];
    for (auto &e : vec) {
        if (e.first == v) {
            return e.second;
        }
    }
    return -1;
}

void relax(Graph &graph, GraphDetails &gd, int u, int v) {
    // Проверяем, не получился ли путь короче найденного ранее.
    //u - current vertix
    if (gd.dist[v] > gd.dist[u] + weight(graph, u, v)) {
        gd.dist[v] = gd.dist[u] + weight(graph, u, v);
        gd.previous[v] = u;
    }
}

int get_min_dist_not_visited_vertex(GraphDetails &gd, Graph &gr) {
    // Находим ещё непосещённую вершину с минимальным расстоянием от s.
    int currentMinimum = std::numeric_limits<int>::max();
    int currentMinimumVertex = -1;

    for (int v = 1; v <= gr.vertices; v++) {
        if (!gd.visited[v] && gd.dist[v] < currentMinimum) {
            currentMinimum = gd.dist[v];
            currentMinimumVertex = v;
        }
    }
    return currentMinimumVertex;
}

void dijkstra(int s, Graph &graph ) {
    GraphDetails gd(graph);

    gd.dist[s] = 0;     // Расстояние от вершины до самой себя 0.

    while (true) {
        int u = get_min_dist_not_visited_vertex(gd, graph);

        if (u == -1 || gd.dist[u] == std::numeric_limits<int>::max()) {
            break;
        }

        gd.visited[u] = true;
        // из множества рёбер графа выбираем те, которые исходят из вершины u
        std::vector<std::pair<int, int>> neighbours = graph.outgoingEdges(u);

        for (auto [v, _] : neighbours) {
            relax(graph, gd, u, v);
        }
    }
} 



void Main(Graph &gr)
{
    //std::vector <int> colorst(gr.vertices + 1, -1);   
    for (int i = 1; i <= gr.vertices; ++i) {
      dijkstra(i, gr);
    }
/*
    for(const auto &v: matrix)
    {
      print(v);
    }
*/
}



int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N, M;
	std::cin >> N >> M;
    std::cin.ignore();
	//std::map <int, std::vector<std::pair<int,int>>> gr;
    Graph gr(N);

	for (int i = 0; i < M; ++i)
    {
        int a, b;
        int c;
        std::cin >> a >> b;
        std::cin >> c;
        gr.edges[a].push_back({b, c});
        gr.edges[b].push_back({a, c}); //uncomment for non-oriented graph
        std::cin.ignore();
    }

  for (auto &e: gr.edges)
  {
    std::sort(e.second.begin(), e.second.end());
  }

  //int start = std::chrono::high_resolution_clock::now();

  Main(gr);

  //std::cout << std::endl;

  return 0;
}

