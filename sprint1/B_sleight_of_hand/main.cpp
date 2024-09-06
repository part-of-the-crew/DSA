//https://contest.yandex.ru/contest/22450/run-report/117155012/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename C> void print(const string& s, const C& c) {
    for (const auto& e : c) {
        cout << e << " ";
    }
    cout << endl;
}

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

// Computational complexity is O(1), due to the fact that the amount of data is constant
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  const int sizeOfMatrix = 4;
  const int NumberOfDigits = 10;

  //vector <string> matrix(sizeOfMatrix);
  vector <int> counter(NumberOfDigits, 0);

  //input
  int k;
  cin >> k;

  for (int i = 0; i < sizeOfMatrix; ++i)
  {
    string temp;
    cin >> temp;
    for (auto &c : temp)
      if (isdigit(c))
        counter[c - '0']++;
  }

//SUM the number of strings that contain at most 2*k digits, and also contain at least k distinct digits
  int sum = count_if(counter.begin(),counter.end(), [k](int value)
  {
    return value <= 2*k && value != 0;
  });

  print(sum);
}
