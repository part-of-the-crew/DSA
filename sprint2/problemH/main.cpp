#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>


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

	//int Nstr;
	//cin >> Nstr;


	stack <char> st;
  string temp;
  cin >> temp;

	for (auto c : temp)
  {
    if (c == '(' || c == '{' || c == '[')
    {
      st.push(c);
      continue;
    }

    if (st.empty() || '(' != st.top() && c == ')')
    {
      cout << "False" << endl;
      return 0;
    }
    if (st.empty() || '{' != st.top() && c == '}')
    {
      cout << "False" << endl;
      return 0;
    }
    if (st.empty() || '[' != st.top() && c == ']')
    {
      cout << "False" << endl;
      return 0;
    }

    if ('(' == st.top() && c == ')')
    {
      st.pop();
      continue;
    }
    if ('{' == st.top() && c == '}')
    {
      st.pop();
      continue;
    }
    if ('[' == st.top() && c == ']')
    {
      st.pop();
      continue;
    }

  }

  if (st.empty())
    cout << "True" << endl;
  else
    cout << "False" << endl;
}
