//https://contest.yandex.ru/contest/25070/run-report/125941655/
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
That's because I need to push and top the edges in the priority_queue(log N) 
    each time doing checking for all edges (M).

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


struct Graph {
    Graph(int N) : vertices(N), edges(N + 1) {}
    //default constructor
    Graph() = default;

    void addEdge(int u, int v) {
        edges[u].insert(v);
    }
    void addmEdge(int u, int v, char t) {
        medges[u].insert({v, t});
        medges[v].insert({u, t});
    }
    int vertices;

    void find_ambigues_v(){
        for (int i = 1; i <= vertices; i++){
            bool flag1 = 0, flag2 = 0;
            for (auto &[v, t]: medges[i]){
                if ( t == 'B' )
                    flag1 = 1;
                if ( t == 'R' )
                    flag2 = 1;
            }
            if (flag1 && flag2){
                ambigues.insert(i);
            }
        }
    }

    void find_ambigues(){
        for (int i = 1; i <= vertices; i++){
            bool flag1 = 0, flag2 = 0;
            for (auto &e: edges[i]){
                if ( e > i )
                    flag1 = 1;
                if ( e < i )
                    flag2 = 1;
            }
            if (flag1 && flag2){
                ambigues.insert(i);
                std::cout << "ambigues" << i << std::endl;
            }
        }
    }

    std::unordered_set <int> ambigues;
    std::vector<std::unordered_set <int>> edges;
    std::unordered_map<int, std::unordered_map <int, char>> medges;

    //print vedges
    void printMap (){
        for (auto &[v, m] : medges) {
            std::cout << v << ": ";
            for (auto &[e, t] : m) {
                std::cout << "(" << e << t << ") ";
            }
            std::cout << std::endl;
        }
    }
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
                    , color(graph.vertices + 1, Color::white)
                        {};
    const Graph &graph_;

    std::vector <Color> color;
};

bool isOptimal(Graph &graph ) {
    GraphDetails gd(graph);
    std::unordered_set<int> visited;
    int start_vertex = 1;
    std::stack<int> stack;
    stack.push(start_vertex);  // Добавляем стартовую вершину в стек.
    if (graph.ambigues.contains(start_vertex) && visited.contains(start_vertex))
        return false;
    visited.insert(start_vertex);

    while (!stack.empty()) {
        int v = stack.top();
        stack.pop();
        //print v and color
        //std::cout << v << " (" << static_cast<int>(gd.color[v]) << ") ";
//print (v);      
        // Проверяем, не все вершины дошли до конца
        if (gd.color[v] == Color::white){
            gd.color[v] = Color::gray;
            size_t s = stack.size();
            for (int w : graph.edges.at(v)) {
                //if (gd.color[w] == Color::gray)
                    //return false;
                //print (w);
                //gd.color[v] == Color::black;
                
                stack.push(w);                 
                //}
            }
                if (s == stack.size()){
                   //gd.color.clear();
                   for (int i = 0; i <= gd.color.size(); i++)
                        gd.color[i] = Color::white;
                    //std::cout << v << " (" << static_cast<int>(gd.color[v]) << ") ";
                }  
        } else {
            
            return false;
        }
    }
    return true;
}

/*
void DFS(int N, const std::map <int, std::vector<int>> &gr,
             std::vector <std::string> &color)
{
    int time = 0;
    int start_vertex = 1;
    std::vector<int> entry(N + 1);
    std::vector<int> leave(entry);

    std::stack<int> stack;
    stack.push(start_vertex);  // Добавляем стартовую вершину в стек.

    while (!stack.empty()) {

        int v = stack.top();
        stack.pop();

        if (color[v] == "white") {
            // Красим вершину в серый. И сразу кладём её обратно в стек:
            // это позволит алгоритму позднее вспомнить обратный путь по графу.
            color[v] = "gray";
            entry[v] = time; // Запишем время входа.
            time += 1;
            stack.push(v);
            //std::cout << v << " ";
            // Теперь добавляем в стек все непосещённые соседние вершины,
            // вместо вызова рекурсии
            auto it = gr.find(v);
            if (it != gr.end())  // Если в графе есть ребра из v.
              for (int w : it->second) {
                //std::cout << it->first << "x";
               //print (it->second);
                  // Для каждого исходящего ребра (v, w):
                  //std::cout << w << color[w] << "x";
                  if (color[w] == "white") {
                      stack.push(w);
                  }
              }
        } else if (color[v] == "gray") {
            // Серую вершину мы могли получить из стека только на обратном пути.
            // Следовательно, её следует перекрасить в чёрный.
            color[v] = "black";
            leave[v] = time; // Запишем время выхода.
            time += 1; // Перед выходом из вершины время снова обновляется.
        }
    }
}
*/

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
        std::getline(std::cin, s); //N - 1 - i
        //print(s);
        for (size_t j = 0; j < s.length(); ++j){
            //gr.addmEdge(i + 1, j + i + 2, s[j]); //let it be forward edge
            if (s[j] == 'B')
                gr.addEdge(i + 1, j + i + 2); //let it be forward edge
            else
                gr.addEdge(j + i + 2, i + 1); //let it be backward edge
        }
    }
    //gr.printMap();
    //gr.find_ambigues_v();
    //gr.printMap();
    //print ("*");
    //print (gr.ambigues);
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

