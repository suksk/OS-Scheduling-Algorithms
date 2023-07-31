#include <stdio.h>

struct process
{
    int ID, AT, BT, CT, TAT, WT, IsCOMP;
};
void main()
{
    struct process P[10];
    int n, i, j;
    float total_tat = 0, total_wt = 0;
    printf("Enter the number of Process: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        P[i].ID = i + 1;
        printf("Enter AT for %d process :", i + 1);
        scanf("%d", &P[i].AT);
        printf("Enter BT for %d process :", i + 1);
        scanf("%d", &P[i].BT);
        P[i].IsCOMP = 0;
    }
    printf("\nGantt Chart:\n");
    int MIN_IND, MIN_BT, COMP = 0, CUR_TIME = 0;
    while (COMP != n)
    {
        MIN_IND = -1;
        MIN_BT = 999;
        for (i = 0; i < n; i++)
        {
            if (P[i].AT <= CUR_TIME && P[i].IsCOMP == 0)
                if (P[i].BT < MIN_BT || (P[i].BT == MIN_BT && P[i].AT < P[MIN_IND].AT))
                {
                    MIN_BT = P[i].BT;
                    MIN_IND = i;
                }
        }
        if (MIN_IND == -1)
            CUR_TIME++;
        else
        {
            CUR_TIME += P[MIN_IND].BT;
            P[MIN_IND].CT = CUR_TIME;
            P[MIN_IND].TAT = P[MIN_IND].CT - P[MIN_IND].AT;
            P[MIN_IND].WT = P[MIN_IND].TAT - P[MIN_IND].BT;
            total_tat += P[MIN_IND].TAT;
            total_wt += P[MIN_IND].WT;
            P[MIN_IND].IsCOMP = 1;
            COMP++;
            printf("| P%d(%d) %d", P[MIN_IND].ID, P[MIN_IND].BT, CUR_TIME);
        }
    }
    printf("\n\nID\tAT\tBT\tCT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", P[i].ID, P[i].AT, P[i].BT, P[i].CT, P[i].WT, P[i].TAT);
    printf("AVG TAT : %.3f\n", total_tat / n);
    printf("AVG WT : %.3f\n", total_wt / n);
}

/*
Enter the number of Process: 5
Enter AT for 1 process :2
Enter BT for 1 process :1
Enter AT for 2 process :1
Enter BT for 2 process :5
Enter AT for 3 process :4
Enter BT for 3 process :1
Enter AT for 4 process :0
Enter BT for 4 process :6
Enter AT for 5 process :2
Enter BT for 5 process :3

Gantt Chart:
| P4(6) 6| P1(1) 7| P3(1) 8| P5(3) 11| P2(5) 16

ID      AT      BT      CT      WT      TAT
1       2       1       7       4       5
2       1       5       16      10      15
3       4       1       8       3       4
4       0       6       6       0       6
5       2       3       11      6       9
AVG TAT : 7.800
AVG WT : 4.600
*/