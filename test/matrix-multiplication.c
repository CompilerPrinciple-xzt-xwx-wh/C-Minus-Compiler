
int main()
{
    int m1, n1, m2, n2;
    input(m1);
    input(n1);
    int i, j;
    int A[25][25], B[25][25];
    int num;
    i = 0;
    while (i < m1) {
        j = 0;
        while (j < n1) {
            input(num);
            A[i][j] = num;
            j=j+1;
        }
        i=i+1;
    }
    input(m2, n2);
    i = 0;
    while (i < m2) {
        j = 0;
        while (j < n2) {
            input(num);
            B[i][j] = num;
            j=j+1;
        }
        i=i+1;
    }
    if (n1 != m2) {
        printf("Incompatible Dimensions\n");
    } else {
        int C[25][25], k;
        i = 0;
        while (i < m1) {
            j = 0;
            while (j < n2) {
                C[i][j] = 0;
                k = 0;
                while (k < n1) {
                    C[i][j] = C[i][j] + A[i][k] * B[k][j];
                    k=k+1;
                }
                j=j+1;
            }
            i=i+1;
        }
        i = 0;
        while (i < m1) {
            j = 0;
            while (j < n2) {
                // printf("%10d", C[i][j]);
                printf("%d", C[i][j]);
                j=j+1;
            }
            printf("\n");
            i=i+1;
        }
    }

    return 0;
}