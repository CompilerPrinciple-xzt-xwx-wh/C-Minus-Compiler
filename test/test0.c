int arr[10] ;

int sub(int a, int b) {
    int ret;
    ret = a-b ;
    return ret ;
}
int main(){
    int maxn = 10 ;
    int subret = sub(210,92) ;
    print(subret) ;
    
    int a[10][10] ;
    a[0][0] = 123 ;
    print(a[0][0]) ;
    int i = 0 , j = 0 ;
    // for ( i = 0 ; i < 10 ; i=i+1 ) {
    //     a[i][i] = i*i ;
    // } 
    // for ( i = 9 ; i >= 0 ; i=i-1 ) {
    //     print(a[i][i]) ;
    // }
    // print(a[0][0]) ;
    int arr[10] ;
    for ( i = 0 ; i < maxn ; i++ ) {
        for ( j = 0 ; j < maxn ; j++ ) {
            a[i][j] = i*j ;
        }
    }
    for ( i = 9 ; i > 0 ; i-- ) {
        for ( j = 9 ; j > 0 ; j-- ) {
            printf("%d ",a[i][j]) ;
        }
        print("") ;
    }
    print(123);
    if ( a[0][0] == 0 || a[9][9] == 80 ){
        print("Yes") ;
    }
    return 0 ;
}