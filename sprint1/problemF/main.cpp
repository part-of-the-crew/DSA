#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

void print(const vector <int> &v) {
  for (auto i : v) 
    cout << i << " ";
  cout << endl;
}
void print(const int v) {
    cout << v << endl;
}
void print(const string &s) {
    cout << s << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	//int el;
	//cin >> el;

  std::string str;
  //cin.ignore();
  std::getline (std::cin, str);
  std::transform(str.begin(),
                 str.end(),
                 str.begin(),
                 ::tolower);
  str.erase (std::remove_if (str.begin (), str.end (), [](char c)
                 {
                 return (c < '0' || c > 'z' || (c > '9' && c < 'a'));
                 }),
                 str.end ());
  std::string str_rev(str.rbegin(), str.rend());
   if (str_rev.compare(str) == 0)
    print("True");
  else
  {
    print("False");
    //print(str);
    //print(str_rev);
  }


}
