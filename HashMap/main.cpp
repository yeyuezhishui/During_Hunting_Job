#include <iostream>
#include <string>
#include "hashmap.cpp"


using namespace std;
int main(void)
{
    HashMap<string,string, HashFunc<string>,EqualFunc<string> > hashmap(100);
    hashmap.insert("Me","yeyuezhishui");
    hashmap.insert("Son","Aster");

    //
    HashMap<int,int, HashFunc<int>,EqualFunc<int> > hashmap2(100);
    hashmap2.insert(1,2);
    hashmap2.insert(3,4);

    cout << hashmap["Me"]<<endl;
    cout << hashmap2[1] << endl;
    cout << hashmap["Son"] << endl;
    cout << hashmap[3] << endl;

    hashmap.del("Me");
    hashmap["Me"];
    hashmap.del("Son");
    hashmap["Son"];
    hashmap2.del(1);
    hashmap2[1];

    return 0;
}
