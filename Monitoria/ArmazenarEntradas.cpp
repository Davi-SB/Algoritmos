#include <iostream>
using namespace std;

int main() {
    /*----------------------------------------------------------------------------------
    Input: tamanho N seguido de N elementos

    5
    3 -10 7 12 156
    */
    int N;
    cin >> N;
    
    int array[N];
    for (int i = 0; i < N; i++) {
        cin >> array[i]; 
        // como array[i] eh um elemento do tipo int, o cin "usa" essa informacao para
        // armazenar os numeros corretamente. Entao nao eh necessario se preocupar com
        // os espacos: eles serao ignorados (nao armazenados)
    }


    /* ----------------------------------------------------------------------------------
    Input: uma linha composta por um numero inteiro, um float e um caractere, nessa ordem

    19 10.3 d    
    */
    int inteiro;
    float decimal;
    char caractere;

    // armazenamento ocorre da esquerda para a direita, na ordem da linha do input
    cin >> inteiro >> decimal >> caractere; 
    // note que, mais uma vez, cin "usa" os espacos para separar cada valor e, dessa
    // forma, os dados serao armazenados corretamente


    /*----------------------------------------------------------------------------------
    Input: N elementos sabendo que (N <= 30)

    3 -10 7 12 156 34 73 1 0
    */
    int array[30]; // declaracao com tamanho 30 pois sabe-se que nao havera mais elementos que isso
    
    // i --> variavel usada como indice para percorrer o array
    // temp --> variavel temporaria para armazenar o int que acabou de ser armazenado
    int i = 0, temp; 

    // ao escrever while(cin >> temp), está basicamente dizendo: "enquanto for possível armazenar
    // um valor válido para a variável temp a partir do input padrao (cin), continue executando 
    // o loop".
    while(cin >> temp) { // obs: tanto cin como scanf podem acontecer diretamente no array[i]. temp nesse caso so existe para facilidar a visualizacao
        array[i] = temp;
        i++;
    }

    return 0;
}