//https://contest.yandex.ru/contest/22450/run-report/117155007/

#include <iostream>
#include <vector>

using namespace std;

void print(const vector <int> &v) {
  for (auto i : v) 
    cout << i << " ";
  cout << endl;
}
void print(const int a) {
    cout << a << endl;
}
void print(const string &s) {
    cout << s << endl;
}


// Computational complexity is O(N), where N is the number of given elements
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

//input
  cin >> N;
  vector <int> v(N);

  for (int i = 0; i < N; ++i)
    cin >> v[i];

// logic
  int zero_position = __INT_MAX__;

  for (int i = 0; i < N; ++i)
  {
      if (v[i] == 0)
        zero_position = i;
      else if (zero_position != __INT_MAX__)
        v[i] = i - zero_position;
      else
        v[i] = zero_position;
  }

  zero_position = __INT_MAX__;

  for (int i = N - 1; i >= 0; --i)
  {
      if (v[i] == 0)
        zero_position = i;
      else if (zero_position != __INT_MAX__)
       if ( v[i] > zero_position - i)
        v[i] = zero_position - i;
  }

  print(v);
}
