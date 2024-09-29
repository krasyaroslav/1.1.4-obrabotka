#include <stdio.h>
#include <stdlib.h>


void buildDataForGist(int* dataPtr, double* gistPtr, int dataNum, int maxNum, int groupSize);


int main()
{
    int dataNum = 4000,
        groupSize = 0,
        maxNum = 0;

    printf("Gruppirovka po ");
    scanf("%d", &groupSize);

    FILE* filePtr = fopen("experiment.txt", "r");

    int * dataPtr = (int*)calloc(dataNum, sizeof(int));

    for (int i = 0; i < dataNum; i++)
        fscanf(filePtr, "%d", dataPtr + i);

    for (int i = 0; i < dataNum; i++)
    {
        if (maxNum < dataPtr[i]) maxNum = dataPtr[i];
        printf("%d ", dataPtr[i]);
    }

    printf("\n%d\n", maxNum);

    double* gistPtr = (double*)calloc(maxNum * groupSize + 1, sizeof(double));

    buildDataForGist(dataPtr, gistPtr, dataNum, maxNum, groupSize);

    for (int i = 0; i < maxNum * groupSize + 1; i++)
    {
        printf("num [%3d] | frequency %lg\n", i, gistPtr[i]);
    }
}


void buildDataForGist(int* dataPtr, double* gistPtr, int dataNum, int maxNum, int groupSize)
{
    int summ = 0;
    for (int i = 0; i < 4000 / groupSize; i++)
    {
        summ = 0;
        for (int j = 0; j < groupSize; j++)
        {
            summ += dataPtr[i * groupSize + j];
        }

        gistPtr[summ] += 1;
    }

    for (int i = 0; i < maxNum * groupSize + 1; i++)
    {
        gistPtr[i] /= dataNum / groupSize;
    }
}
