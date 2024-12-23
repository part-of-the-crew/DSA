#include <iostream>
#include <string>
#include <ranges>
#include <map>
#include <vector>
#include <type_traits>
#include <stack>
#include <deque>
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


void DFS(int start_vertex, const std::map <int, std::vector<int>> &gr,
             std::vector <int> &color, int &component_count)
{
    

    std::stack<int> stack;
    stack.push(start_vertex);

    while (!stack.empty()) {

        int v = stack.top();
        stack.pop();

        if (color[v] == -1) {

            color[v] = component_count;
            stack.push(v);
            auto it = gr.find(v);
            if (it != gr.end())v.
              for (int w : it->second) {
                  if (color[w] == -1) {
                      stack.push(w);
                  }
              }
        }
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

void MainDFS( int N, const std::map <int, std::vector<int>> &gr,
             std::vector <int> &color)
{
    (void) N;
    int component_count = 0;
    for (std::size_t i = 1; i < color.size(); ++i) {
        if (color[i] == -1)
           DFS(i, gr, color, ++component_count);
    }
    print (component_count);

    for (int j = 1; j <= component_count; ++j){
      for (std::size_t i = 1; i < color.size(); ++i) {
        if (color[i] == j){
          std::cout << i << " ";
        }
      }
      std::cout << std::endl;
    }
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
    std::sort(e.second.rbegin(), e.second.rend());
  }


  MainDFS(N, gr, colorst);

  std::cout << std::endl;

  return 0;
}

