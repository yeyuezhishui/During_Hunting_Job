# include <iostream>
# include <map>
# include <utility>
using namespace std;
int main(void)
{
    long long int n;
    cin  >> n;
    while(n--)
    {
        long long int m;
        cin >> m;
        map<pair<long long int,long long int>,long long int> count;
        map<pair<long long int,long long int>,long long int> mark;
        map<pair<long long int,long long int>,long long int> max;
        long long int maxi = 0;
        while(m--)
        {
            long long int y;
            cin >> y;
            while(y--)
            {
                long long int t1,t2;
                cin >> t1 >> t2;
                if(mark[make_pair(t1,t2)] == m+1)
                {
                    mark[make_pair(t1,t2)] = m;
                    count[make_pair(t1,t2)] += 1;
                    if(count[make_pair(t1,t2)] > max[make_pair(t1,t2)])
                    {
                        max[make_pair(t1,t2)] = count[make_pair(t1,t2)];
                        if(max[make_pair(t1,t2)]>maxi)
                        {
                            maxi = max[make_pair(t1,t2)];
                        }
                    }
                }
                else
                {
                    mark[make_pair(t1,t2)] = m;
                    count[make_pair(t1,t2)] = 1;
                }

            }
        }
        if(maxi == 0 ) maxi = 1;
        cout  << maxi;
    }
    return 0;
}
