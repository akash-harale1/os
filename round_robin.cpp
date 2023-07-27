#include <bits/stdc++.h>
using namespace std;

class process
{
public:
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    string pid;
    process()
    {
        at = bt = ct = tat = wt = 0;
        pid = "";
    }

    void setInfo()
    {
        cout << "Enter arrival time : ";
        cin >> at;
        cout << "Enter burst time : ";
        cin >> bt;
        cout << "Enter process id : ";
        cin >> pid;
        cout << endl;
    }

    void getInfo()
    {
        cout << "Arrival time is : " << this->at << endl;
        cout << "Burst time is : " << this->bt << endl;
        cout << "Completion time is : " << this->ct << endl;
        cout << "Process id : " << this->pid << endl;
        cout << endl;
    }
    static bool shorter(process &obj1, process &obj2)
    {
        return obj1.at < obj2.at;
    }
};

void rr()
{
    queue<process *> qu;
    int tq;

    vector<process *> v;
    cout << "Enter total number of processes : ";
    int num;
    cin >> num;
    cout << "Enter time slicing : ";
    cin >> tq;
    int cnt = 0;
    for (int i = 0; i < num; i++)
    {
        process *temp = new process();
        temp->setInfo();
        v.push_back(temp);
        qu.push(temp);
    }

    bool flag = true;
    while (!qu.empty())
    {
        process *temp = qu.front();
        qu.pop();
        if (temp->bt >= tq)
        {
            temp->bt -= tq;
            cnt += tq;
            temp->ct = cnt;
            cout << temp->pid << " : " << temp->ct << endl;
        }
        else
        {
            cnt += temp->bt;
            temp->bt = 0;
            temp->ct = cnt;
            cout << temp->pid << " : " << temp->ct << endl;
        }
        if (temp->bt > 0)
        {
            qu.push(temp);
        }
    }

    // for (int i = 0; i < v.size(); i++)
    // {
    //     cout << v[i]->ct << " ";
    // }
}

int main()
{
    rr();
}
