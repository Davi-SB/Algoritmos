#include <stdio.h>

int main() {
    /*----------------------------------------------------------------------------------
    Input: tamanho N seguido de N elementos

    5
    3 -10 7 12 156
    */
    int N;
    scanf("%d", &N); // intput inteiro --> %d
    
    int array[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &array[i]); 
        // como o scanf esta recebendo inputs de int (%d), os espacos entre os numros 
        // sao ignorados automaticamente e usados pelo scanf para saber onde "comeca" e 
        // "termina" um numero
    }


    /* ----------------------------------------------------------------------------------
    Input: uma linha composta por um numero inteiro, um float e um caractere, nessa ordem

    19 10.3 d    
    */
    int inteiro;
    float decimal;
    char caractere;

    scanf("%d %f %c", &inteiro, &decimal, &caractere); 
    // note que, mais uma vez, o scanf usa a formatacao da entrada (primeiro argumento, 
    // parte entre aspas) para saber onde "comeca" e "termina" cada valor. O espaco 
    // separa cada um deles e isso fica explicito nesse primeiro argumento


    /* ----------------------------------------------------------------------------------
    Input: uma linha composta por um numero inteiro, um float e um caractere, nessa ordem.
           Porem, dessa vez, eles estao separados por virgulas

    19,10.3,d    
    */
    int inteiro1;
    float decimal1;
    char caractere1;

    scanf("%d,%f,%c", &inteiro1, &decimal1, &caractere1); 
    // Dessa vez, formatamos os valores separados por virgulas no scanf.
    // Dessa forma o scanf armazena corretamente os valores nas devidas variaveis.
    // O mesmo se aplica nao somente para virgula, mas para qualquer ou quaisquer caractere


    /*----------------------------------------------------------------------------------
    Input: N elementos sabendo que (N <= 30)

    3 -10 7 12 156 34 73 1 0
    */
    int array[30]; // declaracao com tamanho 30 pois sabe-se que nao havera mais elementos que isso
    
    // i --> variavel usada como indice para percorrer o array
    // temp --> variavel temporaria para armazenar o int que acabou de ser armazenado
    int i = 0, temp; 

    // while(scanf()) funciona pois quando nao ha mais nenhum input no arquivo, ou seja, 
    // quando nao ha mais inteiros para ser armazenados, o scanf retorna EOF (End Of File)
    // o que interrompe o laco while
    while(scanf("%d", &temp) != EOF) { // obs: tanto cin como scanf podem acontecer diretamente no array[i]. temp nesse caso so existe para facilidar a visualizacao
        array[i] = temp;
        i++;
    }

    return 0;
}