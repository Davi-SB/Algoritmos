#include <iostream>
#include <vector>
using namespace std;

using ll = unsigned long int;

ll mod(int n) { return n/*%1000000007*/; }

ll fib(int n, vector<ll>& memo) {
    if(memo[n] != 0) return memo[n];
    if((n == 1) || (n == 2)) {
        memo[n] = 1;
        return memo[n];
    }
    if(!n) return 0;
    int result = (fib(n-1, memo) + fib(n-2, memo));
    memo[n] = mod(result); // memoization step
    return memo[n];
}

int main() {
    int n; cin >> n;
    vector<ll> memo; memo.resize(n+1); // 1-based array
    cout << fib(n, memo) << endl;
    return 0;
} // 0 1 1 2 3 5 8