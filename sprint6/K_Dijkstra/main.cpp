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

void relax(int u, int v) {
    // Проверяем, не получился ли путь короче найденного ранее.
    if (dist[v] > dist[u] + weight(u, v)) {
        dist[v] = dist[u] + weight(u, v);
        previous[v] = u;
    }
}

int get_min_dist_not_visited_vertex() {
    // Находим ещё непосещённую вершину с минимальным расстоянием от s.
    int currentMinimum = INT_MAX;
    int currentMinimumVertex = -1;

    for (int v : graph.vertices) {
        if (!visited[v] && dist[v] < currentMinimum) {
            currentMinimum = dist[v];
            currentMinimumVertex = v;
        }
    }
    return currentMinimumVertex;
}

void dijkstra(Graph graph, int s) {
    for (int v : graph.vertices) {
        dist[v] = std::numeric_limits<int>::max();         // Задаём расстояние по умолчанию.
        previous[v] = -1;          // Задаём предшественника для восстановления SPT.
        visited[v] = false;        // Список статусов посещённости вершин.
    }

    dist[s] = 0;     // Расстояние от вершины до самой себя 0.

    while (true) {
        int u = get_min_dist_not_visited_vertex();

        if (u == -1 || dist[u] == INT_MAX) {
            break;
        }

        visited[u] = true;
        // из множества рёбер графа выбираем те, которые исходят из вершины u
        std::vector<std::pair<int, int>> neighbours = graph.outgoingEdges(u);

        for (auto [_, v] : neighbours) {
            relax(u, v);
        }
    }
} 

void DFS(int start_vertex, const std::map <int, std::vector<std::pair<int,int>>> &gr,
             std::vector <int> &color, std::vector<std::vector<int>> traversal)
{

    color[start_vertex] = 1;
    std::queue<int> planned;
    planned.push(start_vertex);
    traversal.push_back(start_vertex);
    while (!planned.empty()) {

        int v = planned.front();
        planned.pop();
        
        if (auto it = gr.find(v); it != gr.end())
          for (int w : it->second) {
              if (color[w] == -1) {
                  color[w] = 1;
                  planned.push(w);
                  traversal.push_back(w);
              }
          }
        color[v] = 2;
    }
}
/*
    std::map <int, std::vector<int>> gr = {
        {1, {2, 3}},
        {2, {4}},
        {3, {5}},
        {4, {}},
        {5, {}}
}
*/
struct Graph {
    Graph(int N, int M) : vertices(N), edge(M), matrix(N, std::vector<int>(N, 0)) {}
    int vertices;
    int edge;
    std::vector<std::pair<int, int>> outgoingEdges(int v) const {
        return std::vector<std::pair<int, int>>{edges.at(v)};
    }
    //private:
    std::map<int, std::vector<std::pair<int, int>>> edges;
    std::vector<std::vector<int>> matrix;
};
struct GraphDetails {
    GraphDetails(const Graph &graph) :
                        dist(graph.vertices, std::numeric_limits<int>::max()),
                        previous(graph.vertices, -1),
                        visited(graph.vertices, false) {}
    std::vector<int> dist;
    std::vector<int> previous;          // SPT.
    std::vector<bool> visited;
};
void MainDFS( int N, const std::map <int, std::vector<std::pair<int,int>>> &gr,
             std::vector <int> &color)
{
    
    std::vector<std::vector<int>> matrix(N, std::vector<int>(N, 0));

    for (int i = 0; i < N; ++i) {
      DFS(N, gr, color, matrix);
    }

    for(const auto &v: matrix)
    {
      print(v);
    }
}



int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N, M;
	std::cin >> N >> M;
    std::cin.ignore();
	std::map <int, std::vector<std::pair<int,int>>> gr;
    std::vector <int> colorst(N + 1, -1);

	for (int i = 0; i < M; ++i)
    {
        int a, b;
        int c;
        std::cin >> a >> b;
        std::cin >> c;
        gr[a].push_back({b, c});
        gr[b].push_back({a, c}); //uncomment for non-oriented graph
        std::cin.ignore();
    }

  for (auto &e: gr)
  {
    std::sort(e.second.begin(), e.second.end());
  }

  //int start = std::chrono::high_resolution_clock::now();

  MainDFS(N, gr, colorst);

  //std::cout << std::endl;

  return 0;
}

