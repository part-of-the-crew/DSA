//https://contest.yandex.ru/contest/25070/run-report/126673845/
/*
-- WORKING PRINCIPLE --

First, I add roads "B" as an edge with forward direction, and "R" as an edge with
backward direction.

Then, I perform DFS without recursion for every vertex with 0(white) color.
During DFS I put vertices in a stack, paint them in gray color, look for adjacent white vertices, 
and put them in the stack again.If I encounter a vertex with a gray color topping in out of the stack, 
I paint it black(2).

Second, I check whether the processed vertex has an adjacent vertex with a 1(gray) color,
if so, the graph is supposed to be a cyclic graph. It means it is not optimal. 
Otherwise, move on searching until the last vertex. if there is no adjacent vertex with a gray color, 
the graph is optimal.

-- PROOF OF CORRECTNESS --

1. By treating "B" roads as edges in the forward direction and "R" roads as edges in the backward direction,
  the problem can be reduced to detecting cycles in a directed graph.
  because:

  First, If both paths did exist, reversing one type of path would lead to a cycle, because one path would be in
  forward direction, another one would be in the backward direction.

  Second, If either type of path is missing, no cycle is formed, because
  train can only travel to larger vertices in the forward direction, and to smaller ones in the backward direction,
  going in the backward direction would return the train to such vertex, that doesn't have a forward direction
  to the previous larger vertex, because one path doesn't exist, and a cycle isn't formed.


2. If I find a gray vertex in adjacent vertices, this graph has cycles, because gray vertices in
the stack mean that they are not already processed.
             

-- TIME COMPLEXITY --
Assume number of edges(E) = V - 1;
    where V is the number of vertices

Time complexity in the worst case:
    O(V + E), 
    where V is the number of vertices,
          E is the number of edges.
because each vertex V and edge E are visited only once.
Summary: O(V).


-- SPACE COMPLEXITY --
Space complexity in the worst case:
    O(V) for storing all vertices with edges,
    O(V) for storing stack,
    O(V) for storing colors,
where V is the number of vertices,
Summary: O(V).
*/

#include <iostream>
#include <string>
#include <ranges>
#include <unordered_map>
#include <vector>
#include <type_traits>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <stack>

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
/*
    void printMap (){
        for (auto &[v, m] : medges) {
            std::cout << v << ": ";
            for (auto &[e, t] : m) {
                std::cout << "(" << e << t << ") ";
            }
            std::cout << std::endl;
        }
    }
*/

struct Graph {
    Graph(int V) : vertices(V), edges(V + 1) {}
    //default constructor
    Graph() = default;

    void addEdge(int u, int v) {
        edges[u].push_back(v);
    }
    int vertices;
    std::vector<std::vector <int>> edges;

    void print (){
        for (int i = 1; i <= vertices; i++) {
            std::cout << i << ": ";
            for (auto &e : edges[i]) {
                std::cout << "(" << e << ") ";
            }
            std::cout << std::endl;
        }
    }
};

enum class Color { white, gray, black };

struct GraphDetails {
    GraphDetails(Graph &graph) 
                    : graph_(graph)
                    , color(graph.vertices + 1, false)
                        {};
    const Graph &graph_;

    std::vector <int> color;
};

bool isOptimal(Graph &graph ) {

    GraphDetails gd(graph);
    for (int i = 1; i <= graph.vertices; ++i) {
        if (gd.color[i] != 0) {
            continue;
        }
    
        std::stack<int> stack;
        stack.push(i);

        while (!stack.empty()) {
            int v = stack.top();
            stack.pop();

            if (gd.color[v] == 0){
                gd.color[v] = 1;

                stack.push(v);

                for (int w : graph.edges.at(v)) {
                    if (gd.color[w] == 0){
                        stack.push(w);
                    } else if (gd.color[w] == 1) {
                        return false;
                    }               
                }
            } else if (gd.color[v] == 1) {
                gd.color[v] = 2;
            }
        }
    }
    return true;
}

class StreamUntier {
public:
    explicit StreamUntier(std::istream &is_): is(is_) {
        tied_before_ = is.tie(nullptr);
    }

    ~StreamUntier() {
        is.tie(tied_before_);
    }

private:
    std::ostream* tied_before_;
    std::istream &is;
};

int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int V; //V - vertices(towns), M - edges
	std::cin >> V;
    Graph gr(V);
    std::cin.ignore();
	for (int i = 0; i < V - 1; ++i)
    {
        std::string s;
        std::getline(std::cin, s);
        for (size_t j = 0; j < s.length(); ++j){
            if (s[j] == 'B')
                gr.addEdge(i + 1, j + i + 2); //let it be forward edge
            else
                gr.addEdge(j + i + 2, i + 1); //let it be backward edge
        }
    }

    if (std::cin.fail()) {
        print("Invalid input");
        return 1;
    }
    if (V <= 2){
        print("YES");
        return 0;
    }

    if (isOptimal(gr))
        print("YES");
    else
        print("NO");

    return 0;
}

