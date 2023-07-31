#include <stdio.h>
struct process
{
    int ID, AT, BT, CT, TAT, WT;
};
void main()
{
    struct process P[10], temp;
    int n, i, j, ct;
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
    }
    printf("\nGantt Chart:\n");
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (P[j].AT > P[j + 1].AT)
            {
                temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
    P[0].CT = P[0].AT + P[0].BT;
    ct = P[0].CT;
    printf("| P%d(%d) %d", P[0].ID, P[0].BT, ct);
    for (i = 1; i < n; i++)
    {
        if (P[i].AT > P[i - 1].CT)
        {
            printf("|Idle(%d) %d", P[i].AT - P[i - 1].CT, P[i].AT);
            ct = P[i].AT + P[i].BT;
        }
        else
            ct += P[i].BT;
        P[i].CT = ct;
        printf("| P%d(%d) %d", P[i].ID, P[i].BT, ct);
    }
    for (i = 0; i < n; i++)
    {
        P[i].TAT = P[i].CT - P[i].AT;
        P[i].WT = P[i].TAT - P[i].BT;
        total_tat += P[i].TAT;

        total_wt += P[i].WT;
    }
    printf("\n\nID\tAT\tBT\tCT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", P[i].ID, P[i].AT, P[i].BT, P[i].CT, P[i].WT, P[i].TAT);
    }
    printf("AVG TAT : %.3f\n", total_tat / n);
    printf("AVG WT : %.3f\n", total_wt / n);
}
/*
Enter the number of Process: 5
Enter AT for process 1 :2
Enter BT for process 1 :1
Enter AT for process 2 :1
Enter BT for process 2 :5
Enter AT for process 3 :4
Enter BT for process 3 :1
Enter AT for process 4 :0
Enter BT for process 4 :6
Enter AT for process 5 :2
Enter BT for process 5 :3

Gantt Chart:
| P4(6) 6| P2(5) 11| P1(1) 12| P5(3) 15| P3(1) 16

ID      AT      BT      CT      WT      TAT
4       0       6       6       0       6
2       1       5       11      5       10
1       2       1       12      9       10
5       2       3       15      10      13
3       4       1       16      11      12
AVG TAT : 10.200
AVG WT : 7.000
*/