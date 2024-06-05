#include <iostream>
using namespace std;

class customPair {
private:
    int primeiro;
    int segundo;

public:
    customPair(int p, int s) { // contructor
        primeiro = p;
        segundo = s;
    }

    void print() {
        cout << '<' << primeiro << ',' << segundo << '>' << endl;
    }

    // operator overloading de >
    bool operator> (customPair outro) {
        if (this->primeiro == outro.primeiro) {
            return (this->segundo > outro.segundo);
        }
        return (this->primeiro > outro.primeiro);
    }

    // operator overloading de <= usando >
    bool operator<= (customPair outro) {
        return !((*this) > outro);
    }

    // operator overloading de +=
    void operator+= (customPair outro) {
        this->primeiro += outro.primeiro;
        this->segundo  += outro.segundo;
    }

    // operator overloading de << (para cout)
    friend ostream& operator<<(ostream& out, customPair p) {
        out << '<' << p.primeiro << ',' << p.segundo << '>';
        return out;
    }

    // friend permite que essa funcao amiga tenha acesso aos membros
    // privados e protegidos da classe

    // ostream  --> output stream
    
    // ostream& --> funcao operator<< retorna uma referencia para um objeto "ostream",
    // e nao uma copia, o que eh necessario para o funcionamento do cout
};