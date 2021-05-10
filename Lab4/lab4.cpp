#include <iostream>
#include <iomanip>

using namespace std;

int multiply(int a, int b) {
    int ret = 0;
    bool b_is_neg = b < 0;

    if (a == 0 || b == 0) {
        return 0;
    }

    if (b_is_neg) {
        b = ~b + 1;
    }

    while (b != 0) {
        if (b & 1 == 1) {
            ret += a;
        }
        a <<= 1;
        b >>= 1;
    }

    if (b_is_neg) {
        ret = ~ret + 1;
    }
    return ret;
}

int main() {

    // Test
    int a_test[] = { 2, 2, 0, -2,  0, -2,  2, 2, 1, -2,  1 };
    int b_test[] = { 2, 0, 2,  0, -2,  2, -2, 1, 2,  1, -2 };
    try {
        for (unsigned long int i = 0; i < sizeof(a_test) / sizeof(a_test[0]); i++) {
            int a = a_test[i];
            int b = b_test[i];
            int ret = multiply(a, b);
            // https://stackoverflow.com/questions/667183/padding-stl-strings-in-c
            cout << setw(2) << a << " * " << setw(2) << b << " = " << setw(2) << ret << endl;
            if (ret != a * b) {
                throw exception();
            }
        }
    }
    catch (exception e) {
        cout << "Error" << endl;
    }
    return 0;
}