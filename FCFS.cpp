#include <iostream>
using namespace std;

typedef struct Process
{
    // burstTime, turnAroundTime, waitingTime, responseTime, arrivalTime
    char processName[3];    //p1,p2....p99 p+i
    int burstTime;  //userDefined
    int turnAroundTime; //calculate
    int watingTime; //calculate
    int responseTime;   //calculate
}Process;



int main() {

    int numberOfProcess;
    cout << "Enter number of process:::: "; cin >> numberOfProcess;

    Process arr[numberOfProcess];

    for (int i = 0; i < numberOfProcess; i++)
    {
        arr[i].processName[0] = 'p';
        arr[i].processName[1] = i+1;
        arr[i].processName[2] = '\0';

        //bursttimes
        cout << "Enter burst time:::: "; cin >> arr[i].burstTime;
    }

    //calculate
    arr[0].watingTime = 0;
    for (int i = 0; i < numberOfProcess; i++)
    {
        if(i != 0) {
            arr[i].watingTime = arr[i - 1].watingTime + arr[i - 1].burstTime;
        }
        
        arr[i].turnAroundTime = arr[i].burstTime + arr[i].watingTime;
        arr[i].responseTime = arr[i].watingTime;
    }

    float avgTAT = 0, avgWT = 0;
    for (int i = 0; i < numberOfProcess; i++)
    {
        avgTAT += arr[i].turnAroundTime;
        avgWT += arr[i].watingTime;
    }

    avgTAT /= numberOfProcess;
    avgWT /= numberOfProcess;
    

    cout << "AVGTAT:::: " << avgTAT << endl;
    cout << "AVGWT:::: " << avgWT << endl;
    
    

    return 0;
}