#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

int BinarySearch(char** lista, int nColunas, char* procurado) {
    int left = 0, right = nColunas-1;
    while (left <= right) {
        int m = (left+right)/2;
        if(!strcmp(procurado, lista[m])) return 1;
        else if(strcmp(procurado, lista[m]) < 0) right = m-1;
        else left = m+1;
    }
    return 0;    
}

int main() {
    int e;
    cin >> e;
    char** lista = (char**) malloc(e * (sizeof(char*)));
    for (int i = 0; i < e; i++) {
        lista[i] = (char*) malloc(31);
        scanf(" %s", lista[i]);
    }
    int q;
    cin >> q;
    char** consulta = (char**) malloc(q * (sizeof(char*)));
    for (int i = 0; i < q; i++) {
        consulta[i] = (char*) malloc(31);
        scanf(" %s", consulta[i]);
        if(BinarySearch(lista, e, consulta[i])) cout << "+" << endl;
        else cout << "-" << endl;
    }
    return 0;
}

/*
Uma quantidade surpreendente de estudantes solicitou matrícula na 
disciplina de Algoritmos e Estruturas de Dados. Precisamos da sua 
ajuda para buscar de forma eficiente (use busca binária) se um dado 
estudante está dentre aqueles que solicitaram matrícula na 
disciplina em questão.

A primeira linha da entrada contém o número 0 < e <= 100.000 de 
estudantes que solicitaram matrícula. Em cada uma das próximas e 
linhas, tem-se o nome n do e-ésimo estudante (0 < |n| <= 30 letras 
minúsculas, sem espaço). Os estudantes são listados em ordem 
alfabética (lexicográfica). Não existem dois ou mais estudantes com 
o mesmo nome. Após a lista dos estudantes, a entrada contém o número 
0 < q <= 100.000 de consultas. Em cada uma das próximas q linhas, 
tem-se um nome n (0 < |n| <= 30 letras minúsculas, sem espaço).

Para cada consulta, imprima “+” se o estudante em questão tiver 
solicitado matrícula em Algoritmos e Estruturas de Dados. 
Imprima “-”, caso contrário.

Sample input#1:
5
amanda
emanoel
gustavo
lucas
pedro
4
alexandre
pedro
gustaov
gustavo

Sample output#1:
-
+
-
+

*/