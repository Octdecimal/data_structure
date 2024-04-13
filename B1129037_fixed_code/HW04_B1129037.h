#include <vector>
#include <fstream>
#ifndef POLYMUL_H
#define POLYMUL_H

class Polymul{
private:

    class Poly{
    private:
        int coef;
	    int exp;
        Poly *link;
    public:
        Poly(int inCoef = 0, int inExp = 0, Poly *Next = nullptr);

        int getCoef() const;

        int getExp() const;

        Poly* getLink() const;

        void setCoef(int c);

        void setLink(Poly *p);
    };

    Poly *first;
public:
    Polymul(int in_term = 0, std::vector<int> *c = nullptr, std::vector<int> *e = nullptr, Poly *Now = nullptr);

    Polymul operator*(const Polymul &p) const;

    void polymulPrint(std::fstream *FILE = nullptr) const;
};

#endif

/*
reference websit:
1. about header file: https://learn.microsoft.com/en-us/cpp/cpp/header-files-cpp?view=msvc-170
2. how to separate header files and implementation files:  https://jasonblog.github.io/note/c++/shi_fou_neng_rang_c_++_template_de_biao_tou_dang_z.html

another reference:
1. this reference provide some pseudocode:  Ellis Horowitz, Sartaj Sahni, Dinesh Mehta. (2006).Fundamentals of Data Structures in C++, 2/e. Silicon Press. p.179 ~ p.190
*/