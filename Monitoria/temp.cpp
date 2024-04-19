#include <iostream>
using namespace std;
#define TAM 1

int main() {
    
    string nomes[TAM];
    float notas[TAM];
    float media = 0;

    for (int i = 0; i < TAM; i++) {
        cin >> nomes[i] >> notas[i];
        media += notas[i];
    }

    media /= TAM;
    cout << "A media da sala foi " << media << endl;

    for (int i = 0; i < TAM; i++) {
        cout << "O aluno/a " << nomes[i] << " ";
        if (notas[i] < 7) {
            cout << "nao ";
        }
        cout << "passou em algoritmos\n";
    }



    return 0;
}

// g++ temp.cpp -o arquivodamonitoria.exe && ./a.exe