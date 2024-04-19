#include <stdio.h>
#define TAM_MAX 30

int main() {
    int N;
    int array[TAM_MAX];

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char caractere;
        scanf(" %c", &caractere);

        if(('A' <= caractere) && (caractere <= 'Z')) { // letra maiuscula
            array[i] = 0;
        } 
        else if(('a' <= caractere) && (caractere <= 'z')) { // letra minuscula
            array[i] = 1;
        }
        else {
            array[i] = 3;
        }
    }
    
    for(int i = (N-1); i >= 0; i--) {
        printf("%d ", array[i]);
    } 
    printf("\n");
    
    return 0;
}

//------------------------------------------------------------

/*
#include <iostream>
using namespace std;

#define TAM_MAX 30

int main() {
    int N;
    int array[TAM_MAX];

    cin >> N;
    for (int i = 0; i < N; i++) {
        char caractere;
        cin >> caractere;
        if(('A' <= caractere) && (caractere <= 'Z')) { // letra maiuscula
            array[i] = 0;
        } 
        else if(('a' <= caractere) && (caractere <= 'z')) { // letra minuscula
            array[i] = 1;
        }
        else {
            array[i] = 3;
        }
    }

    for(int i = (N-1); i >= 0; i--) {
        cout << array[i] << ' ';
    } 
    cout << endl;
    
    return 0;
}*/