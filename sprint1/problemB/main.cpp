#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int a;
	int b;
    int c;
	cin >> a >> b >> c;
    
    if (a < 0)
     a *= -1;
    if (b < 0)
     b *= -1; 
    if (c < 0)
     c *= -1;
    
    if (a%2 == b%2 && b%2 == c%2)
    	cout << "WIN";
    else
		cout << "FAIL";
    cout << endl;
}
