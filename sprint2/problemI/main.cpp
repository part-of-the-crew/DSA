
#include <iostream>
#include <queue>


struct MyQueue{
  std::queue<int> q;
  std::size_t size_q;

  MyQueue (std::size_t size) : size_q(size){};

  void push(int x)
  {
    if (q.size() == size_q)
      std::cout << "error" <<  std::endl;
    else  
      q.push(x);
  };

  void pop()
  {
    if (q.size())
    {
      std::cout << q.front() <<  std::endl;
      q.pop();
    }
    else
      std::cout << "None" <<  std::endl;
  }
  void peek()
  {
    if (q.size())
      std::cout << q.front() <<  std::endl;
    else
      std::cout << "None" <<  std::endl;
  }
  auto size() const { return q.size(); }
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

	int Nstr, L;
	cin >> Nstr;
  cin >> L;

	MyQueue st(L);
  int val;
	for (int i = 0; i < Nstr; ++i)
  {
    string temp;
    cin >> temp;
    if (temp == "push")
    {
      cin >> val;
      st.push(val);
    }
    else if (temp == "pop")
    {
      st.pop();
    }
    else if (temp == "peek")
    {
      st.peek();
    }
    else if (temp == "size")
    {
      std::cout << st.size() <<  std::endl;
    }
         

  }
}
