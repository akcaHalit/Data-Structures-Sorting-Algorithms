#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int INPUT_SIZE;
double execution_time;
clock_t start,end;
										
int *array, *temp,inputSize = 10;	//initial value									
										
void printRunningTime();
void printArray(int array[INPUT_SIZE]);

void insertionSort(int array[INPUT_SIZE]);
void selectionSort(int array[INPUT_SIZE]);
void bubbleSort(int array[INPUT_SIZE]);
void mergeSort(int array[INPUT_SIZE], int left, int right);
void merge(int array[INPUT_SIZE],int left,int  k,int right);
void quicksort(int array[INPUT_SIZE], int left, int right);
//HEAP SORT ÝÇÝNLER
void heapsort(int array[INPUT_SIZE], int n);
int heap_size;
void heapify(int array[INPUT_SIZE], int i);
int *M;

int main() {
	int i;
	
	printf("Please enter the input size as integer value: ");
	
	while(1){
			scanf("%d",&inputSize);	
			if(inputSize>10000000 || inputSize<0){
				printf("INVALID INPUT SIZE :  1 to 1.000.000");
			}else {                             		
				break;
			}	
	}
	
				
	INPUT_SIZE = inputSize; 		
	array = malloc(sizeof(int) * inputSize);
	temp = malloc(sizeof(int) * inputSize);
	M = malloc(sizeof(int) * inputSize);

	// RANDOM
	srand(time(NULL));
	for(i=0; i<inputSize; i++){
		int random = rand()%inputSize +1;
		array[i] = random;						
	}
	/*	PRÝNTÝNG NEW ARRAY
	for(i=0; i<INPUT_SIZE; i++){
		printf("%d \n",array[i]);
	}
	*/
	int choice = 100;
	do{
		// Array'i sort edilmiþ halden eski haline getiriyor.
		for(i=0; i<INPUT_SIZE; i++) {
			temp[i] = array[i];
		}
		if(choice != 100){
			printf("Array eski haline getirildi......\n-----------------------------------------------\n");
		}
		printf("1-Insertion Sort \n2-Selection Sort \n3-Bubble Sort \n4-MergeSort \n5-QuickSort \n6-Heap Sort \n0-EXCHANGE THE INPUT SIZE \n");
		printf("Choose the sorting algorithm from the list below to compute the running time in seconds: ");
		scanf("%d",&choice);

		switch(choice){
		case 1:
			
			insertionSort(temp);
			//printArray(temp);
			printRunningTime();			
		break;	
		case 2:
			
			selectionSort(temp);
			//printArray(temp);		
			printRunningTime();
		break;	
		case 3:
			
			bubbleSort(temp);
			//printArray(temp);
			printRunningTime();
		break;	
		case 4:
			
			start = clock();
			mergeSort(temp,0,INPUT_SIZE-1);
			end = clock();
			execution_time = end - start;
			//printArray(temp);
			printRunningTime();
		break;	
		case 5:
			
			start = clock();
			quicksort(temp,0,INPUT_SIZE-1);
			end = clock();
			execution_time = end - start;
			//printArray(temp);
			printRunningTime();
		break;	
		case 6:
			
			start = clock();
			heapsort(temp,INPUT_SIZE);
			end = clock();
			execution_time = end - start;
			//printArray(temp);
			printRunningTime();
		break;
		case 0:
			changeInput();
			break;
		default:
			printf("INVALID CHOICE! ");
			break;
		}
		
	}while(choice != 9);
		
	
	return 0;
}


//---------- HEAPSORT --------------
void heapsort(int array[INPUT_SIZE], int n){
	int i, temp;
	build_heap(array,n);
	for (i = n-1; i >= 1; i--){
		// exchange the root with the ith element
		temp = array[i];
		array[i] = array[0];
		array[0] = temp;
		heap_size--;
		heapify(array,0);
	}

}
//	FOR HEAPÝFY:
int left(int i){
	return(2*i+1);
}
// I*ndex of the right child of node i
int right(int i){
	return(2*i+2);
}

void build_heap(int D[], int n){
	int i;
	heap_size = n-1;
	for (i = (n-1)/2; i >= 0; i--)
		heapify(D,i);
}

