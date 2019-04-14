# include<iostream>
# include<string.h>
# include<ctype.h>
using namespace std;
int main(void)
{
    string s;
    char a;
    cin >> s >> a;
    int i = 0;
    int ans = 0;
    for(i = 0; i< s.length(); i++)
    {
        if(isdigit(s[i]))
        {
            if(s[i] == a) ans++;
        }
        else
        {
            if(toupper(s[i]) == toupper(a)) ans++;
        }
    }
    cout << ans;
    return 0;
}