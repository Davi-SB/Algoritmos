#include <iostream>
using namespace std;

template <typename T1, typename T2>
class customPair {
private:
    T1 primeiro;
    T2 segundo;

public:
    customPair(int p, int s) { // contructor
        primeiro = p;
        segundo = s;
    }

    void print() {
        cout << '<' << primeiro << ',' << segundo << '>' << endl;
    }

    // operator overloading de >
    bool operator> (customPair<T1, T2> outro) {
        if (this->primeiro == outro.primeiro) {
            return (this->segundo > outro.segundo);
        }
        return (this->primeiro > outro.primeiro);
    }

    // operator overloading de <= usando >
    bool operator<= (customPair<T1, T2> outro) {
        return !((*this) > outro);
    }

    // operator overloading de +=
    void operator+= (customPair<T1, T2> outro) {
        this->primeiro += outro.primeiro;
        this->segundo  += outro.segundo;
    }

    // operator overloading de << (para cout)
    friend ostream& operator<<(ostream& out, customPair<T1, T2> p) {
        out << '<' << p.primeiro << ',' << p.segundo << '>';
        return out;
    }

};

int main() {
    customPair<int, float> pair1(3, 4.5);
    customPair<int, float> pair2(1, 2.7);
    pair1.print();
    pair2.print();

    cout << (pair1 > pair2) << endl;  // exemplo de uso de operator>
    cout << (pair1 <= pair2) << endl; // exemplo de uso de operator<=

    pair1 += pair2; // exemplo de uso de operator+=
    pair1.print();

    cout << endl << pair1 << "  " << pair2 << endl; // exemplo de uso de operator<<
    return 0;
}