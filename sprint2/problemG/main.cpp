#include <iostream>
#include <vector>
#include <algorithm>


struct Stack{
  std::vector<int> stack;
  std::vector<int> stack_max;

  //Stack(){};

  void push(int x)
  {
    stack.push_back(x);
    if (stack_max.empty() || stack_max.back() < x) 
      stack_max.push_back(x);
    else 
      stack_max.push_back(stack_max.back());
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
      stack_max.pop_back();
      return 1;
    }
    else
      return 0;
  };

  auto get_max() const
  {
    if (stack.size())
      return stack_max.end() - 1;
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


	Stack st;

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
    } else if (temp == "top")
    {
      if (st.end() == st.top())
        std::cout << "error" <<  std::endl;
      else
        cout << *st.top() << endl;
    }
         

  }
}
