#include<iostream>
#include<string.h>
using namespace std;

typedef struct {
    char nome[30];
    int tempo;
} Pessoa;

void Merge(Pessoa arr[], int left, int right, int size) {
    Pessoa temp[size];
    int m = (left+right)/2;
    int i1 = left, i2 = m+1;
    for (int i = left; i <= right; i++) {
        temp[i] = arr[i];
    }
    for (int curr = left; curr <= right; curr++) {
        if(i1 == m+1) arr[curr] = temp[i2++];
        else if(i2 == right+1) arr[curr] = temp[i1++];
        else if(temp[i1].tempo < temp[i2].tempo) arr[curr] = temp[i1++];
        else if(temp[i1].tempo > temp[i2].tempo) arr[curr] = temp[i2++];
        else { // IGUAL
            if (strcmp(temp[i1].nome, temp[i2].nome) < 0) {
                arr[curr] = temp[i1++];
            }
        }
    }
}

void MergeSort(Pessoa arr[], int left, int right, int size) {
    if(left < right) {
        int m = (left+right)/2;
        MergeSort(arr, left, m, size);
        MergeSort(arr, m+1, right, size);
        Merge(arr, left, right, size);
    }
}

// g++ -std=c++17 MaratonaCin.cpp -o main && time ./main < input.txt

int main() {
    int c;
    cin >> c;
    Pessoa lista[c];
    for (int i = 0; i < c; i++) {
        scanf(" %s", lista[i].nome);
        cin >> lista[i].tempo;
    }
    MergeSort(lista, 0, c-1, c);  
    for (int i = 0; i < c; i++) {
        cout << lista[i].nome << " " << lista[i].tempo << endl;
    }
    return 0;
}

/*
No último final de semana, ocorreu a Maratona Internacional do Centro de Informática. 
Considerando a quantidade surpreendente de concluintes, a organização pediu a sua 
ajuda para ordenar os resultados. Os participantes que concluíram a corrida devem ser 
listados daqueles com menor tempo para aqueles com maior tempo de prova; eventuais 
empates são resolvidos pela ordem alfabética (lexicográfica) do nome dos participantes.

A primeira linha da entrada contém o número 0 < c <= 100.000 de concluintes. Em cada 
uma das próximas c linhas, tem-se o nome n do c-ésimo participante (0 < |n| <= 30 
letras minúsculas, sem espaço) e o seu tempo t de prova em segundos (0 < t <= 21.600). 
Na entrada, os participantes são listados em ordem lexicográfica.

Imprima os resultados ordenados corretamente.

Sample input#1:
8
alice 8044
ana 20400
daniel 7299
eliud 7199 
gustavo 20400
laura 8044
sophia 15000
vanderlei 7399

Sample output#1:
eliud 7199
daniel 7299
vanderlei 7399
alice 8044
laura 8044
sophia 15000
ana 20400
gustavo 20400
*/