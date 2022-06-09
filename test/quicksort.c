int MAXN = 1000;

int partition( int array[], int left, int right )
{
	int pivot = array[(left+right)/2], i = left, j = right;
	while (i <= j) {
		while ( array[i] < pivot ) { i++; }
		while ( array[j] > pivot ) { j--; }
		if ( i <= j ) {
			int temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			i++;
			j--;
		}
	}
	
	return i - 1;
}


void sort ( int array[], int left, int right )
{
    if ( left < right ) {
        int p = partition(array, left, right);
        sort(array, left, p);
        sort(array, p+1, right);
    }
}


int main()
{
    int N;
    scanf("%d", &N);
    int i;
    int array[1000];
	i = 0;
	while (i < N) {
		scanf("%d", &array[i]);
		i++;
	}
	sort(array, 0, N - 1);
	i = 0;
	while (i < N) {
		printf("%d\n", array[i]);
		i++;
	}

	return 0;
}