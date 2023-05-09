#include <iostream>
#include <fstream>
#include <string>

//#define DEBUG

using namespace std;

int sizeOfWrite = 1000;

unsigned long* readfile(string path, unsigned long& arri) {
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
            while (ch != ';') in.get(ch);
            getline(in, num);
            buf[i] = stoi(num);
            in.get(ch);
        }
        in.close();
        arri = siz-1;
        return buf;
    }
    else {
        in.close();
        ofstream out(path);
        out << "pozition;number\n";
        out << "0;1\n";
        out.close();
        arri = 0;
        return new unsigned long[1] {1};
    }
}

void addnum(unsigned long& pozition,unsigned long num, unsigned long*& arr) {
    unsigned int siz = _msize(arr) / sizeof(arr[0]);
    pozition++;
    if (pozition < siz) {
        arr[pozition] = num;
    }
    else {
        unsigned long* buf = new unsigned long[siz + sizeOfWrite];
        for (int i = 0; i < siz; i++)buf[i] = arr[i];
        buf[pozition] = num;
        delete[] arr;
        arr = buf;
    }
}

bool issimple(unsigned long*& arr, unsigned long num) {
    unsigned int siz = _msize(arr) / sizeof(arr[0]);
    unsigned int sqrnum = sqrt(num);
    if (siz) {
        for (unsigned int i = 1; arr[i] <= sqrnum; i++) {
            if (!(num % arr[i]))return 0;
        }
    }
    return 1;
}

void writetofile(unsigned long*& arr,string path) {
    unsigned long begi;
    ifstream in(path);
    if (in.is_open()) {
        unsigned long siz;
        string num = "";
        char ch;
        in.seekg(-3, ios_base::end);
        in.get(ch);
        while (ch != ';') {
            in.seekg(-2, ios_base::cur);
            in.get(ch);
        }
        while (ch != '\n') {
            in.seekg(-2, ios_base::cur);
            in.get(ch);
            num = ch + num;
        }
        begi = stoi(num)+1;
    }
    in.close();
    
    ofstream out(path,ios::app);
    unsigned long siz = _msize(arr) / sizeof(arr[0]);
    for (int i = begi; i < siz; i++) {
        out << i << ";" << arr[i] << '\n';
    }
    out.close();
}

void step(string path, unsigned long*& arr,unsigned long& arri) {

    for (int i = 0,num=1; i < sizeOfWrite; i++,num=1) {
        while (1) {
            if (issimple(arr, arr[arri] + num)) {
                addnum(arri, arr[arri] + num, arr);
                break;
            }
            num++;
        }
    }
}

int main()
{
    string path = "simplenums.csv";
    unsigned long arri=0;
    unsigned long* arr = readfile(path,arri);
    while (1) {
        for (int i = 0; i < 10; i++) {
            step(path, arr, arri);
        }
        writetofile(arr, path);
    }
}