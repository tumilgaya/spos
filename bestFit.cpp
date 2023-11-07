#include <iostream>
using namespace std;

int min(int blockarr[],int old,int newindx)
{
    return(blockarr[newindx] <= blockarr[old])?newindx:old;
}

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
        int bestIndx = -1;
        for (int j = 0; j < blockSize; j++)
        {
            if (blockArr[j] >= ProcessorArr[i])
            {
                if (bestIndx == -1)
                {
                    bestIndx = j;
                }
                else 
                {
                    bestIndx = min(blockArr,bestIndx,j);
                }
                
            }
        }
        if (bestIndx != -1)
        {
            allocation[i] = bestIndx;
            blockArr[bestIndx] -= ProcessorArr[i];
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
    int blockSize[] = {500, 100, 200, 300};
    int processSize[] = {199, 100};

    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    NextFit(blockSize, m, processSize, n);

    return 0;
}