#include <iostream>
#include <string>
#include <ranges>
#include <map>
#include <vector>
#include <type_traits>
#include <stack>
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


void BFS(int start_vertex, const std::map <int, std::vector<int>> &gr,
             std::vector <int> &color, std::vector <int> &traversal)
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

void MainBFS( int N, const std::map <int, std::vector<int>> &gr,
             std::vector <int> &color)
{
    
    std::vector <int> traversal;
    BFS(N, gr, color, traversal);

    print (traversal);
}



int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N, M;
	std::cin >> N >> M;
  std::cin.ignore();
	std::map <int, std::vector<int>> gr;
  std::vector <int> colorst(N + 1, -1);

	for (int i = 0; i < M; ++i)
  {
    int a, b;
    std::cin >> a >> b;
    gr[a].push_back(b);
    gr[b].push_back(a); //uncomment for non-oriented graph
    std::cin.ignore();
  }

  for (auto &e: gr)
  {
    std::sort(e.second.begin(), e.second.end());
  }

  //int start = std::chrono::high_resolution_clock::now();
  int start;
  std::cin >> start;

  MainBFS(start, gr, colorst);

  //std::cout << std::endl;

  return 0;
}

