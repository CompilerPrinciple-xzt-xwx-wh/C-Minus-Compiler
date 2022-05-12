/*
 * @Author: xwxr
 * @Date: 2022-05-12 10:53:03
 * @LastEditors: xwxr
 * @LastEditTime: 2022-05-12 12:55:25
 * @Description: "quicksort" test for C-Minus.
 */
#include <stdio.h>

int MAXN = 1000;
/**
 * @description: This function decides a pivot in the array from left to right and move all element less than the pivot to the left and all greater to the right.
 * @param {int} array
 * @param {int} left
 * @param {int} right
 * @return It returns the index of the pivot after all element are moved.
 */
int partition( int array[], int left, int right )
{
	int pivot = array[(left+right)/2], i = left, j = right;
	for(; i <= j; ) {
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

/**
 * @description: This function sorts the array in non-descending order from left to right.
 * @param {int} array
 * @param {int} left
 * @param {int} right
 * @return {*}
 */
void sort ( int array[], int left, int right )
{
    if ( left < right ) {
        int p = partition(array, left, right);
        sort(array, left, p);
        sort(array, p+1, right);
    }
}

/**
 * @description: main function for quicksort
 * @param {*}
 * @return {*}
 */
int main()
{
    int N;
    scanf("%d", &N);
    int i;
    int array[MAXN];
    for (i = 0; i < N; i++) {
        scanf("%d", &array[i]);
    }
	sort(array, 0, N - 1);
	for (i = 0; i < N; i++) {
		printf("%d\n", array[i]);
	}

	return 0;
}