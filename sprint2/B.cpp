//https://contest.yandex.ru/contest/22781/run-report/117424094/
/*
-- WORKING PRINCIPLE --

  If an operand is fed to the input, it is placed on the top of the stack.
  If an operation sign is fed to the input, 
then this operation is performed on the required number of values
​​taken from the stack in the order of addition. 
The result of the performed operation is placed on the top of the stack.

  If the input set of symbols is not fully processed, go to step 1.
After the input set of symbols is fully processed, 
the result of calculating the expression is at the top of the stack. 
If there are several numbers left on the stack, 
then only the top element should be output.

-- PROOF OF CORRECTNESS --

Since the operation relates to two numbers previously placed on the stack, 
we extract them, perform the appropriate operation and 
put them back so that the next operation could use this result.

-- TIME COMPLEXITY --

Since no container class is specified, the standard container std::deque is used 
with his constant complexity of operations.

Time complexity in the worst case
O(n), where n is the number of tokens in the input.

-- SPACE COMPLEXITY --

Space comlexity in the worst case
O(n), where n is the number of tokens in the input.
*/
#include <iostream>
#include <sstream>
#include <stack>
#include <cmath> // std::numeric_limits<T>::is_integer

template <typename T>
T divide_rounddown(T numer, T denom)
{
  static_assert(std::numeric_limits<T>::is_integer, "Only integer types are allowed");

  T result = ((numer) < 0) != ((denom) < 0) ?
    ((numer) - ((denom) < 0 ? (denom) + 1 : (denom) - 1)) / (denom) :
    (numer) / (denom);
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::string str;
  std::getline (std::cin, str);
  std::istringstream is(str);

  std::string word;
  std::stack<int> st;
  while( is >> word)
  {
    try
    {
      st.push(std::stoi(word));
    }
    catch (std::invalid_argument const& ex)
    {
      int b = st.top();
      st.pop();
      int a = st.top();
      st.pop();
      switch(word.at(0))
      {
        case '+':
          st.push(a+b);
          break;
        case '-':
          st.push(a-b);
          break;
        case '*':
          st.push(a*b);
          break;
        case '/':
          if(b == 0) {
            throw std::invalid_argument("Division by zero");
          }
          st.push(divide_rounddown<int>(a , b));
          break;
        default:
          throw std::invalid_argument("Invalid operator");
      }
    }
  }
  std::cout << st.top() << std::endl;
}
