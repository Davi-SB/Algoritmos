#include <iostream>
using namespace std;

template <typename T>
void print(T e) {
    cout << e << endl;
}

template <typename T>
void max(T a, T b) {
    if(a > b) return a;
    return b;
}

template<typename T1, typename T2>
struct Pair {
    T1 primeiro;
    T2 segundo;
};

template <typename T1, typename T2>
class customPair {
private:
    T1 primeiro;
    T2 segundo;

public:
    customPair(T1 p, T2 s) { // contructor
        primeiro = p;
        segundo = s;
    }

    void print() {
        cout << '<' << primeiro << ',' << segundo << '>' << endl;
    }

};