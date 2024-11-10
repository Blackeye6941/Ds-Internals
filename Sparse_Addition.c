#include <stdio.h>
#define MAX_SIZE 20

struct Sparse {
    int row;
    int col;
    int val;
};

void print_triplet(struct Sparse matrix[], int val) {
    for (int i = 0; i <= val; i++) {
        printf("%d %d %d\n", matrix[i].row, matrix[i].col, matrix[i].val);
    }
}

int main() {
    int row, col, val, val1;
    struct Sparse S1[MAX_SIZE], S2[MAX_SIZE], S3[2 * MAX_SIZE];

    // Input for Sparse Matrix 1
    printf("Enter number of Rows, Columns, and non-zero values in sparse matrix 1: ");
    scanf("%d %d %d", &row, &col, &val);
    S1[0].row = row;
    S1[0].col = col;
    S1[0].val = val;

    printf("Enter details of each non-zero value in sparse matrix 1:\n");
    for (int i = 1; i <= val; i++) {
        printf("Enter row, column, and value: ");
        scanf("%d %d %d", &row, &col, &val1);
        S1[i].row = row;
        S1[i].col = col;
        S1[i].val = val1;
    }

    printf("\nSparse matrix 1 added!\n");
    printf("Triplet representation of Sparse matrix 1:\n");
    print_triplet(S1, val);

    // Input for Sparse Matrix 2
    row = col = val = val1 = 0;
    printf("\nEnter number of Rows, Columns, and non-zero values in sparse matrix 2: ");
    scanf("%d %d %d", &row, &col, &val);
    S2[0].row = row;
    S2[0].col = col;
    S2[0].val = val;

    printf("Enter details of each non-zero value in sparse matrix 2:\n");
    for (int i = 1; i <= val; i++) {
        printf("Enter row, column, and value: ");
        scanf("%d %d %d", &row, &col, &val1);
        S2[i].row = row;
        S2[i].col = col;
        S2[i].val = val1;
    }

    printf("\nSparse matrix 2 added!\n");
    printf("Triplet representation of Sparse matrix 2:\n");
    print_triplet(S2, val);

    // Matrix addition
    if (S1[0].row == S2[0].row && S1[0].col == S2[0].col) {
        S3[0].row = S1[0].row;
        S3[0].col = S1[0].col;
        S3[0].val = 0; // Initialize the non-zero count to 0

        int i = 1, j = 1, k = 1;
        while (i <= S1[0].val && j <= S2[0].val) {
            if (S1[i].row == S2[j].row && S1[i].col == S2[j].col) {
                S3[k].row = S1[i].row;
                S3[k].col = S1[i].col;
                S3[k].val = S1[i].val + S2[j].val;
                i++;
                j++;
                k++;
                S3[0].val++;
            } else if (S1[i].row < S2[j].row || (S1[i].row == S2[j].row && S1[i].col < S2[j].col)) {
                S3[k] = S1[i];
                i++;
                k++;
                S3[0].val++;
            } else {
                S3[k] = S2[j];
                j++;
                k++;
                S3[0].val++;
            }
        }

        // Add remaining elements from S1
        while (i <= S1[0].val) {
            S3[k] = S1[i];
            i++;
            k++;
            S3[0].val++;
        }

        // Add remaining elements from S2
        while (j <= S2[0].val) {
            S3[k] = S2[j];
            j++;
            k++;
            S3[0].val++;
        }

        // Print the resulting sparse matrix
        printf("\nTriplet representation of the resulting sparse matrix (sum):\n");
        print_triplet(S3, S3[0].val);
    } else {
        printf("\nRows and columns of the two matrices are not equal. Addition cannot be performed!\n");
    }

    return 0;
}
