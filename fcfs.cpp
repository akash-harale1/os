#include <bits/stdc++.h>
using namespace std;
class process
{

public:
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;

    process()
    {
        id = at = bt = ct = tat = wt = 0;
    }

    void setInfo()
    {
        cout << "Enter process id : ";
        cin >> this->id;
        cout << "Enter the arrival time : ";
        cin >> this->at;
        cout << "Enter the burst time : ";
        cin >> this->bt;
    }

    void getInfo()
    {
        cout << "Arrival time : " << this->at << " ";
        cout << "Burst time : " << this->bt << " ";
        cout << "Process id : " << this->id << " ";
        cout << endl;
    }

    bool operator<(const process &obj1)
    {
        return (at < obj1.at);
    };
};

void fcfs()
{
    vector<process> r;
    double averageTat = 0;
    double averageWT = 0;
    cout << "Enter total processes : ";
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        process temp;
        temp.setInfo();
        r.push_back(temp);
    }

    sort(r.begin(), r.end());
    for (int i = 0; i < r.size(); i++)
    {
        r[i].getInfo();
    }
    r[0].ct = r[0].bt;
    for (int i = 1; i < r.size(); i++)
    {
        r[i].ct = r[i - 1].ct + r[i].bt;
    }

    for (int i = 0; i < r.size(); i++)
    {
        r[i].tat = r[i].ct - r[i].at;
        r[i].wt = r[i].tat - r[i].bt;
        averageTat += r[i].tat;
        averageWT += r[i].wt;
    }

    cout<<"Average turnaround : "<<averageTat/n<<endl;
    cout<<"Average waiting : "<<averageWT/n<<endl;
}
int main()
{
    fcfs();
}