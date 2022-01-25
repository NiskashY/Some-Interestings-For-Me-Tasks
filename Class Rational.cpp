#include <iostream>
#include <sstream>
using namespace std;
//реализовать для класса Rational возможность == + - >> << 

class Rational {
public:

    Rational(int numerator = 0, int denominator = 1) {
        // Реализуйте конструктор
        if (numerator < 0) {
            symbol *= -1;
            numerator *= -1;
        }
        if (denominator < 0) {
            symbol *= -1;
            denominator *= -1;
        }
        num = numerator; den = denominator;

        while (numerator > 0 && denominator > 0) {

            if (numerator > denominator) {
                numerator %= denominator;
            } else {
                denominator %= numerator;
            }
        }

        int nod = numerator + denominator;
        num /= nod;
        den /= nod;
        SetSymbol();
    }
    int Numerator() const {
        // Реализуйте этот метод
        return num;
    }

    int Denominator() const {
        // Реализуйте этот метод
        return den;
    }

private:
    // Добавьте поля
    void SetSymbol() {
        num *= symbol;
    }
    int num;
    int den;
    int symbol = 1;
};

bool operator ==(const Rational& lhs, const Rational& rhs) {
    return (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator());
}

int FindNok(int x, int y) {
    int count = (x > y) ? x : y;

    for (int i = count;; i++) {
        if (!(i % x) && !(i % y)) {
            return i;
        }
    }
}

Rational SomeOperationWithValues(const Rational& lhs, const Rational& rhs, char operation) {
    int numerator_tmp, denominator_tmp;

    if (operation == '+') {
        denominator_tmp = FindNok(lhs.Denominator(), rhs.Denominator());
        numerator_tmp = lhs.Numerator() * (denominator_tmp / lhs.Denominator())
                + rhs.Numerator() * (denominator_tmp / rhs.Denominator());
        return {numerator_tmp, denominator_tmp};
    } else if (operation == '-'){
        denominator_tmp = FindNok(lhs.Denominator(), rhs.Denominator());
        numerator_tmp = lhs.Numerator() * (denominator_tmp / lhs.Denominator())
                        - rhs.Numerator() * (denominator_tmp / rhs.Denominator());
        return {numerator_tmp, denominator_tmp};
    }
    else if (operation == '*'){
        return {lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator()};
    }
    else {
        return {lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator()};
    }
}

Rational operator +(const Rational& lhs, const Rational& rhs){
    return Rational(SomeOperationWithValues(lhs, rhs, '+'));
}

Rational operator -(const Rational& lhs, const Rational& rhs){
    return Rational(SomeOperationWithValues(lhs, rhs, '-'));
}

Rational operator *(const Rational& lhs, const Rational& rhs){
    return Rational(SomeOperationWithValues(lhs, rhs, '*'));
}

Rational operator /(const Rational& lhs, const Rational& rhs){
    return Rational(SomeOperationWithValues(lhs, rhs, '/'));
}

istream& operator >>(istream& stream, Rational& rational) {
    int num_tmp, den_tmp;
    char symbol_operation;

/*    stream >> num_tmp;
    stream.ignore(1);
    stream >> den_tmp;*/

    if ((stream >> num_tmp) && ((stream >> symbol_operation) && symbol_operation == '/') && (stream >> den_tmp) ) {
        rational = {num_tmp, den_tmp};
    }

    return stream;
}

ostream& operator <<(ostream& stream, const Rational& rational) {
    stream << rational.Numerator() << '/' << rational.Denominator();
    return stream;
}

int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                 << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    cout << "OK" << endl;
    return 0;
}
