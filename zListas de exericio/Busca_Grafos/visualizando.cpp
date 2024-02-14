#include <iostream>
using namespace std;

// https://codeforces.com/problemset/gymProblem/100952/F

int strToKey(string str) {
    if(str == "Ahmad") return 0;
    if(str == "Mousaab") return 1;
    if(str == "Khalid") return 2;
    if(str == "Ali") return 3;
    if(str == "Nizar") return 4;
    if(str == "Bassel") return 5;
    if(str == "Kassem") return 6;
    if(str == "Saeed") return 7;
    if(str == "Fadel") return 8;
    if(str == "Salwa") return 9;
    if(str == "Samer") return 10;
    if(str == "Mona") return 11;
    if(str == "Abdo") return 12;
    if(str == "Qussi") return 13;
    return -1; // not found
}

int main() {

    int n; cin >> n;
    while(n--) {

        int lineCount; cin >> lineCount;
        while(lineCount--) {

            int keys[3];
            string line[3];
            for (int i = 0; i < 3; i++) {
                cin >> line[i];
                keys[i] = strToKey(line[i]);
            }

            //bool doPrint = false;
            //for (int i = 0; i < 3; i++) if((keys[i] == 1) || (keys[i] == 2) || (keys[i] == 6)) doPrint = true;
            
            //if(doPrint) {
                cout << keys[0] << ' ' << keys[1] << endl;
                cout << keys[0] << ' ' << keys[2] << endl;
                cout << keys[1] << ' ' << keys[2] << endl;
            //}
        }
        cout << endl;
    }

    return 0;
} // g++ visualizando.cpp -o GA && ./GA < input.in > outputGrafo.out