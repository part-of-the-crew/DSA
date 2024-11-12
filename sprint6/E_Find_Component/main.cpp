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
             std::vector <std::string> &color, int N, std::vector<int> &entry,
             std::vector<int> &leave, int &time, std::stack<int> &stack_topo)
{
    

    std::stack<int> stack;
    //std::stack<int> stack_topo;
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
            //std::cout << v << " ";
            color[v] = "black";
            stack_topo.push(v) ;
            leave[v] = time; // Запишем время выхода.
            time += 1; // Перед выходом из вершины время снова обновляется.
        }
    }

    // Выводим время входа и выхода для каждой вершины.
    //print reverse stack_topo
    //for (auto it = stack_topo.rbegin(); it != stack_topo.rend(); ++it)
     // std::cout << *it << " ";


    


}
/*
int main() {
    // Пример графа в виде массива смежности.
    std::map <int, std::vector<int>> gr = {
        {1, {2, 3}},
        {2, {4}},
        {3, {5}},
        {4, {}},
        {5, {}}
    };

    // Массив цветов для вершин.
    std::vector <std::string> color(gr.size() + 1, "white");

    // Запускаем обход графа.
    DFS(gr.size(), gr, color);

    return 0;
}
*/

void MainDFS(int N, const std::map <int, std::vector<int>> &gr,
             std::vector <std::string> &color)
{
    std::vector<int> entry(N + 1);
    std::vector<int> leave(entry);
    std::stack<int> stack_topo;
    int time = 0;
    for (int i = 1; i < color.size(); ++i) {
        // Перебираем варианты стартовых вершин, пока они существуют.
        if (color[i] == "white")
           DFS(i, gr, color, N, entry, leave, time, stack_topo);
    }
    //for (std::size_t i = 1; i < leave.size(); i++)
    //  std::cout << entry[i] << " " << leave[i] << std::endl;
    while(!stack_topo.empty()) {
      int v = stack_topo.top();
      stack_topo.pop();
      std::cout << v << " ";
    }
}
/*
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
    //gr[b].push_back(a);
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



  MainDFS(N, gr, colorst);
  //DFS(N, gr, colorst);
  std::cout << std::endl;


  return 0;
}

