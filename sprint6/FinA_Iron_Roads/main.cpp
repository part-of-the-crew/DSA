//https://contest.yandex.ru/contest/25070/run-report/126278816/
/*
-- WORKING PRINCIPLE --

First, I check whether I already have an edge with the same vertices, if so, 
I rewrite it in a vector of maps if it has more weight.
I put all existing vertices into a set of not-added vertices.

Second, I remove any existing vertex from the not_added and put all adjacent edges 
into priority_queue by weight in the decreasing order.

After that, I will top&pop the first element off the priority_queue until 
not_added and the queue are empty putting the adjacent edges with not added vertex into the priority_queue.

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
Assume number of edges(E) = N - 1;
    where N is the number of vertices

Time complexity in the worst case:
    O(N + E), 
    where N is the number of vertices,
          E is the number of edges.
because each vertex N and edge E are visited only once.
Summary: O(N).


-- SPACE COMPLEXITY --
Space complexity in the worst case:
    O(N) for storing all vertices with edges,
    O(N) for storing stack,
    O(N) for storing colors,
where N is the number of vertices,
Summary: O(N).
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
    Graph(int N) : vertices(N), edges(N + 1) {}
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

int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N; //N - vertices(towns), M - edges
	std::cin >> N;
    Graph gr(N);
    std::cin.ignore();
	for (int i = 0; i < N - 1; ++i)
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
    if (N <= 2){
        print("YES");
        return 0;
    }

    if (isOptimal(gr))
        print("YES");
    else
        print("NO");

    return 0;
}

