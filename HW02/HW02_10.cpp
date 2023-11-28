#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;
int BinarySearch(int *a, const int x, const int n){   // Binary Search 
	int l = 0, r = n -1;
	while(l<=r){
		int m = (l + r)/2;
		if(x < *(a + m)){
		    r = m - 1;
		}else if(x > *(a + m)){
			l = m + 1;
		}else{
			return m;
		}
	}
	return -1;
}
int main(){                             
	srand(time(NULL));
	clock_t start_time, end_time;
	float total_time = 0;
	const int x = 100;                      // x is the goal of Binary Search,
	                                        // suppose it as the worst case
	for(int n = 0; n <= 100; n++){          // n in range [0, 100]
        
		int *a = new int[n];
	    
		for(int i = 0; i < n; i++){
    	    a[i] = i + 1;
		}

	    start_time = clock();               // start 

    	for(int j = 0; j < 10000000; j++){
	    	BinarySearch(a, x, n);
	    }

    	end_time = clock();                 // end

    	total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
    	cout << "\nn = " << n << "\nstart time tick = " << start_time <<
		 "\nend time clock = " << end_time << "\ntotal time = " << total_time << " second\n";
		
		delete[] a;
	}
	return 0;
}