int main(){
    int a[10][10] ;
    a[0][0] = 123 ;
    // print(a[0][0]) ;
    int i = 0 ;
    // for ( i = 0 ; i < 10 ; i=i+1 ) {
    //     a[i][i] = i*i ;
    // } 
    // for ( i = 9 ; i >= 0 ; i=i-1 ) {
    //     print(a[i][i]) ;
    // }
    // print(a[0][0]) ;
    int arr[10] ;
    for ( i = 0 ; i < 10 ; i=i+1 ) {
        if ( i==0 ) {
            arr[i] = 2 ;
        } else {
            arr[i] = arr[i-1]*2-1 ;
        }
    }
    for ( i = 9 ; i >= 0 ; i=i-1 ) {
        print(arr[i]) ;
    }
    print(123);
    return 0 ;
}