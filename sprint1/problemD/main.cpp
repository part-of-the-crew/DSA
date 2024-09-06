#include <iostream>
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

	int el;
  //int clm;
	cin >> el;

	vector <int> v(el);
  //vector <int> res;
  //v.resize(n);

	for (int i = 0; i < el; ++i)
    	cin >> v[i];

  //int Nstr, Nclm;
	//cin >> Nstr >> Nclm;
  int res = 0;
  int flag = 0;
  if (el == 1)
    res = 1;
  else
    for ( int i = 0; i < el; ++i)
      if (i == (el - 1))
      {
        if (v[i] > v[i - 1])
          res++;
      } else if (i == 0 && v[i] > v[i + 1])
        {
          res++;
          i++;
        } else if (v[i] > v[i - 1] && v[i] > v[i + 1])
          {
            res++;
            i++;
          }

  //sort(res.begin(), res.end());

  print(res);
  //cout << endl;
}
