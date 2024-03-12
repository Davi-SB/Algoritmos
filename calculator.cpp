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
    cout << "NOTA:" << (int)(sum/12) << endl;
    return 0;
} // g++ calculator.cpp -o calc && ./calc < input.in

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
*/