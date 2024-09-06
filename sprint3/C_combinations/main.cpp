#include <iostream>
#include <vector>
#include <string>

//print mobile phone combinations

void print_letters(const std::string s, std::size_t pos, const std::string &prefix, 
                   const std::vector<std::string> base) {

    if (pos == s.length()) {
      std::cout << prefix << " ";
    } else {
      for (const auto l: base.at(s.at(pos) - '0'))
      {
        print_letters(s, pos + 1, prefix + l, base);
      }
    }
}


int main () {
  //fast input-output
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

  const std::vector<std::string> base {"", "", 
                            "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

  std::string s;
  std::cin >> s;

  print_letters(s, 0, "", base);

  std::cout << std::endl;
}