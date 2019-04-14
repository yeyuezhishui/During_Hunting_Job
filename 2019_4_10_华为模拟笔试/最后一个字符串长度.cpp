#include<iostream>
#include<string.h>
using namespace std;
int main(void)
{
    string cur;
    getline(cin,cur);
    int ans = 0;
    int last = cur.length() - 1;
    while(1)
    {
        if(cur[last]!=' ' && last != -1)
        {
            ans++;
            last--;
        }
        else break;
    }
    cout << ans;
    return 0;
}