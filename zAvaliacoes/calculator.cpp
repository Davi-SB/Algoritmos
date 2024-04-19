#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<float> vec;
    float nota, sum=0;
    while(cin >> nota) vec.push_back(nota);

    sort(vec.begin(), vec.end(), greater<float>());
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << ' ';
        if(i == 11) cout << "| ";
    } cout << endl;

    for (int i = 0; i < 12; i++) sum += vec[i];
    cout << "NOTA APs: " << (sum/12) << endl << endl;

    ///////////////////

    float N, N1, N2, EE = (2.5/10.f);
    N1 = ((4.f*(6.5/8.f)) + (6.f*(5.f/5.f)));
    N2 = ((1.f*(17.f/17.f)) + (2.f*(12.f/12.f)) + (7.f*(EE)));
    N = (N1 + N2)/2;
    cout << "Com EE=" << EE << ", a nota final seria: " << N << endl;
    cout << "confirmacao: " << ((3.5*EE)+(3.f)+(2.f*(6.5/8.f))+(1.f)+(0.5)) << endl;
    return 0;
} // g++ calculator.cpp -o calc && ./calc < input.in

/*
100 100 100 100 100 100 100 100 100 100 100 90 | 90 90 86 60 
NOTA APs: 99.1667

Com EE=0.25, a nota final seria: 7
confirmacao: 7
*/

/*
100
86
100
100
100
60
100
100
90
90
100
100
90
100
100
100
*/