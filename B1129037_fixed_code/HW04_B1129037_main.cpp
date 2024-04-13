#include "HW04_B1129037.h"
#include <iostream>
#include <vector>
#include <random>
#include <cstring>
#include <algorithm>
#include <time.h>
#include <fstream>   // use to create output.txt
#include <iomanip>
#include <sstream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);        // I/O optimization, referance website (9.), (10.)
    std::cin.tie(0);
    clock_t start_time, end_time;
    float total_time = 0;

    const long int termLimit = 1000;    // the variable shoulen't be changed
    const long int HASHLIMIT = 1000000L;
    int *hash = new int[HASHLIMIT]();     // hash table, reference website (3.)
    vector<int> coefList;
    vector<int> expList;
    int tempCoef = 0;
    int tempExp = 0;
    int term = 0;
    Polymul n_poly;
    Polymul m_poly;
    
    for(int i = 0; ; i = ++i % 2) { // (i = ++i % 2) and (i++, i %= 2) are same
        cout << "please input how many term, and the limit of term is " << termLimit << "\n(the input number <= 0, then end of the program)\n";
        if(i) {
            cout <<"m => ";
        }else {
            cout <<"n => ";
        }
        cin >> term;
        if (term <= 0) {
            break;
        }
        memset(hash, 0, HASHLIMIT);  // memset, reference (7.)
        coefList.clear();
        expList.clear();
        cout << "\ninput form (coef, exp), if the exp has existed, then the coef would be plus to the old one\n=> ";
        for(int j = 0; j < term; j++) {
            cin >> tempCoef >> tempExp;
            if(!hash[tempExp]) {
                expList.push_back(tempExp);
            }
            hash[tempExp] += tempCoef;
        }
        sort(expList.begin(), expList.end(), [](int a, int b) {return a < b; }); // sort, reference websit (8.)
        for(auto &index : expList) {
            coefList.push_back(hash[index]);
        }
        Polymul tmpPoly(coefList.size(), &coefList, &expList, nullptr);
        if(!i) {
            m_poly = tmpPoly;
            cout << "now = ";
            m_poly.polymulPrint();
            cout << "\n\n";
        }else {
            n_poly = tmpPoly;
            cout << "now = ";
            n_poly.polymulPrint();
            cout << "\n\n";

            start_time = clock();
            Polymul ans = n_poly * m_poly;
            end_time = clock();
            total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;

            cout << "ans = ";
            ans.polymulPrint();
            cout << "\n\nstart time tick = " << start_time << "\nend time clock = " << end_time << "\ntotal time = " << total_time << " second\n\n";
        }
    }

    delete[] hash;
    std::cin.get();
    return 0;
}

/*
reference websit:
1. about header file: https://learn.microsoft.com/en-us/cpp/cpp/header-files-cpp?view=msvc-170
2. how to separate header files and implementation files: https://jasonblog.github.io/note/c++/shi_fou_neng_rang_c_++_template_de_biao_tou_dang_z.html
3. about hash table: https://domino.ai/data-science-dictionary/hash-table
4. about <random>: https://learn.microsoft.com/en-us/cpp/standard-library/random?view=msvc-170
5. about mt19937: https://cplusplus.com/reference/random/mt19937/
6. about uniform_int_distribution: https://cplusplus.com/reference/random/uniform_int_distribution/
7. about memset: https://cplusplus.com/reference/cstring/memset/
8. about sort: https://cplusplus.com/reference/algorithm/sort/
9. about I/O optimization: https://cp.wiwiho.me/io-optimize/
10. about sync_with_stdio(): https://cplusplus.com/reference/ios/ios_base/sync_with_stdio/
11. about ios::app: https://cplusplus.com/doc/tutorial/files/

another reference:
1. this reference provide some pseudocode:  Ellis Horowitz, Sartaj Sahni, Dinesh Mehta. (2006).Fundamentals of Data Structures in C++, 2/e. Silicon Press. p.179 ~ p.190
*/
