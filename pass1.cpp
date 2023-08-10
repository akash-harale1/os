#include<bits/stdc++.h>
using namespace std;


class ic{

    string cl;
    int code;
    vector<pair<string,int>> rslt;
    public:
    ic()
    {
        cl="";
        code = 0;
    }

    ic(string cl, int code)
    {
        this->cl = cl;
        this->code = code;
        rslt.push_back(make_pair(this->cl,this->code));
    }

    void diplay()
    {
        for(auto it : rslt)
        {
            cout<<"("<<it.first<<","<<it.second<<")"<<endl;
        }
    }

};


void readF()
{
    map<string, pair<string,int>> mot;
    map<string,int> cc;
    vector<string> imp = {"ADD","SUB","STOP","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};
    vector<string> ad = {"START","END","ORIGIN","EQU","LTORG"};
    vector<string> dl = {"DC","DS"};
    vector<string> c = {"LT","LE","EQ","GT","GE","ANY"};
    for (int i = 0; i < imp.size(); i++)
    {
       mot[imp[i]] = make_pair("IS",i);                        
    }

    for (int i = 0; i < ad.size(); i++)
    {
       mot[ad[i]] = make_pair("AD",i);
    }

    for (int i = 0; i < dl.size(); i++)
    {
       mot[dl[i]] = make_pair("DL",i);
    }

    for(int i=0;i<c.size();i++)
    {
        cc[c[i]] = i+1;
    }
   
    // for(auto it:mot)
    // {
    //     cout<<it.first<<" "<<it.second.first<<" "<<it.second.second;
    //     cout<<endl;
    // }

    map<string,string> ans;

    fstream myfile;
    myfile.open("a.asm",ios::in);
    string temp;
    ic obj;
    while (getline(myfile,temp))
    {
        vector<string> temp2;
        string temp3;
        for(auto it:temp)
        {
            if(it!=' ')
            {
                temp3+=it;
            }
            else
            {
                temp2.push_back(temp3);
                temp3 = "";
            }
        }

        for(auto it:temp2)
        {
            cout<<it<<" ";

        }
        cout<<endl;
    }
    
}
int main()
{
    readF();
}