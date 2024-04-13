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

    const long int termLimit = 1000;    // the variable shoulen't be changed
    const long int HASHLIMIT = 10000000L;
    int *hash = new int[HASHLIMIT]();     // hash table, reference website (3.)
    vector<int> coefList;
    vector<int> expList;
    int tempCoef = 0;
    int tempExp = 0;
    int term = 0;
    Polymul n_poly;
    Polymul m_poly;
    

    /*================for HW_demo (start):==================================================================================*/
    for(int i = 0; ; i = ++i % 2) { // (i = ++i % 2) and (i++, i %= 2) are same
        cout << "please input how many term, and the limit of term is " << termLimit;
        if(i) {
            cout <<", m => ";
        }else {
            cout <<", n => ";
        }
        cin >> term;
        memset(hash, 0, HASHLIMIT);  // memset, reference (7.)
        coefList.clear();
        expList.clear();
        cout << "\ninput form (coef, exp), if the exp has existed, then the coef would be plus to the old one\n=> ";
        for(int j = 0; j < term; j++) {
            cin >> tempCoef >> tempExp;
            if (!hash[tempExp]) {
                expList.push_back(tempExp);
            }
            hash[tempExp] += tempCoef;
        }

        sort(expList.begin(), expList.end()); // sort, reference websit (8.)

        for(auto &index : expList) {
            coefList.push_back(hash[index]);
        }
        Polymul tmpPoly(expList.size(), &coefList, &expList, nullptr);
        if(!i) {
            m_poly = tmpPoly;
            cout << "now = ";
            m_poly.polymulPrint();
            cout << "\n";
        }else {
            n_poly = tmpPoly;
            cout << "now = ";
            n_poly.polymulPrint();
            cout << "\n";
            Polymul ans = n_poly * m_poly;
            cout << "\nans = ";
            ans.polymulPrint();
            cout << "\n\n";
        }
    }
    /*================for HW_demo (end):====================================================================================*/


    /*----------------for HW_word (start):----------------------------------------------------------------------------------*/
    random_device rd;
    mt19937 mt(rd()); // mt19937, reference website 5.
    //uniform_int_distribution< int > randCoef(250, 300);    // for large coef
    uniform_int_distribution< int > randCoef(0, 1);      // for small coef
    //uniform_int_distribution< int > randExp(0, 50000);      // for non-dense <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< for non-dense
    uniform_int_distribution< int > randExp(10000, 60000);   // for dense \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ for dense
    // uniform_int_distribution, reference website (6.)
    int N = 0;
    
    clock_t start_time, end_time;
    float total_time = 0;

    cout << fixed << setprecision(4);       // set float output form

    stringstream stream;
    stream << fixed << setprecision(4);       // set float output form

    fstream output;
    output.open("output.txt", ios::app);      // about ios::app, reference website (11.)
    if (output.fail()) {
        cout << "input file opening failed\n";
        exit(1);
    }

    time_t now = time(0);
    int strSize = 30;
    char *T = new char[strSize];
    ctime_s(T, strSize, &now);
    output << "\n-----------wirte output start ----------\n" << T << "\n";
    delete[] T;

    uniform_int_distribution< int > digitalTerm(1, 9);
    uniform_int_distribution< int > decimalTerm(10, 99);
    uniform_int_distribution< int > hundredTerm(100, 999);
    int testDataNumber = 2000;                 // becuase the result need two data => the result number = testDataNumer / 2
    int X;
    for(int ii = 3; ii <= 3; ii++) {
        X = 1;
        if (ii == 1) {
            cout << "digital X digital:\n";
        } 
        else if (ii == 2) {
            cout << "decimal X digital:\n";
        } 
        else if (ii == 3) {
            cout << "hundred X hundred:\n";
        } 
        for(int i = 1; i <= testDataNumber; i++) {

            stream.str("");
            stream.clear();
            // create polymul
            coefList.clear();
            expList.clear();
            if ((i % 2)) {        // if ((i % 2) == 0) => m_poly
                if (ii == 1) {
                    term = 5;
                }
                else if (ii == 2) {
                    term = 50;
                }
                else {
                    term = 500;
                }
            }
            else {
                term = X;
            }
            X = X + 5;
            tempExp = randExp(mt);        // for dense \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ for dense
            for(int n_times = 0; n_times < term; n_times++) {
                tempExp--;                // for dense \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ for dense
                tempCoef = randCoef(mt);
                //tempExp = randExp(mt);    // for non-dense <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< for non-dense
                if(!hash[tempExp]) {    // hash[tempExp] != 0
                    hash[tempExp] = tempCoef;
                    expList.push_back(tempExp);
                }else {                 // the exp has been declare, should creat another tempExp
                    n_times--; 
                }
            }
            sort(expList.begin(), expList.end(), [](int a, int b) {return a < b;}); // sort, reference websit (8.)
            for(auto &index : expList) {
                coefList.push_back(hash[index]);
            }
            memset(hash, 0, HASHLIMIT);  // memset, reference (7.)

            m_poly = Polymul(term, &coefList, &expList, nullptr);
            if(!(i % 2)) {        // if ((i % 2) == 0) => m_poly, and output the result. else => n_poly

                start_time = clock();

                Polymul ans = n_poly * m_poly;  // multiplication

                end_time = clock();

                total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
                //output << "ans => \n";
                //ans.polymulPrint(&output);                    // write the result to the file

                //stream << "\n" << N << " * " << term  << "\n" << "\nstart time tick = " << start_time << "\nend time clock = " << end_time << "\ntotal time = " << total_time << " second\n\n";
                stream << N << " * " << term << ", " << total_time << "\n";
                string outputMessage = stream.str();
                //cout << N << " * " << term << ", " << total_time << "\n";
                output << outputMessage;
            }else {
                n_poly = m_poly;
                N = term;
            }
        }
        string message = "\n###############################\n\n";    // use to separate if ii++
        
        output << message;
        cout << message;
    }
    output << "\n-----------wirte output finish----------\n";
    output.close();
    /*----------------for HW_word (end):------------------------------------------------------------------------------------*/


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
