#include <stdio.h>

//#define len(a) (sizeof(a)/sizeof(a[0]))

void printArray(int* arr, int len){
	printf("{");
	if (len != 0){
		printf("%d", arr[0]);
	}


	for (int i=1; i < len; ++i){
		printf(", %d", arr[i]);
	}
	printf("}\n");
}

void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void rotate(int* first, int* n_first, int* last){
	int* next = n_first;
	while (next != first){
		
		swap(next++, first++);
		
		if (next==last){
			next = n_first;
		} else if (first==n_first){
			n_first = next;
		}

	}
}


int main(){
	int arr[] = {0,1,2,3,4,5,6,7,8,9,10};

	printArray(arr, 10);

	rotate(arr, arr+4, arr+10);
	printArray(arr,10);

	return 0;
}
