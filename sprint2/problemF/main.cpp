#include <iostream>
#include <vector>
#include <algorithm>


template<typename T> struct Stack{
  std::vector<T> stack;
  T max_el;
  int Qty = 0;
  Stack(): stack(std::vector<T> ()){

  };

  void push(T x)
  {
    stack.push_back(x);
    if (max_el < x) 
      max_el = x;
    else if ( max_el == x )
      Qty++;
  };

  auto top() const
  {
    if (stack.size())
      return stack.end() - 1;
    else
    {
      return stack.end();
    }
  }

  int pop()
  { 
    if (stack.size())
    {
      stack.pop_back();
      return 1;
    }
    else
      return 0;
  };

  auto get_max() const
  {
    if (stack.size())
      return max_element(stack.begin(), stack.end());
    else
    {
      return stack.end();
    }
  };

  auto end() const
  {
    return stack.end();
  }
};

/*
get_max
push 7
pop
push -2
push -1
pop
get_max*/





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


	Stack <int> st;

	for (int i = 0; i < Nstr; ++i)
  {
    string temp;
    cin >> temp;
    if (temp == "push")
    {
      int val;
      cin >> val;
      st.push(val);
    }
    else if (temp == "pop")
    {
      if (!st.pop())
        std::cout << "error" <<  std::endl;
    }
    else if (temp == "get_max")
    {
      if (st.end() == st.get_max())
        std::cout << "None" <<  std::endl;
      else
        cout << *st.get_max() << endl;
    }
         

  }
}
