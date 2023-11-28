#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
	int x, count;              // count: count first space's location
	int size = 0, FNsize = 0;  // size: store the longest name, FNsize: store the longest first name
	vector<string> list;       // store name
	vector<int> FNlist;        // store first name's length
	string str;
	cout << "Please input x: ";
	cin >> x;
	cin.ignore();

	for(int i = 0; i < x; i++){
		cout << "Input " << i + 1 << ": ";
		getline(cin, str);
		list.push_back(str);

		count = 0;
		for(int j = 0; j < str.length(); j++){// store all the first name's size which will be use to output space
			if(str[j] != ' '){
				count++;
			}else if(str[j] == ' '){
				FNlist.push_back(count);      
				break;
			}
		}
		if(count > FNsize){
			FNsize = count;                   // find the longest first name's size
		}

		if(str.length() > size){
			size = str.length();              // find the longest name's size
		}

		for(int j = 0; j < size; j++){        // clear whole the str, the value is the known biggest size
			str[j] = ' ';
		}
	}

	int **arr = new int*[x];                  // declare arr[x][size]
	for(int i = 0; i < x; i++){
		arr[i] = new int[size];
	}

	for(int i = 0; i < x; i++){               // put all the name to into arr
		for(int j = 0; j < size; j++){
			if(j < list[i].length()){         // if j > list[i].legnth(), the value of list[i][j] is unpredictable, but it should be ' '
		    	arr[i][j] = list[i][j];
			}else{
				arr[i][j] = ' ';
			}
		}
	}

    cout << "\n";
	for(int i = 0; i < x; i++){
		for(int j = 0; j < FNsize - FNlist[i]; j++){// align name's first space
			cout << " ";
		}
		for(int k = 0; k < size; k++){
			cout << char(arr[i][k]);          // output name
		}
		cout << "\n";
	}

	for(int i = 0; i < x; i++){              
		delete[] arr[i];
	}
	delete[] arr;

	return 0;
}