void heapify(int array[INPUT_SIZE], int i){
	
	int left_child, right_child, max, temp;
	left_child = left(i);
	right_child = right(i);
	
	// find the max of nodes left, right, and i
	if ((left_child <= heap_size) &&
		(array[left_child] > array[i]))
		max = left_child;
	else
	max = i;
	
	if ((right_child <= heap_size) &&
	(array[right_child] > array[max]))
	max = right_child;
	// if max is not the i th node, exchange
	if (max != i){
		temp = array[max];
		array[max]= array[i];
		array[i] = temp;
		heapify(array, max);
	}
}

//---------- HEAPSORT --------------


void quicksort(int array[INPUT_SIZE], int left, int right){
	
	int k, j, q, temp;
	//partition the array into two parts
	k = left;
	j = right;
	q = array[(left+right)/2]; //pivot
	 
	do{
		while ((array[k] < q) && (k < right))
			k++;
		while ((array[j] > q) && (j > left))
			j--;
		if (k <= j) { //exchange D[k] & D[j]
			temp = array[k];
			array[k] = array[j];
			array[j] = temp;
			k++; j--;
			}
	}while(k <= j);
	// Sort each part using quicksort
	if (left < j)
	quicksort(array, left, j);
	if (k < right)
	quicksort(array, k, right);

}





void mergeSort(int array[INPUT_SIZE], int left, int right){
	int k;
	if (left < right) {
		k = (left + right)/2; // index of midpoint
		mergeSort(array, left, k);
		mergeSort(array, k+1, right);
		// merge the two halves
		merge(array, left, k, right);
	}
	
}

void merge(int array[INPUT_SIZE], int left, int k, int right){
	int i, j, l = 0;
	//int M[INPUT_SIZE]; // temporary array
	for (i=left, j=k+1; (i <= k) && (j <= right); ) {
		if (array[i] < array[j]) {
			M[l] = array[i];
			i++;
			l++;
		}else {
			M[l] = array[j];
			j++;
			l++;
		}
	}
	
	// copy the remaining elements to M
	while (i <= k){
		M[l] = array[i];
		i++;
		l++;
	}
	while (j <= right){
		M[l] = array[j];
		j++;
		l++;
	}
	for (i = left, l = 0; i <= right; i++, l++)
		array[i] = M[l];
}



void bubbleSort(int array[INPUT_SIZE]){
	int temp, k, move;
	
	start = clock();
	for (move = 0; move < (INPUT_SIZE-1); move++){
		for (k = 0; k < (INPUT_SIZE-1-move); k++){
			if (array[k] > array[k+1]){ //exchange the values
				temp = array[k];
				array[k] = array[k+1];
				array[k+1] = temp;
			}
		}
	}
	end = clock();
	
	execution_time = end -start;
}

void selectionSort(int array[INPUT_SIZE]){
	int i, index, j, min;
	start = clock();
	for (i = 0; i < (INPUT_SIZE-1); i++) {
		min = array[INPUT_SIZE-1];
		index = INPUT_SIZE-1;
		for (j = i; j < (INPUT_SIZE-1); j++){
			if (array[j] < min){
				min = array[j];
				index = j;
			}
		}
		
		if (i != index){
			array[index] = array[i];
			array[i] = min;
		}	
	}
	end = clock();
	execution_time = end -start;
		
}
void insertionSort(int array[INPUT_SIZE]){

	int i,j,key;
	start = clock();
	for(i=1; i<INPUT_SIZE; i++){
		key = array[i];
		for(j = i-1; j>=0 && key <= array[j]; j--){
			array[j+1] =array[j];
		}
		array[j+1] = key;
	}
	end = clock();
	
	execution_time = end - start;
}



void printRunningTime(){
	printf("The running time of your chosen sorting algorithm is: %10f ms\n",execution_time);
}


void printArray(int array[INPUT_SIZE]){
	int i;
	for(i=0; i<INPUT_SIZE; i++){
		printf("%d \n",array[i]);
	}
	
}
void changeInput(){
	int i;
	printf("NEW INPUT?:  ");	
	while(1){
		scanf("%d",&inputSize);	
		if(inputSize>1000000 || inputSize<0){
			printf("INVALID INPUT SIZE :  1 to 1.000.000");
		}else {                             		
			break;			
		}	
	}
				
	INPUT_SIZE = inputSize; 		
	array = malloc(sizeof(int) * inputSize);
	temp = malloc(sizeof(int) * inputSize);
	M = malloc(sizeof(int) * inputSize);

	// RANDOM
	srand(time(NULL));
	for(i=0; i<inputSize; i++){
		int random = rand()%inputSize +1;
		array[i] = random;						
	}
}

