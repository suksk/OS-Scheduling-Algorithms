#include <stdio.h>
struct process
{
    int ID, PRI, AT, BT, CT, TAT, WT, IsCOMP;
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
        printf("Enter AT for process %d :", i + 1);
        scanf("%d", &P[i].AT);
        printf("Enter BT for process %d :", i + 1);
        scanf("%d", &P[i].BT);
        printf("Enter Priority for process %d :", i + 1);
        scanf("%d", &P[i].PRI);
        P[i].IsCOMP = 0;
    }
    int MIN_IND, MIN_PRI, COMP = 0, CUR_TIME = 0;
    printf("\nGantt Chart:\n");
    while (COMP != n)
    {
        MIN_IND = -1;
        MIN_PRI = 999;
        for (i = 0; i < n; i++)
        {
            if (P[i].AT <= CUR_TIME && P[i].IsCOMP == 0)
                if (P[i].PRI < MIN_PRI || (P[i].PRI == MIN_PRI && P[i].AT < P[MIN_IND].AT))
                {
                    MIN_PRI = P[i].PRI;
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
    printf("\n\nID\tAT\tBT\tPRI\tCT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", P[i].ID, P[i].AT, P[i].BT, P[i].PRI, P[i].CT, P[i].WT, P[i].TAT);
    printf("AVG TAT : %.3f\n", total_tat / n);
    printf("AVG WT : %.3f\n", total_wt / n);
}

/*
Enter the number of Process: 5
Enter AT for process 1 :2
Enter BT for process 1 :1
Enter Priority for process 1 :3
Enter AT for process 2 :1
Enter BT for process 2 :5
Enter Priority for process 2 :3
Enter AT for process 3 :4
Enter BT for process 3 :1
Enter Priority for process 3 :1
Enter AT for process 4 :0
Enter BT for process 4 :6
Enter Priority for process 4 :4
Enter AT for process 5 :2
Enter BT for process 5 :3
Enter Priority for process 5 :2

Gantt Chart:
| P4(6) 6| P3(1) 7| P5(3) 10| P2(5) 15| P1(1) 16

ID      AT      BT      PRI     CT      WT      TAT
1       2       1       3       16      13      14
2       1       5       3       15      9       14
3       4       1       1       7       2       3
4       0       6       4       6       0       6
5       2       3       2       10      5       8
AVG TAT : 9.000
AVG WT : 5.800
*/