#include <iostream>
#include <fstream>
#include <string>

using namespace std;

unsigned long* readfile(string path) {
    ifstream in(path);
    if (in.is_open()) {
        unsigned long siz;
        string num = "";
        char ch;
        in.seekg(-3,ios_base::end);
        in.get(ch);
        while (ch != ';') {
            in.seekg(-2,ios_base::cur);
            in.get(ch);
        }
        while (ch != '\n') {
            in.seekg(-2, ios_base::cur);
            in.get(ch);
            num = ch + num;
        }
        siz = stoi(num);
        unsigned long* buf = new unsigned long[siz];
        in.seekg(18, ios_base::beg);
        
        for (int i = 0; i < siz; i++) {
            while (ch != ';') {
                in.get(ch);
            }
            getline(in, num);
            buf[i] = stoi(num);
            in.get(ch);
        }
        in.close();
        return buf;
    }
    else {
        in.close();
        ofstream out(path);
        out << "pozition;number\n";
        out.close();
        return new unsigned long[0]; 
    }
}



int main()
{
    string path = "simplenums.csv";
    unsigned long* arr = readfile(path);
    int size = _msize(arr) / sizeof(arr[0]);
    for (int i = 0; i < size; i++)cout << arr[i] << endl;
}