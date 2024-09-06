#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(vector <int> &v) {
  for (auto i : v) 
    cout << i << " ";
  cout << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int str;
  int clm;
	cin >> str >> clm;
	vector <int> v(str * clm);
  vector <int> res;
  //v.resize(n);

	for (int i = 0; i < str * clm; ++i)
    	cin >> v[i];

  int Nstr, Nclm;
	cin >> Nstr >> Nclm;

  int x = Nclm + clm * (Nstr - 1);
  //cout << "x = " << x  + clm + 2 << endl;
  if (Nstr > 0)
    res.push_back(v[x]);

  if (Nclm > 0)
    res.push_back(v[x + clm - 1]);

  if (Nstr < (str - 1))
    res.push_back(v[x + 2*clm]);

  if (Nclm < (clm - 1))
    res.push_back(v[x + clm + 1]);

  sort(res.begin(), res.end());

  print(res);
  //cout << endl;
}
