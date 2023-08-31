#include <bits/stdc++.h>
using namespace std;
void readF()
{
    int lccnt = 0;
    map<string, pair<string, int>> mot; // machine operational table

    vector<string> imp = {"STOP", "ADD", "SUB", "MULT", "MOVER", "MOVEM", "COMP", "BC", "DIV", "READ", "PRINT"}; // imperative instructions
    vector<string> ad = {"START", "END", "ORIGIN", "EQU", "LTORG"};                                              // assembler directives
    vector<string> dl = {"DC", "DS"};                                                                            // declarative statements
    vector<string> c = {"LT", "LE", "EQ", "GT", "GE", "ANY"};                                                    // compare statements
    vector<string> reg = {"AREG", "BREG", "CREG", "DREG"};                                                       // registers
    map<string, string> lt;                                                                                      // literal table
    map<string, pair<int, int>> st;                                                                              // symbol table

    // assigning the different instructions their codes and storing them in mot
    for (int i = 0; i < imp.size(); i++)
    {
        mot[imp[i]] = make_pair("IS", i);
    }

    for (int i = 0; i < ad.size(); i++)
    {
        mot[ad[i]] = make_pair("AD", i);
    }

    for (int i = 0; i < dl.size(); i++)
    {
        mot[dl[i]] = make_pair("DL", i);
    }

    for (int i = 0; i < reg.size(); i++)
    {
        mot[reg[i]] = make_pair("reg", (i + 1));
    }

    for (int i = 0; i < c.size(); i++)
    {
        mot[c[i]] = make_pair("c", (i + 1));
    }

    // main logic

    fstream myfile("a.asm", ios::in);
    ofstream ic("ic.txt");
    string word;
    int stcnt = 0;
    while (getline(myfile, word))
    {
        vector<string> ins;
        string temp;
        for (int i = 0; i < word.length(); i++)
        {
            if (word[i] == ' ')
            {
                ins.push_back(temp);
                temp = "";
            }
            else
            {
                temp += word[i];
            }
        }
        ins.push_back(temp);
        if (ins[0] == "START" && ins.size() == 2)
        {
            lccnt = stoi(ins[1]);
        }
        auto it = mot.find(ins[0]);
        if (it->second.first == "IS")
        {
            ic << "(IS," << it->second.second << ") ";
            for (int i = 1; i < ins.size(); i++)
            {
                auto temp = mot.find(ins[i]);
                if (temp != mot.end())
                {
                    if (temp->second.first == "reg" || temp->second.first == "c")
                    {
                        ic << "(" << temp->second.second << ") ";
                    }
                }
                else
                {
                    auto temp1 = st.find(ins[i]);
                    if (temp1 == st.end())
                    {
                        st[ins[i]] = make_pair(++stcnt, 0);
                    }
                    temp1 = st.find(ins[i]);
                    ic << "(S," << temp1->second.first << ")";
                }
            }
            ic << "\n";
        }
    }

    // for (auto it : st)
    // {
    //     cout << it.first << " " << it.second.first << " ";
    //     cout << endl;
    // }
}

int main()
{
    readF();
}
