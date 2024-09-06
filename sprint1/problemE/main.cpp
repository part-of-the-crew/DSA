#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

void print(vector <int> &v) {
  for (auto i : v) 
    cout << i << " ";
  cout << endl;
}
void print(int v) {
    cout << v << endl;
}
void print(string &s) {
    cout << s << endl;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int el;

	cin >> el;

  std::string str;
  cin.ignore();
  std::getline (std::cin, str);
  istringstream is(str);

  string word, biggestword;
  int length = 0;

  while( is >> word)
  {
    if (word.length() > length)
    {
      biggestword = word;
      length = word.length();
    }
  }

  print(biggestword);
  print(length);
}
