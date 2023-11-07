#include <iostream>
using namespace std;

typedef struct Process
{
    char pro_name[3];
    int arrival_time;
    int burst_time;
    int remaining_burst_time;
    int turn_around_time;
    int waiting_time;
} Process;

int main()
{

    int no_procs, time_quantum;
    cout << "Enter the number of processes: ";
    cin >> no_procs;
    cout << "Enter the time quantum: ";
    cin >> time_quantum;

    Process arr[no_procs];

    for (int i = 0; i < no_procs; i++)
    {
        arr[i].pro_name[0] = 'P';
        arr[i].pro_name[1] = i + 1 + '0';
        arr[i].pro_name[2] = '\0';

        cout << "Enter the Arrival Time for " << arr[i].pro_name << ": ";
        cin >> arr[i].arrival_time;

        cout << "Enter the Burst Time for " << arr[i].pro_name << ": ";
        cin >> arr[i].burst_time;

        arr[i].remaining_burst_time = arr[i].burst_time;
    }

    int current_time = 0;
    bool all_processes_completed = false;

    while (!all_processes_completed)
    {
        all_processes_completed = true; // assume

        for (int i = 0; i < no_procs; i++)
        {
            if (arr[i].remaining_burst_time > 0 && arr[i].arrival_time <= current_time)
            {
                all_processes_completed = false;

                if (arr[i].remaining_burst_time <= time_quantum)
                {
                    current_time = current_time + arr[i].remaining_burst_time;
                    arr[i].turn_around_time = current_time - arr[i].arrival_time;
                    arr[i].waiting_time = arr[i].turn_around_time - arr[i].burst_time;
                    arr[i].remaining_burst_time = 0;
                }
                else
                {
                    current_time = current_time + time_quantum;
                    arr[i].remaining_burst_time = arr[i].remaining_burst_time - time_quantum;
                }
            }
        }

        for (int i = 0; i < no_procs; i++)
        {
            cout << "Turnaround for " << arr[i].pro_name << "\t" << arr[i].turn_around_time << "\t"
                 << "Waiting_time for :- " << arr[i].waiting_time << endl;
        }

        int total_turnaround_time = 0, total_waiting_time = 0;

        for (int i = 0; i < no_procs; i++)
        {
            total_turnaround_time += arr[i].turn_around_time;
            total_waiting_time += arr[i].waiting_time;
        }

        float avg_turnaround_time = (float)total_turnaround_time / no_procs;
        float avg_waiting_time = (float)total_waiting_time / no_procs;

        cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
        cout << "Average Waiting Time: " << avg_waiting_time << endl;
    }
    return 0;
}
