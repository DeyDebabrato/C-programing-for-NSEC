#include <stdio.h>
#include <stdlib.h>

struct Job {
    char id;
    int deadline;
    int profit;
};

int compare(const void* a, const void* b) {
    return ((struct Job*)b)->profit - ((struct Job*)a)->profit;
}

void jobSequencing(struct Job jobs[], int n) {
    qsort(jobs, n, sizeof(struct Job), compare);

    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }

    char sequence[maxDeadline];

    int filledSlots[maxDeadline];
    for (int i = 0; i < maxDeadline; i++)
        filledSlots[i] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (filledSlots[j] == 0) {
                sequence[j] = jobs[i].id;
                filledSlots[j] = 1;
                break;
            }
        }
    }

    printf("Job Sequence: ");
    for (int i = 0; i < maxDeadline; i++) {
        if (filledSlots[i])
            printf("%c ", sequence[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    struct Job jobs[n];
    printf("Enter the job ID, deadline, and profit for each job:\n");
    for (int i = 0; i < n; i++) {
        scanf(" %c %d %d", &jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
    }

    jobSequencing(jobs, n);

    return 0;
}
