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


//std::vector<std::string> color = {"white", "white", ...}; // Длина массива равна числу вершин |V|.

void DFS(int start_vertex, const std::map <int, std::vector<int>> &gr,
             std::vector <std::string> &color)
{
    std::stack<int> stack;
    stack.push(start_vertex);  // Добавляем стартовую вершину в стек.

    while (!stack.empty()) {  // Пока стек не пуст:
        // Получаем из стека очередную вершину.
        // Это может быть как новая вершина, так и уже посещённая однажды.
        int v = stack.top();
        stack.pop();
        
        if (color[v] == "white") {
            // Красим вершину в серый. И сразу кладём её обратно в стек:
            // это позволит алгоритму позднее вспомнить обратный путь по графу.
            color[v] = "gray";
            stack.push(v);
            std::cout << v << " ";
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
        }
    }
}
/*
void MainDFS(int start, const std::map <int, std::vector<int>> &gr,
             std::map <int, std::string> &color)
{
  DFS(start, gr, color);
  
  for (auto &c : color)
  {
      std::cout << c.first << color[c.first] << "x";
  }
 
  
  for (auto &c : color)
  {
      
      if (c.second == "white")
          DFS(c.first, gr, color);
  }
   
}

void MainDFS() {
    for (int i = 0; i < color.size(); ++i) {
        // Перебираем варианты стартовых вершин, пока они существуют.
        if (color[i] == "white")
            DFS(i); // Запускаем обход, стартуя с i-й вершины.
    }
} 
*/




int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N, M;
	std::cin >> N >> M;
  std::cin.ignore();
	std::map <int, std::vector<int>> gr;
	std::map <int, std::string> color;
  std::vector <std::string> colorst(N + 1, "white");
	for (int i = 0; i < M; ++i)
  {
    int a, b;
    std::cin >> a >> b;
    gr[a].push_back(b);
    gr[b].push_back(a);
    std::cin.ignore();
  }

  for (int i = 1; i <= N; ++i)
  {
    color[i] = "white";
  }
  for (auto &e: gr)
  {
    std::sort(e.second.rbegin(), e.second.rend());
  }

  int sv;
  std::cin >> sv;

  //MainDFS(sv, gr, colorst);
  DFS(sv, gr, colorst);
  std::cout << std::endl;


  return 0;
}

