#include <stdio.h>

#define MAX_ITEMS 100

struct Item {
    int weight;
    int value;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(int W, struct Item items[], int n) {
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (items[i - 1].weight <= w)
                dp[i][w] = max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][W];
}

int main() {
    int n, W;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct Item items[MAX_ITEMS];
    printf("Enter the weight and value of each item:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &items[i].weight, &items[i].value);
    }

    printf("Enter the capacity of knapsack: ");
    scanf("%d", &W);

    int max_value = knapsack(W, items, n);
    printf("Maximum value that can be obtained: %d\n", max_value);

    return 0;
}
