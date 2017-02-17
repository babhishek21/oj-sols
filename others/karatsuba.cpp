/**
 * Implementation of Karatsuba Multiplication using C++/STL
 */

#include<bits/stdc++.h>
#include<string>

using namespace std;

int equalizeLength (string &num1, string &num2) { // Equalizes length
    int n1 = num1.length(), n2 = num2.length();

    if(n1 == n2) return n1;

    if(n1>n2) {
        num2 = string(n1-n2, '0') + num2;
        return n1;
    } else {
        num1 = string(n2-n1, '0') + num1;
        return n2;
    }
}

string multiplySingleDigit (string a, string b) {
    char buf[3];
    int mult = atoi(a.c_str()) * atoi(b.c_str());
    sprintf(buf, "%d", mult);
    string multstr = string(buf);
    return multstr;
}

string addStringDigits (string a, string b) {
    string c; // c = a+b

    int n = equalizeLength(a, b);

    char carry = 0;
    for(int i=n-1; i > -1; i--) {
        char temp = (a[i] - '0') + (b[i] - '0') + carry;
        if(temp > 9) {
            carry = 1;
            temp -= 10;
        } else carry = 0;
        temp += '0';
        c = string(1, temp) + c;
    }

    carry += '0';
    c = string(1, carry) + c; // add final carry

    c.erase(0, c.find_first_not_of("0")); // remove prefix zeros, if any
    return c;
}

string subtractStringDigits (string a, string b) { //assume a>b
    string c; // c = a-b

    int n = equalizeLength(a, b);

    for(int i=n-1; i > -1; i--) {
        char x = a[i] - '0', y = b[i] - '0';
        if(x < y) {
            x += 10;
            a[i-1]--;
        }
        char temp = x - y;
        temp += '0';
        c = string(1, temp) + c;
    }

    c.erase(0, c.find_first_not_of("0")); // remove prefix zeros, if any
    return c;
}

string multiply(string x, string y) {
    int n = equalizeLength(x, y);

    if (n==0) return string(1,'0');                          // Base
    if (n==1) return multiplySingleDigit(x, y);    // case

    /* If x = a[n/2] + b[n/2]
     * and y = c[n/2] + d[n/2]
     * then compute ac, bd, and (a+b)(c+d)
     */

     string a = x.substr(0, (n - n/2)), b = x.substr((n - n/2), n/2); // n/2 is floor
     string c = y.substr(0, (n - n/2)), d = y.substr((n - n/2), n/2);

     string comp1 = multiply(a, c); // ac
     string comp2 = multiply(b, d); // bd
     string comp3 = multiply(addStringDigits(a, b), addStringDigits(c, d)); // (a+b).(c+d)

     string comp1_r = comp1 + string(2*(n - n/2), '0'); // 10^n.ac
     string ret1 = addStringDigits(comp1_r, comp2); // 10^n.ac + bd
     string ret2 = subtractStringDigits(comp3, addStringDigits(comp1, comp2)).append(n/2, '0'); // 10^(n/2).(ad + bc)
     string ret = addStringDigits(ret1, ret2);

     return ret;
}

int main() {
    string num1, num2, mult, sub;

    cout << "Karatsuba multiplication\nEnter two numbers: " << endl;
    cin >> num1 >> num2;

    mult = multiply(num1, num2);

    cout << num1 << " multiplied by " << num2 << " is " << mult << endl;

    return 0;
}
