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
    string id;
    process()
    {
        at = bt = ct = tat = wt = 0;
        id = "";
    }

    void setInfo()
    {
        cout << "Enter process id : ";
        cin >> id;
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
        cout << "Process id : " << this->id << endl;
        cout << "completion time : " << this->ct << endl;
        cout << endl;
    }
};
process *fcfsarr;
process *sjfarr;
process *prior;
process *rrarr;
int n;
void getInput()
{
    cout << "Enter the total number of processes : ";
    cin >> n;
    fcfsarr = new process[n];
    sjfarr = new process[n];
    prior = new process[n];
    for (int i = 0; i < n; i++)
    {
        process temp;
        temp.setInfo();
        fcfsarr[i] = temp;
        sjfarr[i] = temp;
        prior[i] = temp;
        rrarr[i] = temp;
    }
}

void fcfs()
{
    double averageTAT = 0, averageWT = 0;

    // sort according to at
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (fcfsarr[i].at > fcfsarr[j].at)
            {
                swap(fcfsarr[i], fcfsarr[j]);
            }
        }
    }
    bool flag = true;
    fcfsarr[0].ct = fcfsarr[0].at + fcfsarr[0].bt;
    cout << "Gantt chart : ";

    // check for the arrival time of current process and completion time of the last process
    cout << fcfsarr[0].id << "->" << fcfsarr[0].ct << ", ";
    for (int i = 1; i < n; i++)
    {
        if (fcfsarr[i - 1].ct < fcfsarr[i].at)
        {
            fcfsarr[i].ct = fcfsarr[i].at + fcfsarr[i].bt;
            cout << fcfsarr[i].id << "->" << fcfsarr[i].ct << ", ";
        }
        else
        {
            fcfsarr[i].ct = fcfsarr[i - 1].ct + fcfsarr[i].bt;
            cout << fcfsarr[i].id << "->" << fcfsarr[i].ct << ", ";
        }
    }

    for (int i = 0; i < n; i++)
    {
        fcfsarr[i].tat = fcfsarr[i].ct - fcfsarr[i].at;
        fcfsarr[i].wt = fcfsarr[i].tat - fcfsarr[i].bt;
        averageTAT += fcfsarr[i].tat;
        averageWT += fcfsarr[i].wt;
    }
    cout << endl;
    cout << "\nAverage turn around time : " << averageTAT / n << endl;
    cout << "Average waiting time : " << averageWT / n;
}

void sjf()
{
    double averageTAT = 0, averageWT = 0;

    // sort according to at
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (sjfarr[i].at > sjfarr[j].at)
            {
                swap(sjfarr[i], sjfarr[j]);
            }
        }
    }
    int currentTime = 0;
    int completedProcesses = 0;
    int shortestJobIndex;

    while (completedProcesses < n)
    {
        shortestJobIndex = -1;
        int shortestJobTime = INT_MAX;

        // Find the process with the shortest remaining burst time among the uncompleted processes
        for (int i = 0; i < n; i++)
        {
            if (sjfarr[i].at <= currentTime && sjfarr[i].bt < shortestJobTime && sjfarr[i].ct == 0)
            {
                shortestJobIndex = i;
                shortestJobTime = sjfarr[i].bt;
            }
        }

        if (shortestJobIndex == -1)
        {
            // If no eligible process is found at the current time, find the next arrival time
            int nextArrivalTime = INT_MAX;
            for (int i = 0; i < n; i++)
            {
                if (sjfarr[i].at > currentTime && sjfarr[i].at < nextArrivalTime && sjfarr[i].ct == 0)
                {
                    nextArrivalTime = sjfarr[i].at;
                }
            }
            currentTime = nextArrivalTime;
        }
        else
        {
            // Execute the shortest job for one time unit
            sjfarr[shortestJobIndex].bt -= 1;
            currentTime += 1;

            if (sjfarr[shortestJobIndex].bt == 0)
            {
                // If the process is completed, update its completion time and set completed flag
                sjfarr[shortestJobIndex].ct = currentTime;
                sjfarr[shortestJobIndex].tat = sjfarr[shortestJobIndex].ct - sjfarr[shortestJobIndex].at;
                sjfarr[shortestJobIndex].wt = sjfarr[shortestJobIndex].tat - sjfarr[shortestJobIndex].bt;
                completedProcesses++;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        sjfarr[i].getInfo();
    }
}

void priority()
{

    // Sort according to arrival time and priority
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (prior[j].at < prior[i].at || (prior[j].at == prior[i].at && prior[j].pt < prior[i].pt))
            {
                swap(prior[j], prior[i]);
            }
        }
    }

    int currentTime = 0;
    int completedProcesses = 0;
    int highestPriorityIndex;

    while (completedProcesses < n)
    {
        highestPriorityIndex = -1;
        int highestPriority = INT_MAX;

        // Find the process with the highest priority among the uncompleted processes
        for (int i = 0; i < n; i++)
        {
            if (prior[i].at <= currentTime && prior[i].pt < highestPriority && prior[i].ct == 0)
            {
                highestPriorityIndex = i;
                highestPriority = prior[i].pt;
            }
        }

        if (highestPriorityIndex == -1)
        {
            // If no eligible process is found at the current time, find the next arrival time
            int nextArrivalTime = INT_MAX;
            for (int i = 0; i < n; i++)
            {
                if (prior[i].at > currentTime && prior[i].at < nextArrivalTime && prior[i].ct == 0)
                {
                    nextArrivalTime = prior[i].at;
                }
            }
            currentTime = nextArrivalTime;
        }
        else
        {
            // Execute the highest priority process till completion
            currentTime += prior[highestPriorityIndex].bt;
            prior[highestPriorityIndex].ct = currentTime;
            prior[highestPriorityIndex].tat = prior[highestPriorityIndex].ct - prior[highestPriorityIndex].at;
            prior[highestPriorityIndex].wt = prior[highestPriorityIndex].tat - prior[highestPriorityIndex].bt;
            completedProcesses++;
        }
    }

    // Print results
    cout << "\nPriority Scheduling (Non-Preemptive) Results:\n";
    for (int i = 0; i < n; i++)
    {
        prior[i].getInfo();
    }
}

void rr()
{
    int quantum;
    cout << "Enter the time quantum : ";
    cin >> quantum;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (rrarr[i].at > rrarr[j].at)
            {
                swap(rrarr[i], rrarr[j]);
            }
        }
    }

    int currentTime = 0;
    int *remainingBurstTimes = new int[n];

    for (int i = 0; i < n; i++)
    {
        remainingBurstTimes[i] = rrarr[i].bt;
    }

    while (true)
    {
        bool allCompleted = true;
        for (int i = 0; i < n; i++)
        {
            if (remainingBurstTimes[i] > 0)
            {
                allCompleted = false;
                if (remainingBurstTimes[i] > quantum)
                {
                    currentTime += quantum;
                    remainingBurstTimes[i] -= quantum;
                }
                else
                {
                    currentTime += remainingBurstTimes[i];
                    remainingBurstTimes[i] = 0;
                    rrarr[i].ct = currentTime;
                    rrarr[i].tat = rrarr[i].ct - rrarr[i].at;
                    rrarr[i].wt = rrarr[i].tat - rrarr[i].bt;
                }
            }
        }

        if (allCompleted)
            break;
    }
    // Print results
    cout << "\nRound Robin Scheduling Results:\n";
    for (int i = 0; i < n; i++)
    {
        rrarr[i].getInfo();
    }
}

int main()
{
    getInput();
    // fcfs();
    // sjf();
    // priority();
    rr();
}