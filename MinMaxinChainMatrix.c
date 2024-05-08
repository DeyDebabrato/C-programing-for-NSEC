#include <stdio.h>
#include <limits.h>

int matrixChainOrder(int dims[], int n) {
    int dp[n][n];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }

    for (int len = 2; len < n; len++) {
        for (int i = 1; i < n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (cost < dp[i][j])
                    dp[i][j] = cost;
            }
        }
    }
    return dp[1][n - 1];
}

int main() {
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    int dims[n + 1];
    printf("Enter the dimensions of %d matrices:\n", n);
    for (int i = 0; i <= n; i++) {
        scanf("%d", &dims[i]);
    }

    int minMultiplications = matrixChainOrder(dims, n + 1);
    printf("Minimum number of scalar multiplications: %d\n", minMultiplications);

    return 0;
}
