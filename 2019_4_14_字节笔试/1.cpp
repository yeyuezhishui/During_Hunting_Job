# include <iostream>
# include <vector>
# include <string.h>
# include <stdlib.h>
using namespace std;

int main()
{
    vector<int> pix;
    vector<int> pix_new;
    string one_line;
    pix.clear();
    int num_one_line = 0;
    int num_all = 0;
    while(getline(cin,one_line))
    {
        int i = 0;
        num_one_line = 0;
        for(i=0;i<one_line.size();i++)
        {
            int m = atoi(one_line[i]);
            i+=1;
            pix.push_back(m);
            pix_new.push_back(m);
            num_one_line+=1;
            num_all +=1;
        }
    }
    int iter = 0;
    int flag1 = 0;
    int flag2 = 0;
    while(1)
    {
        flag2 = 0;
        flag1 =0;
        for(int i = 0; i<pix.size();i++)
        {
            if(pix[i] == 1)
            {
                flag1 = 1;
                if((i-1>=0 && pix[i-1]==2)||(i+1<num_all && pix[i+1] == 2)|| 
                (i-num_one_line>0 && pix[i-num_one_line] == 2) || 
                (i+num_one_line) < num_all && pix[i+num_one_line] == 2)
                {
                    flag2 = 1;
                    pix_new[i] = 2
                }
            }
        }
        if(flag1 == 0 || (flag1==1 && flag2 == 0))
        {
            break;
        }
        iter++;
    }
    if(flag1 == 1)
    {
        cout << -1;
    }
    else
    {
        cout<<iter;
    }
    
    //cout << "Hello world!" << endl;
    return 0;
}
