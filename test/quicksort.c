int array[10000];

int partition(int left, int right )
{
	int pivot = array[(left+right)/2], i = left, j = right;
	while (i <= j) {
		while ( array[i] < pivot ) { i=i+1; }
		while ( array[j] > pivot ) { j=j-1; }
		if ( i <= j ) {
			int temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			i=i+1;
			j=j-1;
		}
	}
	
	return i - 1;
}


int sort (int left, int right )
{
    if ( left < right ) {
        int p = partition(left, right);
        int pp = sort(left, p);
        int ppp = sort(p+1, right);
    }

	return 2;
}


int main()
{
    int N;
    scanf("%d", &N);
    int i;
	i = 0;
	while (i < N) {
		int num;
		scanf("%d", &num);
		array[i] = num;
		i=i+1;
	}
	int pppp = sort(0, N - 1);
	i = 0;
	while (i < N) {
		printf("%d", array[i]);
		print("");
		i=i+1;
	}

	return 0;
}