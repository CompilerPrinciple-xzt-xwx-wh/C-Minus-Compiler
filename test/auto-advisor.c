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
            j=j+1;
        }
        while (1) {
            scanf("%c", &ch);
            if (ch == '|') {
                course[i][j] = '\0';
                break;
            } else {
                course[i][j] = ch;
                j=j+1;
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
                j=j+1;
            }
        }
        scanf("%c", &ch);
        if (ch == '\n') {
            grade[i] = '\0';
        } else {
            grade[i] = ch;
            scanf("%c", &ch);
        }
        i=i+1;
    }
    int coursenum = i;
    int creditsAttempted = 0, creditsCompleted = 0, creditsRemain = 0;
    float GPA = 0;
    int remainIndex[100], cnt = 0;
    i = 0;
    while (i < coursenum) {
        if (grade[i] != '\0') {
            if (grade[i] != 'F') {
                remainIndex[cnt] = i;
                cnt=cnt+1;
                creditsCompleted = creditsCompleted + credit[i];
                GPA = GPA + credit[i] * ('A' + 4 - grade[i]);
            } else {
                creditsRemain = creditsRemain + credit[i];
            }
            creditsAttempted = creditsAttempted + credit[i];
        } else {
            creditsRemain = creditsRemain + credit[i];
        }
        i=i+1;
    }
    if (GPA != 0.0) {
        GPA = GPA / creditsAttempted;
    }
    printf("GPA: %.1f", GPA);
    print("");
    printf("Hours Attempted: %d", creditsAttempted);
    print("");
    printf("Hours Completed: %d", creditsCompleted);
    print("");
    printf("Credits Remaining: %d", creditsRemain);
    print("");
    print("");
    printf("Possible Courses to Take Next");
    print("");
    if (creditsRemain == 0) {
        printf("  None - Congratulations!");
        print("");
    }
    if (cnt == 0) {
        int pp = 0;
        while (pp < coursenum) {
            if (precourse[pp][0] == '\0') {
                int q = 0;
                printf("  ");
                while (course[pp][q] != '\0') {
                    printf("%c", course[pp][q]);
                    q=q+1;
                }
                print("");
            }
            pp=pp+1;
        }
    }
    i = 0;
    while (i < coursenum) {
        if (cnt == 0) {
            break;
        }
        if (grade[i] == 'F' || grade[i] == '\0') {
            if (precourse[i][0] == '\0') {
                j = 0;
                printf("  ");
                while (course[i][j] != '\0') {
                    printf("%c", course[i][j]);
                    j=j+1;
                }
                print("");
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
                                m = 0;
                                while (m < cnt) {
                                    innerflag = 1;
                                    n = 0;
                                    while (precourseterm[n] != '\0') {
                                        if (course[remainIndex[m]][n] != precourseterm[n]) {
                                            innerflag = 0;
                                        }
                                        n=n+1;
                                    }
                                    if (course[remainIndex[m]][n] != '\0') { innerflag = 0; }
                                    if (innerflag == 1) {
                                        break;
                                    }
                                    m=m+1;
                                }
                                // printf("  %d\n", innerflag);
                                if (m == cnt && innerflag == 0) { flagnum=flagnum-1; }
                                flagnum=flagnum+1;
                                num=num+1;
                                l = 0;
                                k=k+1;
                                if (precourseset[k-1] == '\0') {
                                    break;
                                }
                            }
                            
                            precourseterm[l] = precourseset[k];
                            l=l+1;
                            k=k+1;
                        }
                        if (num == flagnum) {
                            int p = 0;
                            printf("  ");
                            while (course[i][p] != '\0') {
                                printf("%c", course[i][p]);
                                p=p+1;
                            }
                            print("");
                            break;
                        }
                        k = 0;
                        j=j+1;
                        if (precourse[i][j-1] == '\0') { break; }
                    }
                    precourseset[k] = precourse[i][j];
                    j=j+1;
                    k=k+1;
                    
                }
            }
        }
        i=i+1;
    }
    

    return 0;
}