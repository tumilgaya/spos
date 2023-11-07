#include <iostream>
using namespace std;

void NextFit(int blockArr[], int blockSize, int ProcessorArr[], int processorSize)
{
    int allocation[processorSize];

    for (int i = 0; i < processorSize; i++)
    {
        allocation[i] = -1;
    }

    int j = 0, endptr = blockSize - 1;

    // pick one processor
    for (int i = 0; i < processorSize; i++)
    {
        while (j < blockSize)
        {
            if (blockArr[j] >= ProcessorArr[i])
            {
                allocation[i] = j;
                blockArr[j] -= ProcessorArr[i];

                // set a new endptr
                endptr = (j - 1) % blockSize;
                break;
            }

            if (j == endptr)
            {
                endptr = (j - 1) % blockSize;
                break;
            }

            j = (j + 1) % blockSize;
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < processorSize; i++)
    {
        cout << " " << i + 1 << "\t\t" << ProcessorArr[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1 << endl;
        else
            cout << "Not Allocated" << endl;
    }
}

int main()
{
    int blockSize[] = {50,100,200,300};
    int processSize[] = {199,100};

    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    NextFit(blockSize, m, processSize, n);

    return 0;
}