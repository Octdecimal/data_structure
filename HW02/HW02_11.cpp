#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;
int SelectionSort(int *a, const int n){
	for(int i = 0; i < n; i++){
		int j = i;
		for(int k = i + 1; k < n; k++){
			if(*(a + k) < *(a + j)){
				j = k;
			}
		}
		swap(*(a + i), *(a + j));
	}
}
int main(){                             
	srand(time(NULL));
	clock_t start_time, end_time;
	float total_time = 0;
	srand(time(NULL));

	for(int n = 0; n <= 100; n++){          // n in range [0, 100]    

	    int *a = new int[n];
	    
	    for(int i = 0; i < n; i++){         // suppose it as the best case
   	        a[i] = i + 1;
	    }

	    start_time = clock();               // start 

    	for(int j = 0; j < 2000000; j++){
	    	SelectionSort(a, n);
	    }

    	end_time = clock();                 // end

    	total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
    	cout << "\nn = " << n << "\nstart time tick = " << start_time <<
		 "\nend time clock = " << end_time << "\ntotal time = " << total_time << " second\n";
		
	    delete[] a;
	}
	return 0;
}