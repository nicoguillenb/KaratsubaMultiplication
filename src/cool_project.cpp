// my project

#include <iostream>
#include <string>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "strlib.h"
#include "math.h"
using namespace std;

string multiply(string xx, string yy);
long long toLong(string x);
int charToNum (char x);
string stringAdd (string x, string y);
string stringResta (string x, string y);
string zero(int x);

int main() {
    cout << "Hello, world!" << endl;
    string x = "3141592653589793238462643383279502884197169399375105820974944592";
    string y = "2718281828459045235360287471352662497757247093699959574966967627";

    string result = multiply(x,y);
    cout << result << endl;
    return 0;
}

string multiply(string xx, string yy){
    cout << "recursion" << endl;
    int n = xx.length();
    if (n <= 1){
        int x = stringToInteger(xx);
        int y = stringToInteger(yy);
        string result = integerToString(x*y);
        cout << result << endl;
        return result;
    } else {
        string a = xx.substr(0,xx.length()/2);
        string b = xx.substr(xx.length()/2);
        string c = yy.substr(0,yy.length()/2);
        string d = yy.substr(yy.length()/2);
        string p = stringAdd(a,b);
        string q = stringAdd(c,d);
        string ac = multiply(a, c);
        string bd = multiply(b, d);
        string pq = multiply(p, q);
        string abdc = stringResta(pq,stringAdd(ac,bd));
        string acZero = zero(n);
        string abdcZero = zero(n/2);

        ac = ac +  acZero;

        abdc = abdc + abdcZero;

        return stringAdd(ac,stringAdd(abdc,bd));
    }
}

//long long toLong(string x){
//    long long ten = 1;
//    long long result = 0;
//    long long current = 0;
//    for (int i = x.length()-1; i >= 0; i-- ){
//        if (x[i] == '0'){
//            current = 0;
//        } else if (x[i] == '1'){
//            current = 1;
//        }else if (x[i] == '2'){
//            current = 2;
//        }else if (x[i] == '3'){
//            current = 3;
//        }else if (x[i] == '4'){
//            current = 4;
//        }else if (x[i] == '5'){
//            current = 5;
//        }else if (x[i] == '6'){
//            current = 6;
//        }else if (x[i] == '7'){
//            current = 7;
//        }else if (x[i] == '8'){
//            current = 8;
//        }else if (x[i] == '9'){
//            current = 9;
//        }
//        result += current*ten;
//        ten *= 10;
//    }
//    return result;
//}

string stringAdd (string x, string y){
    bool negative = false;
    if (x[0] == '-' && y[0] != '-'){
        return stringResta(y,x.substr(1));
    } else if (y[0] == '-' && x[0] != '-'){
        return stringResta(x,y.substr(1));
    } else if (x[0] == '-' && y[0] == '-'){
        negative = true;
        x = x.substr(1);
        y = y.substr(1);
    }
    int xL = x.length()-1;
    int yL = y.length()-1;
    string sobra = "0";
    string result = "";
    while (true){
        int current = charToNum(x[xL]) + charToNum(y[yL]) + stringToInteger(sobra);
        string currentString = integerToString(current);
        result = currentString.substr(currentString.length()-1) + result;
            if (currentString.length() > 1) {
                sobra = "" + currentString.substr(0,currentString.length()-1);
            }   else{
                sobra = "0";
            }
        xL--;
        yL--;
        if (xL < 0 || yL < 0) break;
    }
    if (sobra != "0") result = sobra + result;
    if (negative) result = "-" + result;
    return result;
}

string stringResta (string x, string y){

    if (x[0] == '-' && y[0] != '-'){
        return stringAdd(x, "-" + y);
    } else if (y[0] == '-' && x[0] != '-'){
        return stringAdd(x,y.substr(1));
    } else if (x[0] == '-' && y[0] == '-'){
        return stringResta(y.substr(1),x.substr(1));
    }

    int xL = x.length()-1;
    int yL = y.length()-1;

    string result = "";
    int sobra = 0;
    bool resta = false;
    while (true){
        if (resta) {
            sobra = -1;
        } else {
            sobra = 0;
        }
        int current = charToNum(x[xL]) - charToNum(y[yL]) + sobra;
        if (current < 0){
            resta = true;
        } else {
            resta = false;
        }
        string currentString = integerToString(current);
        result = currentString + result;
        xL--;
        yL--;
        if (xL < 0 || yL < 0) break;
    }
    if (resta){
        result = "-" + result;
    }
    return result;
}

int charToNum (char x){
    int current = 0;
    if (x == '0'){
        current = 0;
    } else if (x == '1'){
        current = 1;
    }else if (x == '2'){
        current = 2;
    }else if (x == '3'){
        current = 3;
    }else if (x == '4'){
        current = 4;
    }else if (x == '5'){
        current = 5;
    }else if (x == '6'){
        current = 6;
    }else if (x == '7'){
        current = 7;
    }else if (x == '8'){
        current = 8;
    }else if (x == '9'){
        current = 9;
    }
    return current;
}

string zero(int x){
    string result = "";
    while (x > 0){
        result += "0";
        x--;
    }
    return result;
}
