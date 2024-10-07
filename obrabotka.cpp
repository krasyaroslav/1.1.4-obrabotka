#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void buildDataForGist(int* dataPtr, int* gistPtr, int dataNum, int maxNum, int groupSize);


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
        //printf("%d ", dataPtr[i]);
    }

    printf("\n%d\n", maxNum);

    int * gistPtr = (int*)calloc(maxNum * groupSize + 1, sizeof(int));

    buildDataForGist(dataPtr, gistPtr, dataNum, maxNum, groupSize);

    for (int i = 0; i < maxNum * groupSize + 1; i++)
    {
        printf("num [%3d] | frequency %lg\n", i, (double)gistPtr[i] / (dataNum / groupSize));
    }

    int * groupedDataPtr = (int*)calloc(dataNum / groupSize, sizeof(int)), summ = 0;

    for (int i = 0; i < dataNum / groupSize; i++)
    {
        summ = 0;
        for (int j = 0; j < groupSize; j++)
        {
            summ += dataPtr[i * groupSize + j];
        }

        groupedDataPtr[i] = summ;
    }

    for (int i = 0; i < dataNum / groupSize; i++)
    {
        printf("%d\n", groupedDataPtr[i]);
    }

    double sredN = 0;

    for (int i = 0; i < dataNum / groupSize; i++)
    {
        sredN += groupedDataPtr[i];
    }

    sredN /= (dataNum / groupSize);

    printf("sredN = %lg\n", sredN);


    double porgKv = 0;

    for (int i = 0; i < dataNum / groupSize; i++)
    {
        porgKv += ((groupedDataPtr[i] - sredN) * (groupedDataPtr[i] - sredN));
    }
    porgKv /= (dataNum / groupSize);
    porgKv = sqrt(porgKv);

    printf("porgKv = %lg\n", porgKv);

    double porgSred = porgKv / sqrt(dataNum / groupSize);
    printf("porgSred = %lg\n", porgSred);

    printf("j = %lg\n", sredN / groupSize);
    printf("porg_j = %lg", porgSred / groupSize);

    double c1 = 0, c2 = 0, c3 = 0;
    for(int i = 0; i < dataNum / groupSize; i++)
    {
        if (fabs(groupedDataPtr[i] - sredN) < porgKv) c1++;
        if (fabs(groupedDataPtr[i] - sredN) < 2*porgKv) c2++;
        if (fabs(groupedDataPtr[i] - sredN) < 3*porgKv) c3++;
    }

    printf("\n\n%lg %lg %lg", c1 / (dataNum / groupSize), c2 / (dataNum / groupSize), c3 / (dataNum / groupSize));
}


void buildDataForGist(int* dataPtr, int* gistPtr, int dataNum, int maxNum, int groupSize)
{
    int summ = 0;
    for (int i = 0; i < dataNum / groupSize; i++)
    {
        summ = 0;
        for (int j = 0; j < groupSize; j++)
        {
            summ += dataPtr[i * groupSize + j];
        }

        gistPtr[summ] += 1;
    }
}
