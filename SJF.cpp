#include<iostream>
using namespace std;

typedef struct Process
{
    char Processname [3];
    int burstTime ,waitingTime , arrivalTime , responseTime, turnAroundTime;

}Process;


void swap(Process arr[], int i, int j) {
    Process temp = arr[i];
    arr[i] = arr[j];
    arr[j] = arr[i];
}


int main()
{
    int numberOfProcess =0;

    cout<<"Enter the number of proces ";
    cin>>numberOfProcess;

    Process pros[numberOfProcess];

    for (int i = 0; i < numberOfProcess; i++)
    {
        pros[i].Processname[0] = 'p';
        pros[i].Processname[1] = i + 1;
        pros[i].Processname[2] = '\0';

        cout<<"Enetr burst time :- ";
        cin>>pros[i].burstTime; 
    }


    //sorting

    for (int i = 0; i < numberOfProcess; i++)
    {
        for (int j = i+1; j < numberOfProcess; j++)
        {
            if (pros[i].burstTime > pros[j].burstTime)
            {
                Process temp = pros[i];
                pros[i] = pros[j];
                pros[j] = pros[i];
            }   
        }
    }

        for (int i = 0; i < numberOfProcess; i++)
    {
        cout<<pros[i].Processname;
    }

    // Calculation
    pros[0].waitingTime = 0;
    for (int i = 0; i < numberOfProcess; i++)
    {
        if (i != 0 )
        {
            pros[i].waitingTime = pros[i - 1].waitingTime + pros[i -1].burstTime; 
        }
        pros[i].responseTime =pros[i].waitingTime;
        pros[i].turnAroundTime = pros[i].burstTime + pros[i].waitingTime ;
    }

    float avgTAT = 0,avgWT = 0;


    for (int i = 0; i < numberOfProcess; i++)
    {
        avgTAT += pros[i].turnAroundTime;
        avgWT += pros[i].waitingTime;
    }

    avgTAT /=numberOfProcess;
    avgWT /=numberOfProcess;

    cout<<"Average Turnaround Time "<< avgTAT<<endl;    
    cout<<"Average Waiting Time "<< avgWT;    
}