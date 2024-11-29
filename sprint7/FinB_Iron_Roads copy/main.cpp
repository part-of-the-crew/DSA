#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
using namespace std;
string GetLine(istream& in);
// реализуйте эту функцию:
void CreateFiles(const string& config_file){
    ifstream out_file(config_file);
    string s, s1;
    ofstream in_file;
    s = GetLine(out_file);
    while (s != ""){
        if (s[0] != '>'){
            in_file.close();
            in_file.open(s);
            s1 = s;
        } else {
            std::string sub = s.substr(1, s.size());
            in_file << sub;
            in_file << std::endl;
        }
        s = GetLine(out_file);
    }
}


string GetLine(istream& in) {
    string s;
    getline(in, s);
    return s;
}

int main() {
    ofstream("test_config.txt"s) << "shakespeare/hamlet.txt\n"
">To be, or not to be,\n"
">that is the question;\n"
"empty.txt\n"
"lear.txt\n"
">Nor are those empty-hearted whose low sound\n"
">Reverbs no hollowness.;"s;

    CreateFiles("test_config.txt"s);
    ifstream in_a("a.txt"s);
    /*
    assert(GetLine(in_a) == "10"s && GetLine(in_a) == "abc"s);

    ifstream in_b("b.txt"s);
    assert(GetLine(in_b) == "123"s);
    */
}