#include <iostream>
using namespace std;

// define
int main() {
    // declaracao ---------------------------------------
    bool booleano;
    char caractere = 'a'; // aspas simples necessaria
    int inteiro;
    unsigned int natural; // mais um bit na memoria
    float real;
    long long int inteiroMaior;

    int a = 1, b = 2, c = 3; // a, b, c = 1, 2, 3

    // if, ternario, switch ---------------------------------------
    if(caractere == 'a') { // chaves definesm o escopo. Identacao nao faz diferenca na compilacao
        /* code */
    } 
    else if (booleano) c = 33; // quando ha apenas um statement, nao eh necessario o uso de chaves para definir o escopo
    else {
        if (true) {

        } 
        else {
            
        }
    }

    // array/matriz ---------------------------------------
    int array[5] = {0, 1, 2, 3, 4}; // essa atribuicao com uso de chaves so funciona na declaracao
    int tamArray = (sizeof(array)/sizeof(int));
    int matriz[2][3];

    // lacos ---------------------------------------
    for (int i = 0; i < tamArray; i++) {
        /* code */
    }
    
    int j = 0;
    while(j < tamArray) {
        /* code */
        j++;
    }

    int k = 0;
    do {
        k++;
        /* code */
    } while(k < tamArray);
    // spoiler: tem um foreach
    
    // struct (classe) ---------------------------------------
    struct vetorR2 {
    // public: (implicito)
        int x, y;
    };

    class vetorR3 {
    // private: (implicito)
        int x, y, z;
    };

    vetorR2 v;
    v.x = 10;
    v.y = 20;

    vetorR2 arrayV[10];
    arrayV[5].x = 5;

    // funcoes
    /*bool divisivel(int a, int b) {
        return (a % b == 0);
    }

    void clear(int arr[], int tam) {
        for (int i = 0; i < tam; i++) {
            arr[i] = 0;
        }
    }

    void incrementa(int &num) { // uso do '&' indica passagem por referencia, permitindo que a funcao modifique diretamente o valor da variavel original
        num++; // num += 1;
    }*/

    // ponteiro/alocacao ---------------------------------------
    int *ptr = new int; // aloca espaço para um inteiro na memoria
    (*ptr) = 42; // atribui um valor ao espaco de memoria alocado. (<ponteiro>*) acessa o conteudo do ponteiro e nao ele em si (endereco de memoria)
    delete ptr; // libera a memoria alocada. agora, prt == NULL

    int tamanho = 5;
    int *arr = new int[tamanho]; // aloca espaço para um array de inteiros na memoria
    for (int i = 0; i < tamanho; ++i) { // preenche o array com valores
        arr[i] = i * 10;
    }
    delete[] arr; // libera a memoria alocada para o array

    return 0;
}

/*

input: tamanho N (N <= 30) do array em seguida dos N elementos dele
output: para cada elemento desse array, imprima 0 se ele for uma letra maiuscula, 1 se for uma letra minúscula e 3 para o restante dos caracteres. Entretanto, imprima o novo array composto por 0, 1 e 3 INVERTIDO
  
|Sample #1:
input:
	5
	Davi!

Transformando o array em 0, 1 e 2 seguindo as regras:
	01113

Imprimindo em ordem invertida:
	31110

Output: 31110

*/