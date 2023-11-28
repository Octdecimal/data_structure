#include <iostream>

using namespace std;

void print(int x, int y, int **arr){
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			cout << char(*(*(arr+i)+j));
		}
		cout << "\n";
	}
}

void bubble_sort(int x, int **arr){                            // as ASCII code, from big to small
	for(int i = 0; i < x-1; i++){                              // => Z~A, z~a, 9~1
		for(int j = 0; j < x-i-1; j++){
			if(char(*(*(arr+j+1))) > char(*(*(arr+j)))){       // pointer operate => swap their address
				int *tmp = *(arr+j);
				*(arr+j) = *(arr+j+1);
				*(arr+j+1) = tmp;
			}
		}
	}
}

int main(){
	int x, y;
	string str;
	cout << "Please input x, y: ";
	cin >> x >> y;
	cin.ignore();                       // because I will use getline(), cin will stop forward by '\n'
                                        // but getline() will stop at '\n', ignore() can handle the problem
	int **arr = new int*[x];            // declare arr[x][]
	for(int i = 0; i < x; i++){         // declare arr[][y] in proper order
		arr[i] = new int[y];
	}

	for(int i = 0; i < y; i++){
		str[i] = ' ';                   // initialize str;
	}

	for(int i = 0; i < x; i++){
		cout << "Input " << i + 1 << ": ";   // it will tell user the turn's number
		getline(cin, str);                     // because cin can't input ' '

		if(str.length() > y){                  // input-length checker
			cout << "\n Your string is too long, pleasr type a shorter one";
			i--;
			continue;                          // it will stop the turn and start a new one
		}                                      // in other words, the codes after continue wil be skip until new loop's turn 
		
		for(int j = 0; j < y; j++){
			arr[i][j] = str[j];                // write str to arr
			str[j] = ' ';                      // clear whole the str, str.clear() just set the str.begin() as '\0'
		}
	}
	cout << "\n";
	
	bubble_sort(x, arr);

	print(x, y, arr);

	for(int i = 0; i < x; i++){
		delete[] arr[i];
	}
	delete[] arr;

	return 0;
}