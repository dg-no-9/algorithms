#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
#define SIZE(arr)	(sizeof(arr) / sizeof(arr[0]))

int* getArray(const int n)
{
	int* arr = new int[n];
	if (n > 1) {
		for (int i = 0; i < n; i++) {
			arr[i] = rand()% (n*7);
		}
	}
	return arr;
}

int* copyArray(int* A, const int n){
	int* copy = new int[n];
	for (int i=0; i < n; i++){
		copy[i] = A[i];
	}
	return copy;
}

void printArray(int* A, const int size) {
	for (int i=0; i<size; ++i) {
		cout << A[i] << " ";
	}
	cout << endl;
}

int partition(int* A, int left, int right) {
	int who=A[right];
	int i = left - 1;
	for (int j=left; j<right; j++) {
		if (A[j] <= who) {
			i++;
			swap(A[i],A[j]);
		}
	}
	swap(A[i+1], A[right]);
	return i+1;;
}

/**
 *  * Quick sort vector A, between index "left" and index "right".
 *   */
void qsort(int* A, int left, int right) {
	if (left >= right) return;
	
	int midpoint = partition(A, left, right);
	qsort(A, left, midpoint - 1 );
	qsort(A, midpoint + 1, right);
}

void isort(int* A, const int size, const int start=0){
	for (int i=start + 1; i< size; i++){
		int hand = A[i];
		int j = i - 1;
		while(j >= 0 && hand < A[j]){
			A[j+1] = A[j];
			j--;
		}
		A[j+1] = hand;

	}
}

void combosort(int* A, const int start, const int end){
	if (left >= right) return;
	if(end-start < 70){
		isort(A,end + 1,start);
		return;
	}
	int midpoint = partition(A, start, end);
	qsort(A, start, midpoint - 1 );
	qsort(A, midpoint + 1, end);

}


void testSort() {
	const int testSize = 20;
	int increment = 80000;
	int iterations = 10;
	int** arr = new int*[testSize];
	for ( int i = 0; i < testSize; i++){
		int a = 0, b = 0, c = 0;
		const int size = increment + (i+1) *increment/testSize;
		for (int j = 0; j < iterations; j++){
			arr[i] = getArray(size);
			int* A = copyArray(arr[i], size);
			int* B = copyArray(arr[i], size);
			int* C = copyArray(arr[i], size);
			std::clock_t begin = std::clock();
			//printArray(arr[i],size);
			qsort(C, 0, size-1);
			int t = ((std::clock() - begin)/(double)(CLOCKS_PER_SEC/1000000));
			a = a + t;

			//a = (a + ((std::clock() - begin)/(double)(CLOCKS_PER_SEC/1000000)) ) / divider;
			
			//printArray(A,size);
			//begin = std::clock();
			//isort(A, size);
			//t = ((std::clock() - begin)/(double)(CLOCKS_PER_SEC/1000000));
			//b = b + t;	
			
			//printArray(B,size);
			begin = std::clock();
			combosort(B,0,size-1);
			t = ((std::clock() - begin)/(double)(CLOCKS_PER_SEC/1000000));
			c = c+ t;
			//printArray(arr[i], size);	
		}
		cout << size << "," << a/iterations << "," << b/iterations << "," << c/iterations << endl;
	}
	
	/*int* A = getArray(length);
	printArray(A, length);
	qsort(A, 0, length-1);
	printArray(A,length);
	delete A;
	A = getArray(length);
	printArray(A, length);
	isort(A, length);
	printArray(A,length);
	delete A;
	A = getArray(length);
	printArray(A, length);
	combosort(A, 0, length -1);
	printArray(A,length);
	*/
}

int main ()
{
	
	srand(time(NULL));
	testSort();	    
	return 0;
}
 
