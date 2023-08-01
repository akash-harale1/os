#include <bits/stdc++.h>
using namespace std;

class process
{
public:
    int at;
    int bt;
    int ct;
    int tat;
    int pt;
    int wt;
    string pid;
    process()
    {
        at = bt = ct = tat = wt = 0;
        pid = "";
    }

    void setInfo()
    {
        cout << "Enter process id : ";
        cin >> pid;
        cout << "Enter the priority : ";
        cin >> pt;
        cout << "Enter arrival time : ";
        cin >> at;
        cout << "Enter burst time : ";
        cin >> bt;

        cout << endl;
    }

    void getInfo()
    {
        // cout << "Arrival time is : " << this->at << endl;
        // cout << "Burst time is : " << this->bt << endl;
        // cout << "Priority is : " << this->pt << endl;
        cout << "Process id : " << this->pid << endl;
        cout << "completion time : " << this->ct << endl;
        cout << endl;
    }
};

void priority()
{
    queue<process*> rt;
    int n;
    cout << "Enter the total number of processes : ";
    cin >> n;
    process **arr = new process *[n];
    for (int i = 0; i < n; i++)
    {
        process *temp = new process;
        temp->setInfo();
        arr[i] = temp;
    }
    // for arrival
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j]->at < arr[i]->at)
            {
                swap(arr[j], arr[i]);
            }
        }
    }
    // for priority

    int start = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i]->at == arr[i + 1]->at)
        {
            if (arr[i]->pt > arr[i + 1]->pt)
            {
                swap(arr[i], arr[i + 1]);
            }
        }
    }

    bool flag = true;
    arr[0]->ct = arr[0]->bt;
    int end = 0;
    arr[0]->bt = 0;

    if (arr[0]->ct > n)
    {
        end = n;
    }
    else
    {
        end = arr[0]->ct;
    }
    int cnt = 0;
    int avgBurst = 0;
    rt.push(arr[0]);
    while (flag)
    {
        process *shortest = new process;
        shortest->pt = INT_MAX;

        for (int i = 1; i < end; i++)
        {
          
            if (arr[i]->pt < shortest->pt && arr[i]->bt != 0)
            {
                shortest = arr[i];
            }
        }
        process *temp = rt.front();
        rt.pop();
        shortest->ct = shortest->bt + temp->ct;
        shortest->bt = 0;
        rt.push(shortest);
        // cout << shortest->pid << " : " << shortest->ct << endl;
        cnt++;
        if (shortest->ct > n)
        {
            end = n;
        }
        else
        {
            end = shortest->ct;
        }
        if (cnt==n)
        {
            flag = false;
        }
    }

    for (int i = 0; i < n; i++)
    {
        arr[i]->getInfo();
    }
}

int main()
{
    priority();
}
