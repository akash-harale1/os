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

// string shortest(vector<process> p, )

void sjf()
{
    cout << "Enter number of processes : ";

    int num;
    cin >> num;
    vector<process> r;

    for (int i = 0; i < num; i++)
    {
        process temp;
        temp.setInfo();
        r.push_back(temp);
    }

    sort(r.begin(), r.end(), process::shorter);
    int initialArrival = r[0].at;
    bool flag = true;
    int end = 0;
    int atTracker = 0;
    int cnt = 0;

    while (flag)
    {
        int avgBurst = 0;
        int shortest = INT_MAX;
        process *shortProcess = nullptr;
        for (int i = 0; i <= end; i++)
        {
            if (r[i].bt < shortest && r[i].bt > 0)
            {
                shortest = r[i].bt;
                shortProcess = &r[i];
            }
        }
        if (shortProcess->bt != 0 && shortProcess)
        {
            cnt++;
            shortProcess->bt -= 1;
            shortProcess->ct = cnt;
        }

        for (int i = 0; i < r.size(); i++)
        {
            avgBurst += r[i].bt;
        }

        // cout << "atTracker : " << atTracker << endl;
        if (r[end + 1].at - atTracker == 1)
        {
            end++;
        }
        if (end >= r.size())
        {
            end = r.size() - 1;
        }
        if (avgBurst == 0)
        {
            flag = false;
        }
                
        atTracker++;
        // cout << end << endl;
    }

    // shortProcess.getInfo();

    // for (int i = 0; i < r.size(); i++)
    // {
    //     r[i].getInfo();
    // }

    for (int i = 0; i < r.size(); i++)
    {
        cout << r[i].ct << " ";
    }
}

int main()
{
    sjf();
}
