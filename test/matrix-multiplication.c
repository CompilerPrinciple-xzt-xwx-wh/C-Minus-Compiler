/*
 * @Author: xwxr
 * @Date: 2022-05-14 10:19:46
 * @LastEditors: xwxr
 * @LastEditTime: 2022-05-21 22:57:11
 * @Description: delete addition assignment operator '+='
 */

/*
 * @Author: xwxr
 * @Date: 2022-05-14 10:19:46
 * @LastEditors: xwxr
 * @LastEditTime: 2022-05-14 12:56:51
 * @Description: "matrix multiplication" test for C-Minus.
 */

int main()
{
    int m1, n1, m2, n2;
    scanf("%d %d", &m1, &n1);
    int i, j;
    int A[25][25], B[25][25];
    int num;
    i = 0;
    while (i < m1) {
        j = 0;
        while (j < n1) {
            scanf("%6d", &num);
            A[i][j] = num;
            j++;
        }
        i++;
    }
    scanf("%d %d", &m2, &n2);
    i = 0;
    while (i < m2) {
        j = 0;
        while (j < n2) {
            scanf("%6d", &num);
            B[i][j] = num;
            j++;
        }
        i++;
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
                    k++;
                }
                j++;
            }
            i++;
        }
        i = 0;
        while (i < m1) {
            j = 0;
            while (j < n2) {
                printf("%10d", C[i][j]);
                j++;
            }
            printf("\n");
            i++;
        }
    }

    return 0;
}