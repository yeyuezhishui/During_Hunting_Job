#include<iostream>
#include<string>
#include<set>
using namespace std;
int main(void)
{
    int n;
    while(cin >> n)
    {
        set<int> intset;
        for(int i = 0; i< n; i++)
        {
            int temp;
            cin >> temp;
            intset.insert(temp);
        }
        set<int>::iterator iter;
        for(iter = intset.begin(); iter != intset.end(); iter++ )
        {
            cout << *iter << endl;
        }
    }   
    return 0;
}
