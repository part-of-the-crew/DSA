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

	int Nstr;
    int Nrow;
	cin >> Nstr;
    cin >> Nrow;

	vector <vector <int>> v(Nstr);

	for (int i = 0; i < Nstr; ++i)
	  for (int j = 0; j < Nrow; ++j)
    {
      int temp;
      cin >> temp;
      v[i].push_back(temp);
    }
  
	  for (int j = 0; j < Nrow; ++j)
    {
	    for (int i = 0; i < Nstr; ++i)
      {
        cout << v[i][j] << " ";
      }
      cout << endl;
    }


}
