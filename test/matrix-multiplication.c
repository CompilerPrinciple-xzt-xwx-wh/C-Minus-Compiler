/*
 * @Author: xwxr
 * @Date: 2022-05-14 10:19:46
 * @LastEditors: xwxr
 * @LastEditTime: 2022-05-15 18:04:44
 * @Description: delete addition assignment operator '+='
 */

/*
 * @Author: xwxr
 * @Date: 2022-05-14 10:19:46
 * @LastEditors: xwxr
 * @LastEditTime: 2022-05-14 12:56:51
 * @Description: "matrix multiplication" test for C-Minus.
 */

#include <stdio.h>

int main()
{
    int m1, n1, m2, n2;
    scanf("%d %d", &m1, &n1);
    int i, j;
    int A[25][25], B[25][25];
    int num;
    for (i = 0; i < m1; i++) {
        for (j = 0; j < n1; j++) {
            scanf("%6d", &num);
            A[i][j] = num;
        }
    }
    scanf("%d %d", &m2, &n2);
    for (i = 0; i < m2; i++) {
        for (j = 0; j < n2; j++) {
            scanf("%6d", &num);
            B[i][j] = num;
        }
    }
    if (n1 != m2) {
        printf("Incompatible Dimensions\n");
    } else {
        int C[25][25], k;
        for (i = 0; i < m1; i++) {
            for (j = 0; j < n2; j++) {
                C[i][j] = 0;
                for (k = 0; k < n1; k++) {
                    C[i][j] = C[i][j] + A[i][k] * B[k][j];
                }
            }
        }
        for (i = 0; i < m1; i++) {
            for (j = 0; j < n2; j++) {
                printf("%10d", C[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}