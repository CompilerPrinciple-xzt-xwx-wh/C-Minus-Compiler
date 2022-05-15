/*
 * @Author: xwxr
 * @Date: 2022-05-14 10:26:11
 * @LastEditors: xwxr
 * @LastEditTime: 2022-05-15 18:06:41
 * @Description: delete addition assignment operator '+=' and division assignment operator '/='
 */

/*
 * @Author: xwxr
 * @Date: 2022-05-14 10:26:11
 * @LastEditors: xwxr
 * @LastEditTime: 2022-05-14 23:36:07
 * @Description: "auto advisor" test for C-Minus.
 */

#include <stdio.h>

int main()
{
    char course[100][5], precourse[100][1000], grade[100];
    int credit[100];
    int i = 0, j = 0;
    while (1) {
        char ch;
        int crd;
        scanf("%c", &ch);
        j = 0;
        if (ch == '\n') { break; }
        else {
            course[i][j] = ch;
            j++;
        }
        while (1) {
            scanf("%c", &ch);
            if (ch == '|') {
                course[i][j] = '\0';
                break;
            } else {
                course[i][j] = ch;
                j++;
            }
        }
        scanf("%d", &crd);
        credit[i] = crd;
        j = 0;
        scanf("%c", &ch);
        while (1) {
            scanf("%c", &ch);
            if (ch == '|') {
                precourse[i][j] = '\0';
                break;
            } else {
                precourse[i][j] = ch;
                j++;
            }
        }
        scanf("%c", &ch);
        if (ch == '\n') {
            grade[i] = '\0';
        } else {
            grade[i] = ch;
            scanf("%c", &ch);
        }
        i++;
    }
    int coursenum = i;
    int creditsAttempted = 0, creditsCompleted = 0, creditsRemain = 0;
    float GPA = 0.0;
    int remainIndex[100], cnt = 0;
    for (i = 0; i < coursenum; i++) {
        if (grade[i] != '\0') {
            if (grade[i] != 'F') {
                remainIndex[cnt] = i;
                cnt++;
                creditsCompleted = creditsCompleted + credit[i];
                GPA = GPA + credit[i] * ('A' - grade[i] + 4);
            } else {
                creditsRemain = creditsRemain + credit[i];
            }
            creditsAttempted = creditsAttempted + credit[i];
        } else {
            creditsRemain = creditsRemain + credit[i];
        }
    }
    GPA = GPA / creditsAttempted;
    printf("GPA: %.1f\n", GPA);
    printf("Hours Attempted: %d\n", creditsAttempted);
    printf("Hours Completed: %d\n", creditsCompleted);
    printf("Credits Remaining: %d\n\n", creditsRemain);
    printf("Possible Courses to Take Next\n");
    if (creditsRemain == 0) {
        printf("  None - Congratulations!");
    }
    
    for (i = 0; i < coursenum; i++) {
        if (grade[i] == 'F' || grade[i] == '\0') {
            if (precourse[i][0] == '\0') {
                j = 0;
                printf("  ");
                while (course[i][j] != '\0') {
                    printf("%c", course[i][j]);
                    j++;
                }
                printf("\n");
            } else {
                char precourseterm[5];
                char precourseset[100];
                j = 0;
                int k = 0;
                while (1) {
                    int l;
                    if (precourse[i][j] == ';' || precourse[i][j] == '\0') {
                        precourseset[k] = '\0';
                        k = 0;
                        l = 0;
                        int num = 0, flagnum = 0;
                        while (1) {
                            if (precourseset[k] == ',' || precourseset[k] == '\0') {
                                precourseterm[l] = '\0';
                                int m = 0, n = 0;
                                int innerflag;
                                for (m = 0; m < cnt; m++) {
                                    innerflag = 1;
                                    n = 0;
                                    while (precourseterm[n] != '\0') {
                                        if (course[remainIndex[m]][n] != precourseterm[n]) {
                                            innerflag = 0;
                                        }
                                        n++;
                                    }
                                    if (course[remainIndex[m]][n] != '\0') { innerflag = 0; }
                                    if (innerflag == 1) {
                                        break;
                                    }
                                }
                                // printf("  %d\n", innerflag);
                                if (m == cnt && innerflag == 0) { flagnum--; }
                                flagnum++;
                                num++;
                                l = 0;
                                k++;
                                if (precourseset[k-1] == '\0') {
                                    break;
                                }
                            }
                            
                            precourseterm[l] = precourseset[k];
                            l++;
                            k++;
                        }
                        if (num == flagnum) {
                            int p = 0;
                            printf("  ");
                            while (course[i][p] != '\0') {
                                printf("%c", course[i][p]);
                                p++;
                            }
                            printf("\n");
                            break;
                        }
                        k = 0;
                        j++;
                        if (precourse[i][j-1] == '\0') { break; }
                    }
                    precourseset[k] = precourse[i][j];
                    j++;
                    k++;
                    
                }
            }
        }
    }
    

    return 0;
}