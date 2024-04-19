#include <stdio.h> // C
#include <iostream> // C++

using namespace std; // C++

int main() {

    char a = 'a', b = 'b';

    // bool d;

    // scanf("%d %f %c", &a, &b, &c);
    // printf("Inteiro: %d Float: %f Char: %c\n", a, b, c);

    // cin >> a >> b >> c >> d;
    // cout << a << " " << b << " " << c << " " << d << endl;

    printf("%c\n", a + b);
    // cout << (char) a + b << endl;

    return 0;
}

#include <stdio.h> // C
#include <iostream> // C++
using namespace std; // C++

int main() {
    int a = 1, b = 3;

    if(a > b) {
        printf("sim\n");
    }
    else if(a == b){
        printf("nao\n");
    }
    else {
        printf("alo\n");
    }

    int array[10] = {}; // inicializa como 0
    int array2[3] = {1, 2, 3};

    int mat[3][3];
    int mat1[10][10][10]; // qtas dimensoes quiserem

    array[3] = 3;
    mat[0][1] = 2;

    scanf("%d\n", &array[3]);
    printf("%d\n", array[3]);
    cout << mat[0][1] << endl;

    return 0;
}

#include <stdio.h> // C
#include <iostream> // C++
using namespace std; // C++

#define size 100 // substituicao textual

int main() {
    int array[size];

    int a = 10;
    while(a > 0) {
        // fazer algo
        a--;
    }

    do {
        // fazer algo
        a--;
    } while(a > 0);

    for(int contador = 0; contador < 10; contador++ ) { // for(inicial; condicao; update)
        //cout << contador << endl;
    }

    for (int i = 0; i < 10; i++) {
        array[i] = i * 10;
    }
    
    for (int i = 0; i < 10; i++) {
        cout << array[i] << endl;
    }

    return 0;
}