#include <bits/stdc++.h>
using namespace std;


// updates - check the type of first element of vector and add if else according to that

void readF()
{
    map<string, pair<string, int>> mot; // machine operational table

    vector<string> imp = {"STOP", "ADD", "SUB", "MULT", "MOVER", "MOVEM", "COMP", "BC", "DIV", "READ", "PRINT"}; // imperative instructions
    vector<string> ad = {"START", "END", "ORIGIN", "EQU", "LTORG"};                                              // assembler directives
    vector<string> dl = {"DC", "DS"};                                                                                // declarative statements
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

    // main logic

    fstream myfile("a.asm", ios::in);
    string word;

    ofstream ic("ic.txt");
    int lc; // location counter
    int stcnt = 0;

    while (getline(myfile, word))
    {
        vector<string> ins;
        string temp;

        //splitting each line and separating each word
        for (int i = 0; i < word.length(); i++)
        {
            if (word[i] != ' ')
            {
                temp += word[i];
            }
            else
            {
                ins.push_back(temp);
                temp = "";
            }
        }
        ins.push_back(temp);

        // for start
        for (int i = 0; i < ins.size(); i++)
        {
            if (ins[i] == "START")
            {
                lc = stoi(ins[i + 1]);
                auto it = mot.find(ins[i]);
                ic << "(" << it->second.first << " " << it->second.second << "),(C," << lc << ")\n";
                ins.clear();
                break;
            }
            break;
        }

        

        // // for others
        if (ins.size() != 0)
        {
            for (int i = 0; i < ins.size()-1; i++)
            {
                auto it = mot.find(ins[i]);
                if (it != mot.end())
                {

                    if (it->second.first != "reg")
                    {
                        // if the next of instruction is a symbol
                        string test = "";
                        test = ins[i+1];
                        cout<<test<<"\n";
                        // cout<<test<<endl;
                        
                        auto symbol = st.find(test);
                        if (symbol != st.end()) // if that symbol is already in the symbol table
                        {
                            ic << "(" << it->second.first << "," << it->second.second << ") "
                               << "(S "<< symbol->second.first << ")";
                        }
                        else
                        {
                            ++stcnt;
                            st[temp] = make_pair(stcnt, 0);
                            ic << "(" << it->second.first << "," << it->second.second << ") "
                               << "(S " << st[temp].first << ")";
                        }
                    }
                    // else if (it->second.first == "reg")
                    // {
                    //     ic << "(" << it->second.second << ") ";
                    //     string temp = "";
                    //     temp = ins[ins.size() - 1];
                    //     cout<<temp<<"\n";
                        // if (temp[0] != '=') // if the next of instruction isn't a literal
                        // {

                        //     auto symbol = st.find(temp);
                        //     if (symbol != st.end()) // if a symbol is already present in the symbol table
                        //     {
                        //         ic << "("
                        //            << "S " << symbol->second.first
                        //            << ")\n";
                        //     }
                        //     else // if a symbol is not present
                        //     {
                        //         ++stcnt;
                        //         st[temp] = make_pair(stcnt, 0);
                        //         ic
                        //             << "("
                        //             << "S " << st[temp].first
                        //             << ")\n";
                        //     }
                        // }
                        // else
                        // {
                        //     ic << "("
                        //        << "L"
                        //        << ")\n";
                        // }
                    }
                }
                // else
                // {
                //     stcnt++;
                //     if (ins[i][0] != '=')
                //         st[ins[i]] = make_pair(stcnt, 0);
                // }
            }
            ic << "\n";
        // }
//         // if (cnt == 4)
//         // {
//         //     break;
//         // }
    }

    // for (auto it : st)
    // {
    //     cout << it.first << " " << it.second.first << endl;
    // }
}

int main()
{
    readF();
}
