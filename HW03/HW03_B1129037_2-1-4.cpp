#include <iostream>

struct Complex {
public:
   Complex() : real(0.0), imagi(0.0) {}                          // set default state without any value
   Complex(double r, double i ) : real(r), imagi(i) {}           // set default state with value
                                                                  // explicit opertator, C:/git/Object-Oriented/Lab3.12/account.h
   Complex operator+(Complex &other ) {                           // overload operator + ==> (a + bi) + (c + di) = (a + b) + (c + d)i
      return Complex( real + other.real, imagi + other.imagi ); 
    }

   Complex operator*(Complex &other ) {                           // overload operator * ==> (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
      return Complex( real * other.real - imagi * other.imagi, real * other.imagi + imagi * other.real);     //    i^2 = -1
    }

   friend std::ostream& operator<<(std::ostream& out, const Complex& c){  // because real and imagi is private, so have to use friend to access
	   out << c.real << " + " << c.imagi << "i";
	   return out;
    }

   friend std::istream& operator>>(std::istream& in, Complex& c){         // same reason as operator <<
	   in >> c.real;
	   in >> c.imagi;
	   return in;
	}
private:
   double real, imagi;
};

int main() {
	Complex a, b;
   while(std::cin >> a >> b){
	   std::cout << "Sum: "<< a + b << "\nProduct: " << a * b <<"\n";
   }
   return 0;
}