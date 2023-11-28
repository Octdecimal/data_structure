#include "HW04_B1129037.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>

using namespace std;

Polymul::Poly::Poly(int inCoef, int inExp, Poly *Next) {
    coef = inCoef;
    exp = inExp;
    link = Next;
}
/* initialize, if no input, (coef, exp, link) should be (0, 0, nullptr).
the follwing code is another style:
(explicit) Polymul::Poly::Poly(int inCoef, int inExp, Poly* Next) : coef(inCoef), exp(inExp), link(Next) {}
*/
int Polymul::Poly::getCoef() const {
    return coef;
}

int Polymul::Poly::getExp() const {
    return exp;
}

Polymul::Poly* Polymul::Poly::getLink() const {
    return link;
}

const long int HASHLIMIT = 10000000L;

Polymul::Polymul(int in_term, vector<int> *c, vector<int> *e, Poly *Now) {  // the in put should be sorted
    if(Now == nullptr) {
        first = nullptr;
    }else {
        first = new Poly(Now->getCoef(), Now->getExp(), Now->getLink());
    }

    for(int i = 0; i < in_term; i++){
        first = new Poly(c->at(i), e->at(i), first);
    }  // at() will automatically check whether n is within the bounds of valid elements in the vector, throwing an out_of_range exception if it is not, more information in reference website (a.)
}

Polymul Polymul::multipli(Polymul &p) {
    long int max = (first->getExp() + p.first->getExp()) + 1;
    pair<int, int>* exp_hash = new pair<int, int>[HASHLIMIT]();                     // hash table, the exp would be the index, and the coef would be the value, more information in reference website (2.)
    vector<int> expList;
    vector<int> coefList;
    int nowExp = 0;
    int nowCoef = 0;

    Poly* now = new Poly(first->getCoef(), first->getExp(), first->getLink());
    while (now != nullptr) {
        Poly* p_now = new Poly(p.first->getCoef(), p.first->getExp(), p.first->getLink());
        while (p_now != nullptr) {
            nowExp = now->getExp() + p_now->getExp();
            nowCoef = now->getCoef() * p_now->getCoef();
            if (!exp_hash[nowExp].second){
                expList.push_back(nowExp);
            }
            exp_hash[nowExp].first += nowCoef;
            exp_hash[nowExp].second++;
            p_now = p_now->getLink();
        }
        delete p_now;
        now = now->getLink();
    }
    delete now;

    sort(expList.begin(), expList.end());
    for (auto& index : expList) {
        coefList.push_back(exp_hash[index].first);
    }

    Polymul result(expList.size(), &coefList, &expList, nullptr);

    delete[] exp_hash;
    return result;
}

Polymul Polymul::operator*(const Polymul &p) const{
    long int max = (first->getExp() + p.first->getExp()) + 1;
    pair<int, int>* exp_hash = new pair<int, int>[HASHLIMIT]();                     // hash table, the exp would be the index, and the coef would be the value, more information in reference website (2.)
    vector<int> expList;
    vector<int> coefList;
    int nowExp = 0;
    int nowCoef = 0;

    Poly* now = new Poly(first->getCoef(), first->getExp(), first->getLink());
    while (now != nullptr) {
        Poly* p_now = new Poly(p.first->getCoef(), p.first->getExp(), p.first->getLink());
        while (p_now != nullptr) {
            nowExp = now->getExp() + p_now->getExp();
            nowCoef = now->getCoef() * p_now->getCoef();
            if (!exp_hash[nowExp].second) {
                expList.push_back(nowExp);
            }
            exp_hash[nowExp].first += nowCoef;
            exp_hash[nowExp].second++;
            p_now = p_now->getLink();
        }
        delete p_now;
        now = now->getLink();
    }
    delete now;

    sort(expList.begin(), expList.end());
    for (auto& index : expList) {
        coefList.push_back(exp_hash[index].first);
    }

    Polymul result(expList.size(), &coefList, &expList, nullptr);

    delete[] exp_hash;
    return result;
}

void Polymul::polymulPrint(fstream *FILE) const {
    Poly *cur = new Poly(first->getCoef(), first->getExp(), first->getLink());

    if (FILE != nullptr) {
        stringstream stream;
        while (cur != nullptr) {
            stream << " " << cur->getCoef() << "x^" << cur->getExp();
            string str = stream.str();
            *FILE << str;
            cur = cur->getLink();
            if (cur && cur->getCoef()) {  // ensures that doesn't access coef on a null pointer.
                str = " +";
                *FILE << str;
            }
            stream.str("");
            stream.clear();
        }
    }
    else {
        while(cur != nullptr) {
                cout << " " << cur->getCoef() << "x^" << cur->getExp();
            cur = cur->getLink();
            if(cur != nullptr) {  // ensures that doesn't access coef on a null pointer.
                cout << " +";
            }
        }
    }
    delete cur;
}


/*
reference websit:
1. about header file: https://learn.microsoft.com/en-us/cpp/cpp/header-files-cpp?view=msvc-170
2. how to separate header files and implementation files:  https://jasonblog.github.io/note/c++/shi_fou_neng_rang_c_++_template_de_biao_tou_dang_z.html
3. about hash table: https://domino.ai/data-science-dictionary/hash-table
a. abput at() in vector: https://cplusplus.com/reference/vector/vector/at/

another reference:
1. this reference provide some pseudocode:  Ellis Horowitz, Sartaj Sahni, Dinesh Mehta. (2006).Fundamentals of Data Structures in C++, 2/e. Silicon Press. p.179 ~ p.190
*/
