#include <iostream>

#include "my_list.h"

using namespace std;

int main() {
    my_list<int> v;
    v.push_back(1);
    v.push_back(2);
    auto it = v.insert(v.begin(), 3);
    for(auto it = v.begin();it != v.end();++it){
        cout<<*it<<endl;
    }
    return 0;
}