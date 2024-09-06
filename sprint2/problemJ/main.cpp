#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

template<typename T> struct Queue{
  std::list<T> stack;

  void put(T x)
  {
    stack.push_back(x);
  };

  void get()
  {
    if (stack.size())
    {
      std::cout << stack.front() <<  std::endl;
      stack.pop_front();
    }
    else
      std::cout << "error" <<  std::endl;
  }

  auto size() const { return stack.size(); }

  auto end() const
  {
    return stack.end();
  }
};

using namespace std;

void print(vector <int> &v) {
  for (auto i : v) 
    cout << i << " ";
  cout << endl;
}
void print(int v) {
    cout << v;
  cout << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int Nstr;
	cin >> Nstr;


	Queue <int> st;

	for (int i = 0; i < Nstr; ++i)
  {
    string temp;
    cin >> temp;
    if (temp == "put")
    {
      int val;
      cin >> val;
      st.put(val);
    }
    else if (temp == "get")
    {
      st.get();
    }
    else if (temp == "size")
    {
      std::cout << st.size() <<  std::endl;
    }
         

  }
}
