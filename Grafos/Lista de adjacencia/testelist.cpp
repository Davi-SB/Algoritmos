#include <iostream>
#include <list>
using namespace std;

int main() {

    list<int> llist;
    llist.push_back(1);
    llist.push_back(2);
    //llist.push_back(3);
    llist.push_back(4);

    auto it = llist.begin(); cout << *it << endl;
    bool found = false;
    for(; (it != llist.end()) && (!found); it++) {
        if(*it >= 4) found = true;
    }
    it--;
    llist.insert(it, 3);

    for (const auto& element : llist) cout << element << "  "; 
    cout << endl;

    llist.insert(llist.begin(), -10);

    for (const auto& element : llist) cout << element << "  "; 
    cout << endl;

    cout << *(llist.begin()) << endl;

    llist.erase(llist.begin());
    
    for (const auto& element : llist) cout << element << "  "; 
    cout << endl << endl;

    it = llist.begin();
    found = false;

    for(; (it != llist.end()) && (!found); it++) {
        if(*it == 1) found = true;
    }
    if(!found) cerr << "not found - delEdge" << endl;

    if(it != llist.begin()) it--;
    llist.erase(it);

    for (const auto& element : llist) cout << element << "  "; 
    cout << endl << endl;
    
    return 0;
}