#include <iostream>
#include <fstream>
#include <string>

using namespace std;

unsigned long* readfile(string path) {
    ifstream in(path);
    if (in.is_open()) {
        unsigned long siz;
        in.seekg(16,ios_base::beg);
        in >> siz;
        in.seekg(17+size(to_string(siz)), ios_base::beg);
        string str;
        unsigned long* buf = new unsigned long[siz];
        while (!in.eof()) {
            in >> str;
            cout << str << endl;
        }
    }
    else {
        in.close();
        ofstream out(path);
        out << "pozition;number;0\n";
        out.close();
        return new unsigned long[0]; 
    }
}

int main()
{
    string path = "simplenums.csv";
    readfile(path);
}