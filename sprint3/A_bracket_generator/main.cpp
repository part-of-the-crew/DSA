#include <iostream>
#include <string>
#include <stack>

//binary search

void print(const int v) {
    std::cout << v;
  std::cout << std::endl;
}

bool check_cons(const std::string &s)
{
  std::stack <char> st;
  for (const char c : s) {
    if (c == '(') {
      st.push(c);
    } else if (c == ')') {
      if (st.empty() || st.top()!= '(') {
        return false;
      }
        st.pop();
    }
  }
  return st.empty();
}


void gen_bracets(int n, const std::string &prefix) {
  if (n == 0 ){
    if (check_cons(prefix))
      std::cout << prefix << std::endl;
  } else {
    gen_bracets(n - 1, prefix + "(");
    gen_bracets(n - 1, prefix + ")");
  }
}


int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N;
	std::cin >> N;

  gen_bracets(2*N, "");
}